#include "tile.h"
tile::tile() {}

tile::tile(SDL_Renderer *renderer, int x, int y) {
  this->renderer = renderer;
  value = 0;
  width = (options::screenWidth - 20) / options::tiles - 10;
  height = (options::screenHeight - 20) / options::tiles - 10;

  this->x = x;
  this->y = y;
  xPos = 10 + x * width + x * 10 + 10 / 2;
  yPos = 10 + y * height + y * 10 + 10 / 2;
  color = colors::black;

  fillRect = {xPos, yPos, width, height};
}

tile::tile(SDL_Renderer *renderer) {
  this->renderer = renderer;
  value = 0;
  width = (options::screenWidth - 20) / options::tiles - 10;
  height = (options::screenHeight - 20) / options::tiles - 10;

  x = 0;
  y = 0;
  xPos = 10 + x * width + x * 10 + 10 / 2;
  yPos = 10 + y * height + y * 10 + 10 / 2;
  color = {0x00F, 0x00, 0x00, 0xFF};

  fillRect = {xPos, yPos, width, height};
}

void tile::setX(int x) {
  this->x = x;
  // cout << this->x << endl;
  xPos = 10 + x * width + x * 10 + 10 / 2;
  fillRect = {xPos, yPos, width, height};
}

void tile::setY(int y) {
  this->y = y;
  // cout << this->y << endl;
  yPos = 10 + y * width + y * 10 + 10 / 2;
  fillRect = {xPos, yPos, width, height};
}

void tile::refresh_render() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &fillRect);
  SDL_RenderPresent(renderer);
}
void tile::render() {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &fillRect);
}

void tile::set_value(int value) {
  this->value = value;
  set_color(value);
}
void tile::set_color(int value) {
  switch (value) {
  case 0:
    color = colors::black;
    break;
  case 2:
    color = colors::red;
    break;
  case 4:
    color = colors::orange;
    break;
  case 8:
    color = colors::yellow;
    break;
  case 16:
    color = colors::green;
    break;
  case 32:
    color = colors::blue;
    break;
  case 64:
    color = colors::indigo;
    break;
  case 128:
    color = colors::violet;
    break;
  }
}

void tile::tile_up() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);
  setY(y - 1);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &fillRect);
  SDL_RenderPresent(renderer);
}

void tile::tile_down() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);
  setY(y + 1);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &fillRect);
  SDL_RenderPresent(renderer);
}

void tile::tile_left() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);
  setX(x - 1);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &fillRect);
  SDL_RenderPresent(renderer);
}

void tile::tile_right() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);
  setX(x + 1);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &fillRect);
  SDL_RenderPresent(renderer);
}
