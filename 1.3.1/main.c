#include <SDL2/SDL.h>
#include <math.h>

/* Função para desenhar elipse preenchida */
void drawEllipse(SDL_Renderer* ren, int x0, int y0, int rx, int ry) {
    for (int w = -rx; w <= rx; w++) {
        for (int h = -ry; h <= ry; h++) {
            if ((w*w)*ry*ry + (h*h)*rx*rx <= rx*rx*ry*ry) {
                SDL_RenderDrawPoint(ren, x0 + w, y0 + h);
            }
        }
    }
}

int main(int argc, char* args[]) {
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Cobra Simples",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       400, 200, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* Cabeça da cobra (rect só para posição e tamanho de referência) */
    SDL_Rect r = {50, 100, 12, 12};

    /* EXECUCAO */
    while (r.x < 300) {
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        // Corpo: vários quadrados atrás da cabeça
        SDL_SetRenderDrawColor(ren, 0, 200, 0, 255);
        for (int i = 0; i < 5; i++) {
            SDL_Rect body = { r.x - i*15, r.y, 12, 12 };
            SDL_RenderFillRect(ren, &body);
        }

        // Rabo: triângulo no final do corpo
        SDL_SetRenderDrawColor(ren, 0, 150, 0, 255);
        SDL_Point tail[4] = {
            {r.x - 5*15,     r.y},       // base esquerda
            {r.x - 5*15,     r.y + 12},  // base direita
            {r.x - 5*15 - 10,r.y + 6},   // ponta do rabo
            {r.x - 5*15,     r.y}        // fecha o triângulo
        };
        SDL_RenderDrawLines(ren, tail, 4);

        // Cabeça: elipse azul centrada no retângulo r
        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        drawEllipse(ren, r.x + r.w/2, r.y + r.h/2, 8, 6);

        SDL_RenderPresent(ren);
        SDL_Delay(200);

        // Movimento da cobra para frente
        r.x += 5;
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
