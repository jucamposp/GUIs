#include <SDL2/SDL.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms) {
    if (*ms <= 0) {
        return SDL_PollEvent(evt);
    }
  
    Uint32 start_time = SDL_GetTicks();

    int result = SDL_WaitEventTimeout(evt, *ms);

    Uint32 end_time = SDL_GetTicks();
    
    Uint32 ms_spent = end_time - start_time;
  
    if (*ms > ms_spent) {
        *ms -= ms_spent;
    } else {
        // Se o tempo gasto for maior ou igual ao tempo restante, define o tempo restante como zero.
        *ms = 0; 
    }
    
    return result;
}
