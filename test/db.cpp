#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp" // to use <<
#include <fstream>
#include <vector>
#include <string.h>

using namespace rapidxml;
using namespace std;


int display_all() {    
    
    xml_document<> doc;
    xml_node<> * root_node;

    // Read the xml file into a vector
    ifstream file ("data.xml");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);

    // find out root node
    root_node = doc.first_node("tasks");

    // iterate over the lists
    for (xml_node<> * list_node = root_node->first_node("list"); list_node; list_node = list_node->next_sibling()) {
        printf("------------------------------\n");
        printf("%s %s\n",
                list_node->first_attribute("id")->value(),
                list_node->first_attribute("name")->value());
        printf("------------------------------\n");
        

        // iterate over the tasks
        for (xml_node<> * task_node = list_node->first_node("task"); task_node; task_node = task_node->next_sibling()) {
            printf("%s ",
                    task_node->first_attribute("id")->value());
            printf("%s\n", task_node->value());
        }

        printf("\n\n");

    }

    return 0;
}




int display_list(const char* list) {    
    
    xml_document<> doc;
    xml_node<> * root_node;

    // Read the xml file into a vector
    ifstream file ("data.xml");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);

    // find out root node
    root_node = doc.first_node("tasks");

    // iterate over the lists
    for (xml_node<> * list_node = root_node->first_node("list"); list_node; list_node = list_node->next_sibling()) {
        
        if (strcmp(list_node->first_attribute("name")->value(),list) == 0) {

            printf("------------------------------\n");
            printf("%s %s\n",
                    list_node->first_attribute("id")->value(),
                    list_node->first_attribute("name")->value());
            printf("------------------------------\n");
            

            // iterate over the tasks
            for (xml_node<> * task_node = list_node->first_node("task"); task_node; task_node = task_node->next_sibling()) {
                printf("%s ",
                        task_node->first_attribute("id")->value());
                printf("%s\n", task_node->value());
            }

            printf("\n\n");
        }

    }

    return 0;
}





int add_data() {

    xml_document<> doc;
    xml_node<>* decl = doc.allocate_node(node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(decl);

xml_node<>* root = doc.allocate_node(node_element, "rootnode");
root->append_attribute(doc.allocate_attribute("version", "1.0"));
root->append_attribute(doc.allocate_attribute("type", "example"));
doc.append_node(root);
 
xml_node<>* child = doc.allocate_node(node_element, "childnode");
root->append_node(child);

/*
    save_data();
    return 0;
}

int save_data() {
*/
    ofstream file_stored("file_stored.xml");
    file_stored << doc;
    file_stored.close();
    doc.clear();


    return 0;
}


int main() {

    //display_all();

    display_list("TODO");
    
    //add_data();

    return 0;
}
