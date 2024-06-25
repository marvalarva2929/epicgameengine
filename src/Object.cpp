#include "Object.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <math.h>

Object::Object(std::string filename) {
    std::ifstream file; 
    file.open(filename);
	float scale = 1.0f;
    //std::cout << file.fail() << " " << filename << std::endl; 
    while (!file.eof()) {
        std::string c;
        std::getline(file, c);
        if (c[0] == 'v' && c[1] == ' ' ) {
            std::string vert = c.substr(1);
            std::stringstream ss; ss << vert;  
            float one, two, three;
            ss >> one >> two >> three; two *= -1;
			avg.x += one, avg.y += two, avg.z += three;
            Points.emplace_back(one * scale, two * scale, three * scale); 
        } else if (c[0] == 'f') {
            std::string face = c.substr(1);
			//std::cout << face << std::endl;
			std::stringstream ss; ss << face;
			std::vector<int> shape; 
			while (!ss.eof()) {
				std::string womp;
				std::stringstream ind; ss >> womp; ind << womp;
               	int id; ind >> id;
				shape.push_back(--id);	
			}
       		Faces.push_back(shape);	 
		}
    }

	avg.x /= Points.size();
	avg.y /= Points.size();
	avg.z /= Points.size();
}

void Object::normalize(int dist) {
	for (auto & point : Points)
		point = point - avg;

	float x = 0, y = 0, z = 0;
	for (auto point : Points)
		x = std::max(x, point.x),
		y = std::max(y, point.y),
		z = std::max(z, point.z);

	std::cout << x << ", " << y << " , " << z << std::endl;
}
