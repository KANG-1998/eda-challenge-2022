#pragma once

#include <map>

#include "Block.hpp"
#include "Instance.hpp"
#include "Net.hpp"
#include "Segment.hpp"

namespace irt {
class Database
{
 public:
  // setter
  void set_width(const double width) { _width = width; }
  void set_height(const double height) { _height = height; }
  void set_spacing(const double spacing) { _spacing = spacing; }
  void set_net_list(const std::vector<Net>& list) { _net_list = list; }
  void set_block_list(const std::vector<Block>& list) { _block_list = list; }
  void set_instance_list(const std::vector<Instance>& list) { _instance_list = list; }
  // getter
  double get_width() const { return _width; }
  double get_height() const { return _height; }
  double get_spacing() const { return _spacing; }
  std::vector<Net>& get_net_list() { return _net_list; }
  std::vector<Block>& get_block_list() { return _block_list; }
  std::vector<Instance>& get_instance_list() { return _instance_list; }
  std::vector<Node>& get_node_list() { return _node_list; }
  std::map<std::string, Node*>& get_name_node_map() { return _name_node_map; }
  // add
  void addNet(const Net& n) { _net_list.push_back(n); }
  void addBlock(const Block& b) { _block_list.push_back(b); }
  void addInstance(const Instance& in) { _instance_list.push_back(in); }


 private:
  double _width = -1;
  double _height = -1;
  double _spacing = -1;
  std::vector<Net> _net_list;
  std::vector<Block> _block_list;
  std::vector<Instance> _instance_list;
  std::vector<Node> _node_list;

  std::map<std::string, Instance*> _name_instance_map;
  std::map<std::string, Node*> _name_node_map;
};
}  // namespace irt