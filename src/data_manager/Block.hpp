#pragma once

#include <string>
#include <vector>

#include "Rectangle.hpp"

namespace irt {
class Block
{
 public:
  Block() = default;
  ~Block() = default;
  // getter
  std::string get_name() const { return _name; }
  std::vector<Coordinate<double>> get_corner_list() { return _corner_list; }
  // setter
  void set_name(const std::string& name) { _name = name; }
  void set_corner_list(const std::vector<Coordinate<double>>& corner_list) { _corner_list = corner_list; }

 private:
  std::string _name;
  std::vector<Coordinate<double>> _corner_list;
};

}  // namespace irt
