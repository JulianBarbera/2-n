#include "SDL_io.h"
#include <cmath>

SDL_io::SDL_io(){};

int SDL_io::run() {
  if (init()) {
    cout << "Failed to initialize!" << endl;
  } else {
    quit = false;
    Tile_man_o.tile_set(renderer, font);
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
            Tile_man_o.sort(1);
            render_all();
            break;

          case SDLK_DOWN:
            cout << "SDLK_DOWN has been pressed!" << endl;
            Tile_man_o.sort(3);
            render_all();
            break;

          case SDLK_LEFT:
            cout << "SDLK_LEFT has been pressed!" << endl;
            Tile_man_o.sort(2);
            render_all();
            break;

          case SDLK_RIGHT:
            cout << "SDLK_RIGHT has been pressed!" << endl;
            Tile_man_o.sort(4);
            render_all();
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

bool SDL_io::init() {
  window = NULL;
  renderer = NULL;
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

void SDL_io::close() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;

  SDL_Quit();
  TTF_Quit();
}

void SDL_io::agg_score() {
  int score = 0;
  for (int i = 0; i < options::tiles; i++) {
    score += Tile_man_o.row_agg(i);
  }
  std::string scoreText = "Score: " + std::to_string(score * 2);
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

void SDL_io::render_all() {
  cout << "Rendering all tiles" << endl;
  Tile_man_o.add_tile();
  for (int i = 0; i < options::tiles; i++) {
    for (int j = 0; j < options::tiles; j++) {

      Tile_man_o.render_tile(i, j);
    }
  }
  SDL_io::agg_score();
  SDL_io::merge_score();
  SDL_RenderPresent(renderer);
}

void SDL_io::merge_score() {
  std::string scoreText = "Score: " + std::to_string(Tile_man_o.score);
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
