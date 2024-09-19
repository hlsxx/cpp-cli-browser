#include <iostream>
#include <filesystem>
#include <cstring>
#include <string>
#include <tuple>
#include <chrono>

#include "cli_handler.hpp"
#include "search_handler.hpp"

const int SEARCH_STRING_SIZE = 128;
const int PREFIX_SIZE = 3;
const int SUFFIX_SIZE = 3;

int main(int argc, char *argv[]) {
  try {
    auto start_time = std::chrono::high_resolution_clock::now();

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

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - start_time
    );

    std::cout << "Code execution time: " << duration.count() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}

