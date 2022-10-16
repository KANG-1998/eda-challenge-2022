#pragma once

#include "Instance.hpp"

namespace irt {
class Node
{
 public:
  Node() = default;
  ~Node() = default;
  // getter
  std::string get_node_name() { return _node_name; }
  Coordinate<double> get_coord() { return _coord; }
  // setter
  void set_node_name(const std::string& node_name) { _node_name = node_name; }
  void set_coord(const Coordinate<double>& coord) { _coord = coord; }

 private:
  // Instance* _instance = nullptr;
  std::string _node_name;
  Coordinate<double> _coord;
};

}  // namespace irt