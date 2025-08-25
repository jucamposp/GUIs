#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Figuras complexas",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            500, 500, SDL_WINDOW_SHOWN
                        );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);

    // Círculo azul
    filledCircleRGBA(ren, 100, 100, 50, 0, 0, 255, 255);

    // Elipse vermelha
    filledEllipseRGBA(ren, 300, 100, 60, 40, 255, 0, 0, 255);

    // Polígono verde (triângulo)
    Sint16 vx[3] = {200, 250, 150};
    Sint16 vy[3] = {300, 400, 400};
    filledPolygonRGBA(ren, vx, vy, 3, 0, 255, 0, 255);

    // Linha preta
    thickLineRGBA(ren, 50, 400, 450, 450, 4, 0, 0, 0, 255);

    SDL_RenderPresent(ren);
    SDL_Delay(5000);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
