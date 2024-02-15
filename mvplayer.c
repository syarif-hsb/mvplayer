#include <SDL2/SDL.h>
#include <stdio.h>
#include "ui.h"

#define MVP_WIN_WIDTH  400
#define MVP_WIN_HEIGHT 300


void mvp_init_sdl()
{
  SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);
}

int main(int argc, char *argv[])
{
  mvp_init_sdl();
  mvp_init_window(1000, SDL_WINDOWPOS_UNDEFINED,
      MVP_WIN_WIDTH, MVP_WIN_HEIGHT);

  SDL_Event e;
  int mvp_loop = 1;
  while ( mvp_loop ) {
    if ( SDL_WaitEvent( &e ) ) {
      switch ( e.type ) {
        case SDL_QUIT:
          mvp_loop = 0;
          break;
      }
    }
    mvp_draw_background();
  }

  return 0;
}
