#include "Router.hpp"

namespace irt
{

    Router *Router::_route_inst = nullptr;

    Router& Router::getInst(std::string& file_path)
    {
        if (_route_inst == nullptr) {
            _route_inst = new Router(file_path);
        }
        return *_route_inst;
    }

    void Router::routeNet()
    {
        // TODO
    }


    // private
    void Router::init(std::string& file_path)
    {
        _data_manager.input(file_path);
    }
}