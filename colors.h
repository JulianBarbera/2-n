#pragma once
#include <SDL2/SDL.h>
#include <iostream>
using std::cout;
using std::endl;

class colors {
public:
  static constexpr SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};
  static constexpr SDL_Color red = {0xFF, 0x00, 0x00, 0xFF};
  static constexpr SDL_Color orange = {0xFF, 0x7B, 0x00, 0xFF};
  static constexpr SDL_Color yellow = {0xFF, 0xFF, 0x00, 0xFF};
  static constexpr SDL_Color green = {0x00, 0xFF, 0x00, 0xFF};
  static constexpr SDL_Color blue = {0x00, 0x00, 0xFF, 0xFF};
  static constexpr SDL_Color indigo = {0x4B, 0x00, 0x82, 0xFF};
  static constexpr SDL_Color violet = {0x8F, 0x00, 0xFF, 0xFF};
  static constexpr SDL_Color black = {0x00, 0x00, 0x00, 0xFF};
  static constexpr SDL_Color transparent = {0x00, 0x00, 0x00, 0x00};

  static constexpr SDL_Color colorArray[] = {white, red,  orange, yellow,
                                             green, blue, indigo, violet};

  static constexpr SDL_Color textColorArray[] = {black, white, white, black,
                                                 white, white, white, white};
};
