#pragma once
#include "Tile_man.h"
#include "colors.h"
#include "options.h"
#include <SDL2/SDL.h> // Simple Direct media Layer, for the window and graphics
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream> // For logging to console
#include <unistd.h>

using std::cout;
using std::endl;
class SDL_io {
public:
  SDL_io();
  int run();
  bool init();  // Initialized SDL
  void close(); // Shuts down SDL
  void render_all();
  void agg_score();   // Calculates and displayes total aggregate score
  void merge_score(); // Calculates and displays aggregate of merge values

  // Key press surface constants
  enum keyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL,
  };
  SDL_Window *window;     // The window
  SDL_Renderer *renderer; // The renderer

  SDL_Event e; // Event handler

  TTF_Font *font;

  bool quit;

private:
  Tile_man Tile_man_o;
};
