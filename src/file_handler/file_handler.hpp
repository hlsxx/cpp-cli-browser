#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <filesystem>
#include <cstring>
#include <fstream>
#include <vector>

enum FileType {
  File,
  Directory
};

class FileHandler {
private:
  std::filesystem::path inputFilePath;
  std::ifstream input_file;
  std::vector<std::filesystem::path> files;

  void initFilesFromDirectoryResursive(const std::filesystem::path& folder_path);
  void print_files(std::vector<std::filesystem::path> files);
  void close_file();

  std::vector<std::filesystem::path> getFiles(std::filesystem::path inputFilePath);
  FileType validatePath(std::filesystem::path filePath);


public:
  FileHandler(std::filesystem::path inputFilePath);
  ~FileHandler();

  void print_file_data();
  std::vector<std::filesystem::path> getFiles();
};

#endif
