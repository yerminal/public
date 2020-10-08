#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720
#define BUFFER 300

int checkDeath(SDL_Rect snake[], int totalSnake)
{
    for (int a = 1;a <= totalSnake;a++)
        if (snake[0].x == snake[a].x && snake[0].y == snake[a].y)
            return 1;
    
    if (snake[0].x > WIDTH || snake[0].y > HEIGHT)
        return 1;
    if (snake[0].x < 0 || snake[0].y < 0)
        return 1;

    return 0;
}
void speedAfterEveryDifficulty(int level)
{
    if (level < 10)
        SDL_Delay(100);
    else if (level < 20)
        SDL_Delay(90);
    else if (level < 30)
        SDL_Delay(80);
    else if (level < 40)
        SDL_Delay(70);
    else if (level < 50)
        SDL_Delay(60);
    else if (level < 60)
        SDL_Delay(60);
    else if (level < 70)
        SDL_Delay(50);
    else if (level < 80)
        SDL_Delay(50);
    else
        SDL_Delay(40);
    
}
void draw(SDL_Rect snake, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 155, 255, 255); // Snake color
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
    short copy[BUFFER][2] = {0,0};
    
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Snake written in C and used SDL2", SDL_WINDOWPOS_CENTERED, 
             SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int done = 0;
    const char snake_size = 20;
    int snake_x = WIDTH / 2;
    int snake_y = HEIGHT / 2;
    int bait_x = 0;
    int bait_y = 0;
    char direction = 0;
    int i = 0;
    static int totalSnake = 0;

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

        if (checkDeath(snake, totalSnake))
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
                    direction = 1; // North
                    break;
                case SDLK_s:
                    direction = 2; // South
                    break;
                case SDLK_a:
                    direction = 3; // West
                    break;
                case SDLK_d:
                    direction = 4; // East 
                    break;
                }
                break;
            case SDL_QUIT:
                done = 1;
                break;
            }
        }
        switch (direction)
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
        i = 0;
    }
    
    char strm[20];
    sprintf_s(strm,20,"Your score is %d.", totalSnake);

    SDL_DestroyRenderer(renderer);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "GAME OVER", strm , window);
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    return 0;
}
