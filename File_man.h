#pragma once
#include <stdint.h>
#include "options.h"
#include <fstream>  // File RW
#include <iostream> // For logging to console
#include <unistd.h>
// Using cout, endl, and from std
using std::cout;
using std::endl;

class File_man {
public:
  File_man();
  // Function declarations
  void open_file(); // Creates or opens a file to store game data to
  int read_tile(int x, int y);
  void write_tile(int x, int y, uint8_t val);
  uint64_t read_score();
  void write_score(uint64_t score);
  uint16_t read_board_size();
  void write_board_size(uint16_t);
  bool is_new_file();

  std::fstream file;
  bool newFile;
};
