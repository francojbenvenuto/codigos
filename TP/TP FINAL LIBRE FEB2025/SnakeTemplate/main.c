#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL_main.h>
#endif
#include <SDL.h>
#include "config.h"



/**
Pablo Soligo. Plantilla de proyecto codeblocks para juego snake (Linux/Windows).
*/

void SetColor(SDL_Renderer *renderer, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

SDL_Texture* loadTexture(const char *path, SDL_Renderer *renderer) {
    SDL_Surface *loadedSurface = SDL_LoadBMP(path); // Carga una imagen BMP
    if (!loadedSurface) {
        printf("Error al cargar la imagen: %s\n", SDL_GetError());
        return NULL;
    }

    // Convierte la superficie en una textura
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface); // Libera la superficie temporal

    if (!texture) {
        printf("Error al crear textura: %s\n", SDL_GetError());
    }
    return texture;
}

void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}


int numeroRandom (int min, int max) {
    return min + rand() % (max - min + 1);
}




int main(int argc, char *argv[])
{
    unsigned char done = 0;
    SDL_Rect fillRect;
    SDL_Rect snake;
    SDL_Rect contorno1;   //techo
    SDL_Rect contorno2;   //piso
    SDL_Rect contorno3;   // izq
    SDL_Rect contorno4;   //der

    snake.x = snake.y = 30;
    snake.h = snake.w = 30;

    contorno1.x = contorno1.y = contorno3.y = contorno3.x = contorno2.x = contorno4.y = 0;
    contorno1.h = contorno2.h = 30;
    contorno1.w = contorno2.w = 600;

    contorno2.y = contorno4.x = 570;
    contorno3.w = contorno4.w = 30;
    contorno3.h = contorno4.h = 600;


    int movimiento = 0;
    int flagManzana = 0;
    int contador= 0;


    int delay               = 100;
    //int delay               = 2;
    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;
    SDL_Event e;



    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Create window
    window = SDL_CreateWindow("Snake",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_ORDER,
                                SCREEN_ORDER,
                                SDL_WINDOW_SHOWN);

    if (!window) {
        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }



    // Creamos el lienzo
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_Texture *imgSnakeHead = loadTexture(IMG_HEAD, renderer);
    if (!imgSnakeHead) {
        printf("Error al cargar el sprite.\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }


    SDL_SetWindowTitle(window, "Snake template");
    while (!done){ //Se puede parar tambien cuando no se observen cambios!
        while (SDL_PollEvent(&e) != 0) {
            // Salida del usuario
            if (e.type == SDL_QUIT) {
                puts("Saliendo");
                done = 1;
            }else if(e.type == SDL_KEYDOWN)
            {
                //Salida por ESC
                if(e.key.keysym.sym==SDLK_ESCAPE){
                    done = 1;
                };

                // mover a la derecha
                if(e.key.keysym.sym==SDLK_RIGHT){
                    if(movimiento != 1)
                        movimiento = 0;
                };

                // mover a la izquierda
                if(e.key.keysym.sym==SDLK_LEFT){
                    if(movimiento != 0)
                        movimiento = 1;
                };

                // mover arriba
                if(e.key.keysym.sym==SDLK_UP){
                    if(movimiento != 3)
                        movimiento = 2;
                };

                // mover abajo
                if(e.key.keysym.sym==SDLK_DOWN){
                    if(movimiento != 2)
                        movimiento = 3;
                };
            }
        }
        //Limpiar pantalla de algun color,
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        //Tam de la figura
        fillRect.h = 30; //Alto
        fillRect.w = 30; //Ancho

        //Pinto un cuadrado de ejemplo
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer, &contorno1);
        SDL_RenderFillRect(renderer, &contorno2);
        SDL_RenderFillRect(renderer, &contorno3);
        SDL_RenderFillRect(renderer, &contorno4);



        //Muevo la posicion para que no se superpongan y
        //pinto un ciculo de ejemplo, todo harcodeado, estos numeros
        //tiene que salir de calculos
        if(flagManzana == 0){
            fillRect.x = numeroRandom(30,570);
            fillRect.y = numeroRandom(30,570);

            flagManzana = 1;
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        drawFilledCircle(renderer, fillRect.x, fillRect.y, 20);
        switch (movimiento)
        {
        case 0:
            snake.x = snake.x +10;
            break;

        case 1:
            snake.x = snake.x -10;
            break;

        case 2:
            snake.y = snake.y -10;
            break;

        case 3:
            snake.y = snake.y +10;
            break;

        default:
            break;
        }

        if(snake.x < 30 || snake.x > 570 || snake.y < 30 || snake.y >570 )
            done = 1;

        if( snake.x < fillRect.x + fillRect.w &&
            snake.x + snake.w > fillRect.x &&
            snake.y < fillRect.y + fillRect.h &&
            snake.y + snake.h > fillRect.y)
            {
                flagManzana = 0;
                contador++;
                printf("contador: %d\n", contador);
                delay = delay -5;
            }

        SDL_RenderCopy(renderer, imgSnakeHead, NULL, &snake);
        SDL_RenderPresent(renderer);
        SDL_Delay(delay);

    }

    //destruyo todos los elementos creados
    //Observar ni mas ni menos que destructores, en la asignatura no inventamos nada!
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


