import subprocess
import os
import random
import copy 
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

def aigerToSv(design_aiger, specification):
    input_file = design_aiger
    output_file = design_aiger.replace('.aiger', '.v')
    module_name = design_aiger.replace('.aiger', '')
    clk_name = 'clock'
    yosys_command = f"yosys -p 'read_aiger  -module_name {module_name} -clk_name {clk_name} {out_folder}{input_file}; write_verilog {out_folder}{output_file}'"
    subprocess.run(yosys_command, shell=True, check=False)

    #yosys for some reason mixes inputs and outputs in the module signal list so we need to fix it
    inputs = specification.get('inputs')
    outputs = specification.get('outputs')
    with open(out_folder + output_file, 'r') as file:   
        lines = file.readlines()
        # Find the module declaration line
        for i, line in enumerate(lines):
            if line.startswith('module '):
                module_decl = line.strip()
                break

        # Split the module declaration line into parts
        parts = module_decl.split('(')
        module_name = parts[0]
        signals = parts[1].rstrip(');').split(',')

        # Separate the clock, inputs, and outputs
        new_signals = ['clock'] + inputs.split(',') + outputs.split(',')

        # Create the new module declaration line
        new_module_decl = module_name + '(' + ', '.join(new_signals) + ');'

        # Replace the old module declaration line with the new one
        lines[i] = new_module_decl + '\n'

        # Write the modified lines back to the file
        with open(out_folder + output_file, 'w') as file:
            file.writelines(lines)

    print(f"Generated SystemVerilog file: {output_file} in {out_folder}")

def synthesize_controller(specification, aiger_file='test.aiger'):
    formula = specification.get('formula')
    inputs = specification.get('inputs')
    outputs = specification.get('outputs')
    
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

def generate_top_module(spec_list):
    #prefix of the top module 
    top_module = 'module test(\n'
    top_module += 'clock,' 
    #all submodule inputs
    for spec in spec_list:
        top_module += spec['inputs'] + ','
    #all submodule outputs
    for spec in spec_list:
        if(spec_list.index(spec) != len(spec_list) - 1):
            top_module += spec['outputs'] + ','
        else:
            top_module += spec['outputs'] + ');\n'
    #start input declaration
    top_module +='input clock,'
    for spec in spec_list:
        if(spec_list.index(spec) != len(spec_list) - 1):
            top_module += spec['inputs'] + ','
        else:
            top_module += spec['inputs'] + ';\n'
    #start output declaration
    top_module +='output '
    for spec in spec_list:
        if(spec_list.index(spec) != len(spec_list) - 1):
            top_module += spec['outputs'] + ','
        else:
            top_module += spec['outputs'] + ';\n'

    # instantiate the submodules
    for spec in spec_list:
        top_module += 'spec' + str(spec_list.index(spec)) + ' spec_sbm' + str(spec_list.index(spec)) + '(' + "clock, " + spec['inputs'] + ',' + spec['outputs'] + ');\n'    

    top_module += 'endmodule\n'

    with open(out_folder + 'test.v', 'w') as file:
        file.write(top_module)
    print(f"Generated test module: {out_folder}test.v")

def generate_circuit(specification,spec_list, modules):
    if(modules):
        #We need to generate a module for each property
        for spec in spec_list:
            specfile_name = 'spec' + str(spec_list.index(spec))
            #for each specification generate a controller
            design_aiger = synthesize_controller(spec, specfile_name + '.aiger')
            #Generate a SystemVerilog file for each controller
            aigerToSv(design_aiger,spec)
        generate_top_module(spec_list)
    else:
        design_aiger = synthesize_controller(specification)
        aigerToSv(design_aiger,specification)

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
    #move all .v in outs folder to verilator folder 
    subprocess.run(f"cp {out_folder}*.v {verilator_tb_prefix}", shell=True, check=False)
    # Collect all files that are not test.v
    file_names = ""
    for file in os.listdir(out_folder):
        if file.endswith(".v") and file != "test.v":
            file_names += file + " "
    #run verilator
    subprocess.run(f"cd {verilator_tb_prefix} && make sim", shell=True, check=False)
    subprocess.run(f"cp {verilator_tb_prefix}trace.vcd {out_folder}", shell=True, check=False)
    #clean up 
    subprocess.run(f"rm -rf {verilator_tb_prefix}trace.vcd {verilator_tb_prefix}*.v {verilator_tb_prefix}tb_test.cpp", shell=True, check=False)
    subprocess.run(f"rm -rf {verilator_tb_prefix}obj_dir {verilator_tb_prefix}.stamp.verilate", shell=True, check=False)

def populate_input_dir():
    input_prefix = root + '/input/syntetic'
    subprocess.run(f"mv {out_folder}*.v {input_prefix}/design/", shell=True, check=False)
    subprocess.run(f"mv {out_folder}specifications.txt {input_prefix}/expected/", shell=True, check=False)
    subprocess.run(f"mv {out_folder}trace.vcd {input_prefix}/traces/", shell=True, check=False)
    subprocess.run(f"rm -rf {out_folder}/*", shell=True, check=False)
    with open(xml_prefix + 'temp.txt', 'r') as temp_file:
        temp_content = temp_file.read()
        print(temp_content)

def main():
    import xml.etree.ElementTree as ET
    xml_file = f'{xml_prefix}output_templates.xml'
    tree = ET.parse(xml_file)
    root = tree.getroot()
    templates = root.findall('Template')
    num_templates = len(templates)

    #input parameters
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

    #enable parallel module config
    modules_input = input("Enable parallel module configuration? (yes/no): ").strip().lower()
    if modules_input in ['yes', 'no']:
        modules = modules_input == 'yes'
    else:
        print("Invalid input. Please enter 'yes' or 'no'.")
        exit(4)


    merged_specification = {}
    #randomly select template_number templates
    random_templates = random.sample(templates, template_number)
    #iterate over the selected templates to expand them and merge them
    for i, template in enumerate(random_templates, start=1):
        specification = {}
        specification['formula'] = template.find('TemplateText').text
        specification['inputs'] = template.find('Input').text
        specification['outputs'] = template.find('Output').text
        
        spec_list = []
        #TODO: this works only for multiple instances of the same template, if we get multiple templates we need to share assnumbs between them
        for j, num in enumerate(range(1, assnumbs + 1), start=1):
            #expand special templates
            if(specification['formula'].find('..##1..') or specification['formula'].find('..&&..')):
                print(f"Expanding template")  
                expanded_formula = expand_spec(specification,numprops,j)
            else: 
                expanded_formula = specification
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

            #if module subdivision is enabled
            if(modules):
                #for each iteration add the expanded formula to the list
                spec_list.append(copy.deepcopy(expanded_formula))

    # Write merged specification to a file
    with open(out_folder + 'specifications.txt', 'a') as file:
        file.write("Merged specification:\n")
        file.write(f"Formula: {merged_specification['formula']}\n")
        file.write(f"Inputs: {merged_specification['inputs']}\n")
        file.write(f"Outputs: {merged_specification['outputs']}\n")
    
    print("Merged specification:\n")
    print(merged_specification)
    print("Generating circuit for merged specification")
    generate_circuit(merged_specification,spec_list, modules)
    generate_testbench(merged_specification)
    run_verilator()
    populate_input_dir()

if __name__ == "__main__":
    main()