import subprocess
import os
import random

root = os.environ["USMT_ROOT"]
yosis_prefix = root + '/tool/third_party/oss-cad-suite/bin/'
ltlsynt_prefix = root + '/tool/third_party/spot/bin/'
verilator_tb_prefix = root + '/tool/syntetic_gen/verilator_tests/'
xml_prefix = root +'/tool/syntetic_gen/specs/'
out_folder = root + '/tool/syntetic_gen/outs/'

def expand_spec(specification, lenght, assnumb):
    formula = specification['formula'] 
    #base name for the proposition is a_propertyIndex
    ant_base = specification['inputs'] + "_" + str(assnumb)
    con_base = specification['outputs'] + "_" + str(assnumb)
    #first propositions in the sequences are a_propertyIndex_0 and c_propertyIndex_0
    # + { is needed beacause we are using SERE syntax 
    ant_seq = "{" + ant_base + "_0"
    con_seq = "{" + con_base + "_0"
    #initialize the inputs and outputs with the base propositions
    ins = ant_base + "_0"
    outs = con_base + "_0"

    if '..&&..' in formula:
        #expand the antecedent
        for i in range(1, lenght[0]):
            ins = ins + ',' + ant_base + "_" + str(i)
            ant_seq = ant_seq + " & " + ant_base + "_" + str(i)
        #expand the consequent
        for i in range(1, lenght[1]):
            outs = outs + ',' + con_base + "_" + str(i)
            con_seq = con_seq + " & " + con_base + "_" + str(i)
        #close the sequence with } for SERE syntax
        ant_seq = ant_seq + "}"
        con_seq = con_seq + "}" 
        # Replace only the first instance of '..&&..'
        formula = formula.replace('..&&..', ant_seq,1)
        # Replace the second instance of '..&&..'
        formula = formula.replace('..&&..', con_seq)
        
    if '..##1..' in formula:
        #expand the antecedent
        for i in range(1, lenght[0]):
            ins = ins + ',' + ant_base + "_" + str(i)
            ant_seq = ant_seq + " ##1 " + ant_base + "_" + str(i)
        #expand the consequent
        for i in range(1, lenght[1]):
            outs = outs + ',' + con_base + "_" + str(i)
            con_seq = con_seq + " & " + con_base + "_" + str(i)

        #close the sequence with } for SERE syntax
        ant_seq = ant_seq + "}"
        con_seq = con_seq + "}" 
        # Replace '..##1..' in the antecedent
        formula = formula.replace('..##1..', ant_seq,1)
        # Replace '..##1..' in the consequent
        formula = formula.replace('..##1..',con_seq)
    #return the expanded formula
    ret_spec = {}
    ret_spec['formula'] = formula
    ret_spec['inputs'] = ins
    ret_spec['outputs'] = outs
    print(f"Expanded formula: {ret_spec['formula']}")
    return ret_spec

def aigerToSv(design_aiger):
    input_file = design_aiger
    output_file = design_aiger.replace('.aiger', '.v')
    module_name = 'test'
    clk_name = 'clock'
    yosys_command = f"yosys -p 'read_aiger  -module_name {module_name} -clk_name {clk_name} {out_folder}{input_file}; write_verilog {out_folder}{output_file}'"
    subprocess.run(yosys_command, shell=True, check=False)
    print(f"Generated SystemVerilog file: {output_file} in {out_folder}")

def synthesize_controller(specification):
    formula = specification.get('formula')
    inputs = specification.get('inputs')
    outputs = specification.get('outputs')
    aiger_file = 'test.aiger'
    
    ltlsynt_command = f'ltlsynt --formula="{formula}" --ins="{inputs}" --outs="{outputs}" --aiger > {out_folder}{aiger_file}'

    result = subprocess.run(ltlsynt_command, shell=True, check=False, capture_output=True, text=True)
    if result.returncode == 1:
        print("Error: The design is unrealizable.")
        exit(1)
    elif result.returncode == 2:
        print("Error: An error occurred during the realizability check.")
        exit(2)
    else:
        print("Controller synthesized successfully.")
        #Remove REALIZABLE/UNREALIZABLE output line from aiger file
        with open(out_folder + aiger_file, 'r') as file:
            lines = file.readlines()
        with open(out_folder + aiger_file, 'w') as file:
            file.writelines(lines[1:])
        return aiger_file

def generate_circuit(specification):
    design_aiger = synthesize_controller(specification)
    aigerToSv(design_aiger)

