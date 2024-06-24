#include "math.hpp"
#include <algorithm>
#include <iostream>

Math::Math(int p_w, int p_h) :WINDOW_WIDTH(p_w), WINDOW_HEIGHT(p_h) {
    
    float fovy = 3.14159/4, // 45 degrees
        aspect = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
        near = 0.01,
        far = 100;

    float top = near * tan(fovy/2),
        right = top * aspect,
        bottom = -top,
        left = -right;
    
    projection_matrix = Matrix(std::vector<std::vector<float>>{
        {2*near/(right-left), 0,                   0,                       -near*(right+left)/(right-left)},
        {0,                   2*near/(top-bottom), 0,                       -near*(top+bottom)/(top-bottom)},
        {0,                   0,                    -(far+near)/(far-near), 2*far*near/(near-far)},
        {0,                   0,                   -1,                      0}
    });
    
    viewport = Matrix(std::vector<std::vector<float>>{
        {(float)WINDOW_WIDTH/2.0f, 0,                         0, (float)WINDOW_WIDTH/2.0f},
        {0,                        (float)WINDOW_HEIGHT/2.0f, 0, (float)WINDOW_HEIGHT/2.0f},
        {0,                        0,                         1, 0},
        {0,                        0,                         0, 1},
    });
    
    rotate = Matrix(std::vector<std::vector<float>>{
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 1}
            });

}

void Math::render(SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    std::vector<Vector3> pnts;
    Matrix fin = viewport * projection_matrix;
    
    for (Object& object : objects)
        for (auto &point : object.Points) {
            point = rotate * (point + camera); 
            pnts.emplace_back(fin * point); 
		} 
   	
	bool first = 1;
	for (Object& object : objects) {
        for (auto edge : object.Edges) {
            auto p1 = pnts[edge.first], p2 = pnts[edge.second];
			if (first) p1.print(), p2.print(), std::cout << std::endl;
			first = 0;
            if (std::min({p1.x, p1.y, p2.x, p2.y}) >= 0 && std::max({p1.z, p2.z}) < 1)
                SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
        }
    }
}

void Math::moveCamera(Vector3 dl) {
    camera = dl;
}


void Math::addObject(Object& object) {
    objects.emplace_back(object);
}

void Math::rotCamera(float thetaX, float thetaY, float thetaZ) {
    tx = thetaX, ty = thetaY, tz = thetaZ;
    x += tx, y += ty, z += tz;
    float a = cos(tx), b = sin(tx),
        c = cos(ty), d = sin(ty);
    
    (*rotate[0])[0] = c, (*rotate[0])[2] = d;
    (*rotate[1])[0] = b * d, (*rotate[1])[1] = a, (*rotate[1])[2] = -b * c;
    (*rotate[2])[0] = - a * d, (*rotate[2])[1] = b, (*rotate[2])[2] = a * c;
}
