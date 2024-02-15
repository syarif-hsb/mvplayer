#include <SDL2/SDL.h>
#include "ui.h"

static mvp_ui_t ui_t;

void mvp_init_window(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
  ui_t.window = SDL_CreateWindow(
      "SDL Tutorial",
      x, y,
      w, h,
      SDL_WINDOW_SHOWN );

  ui_t.renderer = SDL_CreateRenderer( ui_t.window, -1,
      SDL_RENDERER_ACCELERATED );

  ui_t.win_w = w;
  ui_t.win_h = h;
  ui_t.slid_rail_x = ui_t.win_w * 1/10;
  ui_t.slid_rail_y = ui_t.win_h * 4/5;
  ui_t.slid_rail_w = ui_t.win_w * 8/10;
  ui_t.slid_rail_h = 4;

  SDL_Rect rail = { 
    ui_t.slid_rail_x, 
    ui_t.slid_rail_y, 
    ui_t.slid_rail_w, 
    ui_t.slid_rail_h 
  };
  ui_t.slid_rail_tex = SDL_CreateTexture( ui_t.renderer,
      SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_TARGET,
      ui_t.slid_rail_w, ui_t.slid_rail_h );

  SDL_SetRenderTarget( ui_t.renderer, ui_t.slid_rail_tex );
  SDL_SetRenderDrawColor( ui_t.renderer, 0, 0, 0, 255 );
  SDL_RenderFillRect( ui_t.renderer, &rail );
  SDL_SetRenderTarget( ui_t.renderer, NULL );

  return;
}

void mvp_draw_background()
{
  SDL_SetRenderDrawColor( ui_t.renderer, 255, 255, 255, 255 );
  SDL_RenderClear( ui_t.renderer );

  mvp_draw_slider( 30.0 );

  SDL_RenderPresent( ui_t.renderer );
  return;
}

void mvp_draw_slider( float progress )
{
  uint32_t slid_w = 8;
  uint32_t slid_h = ui_t.slid_rail_h + 12 ;
  uint32_t slid_x = ui_t.slid_rail_x + 
    (uint32_t) ( progress * ui_t.slid_rail_w ) / 100.0;
  uint32_t slid_y = ui_t.slid_rail_y - 6;

  SDL_Rect slider = { 
    slid_x,
    slid_y,
    slid_w,
    slid_h,
  };
  SDL_Vertex slider_tri1 = { 
    { slid_x, ui_t.slid_rail_y + ui_t.slid_rail_h + 6  }, 
    { 255, 0, 0, 255 }, 
    { 1, 1 } 
  };
  SDL_Vertex slider_tri2 = { 
    { slid_x + slid_w, ui_t.slid_rail_y + ui_t.slid_rail_h + 6  }, 
    { 255, 0, 0, 255 }, 
    { 1, 1 } 
  };
  SDL_Vertex slider_tri3 = { 
    { slid_x + slid_w/2, ui_t.slid_rail_y + ui_t.slid_rail_h + 12 }, 
    { 255, 0, 0, 255 }, 
    { 1, 1 } 
  };
  SDL_Vertex slider_tri[] = { 
    slider_tri1, 
    slider_tri2, 
    slider_tri3 
  };

  SDL_SetRenderDrawColor( ui_t.renderer, 255, 0, 0, 255 );

  SDL_Rect rail = { 
    ui_t.slid_rail_x, 
    ui_t.slid_rail_y, 
    ui_t.slid_rail_w, 
    ui_t.slid_rail_h 
  };
  SDL_RenderCopy( ui_t.renderer, ui_t.slid_rail_tex, NULL, &rail );
  SDL_RenderFillRect( ui_t.renderer, &slider );
  SDL_RenderGeometry( ui_t.renderer, NULL, slider_tri, 3, NULL, 0 );

  return;
}
