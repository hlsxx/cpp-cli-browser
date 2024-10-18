#include <iostream>
#include <filesystem>
#include <cstring>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "file_handler.hpp"

std::vector<std::filesystem::path> FileHandler::getFiles(std::filesystem::path inputFilePath) {
  switch (this->validatePath(inputFilePath)) {
    case FileType::File: 
      this->files.push_back(inputFilePath);
      break;
    case FileType::Directory: 
      this->initFilesFromDirectoryResursive(inputFilePath); 
      break;
  }

  return this->files;
}

void FileHandler::initFilesFromDirectoryResursive(
  const std::filesystem::path& folder_path
) {
  try {
    for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
      if (std::filesystem::is_regular_file(entry)) {
        this->files.push_back(entry.path());
      } else if (std::filesystem::is_directory(entry)) {
        this->initFilesFromDirectoryResursive(entry);
      }
    }
  } catch (const std::filesystem::filesystem_error& ex) {
    std::cerr << "Error traversing directory: " << ex.what() << '\n';
  }
}

void FileHandler::print_files(std::vector<std::filesystem::path> files) {
  for(std::filesystem::path file: files) {
    std::cout << "Found file: " << file << "\n";
  }
}

void FileHandler::close_file() {
  this->input_file.close();
}

FileType FileHandler::validatePath(std::filesystem::path filePath) {
  if (!std::filesystem::exists(filePath)) {
    throw std::runtime_error("File or folder doesn't exist");
  } 

  if (std::filesystem::is_regular_file(filePath)) {
    return FileType::File;
  }

  if (std::filesystem::is_directory(filePath)) {
    return FileType::Directory;
  }

  throw std::runtime_error("Unknown error while validating file path");
}

FileHandler::FileHandler(std::filesystem::path inputFilePath) {
  this->getFiles(inputFilePath);
}

FileHandler::~FileHandler() {
  this->close_file();
}

void FileHandler::print_file_data() {
  std::string input_line;

  while (this->input_file.good()) {
    input_line = this->input_file.get();
    std::cout << input_line;
  }

  if (!this->input_file.eof() && !this->input_file) {
    throw std::runtime_error("Error while reading from file");
  }

  this->input_file.clear();
  this->input_file.seekg(0, std::ios::beg);
}

std::vector<std::filesystem::path> FileHandler::getFiles() {
  return std::move(this->files);
}

