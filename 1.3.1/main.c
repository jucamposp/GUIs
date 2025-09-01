#include <SDL2/SDL.h>
#include <math.h>

int main(int argc, char* args[]) {
    /* INICIALIZAÇÃO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Bola em Circulo",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       400, 300, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* Centro e raio da trajetória */
    int cx = 200, cy = 150;
    int raio = 80;

    /* Bola */
    SDL_Rect bola = {0, 0, 20, 20};  // quadrado usado como bola
    float ang = 0.0f;                
    float velAngular = 10.0f / raio; // rad/s para 10 px/s

    Uint32 lastTick = SDL_GetTicks();

    /* EXECUÇÃO - um único loop */
    while (1) {
        Uint32 now = SDL_GetTicks();
        float delta = (now - lastTick) / 1000.0f;
        lastTick = now;

        // Atualiza ângulo
        ang += velAngular * delta;
        if (ang > 2 * M_PI) ang -= 2 * M_PI;

        // Atualiza posição da bola
        bola.x = cx + (int)(raio * cos(ang)) - bola.w/2;
        bola.y = cy + (int)(raio * sin(ang)) - bola.h/2;

        // Renderiza
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        SDL_RenderFillRect(ren, &bola);

        SDL_RenderPresent(ren);
        SDL_Delay(16); 
    }

    /* FINALIZAÇÃO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
}
