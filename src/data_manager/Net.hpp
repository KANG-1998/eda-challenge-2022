#pragma once

#include "Node.hpp"
#include "Segment.hpp"

namespace irt {
class Net
{
 public:
  Net() = default;
  ~Net() = default;
  // getter
  std::string get_start_node_name() { return _start_node_name; }
  std::string get_end_node_name() { return _end_node_name; }
  std::vector<Segment>& get_segment_list() { return _segment_list; }
  // setter
  void set_start_node_name(std::string start_node_name) { _start_node_name = start_node_name; }
  void set_end_node_name(std::string end_node_name) { _end_node_name = end_node_name; }
 private:
  std::string _start_node_name;
  std::string _end_node_name;
  // process data
  std::vector<Segment> _segment_list;
};
}  // namespace irt