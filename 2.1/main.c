#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

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

    int total_click_cont = 0;
    int multi_click_cont = 0;
    bool is_multiclick = false;

    // Inicializa com fundo preto
    Uint8 bg_r = 0, bg_g = 0, bg_b = 0;

    SDL_Rect color_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    printf("Programa iniciado. Clique na janela ou pressione ESC para sair.\n");

    while (!quit) {
        if (SDL_WaitEventTimeout(&event, 250)) {
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
                    //total_click_cont++;

                    //multi_click_cont++;
                    //is_multiclick = true;

                    //SDL_Event custom_event;
                    //custom_event.type = SDL_USEREVENT;
                    //custom_event.user.code = multi_click_cont;
                    //custom_event.user.data1 = NULL;
                    //custom_event.user.data2 = NULL;

                    SDL_PushEvent(&custom_event);
                    break;

                case SDL_USEREVENT:
                    printf("Clique detectado. Cliques na sequência atual: %d\n", event.user.code);

                    bg_r = rand() % 256;
                    bg_g = rand() % 256;
                    bg_b = rand() % 256;
                    
                    break;
            }
        }else {
            // O tempo de 250ms sem um evento
            //if (is_multiclick) {
                //printf("Fim dos cliques. Total na sequencia: %d\n", multi_click_cont);
                //multi_click_cont = 0;
                //is_multiclick = false;
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
