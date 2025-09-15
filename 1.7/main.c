#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char* args[]) {
    /* INICIALIZAÇÃO */

    SDL_Window* win = SDL_CreateWindow("Animação - Tirinha de Recortes",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       400, 300, SDL_WINDOW_SHOWN);
    
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture* spriteTexture = IMG_LoadTexture(ren, "sprite_sheet.png");
    if (spriteTexture == NULL) {
        printf("IMG_LoadTexture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    int cx = 200, cy = 150;
    int raio = 80;

    /* Configuração da Animação */
    const int FRAME_WIDTH = 32;  
    const int FRAME_HEIGHT = 32; 
    const int NUM_FRAMES = 4;    
    const int FRAME_DELAY = 100; 

    SDL_Rect srcRect = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};

    SDL_Rect dstRect = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};

    float ang = 0.0f;
    float velAngular = 1.5f;

    bool running = true;
    SDL_Event event;
    Uint32 lastTick = SDL_GetTicks();
    Uint32 lastFrameChange = SDL_GetTicks();
    int currentFrame = 0;

    /* EXECUÇÃO */
    while (running) {
        if (SDL_WaitEventTimeout(&event, 10)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    velAngular = -velAngular;
                }
            }
        }

        Uint32 now = SDL_GetTicks();
        float delta = (now - lastTick) / 1000.0f;
        lastTick = now;

        ang += velAngular * delta;
        dstRect.x = cx + (int)(raio * cos(ang)) - dstRect.w / 2;
        dstRect.y = cy + (int)(raio * sin(ang)) - dstRect.h / 2;

        if (now > lastFrameChange + FRAME_DELAY) {
            currentFrame = (currentFrame + 1) % NUM_FRAMES;
            srcRect.x = currentFrame * FRAME_WIDTH;
            lastFrameChange = now;
        }

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        SDL_RenderCopy(ren, spriteTexture, &srcRect, &dstRect);

        SDL_RenderPresent(ren);
    }

    /* FINALIZAÇÃO */
    SDL_DestroyTexture(spriteTexture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
