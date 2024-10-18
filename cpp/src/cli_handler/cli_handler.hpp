#ifndef CLI_HANDLER_H
#define CLI_HANDLER_H

#include <filesystem>

class CliHandler {

private:
  int searchStringSize;
  std::tuple<std::filesystem::path, std::string> arguments;

public:
  CliHandler(int searchStringSize);
  std::tuple<std::filesystem::path, std::string> getArguments(int argc, char *argv[]);

};

#endif

