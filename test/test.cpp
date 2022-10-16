#include "Logger.hpp"
#include "Router.hpp"
using namespace irt;

int main(int argc, char** argv)
{
  std::string config_path;
  if (argc == 2) {
    config_path = argv[1];
  } else {
    LogInst.error(Loc::current(), "Param num is wrong!!!");
  }
  Router& router = Router::getInst(config_path);

  return 0;
}