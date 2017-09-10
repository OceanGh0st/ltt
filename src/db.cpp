#include "db.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp" // to use <<
#include <fstream>
#include <vector>
#include <string.h>

using namespace rapidxml;
using namespace std;

DB::DB(int id) { }

int DB::display_all() {    
    
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

int DB::display_list(const char* list) {    
    
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


int DB::add_list(const char* new_list) {
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

int DB::add_task(const char* new_task, const char* list) {
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



int DB::remove_all() {
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


int DB::remove_list(const char* list) {
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


int DB::remove_task(const char* task) {
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

int DB::clear_list(const char* list) {

    remove_list(list);
    add_list(list);

    return 0;
}

int DB::move_task(const char* task_t, const char* list) {

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

        
            // iterate over the tasks
            for (xml_node<> * task_node = list_node->first_node("task"); task_node; task_node = task_node->next_sibling()) {

                if (strcmp(task_node->value(),task_t) == 0 && strcmp(list_node->first_attribute("name")->value(),list) != 0) {


                    //remove task
                    task_node->value("");
                    break;
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


int DB::cleanup() {
    
    FILE* f;
    FILE* tmp;
    char line[1000];
    unsigned n = 0;

    f = fopen("data.xml", "rb+");
    tmp = fopen("tmp.xml", "wb+");
    
    if (!f) { fprintf(stderr,  "%s", "Could not open file\n"); return 1; }

    while (fgets(line, 1000, f)) {
        if (strstr(line,"<list/>") == NULL) {
            fprintf(tmp, line);
        }
    }
/*
    if (!feof(f)) {
        fprintf(stderr, "%s", "Something went wrong\n");
        fclose(f);
        return 1;
    }

    if (!feof(tmp)) {
        fprintf(stderr, "%s", "Something went wrong\n");
        fclose(f);
        return 1;
    }
*/

    fclose(f);
    fclose(tmp);
    remove("data.xml");
    rename("tmp.xml", "data.xml");
    
    return 0;
}
