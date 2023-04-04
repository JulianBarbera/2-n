#include "File_man.h"
#include "SDL_io.h"
#include <args.hxx>
#include <cstdint>
#include <string>

int main(int argc, char **args) {
  args::ArgumentParser parser("2n - A very large 2048 clone",
                              "2n Dev by Julian Barbera");
  args::HelpFlag help(parser, "help", "Display this help menue", {'h', "flag"});
  args::ValueFlag<uint64_t> newGame(
      parser, "size", "Makes a new game with a specific board size",
      {'n', "new"});
  args::CompletionFlag completion(parser, {"complete"});

  try {
    parser.ParseCLI(argc, args);
  } catch (args::Help) {
    std::cout << parser;
  } catch (args::ParseError e) {
    std::cerr << e.what() << std::endl;
    std::cerr << parser;
    return 1;
  } catch (args::ValidationError e) {
    std::cerr << e.what() << std::endl;
    std::cerr << parser;
    return 1;
  }

  if (newGame) {
    cout << "New game with size " << args::get(newGame) << endl;
    system("rm 2nData.dat");
  }

  SDL_io SDL_io_o;
  return SDL_io_o.run(args::get(newGame));
}
