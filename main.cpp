// Using SDL and standard IO
#include "tile.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
using std::cout;
using std::endl;
using std::string;

// Object array to store the game board
tile tiles[options::tiles][options::tiles];
int overload = 0;
// Function declarations
bool init();
void close();
void tile_set();
void add_tile();
int row_agg(int row);
int col_agg(int col);
void sort(int direction);
void render_all();

// Key press surface constants
enum keyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL,
};

SDL_Window *window = NULL; // The window
SDL_Renderer *renderer = NULL;

bool quit = false; // Main loop flag

SDL_Event e; // Event handler

bool init() {
  srand(time(NULL));
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize! SDL_Error:\n" << SDL_GetError() << endl;
  } else {
    // Create the window
    window = SDL_CreateWindow("n^2", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, options::screenWidth,
                              options::screenHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      cout << "Window could not be created! SDL_Error:\n"
           << SDL_GetError() << endl;
      return 1;
    } else {
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      if (renderer == NULL) {
        cout << "Renderer could not be created! SDL_Error:\n"
             << SDL_GetError() << endl;
        return 1;
      } else {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF,
                               0xFF); // Initialize renderer color
      }
    }
  }
  return 0;
}

void close() {
  // Destroy window
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

void tile_set() {
  cout << "Setting tiles..." << endl;
  for (int i = 0; i < options::tiles; i++) {
    for (int j = 0; j < options::tiles; j++) {
      tiles[i][j] = tile(renderer, i, j);
    }
  }
}

void add_tile() {
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

int row_agg(int row) {
  int sum = 0;
  for (int i = 0; i < options::tiles; i++) {
    sum += tiles[i][row].value;
  }
  return sum;
}

int col_agg(int col) {
  int sum = 0;
  for (int i = 0; i < options::tiles; i++) {
    sum += tiles[col][i].value;
  }
  return sum;
}

void sort(int direction) {
  // Switch doesnt work well with strings, so direction is an int
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
            } else if (tiles[i][k].value == 0 && tiles[i][k + 1].value > 0) {
              tiles[i][k].tile::set_value(tiles[i][k + 1].value);
              tiles[i][k + 1].tile::set_value(0);
            }
          }
        }
      }
    }
    render_all();

    break;

  case 2:
    for (int i = 0; i < options::tiles; i++) {
      if (row_agg(i)) {
        for (int j = 0; j < options::tiles; j++) {
          for (int k = 0; k < options::tiles - 1; k++) {
            if (tiles[k][i].value == tiles[k + 1][i].value) {
              tiles[k][i].tile::set_value(tiles[k][i].value * 2);
              tiles[k + 1][i].tile::set_value(0);
            } else if (tiles[k][i].value == 0 && tiles[k + 1][i].value > 0) {
              tiles[k][i].tile::set_value(tiles[k + 1][i].value);
              tiles[k + 1][i].tile::set_value(0);
            }
          }
        }
      }
    }
    render_all();
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
    render_all();
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
    render_all();
    break;

  default:
    break;
  }
}

void render_all() {
  cout << "Rendering all tiles" << endl;
  add_tile();
  for (int i = 0; i < options::tiles; i++) {
    for (int j = 0; j < options::tiles; j++) {
      tiles[i][j].render();
    }
  }
  SDL_RenderPresent(renderer);
}

int main(int argc, char *args[]) {
  if (init()) {
    cout << "Failed to initialize!" << endl;
  } else {
    bool quit = false;
    SDL_Event e;

    tile_set();
    render_all();

    while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
          case SDLK_UP:
            cout << "SDLK_UP has been pressed!" << endl;
            sort(1);
            // tiles[0][0].tile::tile_up();
            break;

          case SDLK_DOWN:
            cout << "SDLK_DOWN has been pressed!" << endl;
            sort(3);
            // tiles[0][0].tile::tile_down();
            break;

          case SDLK_LEFT:
            cout << "SDLK_LEFT has been pressed!" << endl;
            // tiles[0][0].tile::tile_left();
            sort(2);
            break;

          case SDLK_RIGHT:
            cout << "SDLK_RIGHT has been pressed!" << endl;
            // tiles[0][0].tile::tile_right();
            sort(4);
            break;

          default:
            break;
          }
        }
      }
    }
  }
  close();
  return 0;
}
