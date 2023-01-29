#pragma once
#include "colors.h"
#include "options.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using std::cout;
using std::endl;

class tile {
public:
  tile();
  tile(SDL_Renderer *renderer, TTF_Font *font, int x, int y, int val);

  int value;
  int x;
  int y;
  int xPos;
  int yPos;
  SDL_Rect fillRect;
  SDL_Rect textRect;
  SDL_Color color;
  SDL_Color textColor;
  SDL_Renderer *renderer;
  TTF_Font *font;

  void render();
  void set_value(int value);
  void set_color(int value);

private:
  int width;
  int height;
};
