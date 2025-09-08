#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
    /* INICIALIZACAO */

    SDL_Window* win = SDL_CreateWindow("Multiplos Retângulos",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);


    // Retângulo 1: Move-se pelo tempo
    SDL_Rect rect_time = {10, 10, 20, 20};
    int time_dx = 2; // Velocidade de movimento
    int time_dy = 2;

    // Retângulo 2: Move-se pelo teclado
    SDL_Rect rect_keyboard = {320, 240, 20, 20};

    // Retângulo 3: Acompanha o mouse
    SDL_Rect rect_mouse = {0, 0, 20, 20};
    
    SDL_Event evt;
    bool running = true;
    Uint32 last_update_time = SDL_GetTicks();

    while (running) {
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_update_time) / 1000.0f; // Tempo em segundos
        last_update_time = current_time;

        // Processa os eventos
        while (SDL_PollEvent(&evt)) {
            switch (evt.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                
                case SDL_KEYDOWN:
                    switch (evt.key.keysym.sym) {
                        case SDLK_UP:
                            rect_keyboard.y -= 5;
                            break;
                        case SDLK_DOWN:
                            rect_keyboard.y += 5;
                            break;
                        case SDLK_LEFT:
                            rect_keyboard.x -= 5;
                            break;
                        case SDLK_RIGHT:
                            rect_keyboard.x += 5;
                            break;
                    }
                    // Mantém nos limites da tela o retângulo do teclado
                    if (rect_keyboard.x < 0) rect_keyboard.x = 0;
                    if (rect_keyboard.y < 0) rect_keyboard.y = 0;
                    if (rect_keyboard.x + rect_keyboard.w > SCREEN_WIDTH) rect_keyboard.x = SCREEN_WIDTH - rect_keyboard.w;
                    if (rect_keyboard.y + rect_keyboard.h > SCREEN_HEIGHT) rect_keyboard.y = SCREEN_HEIGHT - rect_keyboard.h;
                    break;

                case SDL_MOUSEMOTION:
                    // Atualiza a posição do retângulo do mouse
                    rect_mouse.x = evt.motion.x - rect_mouse.w / 2;
                    rect_mouse.y = evt.motion.y - rect_mouse.h / 2;
                    break;
            }
        }
        
        // Atualiza a posição do retângulo que se move pelo tempo
        rect_time.x += time_dx;
        rect_time.y += time_dy;

        // Limites para o retângulo que se move pelo tempo
        if (rect_time.x <= 0 || rect_time.x + rect_time.w >= SCREEN_WIDTH) {
            time_dx = -time_dx;
        }
        if (rect_time.y <= 0 || rect_time.y + rect_time.h >= SCREEN_HEIGHT) {
            time_dy = -time_dy;
        }

        /* RENDERIZACAO */
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);

        // Desenha o retângulo que se move com o tempo (vermelho)
        SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(ren, &rect_time);

        // Desenha o retângulo que se move com o teclado (azul)
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderFillRect(ren, &rect_keyboard);

        // Desenha o retângulo que segue o mouse (verde)
        SDL_SetRenderDrawColor(ren, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderFillRect(ren, &rect_mouse);
        
        SDL_RenderPresent(ren);
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
