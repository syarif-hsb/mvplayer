#ifndef MVP_UI_H
#define MVP_UI_H

#include <SDL2/SDL.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *slid_rail_tex;
  uint32_t win_w;
  uint32_t win_h;
  uint32_t slid_rail_x;
  uint32_t slid_rail_y;
  uint32_t slid_rail_w;
  uint32_t slid_rail_h;
} mvp_ui_t;

void mvp_init_window( uint32_t x, uint32_t y, uint32_t w, uint32_t h );

void mvp_draw_background();

void mvp_draw_slider( float progress );

#endif /* CSVR_DATA_H */
