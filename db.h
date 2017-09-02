#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

using namespace rapidxml;

class DB {

    public:
        int load-xml-doc(string name) {
            xml_document<> xml-doc;
            std::ifstream file(name);
            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();
            std::string content(buffer.str());
            xml-doc.parse<0>(&content[0]);
            
            return 0;
        };

};
