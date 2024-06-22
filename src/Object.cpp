#include "Object.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Object::Object(std::string filename) {
    std::ifstream file; 
    file.open(filename);
    while (!file.eof()) {
        std::string c;
        std::getline(file, c);
        if (c[0] == 'v') {
        } else if (c[0] == 'f') {
        }
    }
    //std::string next = " ";
    //while (true) {
    //    while (next[0] != 'v') file >> next, std::cout << next << std::endl;
    //    float one, two, three;
    //    file >> one >> two >> three;
    //    std::cout << one << " " << two << " " << three << std::endl;
    //}
}
