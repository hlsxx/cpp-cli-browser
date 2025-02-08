#include <iostream>
#include <filesystem>
#include <cstring>
#include <string>
#include <fstream>
#include <stdexcept>
#include <thread>
#include <vector>
#include <mutex>

#include "search_handler.hpp"

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36;1m"

SearchHandler::SearchHandler(FileHandler *fileHandler, std::string search, uint8_t prefixSize, uint8_t suffixSize) {
  this->fileHandler = fileHandler;
  this->search = search;
  this->prefixSize = prefixSize;
  this->suffixSize = suffixSize;
}

void SearchHandler::searchInFile(std::mutex &coutMutex, std::filesystem::path filePath, std::string search) {
  std::string line;
  uint16_t currentLine = 0;
  std::ifstream fileStream;

  fileStream.open(filePath);

  while(std::getline(fileStream, line)) {
    currentLine++;

    if (line.find(search) != std::string::npos) {
      std::lock_guard<std::mutex> lock(coutMutex);  
      std::cout << filePath << "(" << currentLine << "): " << search << " Thread: " << std::this_thread::get_id() << std::endl;
    }
  }

  if (!fileStream.eof() && !fileStream) {
    throw std::runtime_error("Error while reading from file");
  }

  //fileStream.clear();
  //fileStream.seekg(0, std::ios::beg);

  fileStream.close();
}

void SearchHandler::searchInFileBuffer(
  std::mutex &coutMutex,
  std::filesystem::path filePath,
  std::string search,
  uint8_t prefixSize,
  uint8_t suffixSize
) {
  std::string line;
  uint16_t currentLine = 0;
  std::ifstream fileStream;

  size_t bufferSize = 1024;
  char buffer[bufferSize];

  size_t searchSize = search.size();
  size_t offset = 0;
  std::string prefix = "";
  std::string suffix = "";

  fileStream.open(filePath);

  while (!fileStream.eof()) {
    fileStream.read(buffer, bufferSize);
    size_t bytesRead = fileStream.gcount();

    for (size_t i = 0; i < bytesRead; ++i) {
      if (buffer[i] == search[0] && search == std::string(&buffer[i], searchSize)) {
        size_t start = std::max(0, int(i) - int(prefixSize));

        prefix = std::string(&buffer[i - prefixSize], prefixSize);
        suffix = std::string(&buffer[i + searchSize], suffixSize);

        std::lock_guard<std::mutex> lock(coutMutex);

        std::string foundString = prefix + search + suffix;

        std::cout << GREEN << filePath << RESET
          << "(" << YELLOW << i << RESET << "): "
          << CYAN << foundString << RESET 
          << std::endl;
      }
    }

    offset += bytesRead;
  }

  if (!fileStream.eof() && !fileStream) {
    throw std::runtime_error("Error while reading from file");
  }
  //fileStream.clear(); fileStream.seekg(0, std::ios::beg);
  fileStream.close();
}

std::string SearchHandler::escape(std::string &s) {
  std::string escapedString;

  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '\t') escapedString += "\\t";
    else if (s[i] == '\n') escapedString += "\\n";
    else escapedString += s[i];
  }

  return escapedString;
}

void SearchHandler::startSearch() {
  std::vector<std::filesystem::path> files = this->fileHandler->getFiles();
  std::mutex coutMutex; 

  for (const auto& filePath: files) {
    this->threads.emplace_back(
      SearchHandler::searchInFileBuffer,
      std::ref(coutMutex),
      filePath, 
      this->search,
      this->prefixSize,
      this->suffixSize
    );
  }

  for (auto& thread : this->threads) {
    thread.join();
  }
}

