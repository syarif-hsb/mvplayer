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
  ui_t.slid_rail_rect.x = ui_t.win_w * 1/10;
  ui_t.slid_rail_rect.y = ui_t.win_h * 4/5;
  ui_t.slid_rail_rect.w = ui_t.win_w * 8/10;
  ui_t.slid_rail_rect.h = 4;

  ui_t.slid_rail_tex = SDL_CreateTexture( ui_t.renderer,
      SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_TARGET,
      ui_t.slid_rail_rect.w, ui_t.slid_rail_rect.h );

  SDL_SetRenderTarget( ui_t.renderer, ui_t.slid_rail_tex );
  SDL_SetRenderDrawColor( ui_t.renderer, 0, 0, 0, 255 );
  SDL_RenderFillRect( ui_t.renderer, &ui_t.slid_rail_rect );
  SDL_SetRenderTarget( ui_t.renderer, NULL );

  ui_t.slid_progress = 0.0;
  ui_t.slid_state = MVP_SLIDER_RELEASED;

  return;
}

void mvp_draw_background()
{
  SDL_SetRenderDrawColor( ui_t.renderer, 200, 200, 200, 255 );
  SDL_RenderClear( ui_t.renderer );

  mvp_draw_slider( ui_t.slid_progress );

  SDL_RenderPresent( ui_t.renderer );
  return;
}

void mvp_draw_slider( float progress )
{
  uint32_t slid_w = 8;
  uint32_t slid_h = ui_t.slid_rail_rect.h + 12 ;
  uint32_t slid_x = ui_t.slid_rail_rect.x + 
    (uint32_t) ( progress * ( ui_t.slid_rail_rect.w - slid_w ) ) 
    / 100.0;
  uint32_t slid_y = ui_t.slid_rail_rect.y - 6;

  SDL_Rect slider = { 
    slid_x,
    slid_y,
    slid_w,
    slid_h,
  };
  SDL_Vertex slider_tri1 = { 
    { slid_x, ui_t.slid_rail_rect.y + ui_t.slid_rail_rect.h + 6  }, 
    { 255, 0, 0, 255 }, 
    { 1, 1 } 
  };
  SDL_Vertex slider_tri2 = { 
    { slid_x + slid_w, ui_t.slid_rail_rect.y + ui_t.slid_rail_rect.h + 6  }, 
    { 255, 0, 0, 255 }, 
    { 1, 1 } 
  };
  SDL_Vertex slider_tri3 = { 
    { slid_x + slid_w/2, ui_t.slid_rail_rect.y + ui_t.slid_rail_rect.h + 12 }, 
    { 255, 0, 0, 255 }, 
    { 1, 1 } 
  };
  SDL_Vertex slider_tri[] = { 
    slider_tri1, 
    slider_tri2, 
    slider_tri3 
  };

  SDL_SetRenderDrawColor( ui_t.renderer, 255, 0, 0, 255 );

  SDL_RenderCopy( ui_t.renderer, ui_t.slid_rail_tex, 
      NULL, &ui_t.slid_rail_rect );
  SDL_RenderFillRect( ui_t.renderer, &slider );
  SDL_RenderGeometry( ui_t.renderer, NULL, slider_tri, 3, NULL, 0 );

  return;
}

void mvp_mouse_slide( uint32_t mx, uint32_t my )
{
  float slid_progress = (int) ( mx - ( ui_t.slid_rail_rect.x + 4 ) ) / 
    (float) ( ui_t.slid_rail_rect.w - 8 ) * 100.0;

  if ( slid_progress < 0.0 ) {
    slid_progress = 0.0;
  } else if ( slid_progress > 100.0 ) {
    slid_progress = 100.0;
  }

  ui_t.slid_progress = slid_progress;
  return;
}

SDL_bool mouse_in_slider_rail( uint32_t mx, uint32_t my )
{
  SDL_Point mouse = { mx, my };

  uint32_t extra_margin = 6;
  SDL_Rect slid_big_rail_rect = {
    ui_t.slid_rail_rect.x,
    ui_t.slid_rail_rect.y - extra_margin,
    ui_t.slid_rail_rect.w,
    ui_t.slid_rail_rect.h + extra_margin * 2,
  };

  return SDL_PointInRect( &mouse, &slid_big_rail_rect );
}

void mvp_mouse_event_handle( SDL_Event *e )
{
  switch ( e->type ) {
    case SDL_MOUSEMOTION:
      {
        if ( ui_t.slid_state == MVP_SLIDER_CLICKED )
          mvp_mouse_slide( e->motion.x, e->motion.y );
        break;
      }
    case SDL_MOUSEBUTTONDOWN:
      {
        if ( ui_t.slid_state == MVP_SLIDER_RELEASED && 
            mouse_in_slider_rail( e->button.x, e->button.y ) == SDL_TRUE ) {
          mvp_mouse_slide( e->button.x, e->button.y );
          ui_t.slid_state = MVP_SLIDER_CLICKED;
        }
        break;
      }
    case SDL_MOUSEBUTTONUP:
      {
        ui_t.slid_state = MVP_SLIDER_RELEASED;
        break;
      }
    case SDL_MOUSEWHEEL:
      {
        break;
      }
  }

  return;
}
