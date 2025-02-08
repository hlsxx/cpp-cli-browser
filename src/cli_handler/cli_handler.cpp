#include <iostream>
#include <filesystem>
#include <cstring>
#include <string>
#include <fstream>
#include <stdexcept>
#include <tuple>
#include <vector>

#include "cli_handler.hpp"

CliHandler::CliHandler(int searchStringSize) {
  this->searchStringSize = searchStringSize;
}

std::tuple<std::filesystem::path, std::string> CliHandler::getArguments(int argc, char *argv[]) {
  if (argc < 3) {
    throw std::runtime_error("Not enough number of aguments, required 2(file path, search string)");
  }

  size_t searchStringSize = std::strlen(argv[2]);

  if (searchStringSize > this->searchStringSize) {
    throw std::runtime_error("The maximum length of the search word is " + std::to_string(this->searchStringSize) + " characters!");
  }

  std::get<0>(this->arguments) = argv[1];
  std::get<1>(this->arguments) = argv[2];

  return this->arguments;
}
