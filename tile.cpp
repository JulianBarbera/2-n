#include "tile.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <string>

tile::tile() {} // This guy is just used to create an empty object

tile::tile(SDL_Renderer *renderer, TTF_Font *font, int x, int y) {

  this->renderer = renderer;
  value = 0;
  // Tile size = (screen size - outer padding) / #tiles - tile padding
  width = (options::screenWidth - 50) / options::tiles - 10;
  height = (options::screenHeight - 50) / options::tiles - 10;

  this->x = x;
  this->y = y;
  // Left outer padding + #x * tile width + #tile * tile padding + offset
  xPos = 25 + x * width + x * 10 + 5;
  yPos = 25 + y * height + y * 10 + 25;
  color = colors::black;
  textColor = colors::white;
  this->font = font;
  fillRect = {xPos, yPos, width, height};
}

void tile::set_value(int value) {
  this->value = value;
  set_color(value);
}

void tile::render() {
  if (value > 0) {
    SDL_Surface *textSurface = TTF_RenderText_Shaded(
        font, std::to_string(value).c_str(), textColor, color);
    if (textSurface == NULL) {
      cout << "Unable to create surface from text! TTF Error: "
           << TTF_GetError() << endl;
    } else {
      SDL_Texture *textTexture =
          SDL_CreateTextureFromSurface(renderer, textSurface);
      if (textTexture == NULL) {
        cout << "Unable to create texture! TTF Error: " << TTF_GetError()
             << endl;
      } else {
        if (textSurface->w > textSurface->h) {
          textRect = {xPos, yPos, width,
                      (int)(((float)width / (float)textSurface->w) *
                            (float)textSurface->h)};
        } else {
          int wid = (int)(((float)height / (float)textSurface->h) *
                          (float)textSurface->w);
          textRect = {xPos + (width - wid) / 2, yPos, wid, height};
        }
        SDL_FreeSurface(textSurface);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &fillRect);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
      }
    }
  } else {
    SDL_SetRenderDrawColor(renderer, colors::black.r, colors::black.g,
                           colors::black.b, colors::black.a);
    SDL_RenderFillRect(renderer, &fillRect);
  }
}

void tile::set_color(int value) {
  switch (value) {
  case 0:
    color = colors::black;
    textColor = colors::white;
    break;
  case 2:
    color = colors::red;
    textColor = colors::white;
    break;
  case 4:
    color = colors::orange;
    textColor = colors::white;
    break;
  case 8:
    color = colors::yellow;
    textColor = colors::black;
    break;
  case 16:
    color = colors::green;
    textColor = colors::white;
    break;
  case 32:
    color = colors::blue;
    textColor = colors::white;
    break;
  case 64:
    color = colors::indigo;
    textColor = colors::white;
    break;
  case 128:
    color = colors::violet;
    textColor = colors::white;
    break;
  default:
    color = colors::white;
    textColor = colors::black;
    break;
  }
}
