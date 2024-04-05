

#include <fstream>
#include "rapidxml/rapidxml.hpp"
#include "src/Game/Graphics/GE.h"

void attributeViewer(rapidxml::xml_node<> * node);

int main(int argc, char * args[]) {

	rapidxml::xml_document<> doc;
	std::ifstream file("Assets/xml_file.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> * rNode = doc.first_node();

	std::cout << sizeof(*rNode) << std::endl;

	attributeViewer(rNode);

	for(rapidxml::xml_node<> * pNode = rNode->first_node("node"); pNode; pNode=pNode->next_sibling()){
		std::cout << pNode->first_attribute()->value() << std::endl;
	}

    GraphicsEngine ge;

    ge._run();
    ge._close();

    return 0;
}

void attributeViewer(rapidxml::xml_node<> * node){
	for(rapidxml::xml_node<> * pNode = node->first_node(); pNode; pNode=pNode->next_sibling()){
//		std::cout << node->first_attribute()->value() << std::endl;
//		if(pNode->first_node() != nullptr){
//			attributeViewer(pNode);
//		}
	}
}