def generate_testbench(specification):
    inputs = specification.get('inputs', '').split(',')
    testbench_code = ""
    #create instructions to insert in tb
    for signal in inputs:
        testbench_code += f"dut->{signal} = rand() % 2;\n\t\t"
    
    print(f"Generated testbench file:\n {testbench_code}")
    
    #retrieve the template for the testbench
    with open(verilator_tb_prefix + 'tb_test_template.txt', 'r') as template_file:
        template_content = template_file.read()

    #substite the placeholder with the generated code
    testbench_content = template_content.replace("PLACEHOLDER", testbench_code)

    #write the testbench to a .cpp file
    with open(verilator_tb_prefix + 'tb_test.cpp', 'w') as testbench_file:
        testbench_file.write(testbench_content)

    print(f"Generated testbench file: {verilator_tb_prefix}tb_test.cpp")

def run_verilator():
    #move test.v file to verilator folder 
    subprocess.run(f"cp {out_folder}test.v {verilator_tb_prefix}", shell=True, check=False)
    #run verilator
    subprocess.run(f"cd {verilator_tb_prefix} && make sim", shell=True, check=False)
    subprocess.run(f"cp {verilator_tb_prefix}trace.vcd {out_folder}", shell=True, check=False)
    #clean up 
    subprocess.run(f"rm -rf {verilator_tb_prefix}trace.vcd {verilator_tb_prefix}test.v {verilator_tb_prefix}tb_test.cpp", shell=True, check=False)
    subprocess.run(f"rm -rf {verilator_tb_prefix}obj_dir", shell=True, check=False)

def populate_input_dir():
    input_prefix = root + '/input/syntetic'
    subprocess.run(f"mv {out_folder}test.v {input_prefix}/design/", shell=True, check=False)
    subprocess.run(f"mv {out_folder}specifications.txt {input_prefix}/expected/", shell=True, check=False)
    subprocess.run(f"mv {out_folder}trace.vcd {input_prefix}/traces/", shell=True, check=False)
    subprocess.run(f"rm -rf {out_folder}/*", shell=True, check=False)

def main():
    import xml.etree.ElementTree as ET
    xml_file = f'{xml_prefix}output_templates.xml'
    tree = ET.parse(xml_file)
    root = tree.getroot()
    templates = root.findall('Template')
    num_templates = len(templates)

    try:
        template_number = int(input(f"Enter how many specification to use (1-{num_templates}): "))
        if not 1 <= template_number <= num_templates:
            print(f"Error: Template number must be between 1 and {num_templates}.")
            exit(3)
    except ValueError:
        print("Error: Invalid input. Please enter a number between 1 and {num_templates}.")
        exit(3)

    
    ant_props = int(input(f"Insert the lenghts of the antecedent sequence: "))
    con_props = int(input(f"Insert the lenghts of the consequent sequence: "))
    numprops = (ant_props,con_props)
    assnumbs = int(input(f"Insert the number of parallel properties to be used in the design: "))


    merged_specification = {}
    #randomly select template_number templates
    random_templates = random.sample(templates, template_number)
    #iterate over the selected templates to expand them and merge them
    for i, template in enumerate(random_templates, start=1):
        specification = {}
        specification['formula'] = template.find('TemplateText').text
        specification['inputs'] = template.find('Input').text
        specification['outputs'] = template.find('Output').text
        
        #TODO: this works only for multiple instances of the same template, if we get multiple templates we need to share assnumbs between them
        for j, num in enumerate(range(1, assnumbs + 1), start=1):
            #expand special templates
            if(specification['formula'].find('..##1..') or specification['formula'].find('..&&..')):
                print(f"Expanding template")  
                expanded_formula = expand_spec(specification,numprops,j)

            # update merged_specification structure
            if(merged_specification.get('formula') == None):
                merged_specification = expanded_formula
            else:  
                merged_specification['formula'] = expanded_formula['formula'] + ' & ' + merged_specification.get('formula', '')
                merged_specification['inputs'] = ','.join(set(merged_specification.get('inputs', '').split(',') + expanded_formula['inputs'].split(',')))
                merged_specification['outputs'] = ','.join(set(merged_specification.get('outputs', '').split(',') + expanded_formula['outputs'].split(',')))
    
            # Write expanded formulas to a file
            with open(out_folder + 'specifications.txt', 'a') as file:
                file.write(f"Expanded formula {j} for template {i}:\n")
                file.write(f"{expanded_formula['formula']}\n\n")


    # Write merged specification to a file
    with open(out_folder + 'specifications.txt', 'a') as file:
        file.write("Merged specification:\n")
        file.write(f"Formula: {merged_specification['formula']}\n")
        file.write(f"Inputs: {merged_specification['inputs']}\n")
        file.write(f"Outputs: {merged_specification['outputs']}\n")
    
    print("Merged specification:\n")
    print(merged_specification)
    print("Generating circuit for merged specification")
    generate_circuit(merged_specification)
    generate_testbench(merged_specification)
    run_verilator()
    populate_input_dir()

if __name__ == "__main__":
    main()