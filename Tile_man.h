#pragma once
#include "File_man.h"
#include "tile.h" // Class for each tile
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
class Tile_man {
public:
  Tile_man();
  Tile_man(SDL_Renderer *renderer, TTF_Font *font);
  void tile_set(SDL_Renderer *renderer, TTF_Font *font,
                int argBoardSize); // Sets the data for each tile
  void add_tile();                 // Makes a random tile with a value of 2
  void render_tile(int x, int y);
  int row_agg(int row);     // Finds the aggregate of a row
  int col_agg(int col);     // Finds the aggregate of a collumn
  void sort(int direction); // Sorts the board in a direction, as well as
                            // squashes when necissary
  void write_board();
  void add_score(int val);
  tile tiles[32][32]; // Object array to store the game board
  uint16_t boardSize;
  int overload;   // Used to stop the rng
  uint64_t score; // Stores the merge score
  SDL_Renderer *renderer;
  TTF_Font *font;

  File_man File_man_o;
};
