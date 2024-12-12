import subprocess
import os
import random

root = os.environ["USMT_ROOT"]
yosis_prefix = '$(pwd)/../third_party/oss-cad-suite/bin/'
ltlsynt_prefix = '$(pwd)/../third_party/spot/bin/'
xml_prefix = root +'/tool/syntetic_gen/specs/'

def aigerToSv(design_aiger):
    input_file = design_aiger
    output_file = design_aiger.replace('.aiger', '.sv')
    yosys_command = f"yosys -p 'read_aiger {input_file}; write_verilog -sv {output_file}'"
    subprocess.run(yosys_command, shell=True, check=False)
    print(f"Generated SystemVerilog file: {output_file}")

def synthesize_controller(specification):
    formula = specification.get('formula')
    inputs = specification.get('inputs')
    outputs = specification.get('outputs')
    aiger_file = 'controller.aiger'
    
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

    random_templates = random.sample(templates, template_number)
    for i, template in enumerate(random_templates, start=1):
        specification = {}
        specification['formula'] = template.find('TemplateText').text
        specification['inputs'] = template.find('Input').text
        specification['outputs'] = template.find('Output').text
        print(f"Generating circuit for template {i}")

    merged_formula = ' & '.join([template.find('TemplateText').text for template in random_templates])
    merged_inputs = ','.join(set(input for template in random_templates for input in template.find('Input').text.split(',')))
    merged_outputs = ','.join(set(output for template in random_templates for output in template.find('Output').text.split(',')))

    merged_specification = {
        'formula': merged_formula,
        'inputs': merged_inputs,
        'outputs': merged_outputs
    }

    print("Generating circuit for merged specification")
    generate_circuit(merged_specification)
    '''
    try:
        template_number = int(input(f"Enter a template number (1-{num_templates}): "))
        if not 1 <= template_number <= num_templates:
            print(f"Error: Template number must be between 1 and {num_templates}.")
            exit(3)
    except ValueError:
        print("Error: Invalid input. Please enter a number between 1 and {num_templates}.")
        exit(3)

        template = root.findall('Template')[template_number - 1]
    specification = {}
    specification['formula'] = template.find('TemplateText').text
    specification['inputs'] = template.find('Input').text
    specification['outputs'] = template.find('Output').text
    '''

    #generate_circuit(specification)
    #aiger_file = 'controller.aigr'
    #if os.path.exists(aiger_file):
    #    os.remove(aiger_file)


if __name__ == "__main__":
    main()