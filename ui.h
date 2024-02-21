#ifndef MVP_UI_H
#define MVP_UI_H

#include <SDL2/SDL.h>

typedef enum {
  MVP_SLIDER_RELEASED = 0,
  MVP_SLIDER_CLICKED,
} MVP_slider_state;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *slid_rail_tex;
  SDL_Rect slid_rail_rect;
  SDL_Colour bg_color;
  uint32_t win_w;
  uint32_t win_h;
  float slid_progress;
  MVP_slider_state slid_state;
} mvp_ui_t;

void mvp_init_window( uint32_t x, uint32_t y, uint32_t w, uint32_t h );

void mvp_draw_background();

void mvp_draw_slider( float progress );

void mvp_mouse_slide( uint32_t mx, uint32_t my );

void mvp_mouse_event_handle( SDL_Event *e );

SDL_bool mouse_in_slider_rail( uint32_t mx, uint32_t my );

#endif /* MVP_UI_H */
