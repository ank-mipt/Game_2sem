#include iostream
using namespace std;

#include tinyxml.h
int main(){
    TiXmlDocument file(example.xml);
    file.LoadFile();

    TiXmlElement head;
    head = file.FirstChildElement(CATALOG);

    TiXmlElement t;
    t = head-FirstChildElement(CD);
    while(t){
        coutt-FirstChildElement(TITLE)-GetText()endl;
        t = t-NextSiblingElement(CD);
    }

    return 0;
}

