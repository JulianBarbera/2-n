#include "Tile.h"

Tile::Tile(int x, int y) {
  value = 2;
  width = (360 - 20) / 4 - 10;
  height = (360 - 20) / 4 - 10;

  x = x;
  y = y;
  xPos = 10 + x * width + x * 10 + 10 / 2;
  yPos = 10 + y * height + y * 10 + 10 / 2;
  color = {0xFF, 0x00, 0xFF};

  fillRect = {xPos, yPos, width, height};
}

Tile::Tile() {
  value = 2;
  width = (360 - 20) / 4 - 10;
  height = (360 - 20) / 4 - 10;

  x = 0;
  y = 0;
  xPos = 10 + x * width + x * 10 + 10 / 2;
  yPos = 10 + y * height + y * 10 + 10 / 2;
  color = {0xFF, 0x00, 0xFF};

  fillRect = {xPos, yPos, width, height};
}

void Tile::setX(int x) {
  this->x = x;
  // cout << this->x << endl;
  xPos = 10 + x * width + x * 10 + 10 / 2;
  fillRect = {xPos, yPos, width, height};
}

void Tile::setY(int y) {
  this->y = y;
  // cout << this->y << endl;
  yPos = 10 + y * width + y * 10 + 10 / 2;
  fillRect = {xPos, yPos, width, height};
}
