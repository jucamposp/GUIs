#include <SDL2/SDL.h>

int main (int argc, char*args[]){
  SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Hello World!",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0xe3,0x0b,0x0b,0x00);
    SDL_Rect ponto = { 20,60, 3,3 };
    SDL_RenderFillRect(ren, &ponto);
    SDL_SetRenderDrawColor(ren, 0xa8,0x4e,0x32,0x00);
    SDL_Rect ret1 = { 70,90, 20,100 };
    SDL_RenderFillRect(ren, &ret1);
    SDL_SetRenderDrawColor(ren, 0x25,0x77,0xdb,0x00);
    SDL_Rect ret2 = { 150,200, 120,30 };
    SDL_RenderFillRect(ren, &ret2);
    SDL_SetRenderDrawColor(ren, 0xdb,0x25,0xc0,0x00);
    SDL_Rect line = { 300,250, 3,50 };
    SDL_RenderFillRect(ren, &line);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);


    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
