#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#define PI 3.14159265

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 320;
const int LINE_SIZE = 100;
bool running = true;
double axiomDegree = PI / 2;
char rule[] = "F-F+F+FF-F-F+F";

int main()
{
  SDL_Window *window;
  SDL_Surface *screenSurface;
  SDL_Renderer *renderer = NULL;
  SDL_Event sevent;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Erro: %s \n", SDL_GetError());
    SDL_Quit();
  }

  window = SDL_CreateWindow("Teste", 100, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if (!window)
  {
    printf("Erro: %s \n", SDL_GetError());
    SDL_Quit();
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == NULL)
  {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
  }

  screenSurface = SDL_GetWindowSurface(window);

  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
  // SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, LINE_SIZE, SCREEN_HEIGHT / 2);

  int x1 = 0;
  int x2 = LINE_SIZE;
  int y1 = SCREEN_HEIGHT / 2;
  int y2 = SCREEN_HEIGHT / 2;
  double currentDegree = axiomDegree;

  for (int i = 0; i < 14; i++)
  {
    char currentChar = rule[i];

    switch (currentChar)
    {
    case 'F':
      x2 = x1 + (cos(currentDegree) * LINE_SIZE);
      y2 = y1 + (sin(currentDegree) * LINE_SIZE);

      SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

      x1 = x2;
      y1 = y2;
      break;
    case '+':
      currentDegree += axiomDegree;
      break;
    case '-':
      currentDegree -= axiomDegree;
      break;
    default:
      break;
    }
  }

  SDL_RenderPresent(renderer);

  while (running)
  {
    while (SDL_PollEvent(&sevent))
    {
      switch (sevent.type)
      {
      case SDL_KEYDOWN:
        if (sevent.key.keysym.sym == SDLK_ESCAPE)
          running = false;
        break;
      case SDL_QUIT:
        running = false;
        break;
      }
    }
  }

  // SDL_Delay(1000);
  SDL_FreeSurface(screenSurface);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
