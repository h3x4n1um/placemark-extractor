#include <bits/stdc++.h>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

int main(){
    file<> kmlFile("ban-do-hien-trang- phuong-03-quan-go-vap-to-7.kml");
    xml_document<> doc;
    doc.parse<0>(kmlFile.data());

    ofstream output;
    int cnt = 0;
    system("mkdir result");//should replace with filesystem, hacky solution
    for (xml_node<> *node = doc.first_node()->first_node()->first_node()->next_sibling()->first_node()->next_sibling();
         node;
         node = node->next_sibling()){
        output.open("result\\" + to_string(cnt) + ".kml");

        xml_document<> subDoc;
        xml_node<> *decl = subDoc.allocate_node(node_declaration);
        decl->append_attribute(subDoc.allocate_attribute("version", "1.0"));
        decl->append_attribute(subDoc.allocate_attribute("encoding", "utf-8"));
        subDoc.append_node(decl);

        xml_node<> *kml = subDoc.allocate_node(node_element, "kml");
        kml->append_attribute(subDoc.allocate_attribute("xmlns", R"(http://www.opengis.net/kml/2.2)"));
        subDoc.append_node(kml);

        xml_node<> *Document = subDoc.allocate_node(node_element, "Document");
        Document->append_attribute(subDoc.allocate_attribute("id", "root_doc"));
        kml->append_node(Document);

        xml_node<> *Schema = doc.clone_node(doc.first_node()->first_node()->first_node());
        Document->append_node(Schema);

        xml_node<> *Folder = subDoc.allocate_node(node_element, "Folder");
        Document->append_node(Folder);

        xml_node<> *name = subDoc.allocate_node(node_element, "name", "entities");
        Folder->append_node(name);

        xml_node<> *Placemark = doc.clone_node(node);
        Folder->append_node(Placemark);

        output << subDoc;
        output.close();
        ++cnt;
    }

    return 0;
}
