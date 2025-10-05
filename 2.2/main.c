#include <SDL2/SDL.h>
#include <stdio.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms) {
    Uint32 start_time = SDL_GetTicks();
    int result = SDL_WaitEventTimeout(evt, *ms);
    Uint32 end_time = SDL_GetTicks();
    
    Uint32 ms_spent = end_time - start_time;
    
    if (*ms > ms_spent) {
        *ms -= ms_spent;
    } else {
        *ms = 0;
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Arraste, Clique ou Cancele",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    
    SDL_Rect square = { 350, 250, 100, 100 };
    SDL_Point original_pos;

    typedef enum {
        STATE_IDLE,     
        STATE_ARMED,     
        STATE_DRAGGING   
    } InteractionState;

    InteractionState state = STATE_IDLE;
    SDL_Point click_offset;

    int running = 1;
    SDL_Event event;

    while (running) {
        Uint32 timeout = 100;

        if (AUX_WaitEventTimeoutCount(&event, &timeout)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        if (state == STATE_ARMED || state == STATE_DRAGGING) {
                            printf("Gesto cancelado com ESC.\n");
                            square.x = original_pos.x;
                            square.y = original_pos.y;
                            state = STATE_IDLE;
                        }
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (state == STATE_ARMED) {
                        printf("Arrasto iniciado.\n");
                        state = STATE_DRAGGING;
                    }
                    if (state == STATE_DRAGGING) {
                        square.x = event.motion.x - click_offset.x;
                        square.y = event.motion.y - click_offset.y;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        SDL_Point mouse_pos = { event.button.x, event.button.y };
                        if (SDL_PointInRect(&mouse_pos, &square)) {
                            state = STATE_ARMED;
        
                            original_pos.x = square.x;
                            original_pos.y = square.y;
            
                            click_offset.x = mouse_pos.x - square.x;
                            click_offset.y = mouse_pos.y - square.y;
                            printf("Mouse pressionado no quadrado. Gesto iniciado (ARMED).\n");
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (state == STATE_ARMED) {
                            printf("Gesto concluido: FOI UM CLIQUE.\n");
                        }
                        if (state == STATE_DRAGGING) {
                            printf("Gesto concluido: FOI UM ARRASTO.\n");
                        }
                        state = STATE_IDLE;
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0, 100, 255, 255);
        SDL_RenderFillRect(ren, &square);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
