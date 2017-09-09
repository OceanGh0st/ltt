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
        printf(" %s\n",
                list_node->first_attribute("name")->value());
        printf("------------------------------\n");
        

        // iterate over the tasks
        for (xml_node<> * task_node = list_node->first_node("task"); task_node; task_node = task_node->next_sibling()) {
            printf("   %s\n", task_node->value());
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

    // iterate over the list
    for (xml_node<> * list_node = root_node->first_node("list"); list_node; list_node = list_node->next_sibling()) {
        
        if (strcmp(list_node->first_attribute("name")->value(),list) == 0) {

            printf("------------------------------\n");
            printf(" %s\n",
                    list_node->first_attribute("name")->value());
            printf("------------------------------\n");
            

            // iterate over the tasks
            for (xml_node<> * task_node = list_node->first_node("task"); task_node; task_node = task_node->next_sibling()) {
                printf("   %s\n", task_node->value());
            }

            printf("\n\n");
        }

    }

    return 0;
}


int add_list(const char* new_list) {
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

    // add list
    xml_node<> * list_node = doc.allocate_node(node_element, "list");
    root_node->append_node(list_node);
    xml_attribute<> *attr = doc.allocate_attribute("name", new_list);
    list_node->append_attribute(attr);

    // add task
    xml_node<> * task_node = doc.allocate_node(node_element, "task");
    list_node->append_node(task_node);
    task_node->value("");

    // save to file
    ofstream file_stored("data.xml");
    file_stored << doc;
    file_stored.close();
    doc.clear();

    return 0;
}

int add_task(const char* new_task, const char* list) {
    xml_document<> doc;
    xml_node<> * root_node;

    // Read the xml file into a vector
    ifstream file ("data.xml");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // parse the buffer using the xml file parsing library into doc
    doc.parse<parse_no_data_nodes>(&buffer[0]);

    // find out root node
    root_node = doc.first_node("tasks");

    // iterate over the list
    for (xml_node<> * list_node = root_node->first_node("list"); list_node; list_node = list_node->next_sibling()) {
        
        if (strcmp(list_node->first_attribute("name")->value(),list) == 0) {

	    // add task
	    xml_node<> * task_node = doc.allocate_node(node_element, "task");
	    list_node->append_node(task_node);
            task_node->value(new_task);
        }

    }

    // save to file
    ofstream file_stored("data.xml");
    file_stored << doc;
    file_stored.close();
    doc.clear();

    return 0;
}



int remove_all() {
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

    // clear list
    for (xml_node<> * list_node = root_node->first_node("list"); list_node; list_node = list_node->next_sibling()) {
        
            list_node->remove_all_nodes();
            list_node->remove_all_attributes();

    }

    // save to file
    ofstream file_stored("data.xml");
    file_stored << doc;
    file_stored.close();
    doc.clear();

    return 0;
}


int remove_list(const char* list) {
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

    // clear list
    for (xml_node<> * list_node = root_node->first_node("list"); list_node; list_node = list_node->next_sibling()) {
        
        if (strcmp(list_node->first_attribute("name")->value(),list) == 0) {
            
//            printf("%s", list_node->name());
            list_node->remove_all_nodes();
            list_node->remove_all_attributes();
        }

    }

    // save to file
    ofstream file_stored("data.xml");
    file_stored << doc;
    file_stored.close();
    doc.clear();

    return 0;
}


int remove_task(const char* task) {
    xml_document<> doc;
    xml_node<> * root_node;

    // Read the xml file into a vector
    ifstream file ("data.xml");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // parse the buffer using the xml file parsing library into doc
    doc.parse<parse_no_data_nodes>(&buffer[0]);

    // find out root node
    root_node = doc.first_node("tasks");

    // iterate over the list
    for (xml_node<> * list_node = root_node->first_node("list"); list_node; list_node = list_node->next_sibling()) {

            // iterate over the tasks
            for (xml_node<> * task_node = list_node->first_node("task"); task_node; task_node = task_node->next_sibling()) {

                if (strcmp(task_node->value(),task) == 0) {

                    // remove task
                    task_node->value("");
                }

            }
        

    }

    // save to file
    ofstream file_stored("data.xml");
    file_stored << doc;
    file_stored.close();
    doc.clear();

    return 0;
}

int clear_list(const char* list) {

    remove_list(list);
    add_list(list);

    return 0;
}

int move_task(const char* task_t, const char* list) {

    xml_document<> doc;
    xml_node<> * root_node;

    // Read the xml file into a vector
    ifstream file ("data.xml");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // parse the buffer using the xml file parsing library into doc
    doc.parse<parse_no_data_nodes>(&buffer[0]);

    // find out root node
    root_node = doc.first_node("tasks");

    // iterate over the list
    for (xml_node<> * list_node = root_node->first_node("list"); list_node; list_node = list_node->next_sibling()) {
        
        if (strcmp(list_node->first_attribute("name")->value(),list) == 0) {
	    // add task
	    xml_node<> * task_node = doc.allocate_node(node_element, "task");
	    list_node->append_node(task_node);
            task_node->value(task_t);
        }

            printf("List_node value: %s\n", list_node->value());
        
            // iterate over the tasks
            for (xml_node<> * task_node = list_node->first_node("task"); task_node; task_node = task_node->next_sibling()) {

                if (strcmp(task_node->value(),task_t) == 0 && strcmp(list_node->first_attribute("name")->value(),list) != 0) {

                    //remove task
                    printf("%s\n", task_node->value());
                    task_node->value("");
                    break;
                }
            printf("task_node value: %s\n", task_node->value());

            }
    }
        

    // save to file
    ofstream file_stored("data.xml");
    file_stored << doc;
    file_stored.close();
    doc.clear();

    return 0;
}

int main() {

    //display_all();

    //display_list("In progress");

    //add_list("testing");
    //display_all();

    //add_task("1 2 3 test", "Done");

    //remove_all();

    //remove_list("TODO");

    //remove_task("alamakota");

    //clear_list("Done");

    //move_task("Do homework", "In progress");


    return 0;
}
