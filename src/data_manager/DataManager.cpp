#include "DataManager.hpp"

#include "COMUtil.hpp"

namespace irt {

void DataManager::input(const std::string& file_path)
{
  initConfig(file_path);
  initDatabase(file_path);
}

// private
void DataManager::initConfig(const std::string& file_path)
{
  std::ifstream& config_stream = COMUtil::getInputFileStream(file_path);
  // json
  nlohmann::json json;
  config_stream >> json;
  // init config
  _config.set_input_file_path(COMUtil::getData(json, {"input_file_path"}));
  _config.set_output_file_path(COMUtil::getData(json, {"output_file_path"}));

  COMUtil::closeFileStream(config_stream);
}

void DataManager::initDatabase(const std::string& file_path)
{
  std::string input_file_path = _config.get_input_file_path();
  std::ifstream& config_stream = COMUtil::getInputFileStream(input_file_path);

  std::string line_data;
  DataType top_type = DataType::kNone;
  DataType curr_type = DataType::kNone;
  while (std::getline(config_stream, line_data)) {
    curr_type = getDataType(line_data);
    top_type = (curr_type != DataType::kItem) ? curr_type : top_type;

    switch (top_type) {
      case DataType::kConstraint:
        wrapConstraints(line_data);
        break;
      case DataType::kBlock:
        wrapBlockList(line_data, curr_type);
        break;
      case DataType::kInstance:
        wrapInstanceList(line_data, curr_type);
        break;
      case DataType::kNode:
        wrapNodeList(line_data, curr_type);
        break;
      case DataType::kFlyLine:
        wrapFlyLineList(line_data, curr_type);
        break;
      default:
        break;
    }
  }

  COMUtil::closeFileStream(config_stream);
}

DataType DataManager::getDataType(std::string& line)
{
  DataType data_type;

  std::vector<std::string> token_list = {line};
  token_list = splitStringList(token_list, '<');
  token_list = splitStringList(token_list, '>');

  std::string& type = token_list.front();
  if (type == "CONSTRAINTS") {
    data_type = DataType::kConstraint;
  } else if (type == "BLOCK") {
    data_type = DataType::kBlock;
  } else if (type == "INSTANCE") {
    data_type = DataType::kInstance;
  } else if (type == "NODE") {
    data_type = DataType::kNode;
  } else if (type == "FLY_LINE") {
    data_type = DataType::kFlyLine;
  } else {
    data_type = DataType::kItem;
  }
  return data_type;
}

void DataManager::wrapConstraints(std::string& line)
{
  std::vector<std::string> token_list = splitLine(line);
  if (token_list.size() != 5) {
    LogInst.error(Loc::current(), "Split line is wrong!!!");
  }

  _database.set_height(COMUtil::stringToNum<double>(token_list[1]));
  _database.set_width(COMUtil::stringToNum<double>(token_list[2]));
  _database.set_spacing(COMUtil::stringToNum<double>(token_list[3]));
}

void DataManager::wrapBlockList(std::string& line, DataType data_type)
{
  if (data_type != DataType::kItem) {
    return;
  }

  std::vector<std::string> token_list = splitLine(line);
  if (token_list.size() < 10) {
    LogInst.error(Loc::current(), "Block line is wrong!!!");
  }

  std::vector<Block>& block_list = _database.get_block_list();
  std::vector<Coordinate<double>> corner_list;
  for (size_t i = 1; i < token_list.size() - 2;) {
    int lb_x = COMUtil::stringToNum<int>(token_list[i]);
    int lb_y = COMUtil::stringToNum<int>(token_list[i + 1]);
    corner_list.emplace_back(lb_x, lb_y);

    i += 2;
  }

  Block new_block;
  new_block.set_name(token_list.front());
  new_block.set_corner_list(corner_list);

  block_list.push_back(std::move(new_block));
}

void DataManager::wrapInstanceList(std::string& line, DataType data_type)
{
  if (data_type != DataType::kItem) {
    return;
  }

  std::vector<std::string> token_list = splitLine(line);
  if (token_list.size() < 6) {
    LogInst.error(Loc::current(), "Split line is wrong!!!");
  }

  std::vector<Instance>& instance_list = _database.get_instance_list();

  Instance new_instance;
  new_instance.set_instance_name(token_list[0]);
  new_instance.set_block(getBlockPtrByName(token_list[1]));
  new_instance.set_orien(getOrientation(token_list[4]));
  new_instance.set_coord(getCoordinate(token_list[2], token_list[3]));

  instance_list.push_back(std::move(new_instance));
}

void DataManager::wrapNodeList(std::string& line, DataType data_type)
{
  if (data_type != DataType::kItem) {
    return;
  }

  std::vector<std::string> token_list = splitLine(line);
  if (token_list.size() != 4) {
    LogInst.error(Loc::current(), "Split line is wrong!!!");
  }

  std::vector<Node>& node_list = _database.get_node_list();

  Node new_node;
  new_node.set_node_name(token_list[0]);
  new_node.set_coord(getCoordinate(token_list[1], token_list[2]));
  node_list.push_back(std::move(new_node));
}

void DataManager::wrapFlyLineList(std::string& line, DataType data_type)
{
  if (data_type != DataType::kItem) {
    return;
  }

  std::vector<std::string> token_list = splitLine(line);
  if (token_list.size() != 2) {
    LogInst.error(Loc::current(), "Split line is wrong!!!");
  }

  std::vector<Net>& net_list = _database.get_net_list();

  Net new_net;
  new_net.set_start_node_name(token_list[0]);
  new_net.set_end_node_name(token_list[1]);
  net_list.push_back(std::move(new_net));
}

Block* DataManager::getBlockPtrByName(std::string& block_name)
{
  Block* block_ptr = nullptr;
  std::vector<Block>& block_list = _database.get_block_list();
  for (size_t i = 0; i < block_list.size(); i++) {
    Block& block = block_list[i];
    if (block.get_name() == block_name) {
      block_ptr = &block;
      break;
    }
  }

  if (block_ptr == nullptr) {
    LogInst.error(Loc::current(), "No name:", block_name, " block!!!");
  }

  return block_ptr;
}

Orientation DataManager::getOrientation(std::string& orien_str)
{
  Orientation orien;
  if (orien_str == "R0") {
    orien = Orientation::kR0;
  } else if (orien_str == "R180") {
    orien = Orientation::kR180;
  } else if (orien_str == "MX") {
    orien = Orientation::kMX;
  } else if (orien_str == "MY") {
    orien = Orientation::kMY;
  } else {
    orien = Orientation::kNone;
  }

  return orien;
}

Coordinate<double> DataManager::getCoordinate(std::string& x_string, std::string& y_string)
{
  return Coordinate<double>(COMUtil::stringToNum<double>(x_string), COMUtil::stringToNum<double>(y_string));
}

std::vector<std::string> DataManager::splitLine(std::string& line)
{
  std::vector<std::string> token_list = {line};
  token_list = splitStringList(token_list, ' ');
  token_list = splitStringList(token_list, '<');
  token_list = splitStringList(token_list, '>');
  token_list = splitStringList(token_list, '{');
  token_list = splitStringList(token_list, '}');
  token_list = splitStringList(token_list, '\r');

  return token_list;
}

std::vector<std::string> DataManager::splitString(std::string& string, const char split)
{
  std::vector<std::string> token_list;

  std::istringstream iss(string);
  std::string token;
  while (getline(iss, token, split)) {
    if (token == "") {
      continue;
    }
    token_list.push_back(token);
  }
  iss.clear();

  return token_list;
}

std::vector<std::string> DataManager::splitStringList(std::vector<std::string>& string_list, const char split)
{
  std::vector<std::string> token_list;

  for (size_t i = 0; i < string_list.size(); i++) {
    std::vector<std::string> split_result = splitString(string_list[i], split);
    token_list.insert(token_list.end(), split_result.begin(), split_result.end());
  }

  return token_list;
}

}  // namespace irt