#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdlib.h>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SQUARE_SIZE = 50; 
const int MAX_SQUARES = 256; 
const Uint32 MULTI_CLICK_EVENT_CODE = 1;

int AUX_WaitEventTimeOut(SDL_Event* evt, Uint32* ms){
    Uint32 start_time = SDL_GetTicks();
    
    int result = SDL_WaitEventTimeout(evt, *ms);

    Uint32 end_time = SDL_GetTicks();
    Uint32 ms_spent = end_time - start_time;

    if (*ms >= ms_spent) {
        *ms -= ms_spent;
    } else {
        *ms = 0; 
    }
    
    return result;

}


typedef struct {
    int x;
    int y;
    int click_count;
} ClickEvent;

int main(int argc, char* args[]) {
    
    SDL_Window* win = SDL_CreateWindow("Multiplos cliques",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SCREEN_WIDTH, SCREEN_HEIGHT,
                                     SDL_WINDOW_SHOWN);

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
   
    bool quit = false;
    SDL_Event event;

    int multi_click_cont = 0;
    ClickEvent last_click_event;

    
    SDL_Rect squares[MAX_SQUARES];
    int square_count = 0;

    
    Uint8 bg_r = 20, bg_g = 20, bg_b = 40;

    Uint32 wait_time = 250;

    printf("-> Clique uma vez para adicionar um quadrado.\n");
    printf("-> Clique duas ou mais vezes rapidamente para mudar a cor do fundo.\n");
    printf("-> Pressione ESC ou feche a janela para sair.\n\n");

  
    while (!quit) {
        if (AUX_WaitEventTimeOut(&event, &wait_time)) {
            switch (event.type) {
                case SDL_QUIT:
                case SDL_KEYDOWN:
                    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                        quit = true;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (multi_click_cont == 0) {
                        wait_time = 250;
                    }
                    
                    multi_click_cont++;
                    last_click_event.x = event.button.x;
                    last_click_event.y = event.button.y;
                    
                    break;
                
                case SDL_USEREVENT:
                    int final_click_count = event.user.code; 
                    
                    if (final_click_count == 1) {
                        printf("Evento de USUÁRIO - Clique único detectado. Adicionando um quadrado em (%d, %d).\n", last_click_event.x, last_click_event.y);
                        if (square_count < MAX_SQUARES) {
                            squares[square_count].x = last_click_event.x - SQUARE_SIZE / 2;
                            squares[square_count].y = last_click_event.y - SQUARE_SIZE / 2;
                            squares[square_count].w = SQUARE_SIZE;
                            squares[square_count].h = SQUARE_SIZE;
                            square_count++;
                        }
                    } else if (final_click_count > 1) {
                        printf("Evento de USUÁRIO - Fim da sequência de múltiplos cliques. Total: %d. Mudando cor do fundo.\n", final_click_count);
                
                        bg_r = rand() % 256;
                        bg_g = rand() % 256;
                        bg_b = rand() % 256;
                    }
                    break;
            }
        } else {
            if (multi_click_cont > 0) {
                
                SDL_Event user_event;
                user_event.type = SDL_USEREVENT;
                
                user_event.user.code = multi_click_cont; 
                
                user_event.user.data1 = NULL;
                user_event.user.data2 = NULL;
                
                SDL_PushEvent(&user_event);
                
                multi_click_cont = 0;
            }
            wait_time = 0; 
        }

        /* RENDERIZAÇÃO */
        SDL_SetRenderDrawColor(ren, bg_r, bg_g, bg_b, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 255, 0, 255); 
        for (int i = 0; i < square_count; ++i) {
            SDL_RenderFillRect(ren, &squares[i]);
        }

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
