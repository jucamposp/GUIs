#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[]) {
    /* INICIALIZAÇÃO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Multiplos Cliques",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SCREEN_WIDTH, SCREEN_HEIGHT,
                                       SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);


    bool quit = false;
    SDL_Event event;

    int click_cont = 0;

    // Inicializa com fundo preto
    Uint8 bg_r = 0, bg_g = 0, bg_b = 0;

    SDL_Rect color_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    printf("Programa iniciado. Clique na janela ou pressione ESC para sair.\n");

    // --- 4. Loop Principal de Eventos ---
    while (!quit) {
        if (SDL_WaitEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    printf("Evento SDL_QUIT detectado. Encerrando o programa.\n");
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        printf("Tecla ESC pressionada. Encerrando o programa.\n");
                        quit = true;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    click_cont++;

                    SDL_Event custom_event;
                    custom_event.type = SDL_USEREVENT;
                    custom_event.user.code = click_count;
                    custom_event.user.data1 = NULL;
                    custom_event.user.data2 = NULL;

                    SDL_PushEvent(&custom_event);
                    break;

                case SDL_USEREVENT:
                    printf("Evento customizado recebido! Código (contador de cliques): %d\n", event.user.code);

                    
                    bg_r = rand() % 256;
                    bg_g = rand() % 256;
                    bg_b = rand() % 256;
                    
                    break;
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        // Define a cor do fundo
        SDL_SetRenderDrawColor(ren, bg_r, bg_g, bg_b, 255);
        
        // Desenha o retângulo que preenche a tela
        SDL_RenderFillRect(ren, &color_rect);

        // Atualiza a tela com o que foi renderizado
        SDL_RenderPresent(ren);
    }
  
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
