#include "tile.h"

tile::tile() {} // This guy is just used to create an empty object

tile::tile(SDL_Renderer *renderer, TTF_Font *font, int x, int y, uint8_t val) {

  this->renderer = renderer;
  set_value(val);
  // Tile size = (screen size - outer padding) / #tiles - tile padding
  width = (options::screenWidth - 50) / options::tiles - 10;
  height = (options::screenHeight - 50) / options::tiles - 10;

  this->x = x;
  this->y = y;
  // Left outer padding + #x * tile width + #tile * tile padding + offset
  xPos = 25 + x * width + x * 10 + 5;
  yPos = 25 + y * height + y * 10 + 25;
  this->font = font;
  innerRect = {xPos + 5, yPos + 5, width - 10, height - 10};
  outerRect = {xPos, yPos, width, height};
}

void tile::set_value(uint8_t value) {
  this->value = value;
  set_color(value);
}

void tile::render() {
  if (value > 0) {
    SDL_Surface *textSurface = TTF_RenderText_Shaded(
        font, std::to_string((int)std::pow(2, value)).c_str(), textColor,
        innerColor);
    if (textSurface == NULL) {
      cout << "Unable to create surface from text! TTF Error: "
           << TTF_GetError() << endl;
    } else {
      SDL_Texture *textTexture =
          SDL_CreateTextureFromSurface(renderer, textSurface);
      if (textTexture == NULL) {
        cout << "Unable to create text texture! TTF Error: " << TTF_GetError()
             << endl;
      } else {
        if (textSurface->w > textSurface->h) {
          textRect = {xPos + 5, yPos + 5, width - 10,
                      (int)(((float)(width - 10) / (float)textSurface->w) *
                            (float)textSurface->h)};
        } else {
          int wid = (int)(((float)(height - 10) / (float)textSurface->h) *
                          (float)textSurface->w);
          textRect = {xPos + ((width - 10) - wid) / 2 + 5, yPos + 5, wid,
                      (height - 10)};
        }
        SDL_FreeSurface(textSurface);
        SDL_SetRenderDrawColor(renderer, outerColor.r, outerColor.g,
                               outerColor.b, outerColor.a);
        SDL_RenderFillRect(renderer, &outerRect);
        SDL_SetRenderDrawColor(renderer, innerColor.r, innerColor.g,
                               innerColor.b, innerColor.a);
        SDL_RenderFillRect(renderer, &innerRect);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
      }
    }
  } else {
    SDL_SetRenderDrawColor(renderer, colors::black.r, colors::black.g,
                           colors::black.b, colors::black.a);
    SDL_RenderFillRect(renderer, &outerRect);
  }
}

void tile::set_color(uint8_t value) {
  int row = value % 8;
  int col = 0;
  if (value >= 8) {
    col = (value - row) / 8;
  }
  innerColor = colors::colorArray[row];
  textColor = colors::textColorArray[row];
  outerColor = colors::colorArray[col];
}
