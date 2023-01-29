#include "Tile_man.h"
#include "File_man.h"

Tile_man::Tile_man() { File_man_o.open_file(); };

Tile_man::Tile_man(SDL_Renderer *renderer, TTF_Font *font) {
  this->renderer = renderer;
  this->font = font;
  File_man_o.open_file();
}

void Tile_man::tile_set(SDL_Renderer *renderer, TTF_Font *font) {
  score = 0;
  cout << "Setting tiles..." << endl;
  if (File_man_o.is_new_file()) {
    for (int i = 0; i < options::tiles; i++) {
      for (int j = 0; j < options::tiles; j++) {
        tiles[i][j] = tile(renderer, font, i, j, 0); // Makes a tile object for
                                                     // each tile
      }
    }
    write_board();
  } else {
    for (int i = 0; i < options::tiles; i++) {
      for (int j = 0; j < options::tiles; j++) {
        tiles[i][j] =
            tile(renderer, font, i, j,
                 File_man_o.read_tile(i, j)); // Makes a tile object for each
        // tile
      }
    }
    score = File_man_o.read_score();
  }
}

void Tile_man::add_tile() {
  int randX = rand() % options::tiles;
  int randY = rand() % options::tiles;
  cout << "rand val = " << randX << endl;
  if (tiles[randX][randY].value == 0) {
    tiles[randX][randY].tile::set_value(2);
    overload = 0;
  } else if (overload < options::tiles * options::tiles) {
    overload++;
    add_tile();
  }
}

void Tile_man::render_tile(int x, int y) { tiles[x][y].render(); }

int Tile_man::row_agg(int row) {
  int sum = 0;
  for (int i = 0; i < options::tiles; i++) {
    sum += tiles[i][row].value;
  }
  return sum;
}

int Tile_man::col_agg(int col) {
  int sum = 0;
  for (int i = 0; i < options::tiles; i++) {
    sum += tiles[col][i].value;
  }
  return sum;
}

void Tile_man::sort(int direction) {
  // 1 up, 2 left, 3 down, options::tiles right
  switch (direction) {

  case 1:
    for (int i = 0; i < options::tiles; i++) {
      if (col_agg(i)) {
        for (int j = 0; j < options::tiles; j++) {
          for (int k = 0; k < options::tiles - 1; k++) {
            if (tiles[i][k].value == tiles[i][k + 1].value) {
              tiles[i][k].tile::set_value(tiles[i][k].value * 2);
              tiles[i][k + 1].tile::set_value(0);
              score += tiles[i][k].value;
            } else if (tiles[i][k].value == 0 && tiles[i][k + 1].value > 0) {
              tiles[i][k].tile::set_value(tiles[i][k + 1].value);
              tiles[i][k + 1].tile::set_value(0);
            }
          }
        }
      }
    }

    break;

  case 2:
    for (int i = 0; i < options::tiles; i++) {
      if (row_agg(i)) {
        for (int j = 0; j < options::tiles; j++) {
          for (int k = 0; k < options::tiles - 1; k++) {
            if (tiles[k][i].value == tiles[k + 1][i].value) {
              tiles[k][i].tile::set_value(tiles[k][i].value * 2);
              tiles[k + 1][i].tile::set_value(0);
              score += tiles[k][i].value;
            } else if (tiles[k][i].value == 0 && tiles[k + 1][i].value > 0) {
              tiles[k][i].tile::set_value(tiles[k + 1][i].value);
              tiles[k + 1][i].tile::set_value(0);
            }
          }
        }
      }
    }
    break;

  case 3:
    for (int i = 0; i < options::tiles; i++) {
      if (col_agg(i)) {
        for (int j = 0; j < options::tiles; j++) {
          for (int k = 0; k < options::tiles - 1; k++) {
            if (tiles[i][options::tiles - 1 - k].value ==
                tiles[i][options::tiles - 1 - k - 1].value) {
              tiles[i][options::tiles - k - 1].tile::set_value(
                  tiles[i][options::tiles - k - 1].value * 2);
              tiles[i][options::tiles - 1 - k - 1].tile::set_value(0);
              score += tiles[i][options::tiles - 1 - k].value;
            } else if (tiles[i][options::tiles - 1 - k].value == 0 &&
                       tiles[i][options::tiles - 1 - k - 1].value > 0) {
              tiles[i][options::tiles - 1 - k].tile::set_value(
                  tiles[i][options::tiles - 1 - k - 1].value);
              tiles[i][options::tiles - 1 - k - 1].tile::set_value(0);
            }
          }
        }
      }
    }
    break;

  case 4:
    for (int i = 0; i < options::tiles; i++) {
      if (row_agg(i)) {
        for (int j = 0; j < options::tiles; j++) {
          for (int k = 0; k < options::tiles - 1; k++) {
            if (tiles[options::tiles - 1 - k][i].value ==
                tiles[options::tiles - 1 - k - 1][i].value) {
              tiles[options::tiles - k - 1][i].tile::set_value(
                  tiles[options::tiles - k - 1][i].value * 2);
              tiles[options::tiles - 1 - k - 1][i].tile::set_value(0);
              score += tiles[options::tiles - 1 - k][i].value;
            } else if (tiles[options::tiles - 1 - k][i].value == 0 &&
                       tiles[options::tiles - 1 - k - 1][i].value > 0) {
              tiles[options::tiles - 1 - k][i].tile::set_value(
                  tiles[options::tiles - 1 - k - 1][i].value);
              tiles[options::tiles - 1 - k - 1][i].tile::set_value(0);
            }
          }
        }
      }
    }
    break;

  default:
    break;
  }
  write_board();
}

void Tile_man::add_score(int val) {
  cout << "Adding " << val << " to score" << endl;
  score += val;
}

void Tile_man::write_board() {
  File_man_o.write_score(score);
  for (int i = 0; i < options::tiles; i++) {
    for (int j = 0; j < options::tiles; j++) {
      File_man_o.write_tile(i, j, tiles[i][j].value);
    }
  }
}
