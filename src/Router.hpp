#pragma once

#include <string>
#include "DataManager.hpp"

namespace irt{
class Router{
    public:
     static Router& getInst(std::string& file_path);
     void routeNet();
     
    private:
     static Router* _route_inst;
     DataManager _data_manager;
     // function
     Router(std::string& file_path) { init(file_path); }
     ~Router() = default;

     void init(std::string& file_path);
};
}