#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int FINISH_LINE_X = SCREEN_WIDTH - 100;

// Estados do jogo
typedef enum {
    RACE_RUNNING,
    RACE_OVER
} GameState;

// Estrutura para representar cada corredor
typedef struct {
    SDL_Rect rect;
    int id;
    int speed;
    bool finished;
} Racer;

// Variáveis globais para os corredores e estado do jogo
Racer racer_auto;
Racer racer_keyboard;
Racer racer_mouse;
GameState current_state;
int winner;
int finished_count;

// Função para resetar a corrida para o estado inicial
void reset_race() {
    printf("\n--- Nova Corrida Iniciando! ---\n");
    
    // Posições iniciais
    racer_auto.rect = (SDL_Rect){10, 50, 20, 20};
    racer_keyboard.rect = (SDL_Rect){10, 230, 20, 20};
    racer_mouse.rect = (SDL_Rect){10, 410, 20, 20};

    // Gera uma nova velocidade aleatória para o corredor automático
    racer_auto.speed = 1 + (rand() % 4);
    printf("Velocidade do corredor automático (vermelho): %d\n", racer_auto.speed);
    
    // Reseta as flags de controle
    racer_auto.finished = false;
    racer_keyboard.finished = false;
    racer_mouse.finished = false;
    
    winner = 0; // 0 significa que ainda não há vencedor
    finished_count = 0;
    current_state = RACE_RUNNING;
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    SDL_Window* win = SDL_CreateWindow("Corrida de Retângulos",
                                       SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // Inicializa os corredores
    racer_auto.id = 1;
    racer_keyboard.id = 2;
    racer_mouse.id = 3;

    // Começa a primeira corrida
    reset_race();
    
    SDL_Event evt;
    bool running = true;

    while (running) {
        if (SDL_WaitEventTimeout(&evt, 16)) {
            switch (evt.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                
                case SDL_KEYDOWN:
                    // Se a corrida acabou, a tecla ESPAÇO reinicia
                    if (current_state == RACE_OVER && evt.key.keysym.sym == SDLK_SPACE) {
                        reset_race();
                    }
                    // Movimenta o corredor do teclado apenas durante a corrida
                    else if (current_state == RACE_RUNNING && !racer_keyboard.finished) {
                        switch (evt.key.keysym.sym) {
                            case SDLK_LEFT:
                                racer_keyboard.rect.x -= 5;
                                break;
                            case SDLK_RIGHT:
                                racer_keyboard.rect.x += 5;
                                break;
                        }
                    }
                    break;
                    
                case SDL_MOUSEMOTION:
                    // Movimenta o corredor do mouse apenas durante a corrida
                    if (current_state == RACE_RUNNING && !racer_mouse.finished) {
                        racer_mouse.rect.x = evt.motion.x - racer_mouse.rect.w / 2;
                    }
                    break;
            }
        }
        
        if (current_state == RACE_RUNNING) {
            // Atualiza a posição do corredor automático
            if (!racer_auto.finished) {
                racer_auto.rect.x += racer_auto.speed;
            }

            Racer* racers[] = {&racer_auto, &racer_keyboard, &racer_mouse};

            for (int i = 0; i < 3; i++) {
                // Se o corredor ainda não terminou e cruzou a linha de chegada
                if (!racers[i]->finished && racers[i]->rect.x + racers[i]->rect.w >= FINISH_LINE_X) {
                    racers[i]->finished = true;        // Marca como finalizado
                    racers[i]->rect.x = FINISH_LINE_X - racers[i]->rect.w; // Trava na linha
                    finished_count++;                  // Contador de finalistas

                    // Se for o primeiro a chegar, define como vencedor
                    if (winner == 0) {
                        winner = racers[i]->id;
                    }
                }
            }

            // Se todos os 3 corredores terminaram, encerra a corrida
            if (finished_count >= 3) {
                current_state = RACE_OVER;
                printf("\n--- Corrida Finalizada! ---\n");
                printf(" O VENCEDOR FOI O CORREDOR %d! \n", winner);
                printf("Pressione ESPAÇO para reiniciar.\n");
            }
        }
        
      
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);

        // Linha de chegada
        SDL_SetRenderDrawColor(ren, 0x80, 0x80, 0x80, 0xFF);
        SDL_RenderDrawLine(ren, FINISH_LINE_X, 0, FINISH_LINE_X, SCREEN_HEIGHT);

        // Corredor 1 (automático, vermelho)
        SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(ren, &racer_auto.rect);

        // Corredor 2 azul pelo teclado
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderFillRect(ren, &racer_keyboard.rect);

        // Corredor 3 verde pelo mouse
        SDL_SetRenderDrawColor(ren, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderFillRect(ren, &racer_mouse.rect);
        
        SDL_RenderPresent(ren);
    }

    // FINALIZAÇÃO
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
