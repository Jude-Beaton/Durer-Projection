#include <stdio.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "mathslibrary/matrix.h"
#include "mathslibrary/vec.h"

const int WIDTH = 800, HEIGHT = 800;

const float XMIN = -0.3f, YMIN = -0.3f, XMAX = 0.3f, YMAX = 0.3f;

const float PI = 3.141593f;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool Initialise(void);
void Update(float);
void Shutdown(void);
void generateCube(void);
void projectPoints(void);
void drawEdges(void);
void rotatePoints(void);

vec points[8];
int* edges[12];
vec projectedPoints[8];
float angle = 0.02f;

mat rotationY;
vec cubePos;


int main( int argc, char * argv[]){
    
    cubePos = vector(0.0f, 0.0f, 3.0f);
    rotationY = newMatrix(3, 3,
        1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f
    );
    rotationY.elements[0][0] = cosf(angle);
    rotationY.elements[0][2] = sinf(angle);
    rotationY.elements[2][0] = -sinf(angle);
    rotationY.elements[2][2] = cosf(angle);

    printMat(rotationY);

    

    generateCube();

    

    srand((unsigned int)time(NULL));
    atexit(Shutdown);


    if (!Initialise())
    {
        exit(1);
    }

    bool quit = false;
    SDL_Event event;


    Uint32 lastTick = SDL_GetTicks64();

    while (!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        //work out how many ticks have passed during processing and pass it in as seconds per loop
        Uint32 currTick = SDL_GetTicks64();
        Uint32 diff = currTick - lastTick;
        float elapsed = diff / 1000.0f;

        

        Update(elapsed);
        lastTick = currTick;
        
    }


    SDL_Quit();

    return 0;
}

void generateCube(void){
    
    points[0] = vector(-0.5f,-0.5f, 2.5f);
    points[1] = vector(-0.5f, 0.5f, 2.5f);
    points[2] = vector( 0.5f, 0.5f, 2.5f);
    points[3] = vector( 0.5f,-0.5f, 2.5f);
    points[4] = vector(-0.5f,-0.5f, 3.5f);
    points[5] = vector(-0.5f, 0.5f, 3.5f);
    points[6] = vector( 0.5f, 0.5f, 3.5f);
    points[7] = vector( 0.5f,-0.5f, 3.5f);

    for(unsigned int i = 0; i < 12; i++){
        edges[i] = malloc(2*sizeof(int));
    }
    
    edges[0][0] = 0;
    edges[1][0] = 1;
    edges[2][0] = 2;
    edges[3][0] = 3;
    edges[4][0] = 0;
    edges[5][0] = 1;
    edges[6][0] = 2;
    edges[7][0] = 3;
    edges[8][0] = 4;
    edges[9][0] = 5;
    edges[10][0] = 6;
    edges[11][0] = 7;

    edges[0][1] = 1;
    edges[1][1] = 2;
    edges[2][1] = 3;
    edges[3][1] = 0;
    edges[4][1] = 4;
    edges[5][1] = 5;
    edges[6][1] = 6;
    edges[7][1] = 7;
    edges[8][1] = 5;
    edges[9][1] = 6;
    edges[10][1] = 7;
    edges[11][1] = 4;
    
}

void projectPoints(){
    
    for(unsigned int i = 0; i < 8; i++){
        float x = points[i].elements[0]/points[i].elements[2];
        float y = points[i].elements[1]/points[i].elements[2];

        x = ((x - XMIN)/(XMAX - XMIN))*WIDTH;
        y = (1 - (y - YMIN)/(YMAX - YMIN))*HEIGHT;



        projectedPoints[i] = vector(x, y);
        //printVec(projectedPoints[i]);
    }
}

void drawEdges(){
    for(unsigned int i = 0; i < 12; i++){
        //printf("Here");
        vec i0 = projectedPoints[edges[i][0]];
        vec i1 = projectedPoints[edges[i][1]];
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, i0.elements[0], i0.elements[1], i1.elements[0], i1.elements[1]);
    }
}

void rotatePoints(){
    for(unsigned int i = 0; i < 8; i++){
        points[i] = vecAdd(matVecMultiplication(rotationY, vecSubtract(points[i], cubePos)), cubePos);
        //printVec(points[i]);
    }
}

bool Initialise(void){
    //Initialise SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Failed to initialise SDL: %s\n",
            SDL_GetError());
        return false;
    }

    //Create the window pointer 
    window = SDL_CreateWindow("Durer Projection", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    
    if(!window) {
        return false;
    }

    //set GPU as renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!window) {
        return false;
    }


    return true;
}

void Update(float elapsed){
    
    //Double buffering is used, essentially memory is written to when changes are made,
    //then copied to another buffer from which the screen renders data so all changes
    //are rendered to the screen at the same time
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    rotatePoints();

    projectPoints();
    
    drawEdges();

    SDL_RenderPresent(renderer);
}

void Shutdown(void){
    if(renderer){
        SDL_DestroyRenderer(renderer);
    }
    if(window){
        SDL_DestroyWindow(window);
    } 
    SDL_Quit();
}