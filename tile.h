#pragma once
#include "colors.h"
#include "options.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include <iostream>
using std::cout;
using std::endl;

class tile {
public:
  tile();
  tile(SDL_Renderer *renderer, TTF_Font *font, int x, int y, uint8_t val);

  uint8_t value;
  int x;
  int y;
  int xPos;
  int yPos;
  int offset;
  SDL_Rect innerRect;
  SDL_Rect outerRect;
  SDL_Rect textRect;
  SDL_Color innerColor;
  SDL_Color outerColor;
  SDL_Color textColor;
  SDL_Renderer *renderer;
  TTF_Font *font;

  void render();
  void set_value(uint8_t value);
  void set_color(uint8_t value);

  void set_size(int screenWidth, int screenHeight);

private:
  int width;
  int height;
};
