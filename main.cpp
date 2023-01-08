// Using SDL and standard IO
#include "Tile.h"
#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_render.h>
#include <iostream>
using std::cout;
using std::endl;

// Screen dimentions
const int screenWidth = 360;
const int screenHeight = 360;

// Function declarations
bool init();
void close();

// Key press surface constants
enum keyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL,
};

SDL_Window *window = NULL;                              // The window
SDL_Surface *keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL]; // Images cooresponding
                                                        // to keypresses
SDL_Renderer *renderer = NULL;

bool quit = false; // Main loop flag

SDL_Event e; // Event handler

bool init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize! SDL_Error:\n" << SDL_GetError() << endl;
  } else {
    // Create the window
    window = SDL_CreateWindow("n^2", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, screenWidth,
                              screenHeight, SDL_WINDOW_SHOWN);
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

int main(int argc, char *args[]) {
  if (init()) {
    cout << "Failed to initialize!" << endl;
  } else {
    bool quit = false;
    SDL_Event e;
    // currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

    Tile tile[16];
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
    int t = 0;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        tile[t].setX(i);
        tile[t].setY(j);
        t++;
      }
    }

    for (int i = 0; i <= 15; i++) {
      SDL_RenderFillRect(renderer, &tile[i].fillRect);
    }

    SDL_RenderPresent(renderer);
    while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
          case SDLK_UP:
            // currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
            cout << "SDLK_UP has been pressed!" << endl;
            break;

          case SDLK_DOWN:
            // currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
            cout << "SDLK_DOWN has been pressed!" << endl;
            break;

          case SDLK_LEFT:
            // currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
            cout << "SDLK_LEFT has been pressed!" << endl;
            break;

          case SDLK_RIGHT:
            // currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
            cout << "SDLK_RIGHT has been pressed!" << endl;
            break;

          default:
            // currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            break;
          }
        }
      }
    }
    // }
  }
  close();
  return 0;
}
