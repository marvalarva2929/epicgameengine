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
}

void Math::moveCamera(Vector3 dl) {
}



void Math::rotCamera(float thetaX, float thetaY, float thetaZ) {
}

