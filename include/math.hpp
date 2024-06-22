#pragma once
#include "Vector3.hpp"
#include "Matrix.hpp"
#include "SDL2/SDL.h"

class Math {
    private:
    Matrix projection_matrix,
           rotate,
           viewport,
           translation;
    Vector3 camera;
    float tx, ty, tz;
    float x, y, z;

    public:
    
    Math(int p_v, int p_h);
    int WINDOW_WIDTH, WINDOW_HEIGHT;        
    void render(SDL_Renderer * renderer);
    void moveCamera(Vector3 dl);
    void rotCamera(float thetaX, float thetaY, float thetaZ);
};

