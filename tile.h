#include "colors.h"
#include "options.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
using std::cout;
using std::endl;

class tile {
public:
  int value;
  int x;
  int y;
  int xPos;
  int yPos;
  SDL_Rect fillRect;
  SDL_Color color;
  SDL_Renderer *renderer;

  tile();
  tile(SDL_Renderer *renderer, int x, int y);
  tile(SDL_Renderer *renderer);

  void setX(int x);
  void setY(int y);
  void tile_up();
  void tile_down();
  void tile_left();
  void tile_right();

  void refresh_render();
  void render();
  void set_value(int value);
  void set_color(int value);

private:
  int width;
  int height;
};
