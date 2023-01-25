#include "tile.h"     // Class for each tile
#include <SDL2/SDL.h> // Simple Direct media Layer, for the window and graphics
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream> // For logging to console
#include <time.h>   // For random seeding
#include <unistd.h> // Sleep

// Using cout, endl, and from std
using std::cout;
using std::endl;

tile tiles[options::tiles]
          [options::tiles]; // Object array to store the game board
int overload = 0;           // Used to stop the rng
int score = 0;              // Stores the merge score
TTF_Font *font;

// Function declarations
bool init();              // Initialized SDL
void close();             // Shuts down SDL
void agg_score();         // Calculates and displayes total aggregate score
void merge_score();       // Calculates and displays aggregate of merge values
void tile_set();          // Sets the data for each tile
void add_tile();          // Makes a random tile with a value of 2
int row_agg(int row);     // Finds the aggregate of a row
int col_agg(int col);     // Finds the aggregate of a collumn
void sort(int direction); // Sorts the board in a direction, as well as squashes
                          // when necissary
void render_all();        // Renders all tiles

// Key press surface constants
enum keyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL,
};

SDL_Window *window = NULL;     // The window
SDL_Renderer *renderer = NULL; // The renderer

bool quit = false; // Main loop flag

SDL_Event e; // Event handler

bool init() {
  srand(time(NULL)); // Seeds the RNG with the current time
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize! SDL_Error:\n" << SDL_GetError() << endl;
  } else {
    // Create the window
    window = SDL_CreateWindow("2^n", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, options::screenWidth,
                              options::screenHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      cout << "Window could not be created! SDL_Error:\n"
           << SDL_GetError() << endl;
      return 1;
    } else {
      // Create the renderer
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      if (renderer == NULL) {
        cout << "Renderer could not be created! SDL_Error:\n"
             << SDL_GetError() << endl;
        return 1;
      } else {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF,
                               0xFF); // Initialize renderer color
        if (TTF_Init() == -1) {
          cout << "Failed to initialize SDL TTF! TTF Error: " << TTF_GetError();
          return 1;
        } // Initializes text
        font = TTF_OpenFont("OpenSans.ttf", 72);
        if (font == NULL) {
          cout << "Failed to load TTF! TTF Error: " << TTF_GetError() << endl;
        } else {
          cout << "Font loaded!" << endl;
        }
      }
    }
  }
  return 0;
}

void close() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;

  SDL_Quit();
  TTF_Quit();
}

void agg_score() {
  int score = 0;
  for (int i = 0; i < options::tiles; i++) {
    score += row_agg(i);
  }
  std::string scoreText = "Score: " + std::to_string(score);
  SDL_Surface *textSurface = TTF_RenderText_Shaded(
      font, scoreText.c_str(), colors::white, colors::black);
  if (textSurface == NULL) {
    cout << "Failed to create surface from text! TTF Error: " << TTF_GetError()
         << endl;
  } else {
    SDL_Texture *textTexture =
        SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textSurface == NULL) {
      cout << "Failed to create texture from surface! TTF Error: "
           << TTF_GetError() << endl;
    } else {
      SDL_Rect textRect = {5, 0, textSurface->w / 2, textSurface->h / 2};
      SDL_FreeSurface(textSurface);
      SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(renderer, &textRect);
      SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    }
  }
}

void merge_score() {
  std::string scoreText = "Score: " + std::to_string(score);
  SDL_Surface *textSurface = TTF_RenderText_Shaded(
      font, scoreText.c_str(), colors::white, colors::black);
  if (textSurface == NULL) {
    cout << "Failed to create surface from text! TTF Error: " << TTF_GetError()
         << endl;
  } else {
    SDL_Texture *textTexture =
        SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textSurface == NULL) {
      cout << "Failed to create texture from surface! TTF Error: "
           << TTF_GetError() << endl;
    } else {
      SDL_Rect textRect = {options::screenWidth - textSurface->w / 2 - 5, 0,
                           textSurface->w / 2, textSurface->h / 2};
      SDL_FreeSurface(textSurface);
      SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(renderer, &textRect);
      SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    }
  }
}
void tile_set() {
  cout << "Setting tiles..." << endl;
  // Runs through each tile
  for (int i = 0; i < options::tiles; i++) {
    for (int j = 0; j < options::tiles; j++) {
      tiles[i][j] =
          tile(renderer, font, i, j); // Makes a tile object for each tile
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
              score += tiles[i][k].value * 2;
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
              score += tiles[i][k].value * 2;
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
              score += tiles[i][k].value * 2;
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
              score += tiles[i][k].value * 2;
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
  agg_score();
  merge_score();
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
      usleep(10000);
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
          case SDLK_UP:
            cout << "SDLK_UP has been pressed!" << endl;
            sort(1);
            break;

          case SDLK_DOWN:
            cout << "SDLK_DOWN has been pressed!" << endl;
            sort(3);
            break;

          case SDLK_LEFT:
            cout << "SDLK_LEFT has been pressed!" << endl;
            sort(2);
            break;

          case SDLK_RIGHT:
            cout << "SDLK_RIGHT has been pressed!" << endl;
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
