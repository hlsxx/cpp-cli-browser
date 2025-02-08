#include <iostream>
#include <filesystem>
#include <cstring>
#include <string>
#include <thread>
#include <vector>
#include <mutex>

#include "file_handler.hpp"

class SearchHandler {
private:
  size_t prefixSize;
  size_t suffixSize;
  FileHandler *fileHandler;
  std::string search;
  std::vector<std::thread> threads;
  uint8_t numThreads = std::thread::hardware_concurrency();

public:
  SearchHandler(FileHandler *fileHandler, std::string search, uint8_t prefixSize, uint8_t suffixSize);

  void startSearch();
  static void searchInFile(std::mutex &coutMutex, std::filesystem::path filePath, std::string search);

  static void searchInFileBuffer(
    std::mutex &coutMutex,
    std::filesystem::path filePath,
    std::string search,
    uint8_t prefixSize,
    uint8_t suffixSize
  );

  static std::string escape(std::string &s);
};

