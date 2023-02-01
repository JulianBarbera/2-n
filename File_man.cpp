#include "File_man.h"
#include <cstdint>
#include <ios>

File_man::File_man() {
  cout << "setting new file false..." << endl;
  newFile = false;
};

void File_man::open_file() {
  file.open("2nData.dat", std::ios::in | std::ios::binary | std::ios::out);
  if (file.is_open()) {
    cout << "File opened succesfully!" << endl;
  } else {
    cout << "Making new save file..." << endl;
    std::ofstream file("2nData.dat");
    cout << "setting new file true..." << endl;

    newFile = true;
    open_file();
  }
}

int File_man::read_tile(int x, int y) {
  file.seekg((x * options::tiles + y) + 8);
  int buffer;
  file.read((char *)&buffer, 1);
  cout << "Read " << buffer << " at (" << x << "," << y << ")" << endl;
  return buffer;
}

void File_man::write_tile(int x, int y, uint8_t val) {
  int pos = (x * options::tiles + y) + 8;
  file.seekp(pos);
  cout << "Writing " << val << " to " << pos << " with size of " << sizeof(val)
       << endl;
  file.write((char *)&val, sizeof(val));
}

bool File_man::is_new_file() {
  cout << "New file? " << newFile << endl;
  return newFile;
}

void File_man::write_score(uint64_t score) {
  int pos = 0;
  file.seekp(pos);
  cout << "writing " << score << " as " << (char *)&score << " to " << pos
       << " with size of " << sizeof(score) << endl;
  file.write((char *)&score, sizeof(score));
}

uint64_t File_man::read_score() {
  file.seekg(0);
  cout << "Reading score..." << endl;
  int buffer;
  file.read((char *)&buffer, 8);
  cout << "Read score as " << (uint64_t)buffer << endl;
  return buffer;
}
