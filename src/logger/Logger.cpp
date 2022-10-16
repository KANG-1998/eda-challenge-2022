#include "Logger.hpp"

namespace irt {

// public

// Logger& Logger::initInst()
// {
//   if (_log_instance == nullptr) {
//     _log_instance = new Logger();
//   }
//   return *_log_instance;
// }

Logger& Logger::getInst()
{
  if (_log_instance == nullptr) {
    _log_instance = new Logger();
  }
  return *_log_instance;
}

void Logger::destroyInst()
{
  if (_log_instance != nullptr) {
    delete _log_instance;
    _log_instance = nullptr;
  }
}
void Logger::setLogVerbose(int log_verbose)
{
  _log_verbose = log_verbose;
}

void Logger::openLogFileStream(std::string log_file_path)
{
  _log_file = new std::ofstream(log_file_path);
}

void Logger::closeLogFileStream()
{
  if (_log_file != nullptr) {
    _log_file->close();
  }
}

// private

Logger* Logger::_log_instance = nullptr;

}  // namespace irt
