#pragma once

#include <string>
#include <vector>

#include "Block.hpp"
#include "Orientation.hpp"
#include "Node.hpp"

namespace irt
{

    class Instance
    {
    public:
        Instance() = default;
        ~Instance() = default;
        // getter
        Block* get_block() { return _block; }
        Instance* get_child() { return _child; }
        Instance* get_parent() { return _parent; }
        std::string get_instance_name() const { return _instance_name; }
        Coordinate<double> get_coord() const { return _coord; }
        Orientation get_orien() const { return _orien; }
        // setter
        void set_block(Block* block) { _block = block; }
        void set_child(Instance* child) { _child = child; }
        void set_parent(Instance* parent) { _parent = parent; }
        void set_instance_name(const std::string& instance_name) { _instance_name = instance_name; }
        void set_coord(const Coordinate<double>& coord) { _coord = coord; }
        void set_orien(Orientation orien) { _orien = orien; }
        void set_node_list(const std::vector<Node> node_list) { _node_list = node_list; }
    private:
        Block* _block = nullptr;
        Instance* _child = nullptr;
        Instance* _parent = nullptr;
        std::string _instance_name;
        Coordinate<double> _coord;
        Orientation _orien = Orientation::kNone;
        std::vector<Node> _node_list;
        //
    };

}