gcc -c src/*.cpp -std=c++14 -m64 -g -Wall -I include && g++ *.o -o bin/debug/main -lSDL2main -lSDL2 -lSDL2_image -lSDL2_gfx -Wl,-rpath=/usr/local/lib/ && ./bin/debug/main

