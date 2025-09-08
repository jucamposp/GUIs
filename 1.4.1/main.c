#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


const int MAX_RECTS = 10;

// Armazenar informações dos retângulos
struct RectangleInfo {
    SDL_Rect rect;
    SDL_Color color;
};

int main(int argc, char* args[]) {
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    /* EXECUÇÃO */
    SDL_Rect r = {320, 240, 20, 20}; // Posição inicial fixa no centro
    
    // Vetor para armazenar os retângulos fixos
    RectangleInfo fixed_rects[MAX_RECTS];
    int num_fixed_rects = 0;
    
    // Cores para os retângulos fixos
    SDL_Color colors[] = {
        {255, 0, 0, 255},   
        {0, 255, 0, 255},   
        {0, 0, 255, 255},  
        {255, 255, 0, 255}, 
        {0, 255, 255, 255}, 
        {255, 0, 255, 255}, 
        {128, 0, 128, 255}, 
        {255, 165, 0, 255}, 
        {0, 128, 128, 255}, 
        {128, 128, 0, 255} 
    };

    SDL_Event evt;
    bool running = true;
    while (running) {
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);

        // Desenha os retângulos fixos
        for (int i = 0; i < num_fixed_rects; ++i) {
            SDL_SetRenderDrawColor(ren, fixed_rects[i].color.r, fixed_rects[i].color.g, fixed_rects[i].color.b, fixed_rects[i].color.a);
            SDL_RenderFillRect(ren, &fixed_rects[i].rect);
        }

        // Desenha o retângulo que se move
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);

        // Processa os eventos
        while (SDL_PollEvent(&evt)) {
            switch (evt.type) {
                // 1. Quando o usuário fechar a janela, termine a aplicação.
                case SDL_QUIT:
                    running = false;
                    break;
                
                case SDL_KEYDOWN:
                    switch (evt.key.keysym.sym) {
                        case SDLK_UP:
                            r.y -= 5;
                            break;
                        case SDLK_DOWN:
                            r.y += 5;
                            break;
                        case SDLK_LEFT:
                            r.x -= 5;
                            break;
                        case SDLK_RIGHT:
                            r.x += 5;
                            break;
                    }
                    // 3. Mantenha nos limites da tela o retângulo que se move.
                    if (r.x < 0) r.x = 0;
                    if (r.y < 0) r.y = 0;
                    if (r.x + r.w > 640) r.x = 640 - r.w;
                    if (r.y + r.h > 480) r.y = 480 - r.h;
                    break;

                // 2. Quando o usuário clicar no mouse, adicione um novo retângulo fixo.
                case SDL_MOUSEBUTTONDOWN:
                    if (evt.button.button == SDL_BUTTON_LEFT) {
                        if (num_fixed_rects < MAX_RECTS) {
                            int mouse_x = evt.button.x;
                            int mouse_y = evt.button.y;
                            fixed_rects[num_fixed_rects].rect = {mouse_x, mouse_y, 20, 20}; // Cria um novo retângulo na posição do clique
                            fixed_rects[num_fixed_rects].color = colors[num_fixed_rects]; // Pega a cor do array de cores
                            num_fixed_rects++; // Incrementa o contador de retângulos
                        }
                    }
                    break;
            }
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
