#include "loader.h"
#include "renderer.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<WavetableRow> Loader::load(std::string filename) {
  std::ifstream file(filename.c_str());
  std::string line;
  std::vector<WavetableRow> rows;

  while (std::getline(file, line)) {
    WavetableRow row;
    row.freq = parseValue(line, 0, 4);
    row.waveform = parseValue(line, 6, 2);
    row.adsr = parseValue(line, 10, 4);
    row.pulse = parseValue(line, 16, 3);
    row.cutoff = parseValue(line, 20, 4);
    row.resonance = parseValue(line, 26, 2);
    row.mode = parseValue(line, 30, 1);
    rows.push_back(row);
  }

  return rows;
}

int Loader::parseValue(std::string line, int start, int length) {
  try {
    std::string value = line.substr(start, length);
    return std::stoi(value, 0, 16);
  } catch (...) {
    return WavetableRow::EMPTY;
  }
}
