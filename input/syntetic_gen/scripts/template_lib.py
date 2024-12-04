import xml.etree.ElementTree as ET
import xml.dom.minidom

def parse_ltl_spects(file_path):
    templates = []
    with open(file_path, 'r') as file:
        lines = file.readlines()
        i = 0
        while i < len(lines):
            if lines[i].strip() == '' or lines[i].startswith('#'):
                i += 1
                continue
            try:
                ins = lines[i].strip().replace('Input : ', '')
                outs = lines[i+1].strip().replace('Output : ', '')
                template = lines[i+2].strip().replace('Template: ', '')
                templates.append({'template': template, 'ins': ins, 'outs': outs})
                i += 3  # Skip the block and the empty line
            except IndexError:
                print(f"Error parsing template starting at line {i+1}")
                break
    return templates

def create_xml(templates, output_file):
    root = ET.Element('Templates')
    for tmpl in templates:
        tmpl_element = ET.SubElement(root, 'Template')
        
        ins_element = ET.SubElement(tmpl_element, 'Input')
        ins_element.text = tmpl['ins']
        
        outs_element = ET.SubElement(tmpl_element, 'Output')
        outs_element.text = tmpl['outs']
        
        template_element = ET.SubElement(tmpl_element, 'TemplateText')
        template_element.text = tmpl['template']
    
    tree = ET.ElementTree(root)
    xml_str = ET.tostring(root, encoding='utf-8')
    pretty_xml_str = xml.dom.minidom.parseString(xml_str).toprettyxml(indent="  ")
    
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(pretty_xml_str)

if __name__ == "__main__":
    input_file = '../ltl_with_propositions.txt'
    output_file = 'output_templates.xml'
    templates = parse_ltl_spects(input_file)
    create_xml(templates, output_file)