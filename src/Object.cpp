#include "Object.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Object::Object(std::string filename) {
    std::ifstream file; 
    file.open(filename);
	float scale = 2.0f;
    //std::cout << file.fail() << " " << filename << std::endl; 
    while (!file.eof()) {
        std::string c;
        std::getline(file, c);
        if (c[0] == 'v') {
            std::string vert = c.substr(1);
            std::stringstream ss; ss << vert;  
            float one, two, three;
            ss >> one >> two >> three;
            Points.emplace_back(one * scale, two * scale, three * scale); 
        } else if (c[0] == 'f') {
            std::string face = c.substr(1);
			//std::cout << face << std::endl;
			std::stringstream ss; ss << face;
			std::vector<Vector3> shape; 
			while (!ss.eof()) {
				std::string womp;
				std::stringstream ind; ss >> womp; ind << womp;
               	int id; ind >> id;
				shape.emplace_back(id);	
			}
       		Faces.emplace_back(shape);	 
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
