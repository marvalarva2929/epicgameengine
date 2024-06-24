#include "math.hpp"
#include <algorithm>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_gfx-1.0.4/SDL2_gfxPrimitives.h>

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
   	
	for (Object& object : objects) {
        for (auto face : object.Faces) {
			Sint16 n = face.size();
			Sint16 vx[n], vy[n];
			for (int i = 0; i < n; i++)
				vx[i] = face[i].x,
				vy[i] = face[i].y;
			filledPolygonColor(renderer, &vx, &vy, n, (Uint32)0xFFFFFF);	
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
