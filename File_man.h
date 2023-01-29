#pragma once
#include "options.h"
#include <fstream>  // File RW
#include <iostream> // For logging to console
// Using cout, endl, and from std
using std::cout;
using std::endl;

class File_man {
public:
  File_man();
  // Function declarations
  void open_file(); // Creates or opens a file to store game data to
  int read_tile(int x, int y);
  void write_tile(int x, int y, int val);
  int read_score();
  void write_score(int score);
  bool is_new_file();

  std::fstream file;
  bool newFile;
};
