#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include <math.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define WIDTH 1280
#define HEIGHT 720
#define BUFFER 300
#define PATH_INTRO "Effects/snake.bmp"
#define PATH_MUSIC "Effects/Cyberpunk-Moonlight-Sonata-v2.wav"
#define PATH_DEATH "Effects/qubodup-PowerDrain.wav"

void MusicsLoadAndStart(Mix_Music* background)
{
    background = Mix_LoadMUS(PATH_MUSIC);
    Mix_PlayMusic(background, -1);
    if (!background) {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }
}
int checkDeath(SDL_Rect snake[], int totalSnake)
{
    for (int a = 1;a <= totalSnake;a++)
        if (snake[0].x == snake[a].x && snake[0].y == snake[a].y)
            return 1;

    return 0;
}
void speedAfterEveryDifficulty(int level)
{
    int a = 90;
    if (level < 10)
        SDL_Delay(a);
    else if (level < 20)
        SDL_Delay(a-10);
    else if (level < 30)
        SDL_Delay(a-20);
    else if (level < 40)
        SDL_Delay(a-20);
    else if (level < 50)
        SDL_Delay(a-30);
    else if (level < 60)
        SDL_Delay(a-30);
    else if (level < 70)
        SDL_Delay(a-40);
    else if (level < 80)
        SDL_Delay(a-40);
    else
        SDL_Delay(40);
    
}
void draw(SDL_Rect snake, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 128, 192, 255); // Snake color
    SDL_RenderFillRect(renderer, &snake);
}
int takeRandom(int min, int max)
{
    int totalSnake = 0;
    while (1)
    {
        totalSnake = rand();
        totalSnake = totalSnake % max;
        if (totalSnake >= min)
            break;
    }
    return totalSnake;   
}
int main()
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music* background = NULL;
    short copy[BUFFER][2] = {0,0};
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music* deathSound = Mix_LoadMUS(PATH_DEATH);
    MusicsLoadAndStart(background);

    window = SDL_CreateWindow("Snake written in C and used SDL2", SDL_WINDOWPOS_CENTERED, 
             SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* image = SDL_LoadBMP(PATH_INTRO);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,image);
    SDL_Rect iamge = { WIDTH/2 - 426/2,HEIGHT/2 - (int)581/2,426,581 };
    SDL_RenderCopy(renderer, texture, NULL, &iamge);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);

    int done = 0;
    const char snake_size = 20;
    int snake_x = WIDTH / 2;
    int snake_y = HEIGHT / 2;
    int bait_x = 0;
    int bait_y = 0;
    char direction1 = 0;
    char direction2 = 0;
    int i = 0;
    static int totalSnake = 0;
    char death = 0;

    SDL_Event test_event;
    bait_x = 20 * takeRandom(0, (WIDTH - snake_size) / snake_size + 1);
    bait_y = 20 * takeRandom(0, (HEIGHT - snake_size) / snake_size + 1);
    SDL_Rect snake[BUFFER] = {0};

    for (int a = 0; a < BUFFER; a++)
    {
        snake[a].x = snake_x;
        snake[a].y = snake_y;
        snake[a].w = snake_size;
        snake[a].h = snake_size;
    }
    SDL_Rect bait = { bait_x, bait_y, snake_size, snake_size };
    
    while (!done)
    {
        if (snake_x > WIDTH)
            snake_x -= WIDTH;
        if (snake_x < 0)
            snake_x += WIDTH;
        if (snake_y > HEIGHT)
            snake_y -= HEIGHT;
        if (snake_y < 0)
            snake_y += HEIGHT;
        
        snake[i].x = snake_x;
        snake[i].y = snake_y;

        if (bait_x == snake_x && bait_y == snake_y)
        {
            totalSnake++;
            snake[totalSnake].x = copy[totalSnake - 1][0];
            snake[totalSnake].y = copy[totalSnake - 1][1];
            bait_x = 20 * takeRandom(0, (WIDTH - snake_size) / snake_size + 1);
            bait_y = 20 * takeRandom(0, (HEIGHT - snake_size) / snake_size + 1);
            bait.x = bait_x;
            bait.y = bait_y;
        }

        if (death=checkDeath(snake, totalSnake))
            break;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Snake color
        SDL_RenderFillRect(renderer, &bait);
        for (int a = totalSnake; a >= 0; a--)
            draw(snake[a],renderer);
        SDL_RenderPresent(renderer);

        speedAfterEveryDifficulty(totalSnake);

        for (int a = 0; a <= totalSnake; a++)
        {
            copy[a][0] = snake[a].x;
            copy[a][1] = snake[a].y;
        }
        
        for (int a = 0; a < totalSnake; a++)
        {
            snake[a + 1].x = copy[a][0];
            snake[a + 1].y = copy[a][1];
        }
        
        while (SDL_PollEvent(&test_event))
        {
            switch (test_event.type)
            {
            case SDL_KEYDOWN:
                switch (test_event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_SPACE:
                    done = 1;
                    break;
                case SDLK_w: 
                    direction1 = 1; // North
                    break;
                case SDLK_s:
                    direction1 = 2; // South
                    break;
                case SDLK_a:
                    direction1 = 3; // West
                    break;
                case SDLK_d:
                    direction1 = 4; // East 
                    break;
                }
                break;
            case SDL_QUIT:
                done = 1;
                break;
            }
        }

        if (direction2 + direction1 == 3 || direction2 + direction1 == 7)
            direction1 = direction2;

        switch (direction1)
        {
        case 1:
            snake_y -= 20;
            break;
        case 2:
            snake_y += 20;
            break;
        case 3:
            snake_x -= 20;
            break;
        case 4:
            snake_x += 20;
            break;
        }
        direction2 = direction1;
        i = 0;
    }
    
    if (death) 
    {
        Mix_PauseMusic(background);
        Mix_PlayMusic(deathSound, 0);
        SDL_Delay(2000);
    }
        
    char strm[20];
    sprintf_s(strm,20,"Your score is %d.", totalSnake);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    Mix_FreeMusic(background);
    Mix_FreeMusic(deathSound);
    window = NULL;
    SDL_Quit();
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "GAME OVER", strm, window);
    return 0;
}
