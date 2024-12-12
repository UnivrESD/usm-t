import subprocess
import os
import random

root = os.environ["USMT_ROOT"]
yosis_prefix = '$(pwd)/../third_party/oss-cad-suite/bin/'
ltlsynt_prefix = '$(pwd)/../third_party/spot/bin/'
xml_prefix = root +'/tool/syntetic_gen/specs/'

def expand_spec(specification, lenght):
    formula = specification['formula']
    ant_base = specification['inputs']
    con_base = specification['outputs']
    ant_seq = ant_base + "_0"
    con_seq = con_base + "_0"
    ins = ant_base + "_0"
    outs = con_base + "_0"

    if '..&&..' in formula:
        for i in range(1, lenght):
            ins = ins + ',' + ant_base + "_" + str(i)
            outs = outs + ',' + con_base + "_" + str(i)
            ant_seq = ant_seq + " & " + ant_base + "_" + str(i)
            con_seq = con_seq + " & " + con_base + "_" + str(i)
        # Replace only the first instance of '..&&..'
        formula = formula.replace('..&&..', ant_seq,1)
        formula = formula.replace('..&&..', con_seq)
        
    if '..##1..' in formula:
        for i in range(1, lenght):
            ins = ins + ',' + ant_base + "_" + str(i)
            outs = outs + ',' + con_base + "_" + str(i)
            ant_seq = ant_seq + "& X " + ant_base + "_" + str(i)
            con_seq = con_seq + "& X " + con_base + "_" + str(i)
        # Replace '..##1..' 
        formula = formula.replace('..##1..', ant_seq,1)
        formula = formula.replace('..##1..',con_seq)

    specification['formula'] = formula
    specification['inputs'] = ins
    specification['outputs'] = outs
    print(f"Expanded formula: {specification['formula']}")

def aigerToSv(design_aiger):
    input_file = design_aiger
    output_file = design_aiger.replace('.aiger', '.sv')
    module_name = 'test'
    clk_name = 'clock'
    yosys_command = f"yosys -p 'read_aiger  -module_name {module_name} -clk_name {clk_name} {input_file}; write_verilog -sv {output_file}'"
    subprocess.run(yosys_command, shell=True, check=False)
    print(f"Generated SystemVerilog file: {output_file}")

def synthesize_controller(specification):
    formula = specification.get('formula')
    inputs = specification.get('inputs')
    outputs = specification.get('outputs')
    aiger_file = 'test.aiger'
    
    ltlsynt_command = f'ltlsynt --formula="{formula}" --ins="{inputs}" --outs="{outputs}" --aiger > {aiger_file}'

    result = subprocess.run(ltlsynt_command, shell=True, check=False, capture_output=True, text=True)
    if result.returncode == 1:
        print("Error: The design is unrealizable.")
        exit(1)
    elif result.returncode == 2:
        print("Error: An error occurred during the realizability check.")
        exit(2)
    else:
        #Remove REALIZABLE/UNREALIZABLE output line from aiger file
        with open(aiger_file, 'r') as file:
            lines = file.readlines()
        with open(aiger_file, 'w') as file:
            file.writelines(lines[1:])
        return aiger_file


def generate_circuit(specification):
    design_aiger = synthesize_controller(specification)
    aigerToSv(design_aiger)

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

    numprops = int(input(f"Insert the lenghts of the properties sequence: "))

    merged_specification = {}
    #randomly select template_number templates
    random_templates = random.sample(templates, template_number)
    for i, template in enumerate(random_templates, start=1):
        specification = {}
        specification['formula'] = template.find('TemplateText').text
        specification['inputs'] = template.find('Input').text
        specification['outputs'] = template.find('Output').text
        
        #expand special templates
        if(specification['formula'].find('..##1..') or specification['formula'].find('..&&..')):
            print(f"Expanding template")  
            expand_spec(specification,numprops)
        
        # update merged_specification structure
        if(merged_specification.get('formula') == None):
            merged_specification = specification
        else:  
            merged_specification['formula'] = specification['formula'] + ' & ' + merged_specification.get('formula', '')
            merged_specification['inputs'] = ','.join(set(merged_specification.get('inputs', '').split(',') + specification['inputs'].split(',')))
            merged_specification['outputs'] = ','.join(set(merged_specification.get('outputs', '').split(',') + specification['outputs'].split(',')))
    print(merged_specification)
    
    print("Generating circuit for merged specification")
    generate_circuit(merged_specification)

if __name__ == "__main__":
    main()