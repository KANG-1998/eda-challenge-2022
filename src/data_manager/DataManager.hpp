#pragma once

#include "DataType.hpp"
#include "Config.hpp"
#include "Database.hpp"

namespace irt
{
class DataManager
{
public:
    DataManager() = default;
    ~DataManager() = default;
    // function
    void input(const std::string& file_path);
    // TODO
private:
    Config _config;
    Database _database;
    // function
    void initConfig(const std::string& file_path);
    void initDatabase(const std::string& file_path);
    DataType getDataType(std::string& line);
    void wrapConstraints(std::string& line);
    void wrapBlockList(std::string& line, DataType data_type);
    void wrapInstanceList(std::string& line, DataType data_type);
    void wrapNodeList(std::string& line, DataType data_type);
    void wrapFlyLineList(std::string& line, DataType data_type);
    Block* getBlockPtrByName(std::string& block_name);
    Orientation getOrientation(std::string& orien_str);
    Coordinate<double> getCoordinate(std::string& x, std::string& y);
    std::vector<std::string> splitLine(std::string& line);
    std::vector<std::string> splitString(std::string& string, const char split);
    std::vector<std::string> splitStringList(std::vector<std::string>& string_list, const char split);

};
}