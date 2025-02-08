#include <iostream>
#include <filesystem>
#include <cstring>
#include <string>
#include <tuple>

#include "cli_handler.hpp"
#include "search_handler.hpp"

const int SEARCH_STRING_SIZE = 128;
const int PREFIX_SIZE = 3;
const int SUFFIX_SIZE = 3;

int main(int argc, char *argv[]) {
  try {
    CliHandler cliHandler = CliHandler(SEARCH_STRING_SIZE);

    std::filesystem::path inputFilePath;
    std::string searchString;

    std::tie(inputFilePath, searchString) = cliHandler.getArguments(argc, argv);
    FileHandler fileHandler = FileHandler(inputFilePath);

    SearchHandler searchHandler = SearchHandler(
      &fileHandler,
      searchString,
      PREFIX_SIZE,
      SUFFIX_SIZE
    );
    searchHandler.startSearch();
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}

