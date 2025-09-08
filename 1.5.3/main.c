#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

int main(int argc, char* args[]) {
    /* INICIALIZAÇÃO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Bola em Círculo - Orientado a Eventos",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       400, 300, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    int cx = 200, cy = 150;
    int raio = 80;

    /* Bola */
    SDL_Rect bola = {0, 0, 20, 20}; 
    float ang = 0.0f;
    float velAngular = 1.5f;

    bool running = true;
    SDL_Event event;
    Uint32 lastTick = SDL_GetTicks();

    /* EXECUÇÃO */
  // Loop principal orientado a eventos 
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            // Inverter direção com clique do mouse
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    velAngular = -velAngular; // Inverte a velocidade angular
                }
            }
        }

        Uint32 now = SDL_GetTicks();
        float delta = (now - lastTick) / 1000.0f; // Delta time em segundos
        lastTick = now;

        // Atualiza ângulo baseado na velocidade e no tempo decorrido
        ang += velAngular * delta;
        

        // Atualiza posição da bola com base no novo ângulo
        bola.x = cx + (int)(raio * cos(ang)) - bola.w / 2;
        bola.y = cy + (int)(raio * sin(ang)) - bola.h / 2;


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
