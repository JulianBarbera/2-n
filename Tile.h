#include <SDL2/SDL.h>
#include <iostream>
using std::cout;
using std::endl;

class Tile {
public:
  int value;
  int x;
  int y;
  int xPos;
  int yPos;
  SDL_Rect fillRect;
  SDL_Color color;

  Tile(int x, int y);
  Tile();

  void setX(int x);
  void setY(int y);

private:
  int width;
  int height;
};
