#pragma once
#include <string>
namespace irt
{

#define kNone 0
#define kString 1
#define kDouble 2
#define kBlock 3
#define kInstance 4
#define kNet 5
#define kNode 6
#define kSegment 7
#define KCoordinate 8
    class parse
    {
    private:
        std::string _name;
        double _value;

    public:
        parse(){};
        ~parse(){};

        // fuction
        void parsedata(const std::ifstream &reader);
        std::ifstream parseDouble(const std::ifstream &reader);
        std::ifstream parseString(const std::ifstream &reader);
        std::ifstream parseBlock(const std::ifstream &reader);
        std::ifstream parseInstance(const std::ifstream &reader);
        std::ifstream parseNet(const std::ifstream &reader);
        std::ifstream parseNode(const std::ifstream &reader);
        std::ifstream parseSegment(const std::ifstream &reader);
        std::ifstream parseCoordinate(const std::ifstream &reader);
    };

}