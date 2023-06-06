#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#define PI 3.14159265

const int SCREEN_HEIGHT = 1080;
const int SCREEN_WIDTH = 1920;
const int LINE_SIZE = 100;
bool running = true;
double axiomDegree = PI / 4;

int main()
{
  SDL_Window *window;
  SDL_Surface *screenSurface;
  SDL_Renderer *renderer = NULL;
  SDL_Event sevent;
  FILE *resultFilePointer;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Erro: %s \n", SDL_GetError());
    SDL_Quit();
  }

  window = SDL_CreateWindow("Fractal X - Estágio X", 100, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

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

  int offset = 100;
  int x1 = 0 + offset;
  int x2 = LINE_SIZE + offset;
  int y1 = 0 + offset;
  int y2 = LINE_SIZE + offset;
  double currentDegree = 0;
   char charBuffer;

  resultFilePointer = fopen("result_file_three.txt", "r");

  while ((charBuffer = getc(resultFilePointer)) != EOF)
  {
    switch (charBuffer)
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
  };

  fclose(resultFilePointer);

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

  SDL_FreeSurface(screenSurface);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
