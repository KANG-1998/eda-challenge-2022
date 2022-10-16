#pragma once

#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include <cassert>
#include <cmath>
#include <ctime>
#include <fstream>
#include <map>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <vector>

#include "Logger.hpp"
#include "Rectangle.hpp"
#include "json.hpp"

namespace irt {

class COMUtil
{
 public:
  template <class T>
  static T stringToNum(const std::string string)
  {
    std::istringstream iss(string);
    T num;
    iss >> num;
    return num;
  }

  static double microtime()
  {
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return static_cast<double>(tv.tv_sec) + static_cast<double>(tv.tv_usec) / 1000000.00;
  }

  static char* nowtime()
  {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    char* buffer = new char[32];
    strftime(buffer, 32, "%Y/%m/%d %H:%M:%S", t);
    return buffer;
  }

  static int getFirstDigit(int n)
  {
    n = n >= 100000000 ? (n / 100000000) : n;
    n = n >= 10000 ? (n / 10000) : n;
    n = n >= 100 ? (n / 100) : n;
    n = n >= 10 ? (n / 10) : n;
    return n;
  }

  static int getDigitNum(int n)
  {
    int count = 0;

    while (n != 0) {
      n /= 10;
      count++;
    }
    return count;
  }

  static int getBatchSize(size_t total_size) { return getBatchSize(static_cast<int>(total_size)); }

  static int getBatchSize(int total_size)
  {
    int batch_size = 10000;

    if (total_size < 0) {
      LogInst.error(Loc::current(), "The total of size < 0!");
    } else if (total_size == 0) {
      batch_size = 0;
    } else if (total_size < 100000) {
      batch_size = total_size / 10;
      int factor = static_cast<int>(std::pow(10, getDigitNum(batch_size) - 1));
      batch_size = batch_size / factor * factor;
    }
    return batch_size;
  }

  template <typename T>
  static void conditionalSwap(T& left, T& right, bool is_swap)
  {
    if (is_swap) {
      std::swap(left, right);
    }
  }

  static bool isDivisible(int dividend, int divisor)
  {
    if (dividend % divisor == 0) {
      return true;
    }
    return false;
  }

  static bool isDivisible(double dividend, double divisor)
  {
    double merchant = dividend / divisor;
    if (std::abs(merchant - static_cast<int>(merchant)) < 1E-6) {
      return true;
    }
    return false;
  }

  template <typename T>
  static void sortASC(T& a, T& b)
  {
    if (a > b) {
      std::swap(a, b);
    }
  }

  template <typename T>
  static void addOffset(Coordinate<T>& coord, T x_value, T y_value)
  {
    coord.set_x(coord.get_x() + x_value);
    coord.set_y(coord.get_y() + y_value);
  }

  template <typename T>
  static void reduceOffset(Coordinate<T>& coord, T x_value, T y_value)
  {
    coord.set_x((coord.get_x() - x_value) < 0 ? 0 : (coord.get_x() - x_value));
    coord.set_y((coord.get_y() - y_value) < 0 ? 0 : (coord.get_y() - y_value));
  }

  template <typename T>
  static int getLength(const Coordinate<T>& start_coord, const Coordinate<T>& end_coord)
  {
    int diff_x = std::abs(start_coord.get_x() - end_coord.get_x());
    int diff_y = std::abs(start_coord.get_y() - end_coord.get_y());
    return diff_x + diff_y;
  }

  template <typename T>
  static Coordinate<T> getInterSectionCoor(Coordinate<T>& one_start, Coordinate<T>& one_end, Coordinate<T>& two_start,
                                           Coordinate<T>& two_end)
  {
    if (one_start == two_start || one_start == two_end) {
      return one_start;
    } else if (one_end == two_start || one_end == two_end) {
      return one_end;
    } else {
      LogInst.error(Loc::current(), "getInterSectionCoor", "no intersection coor");
      exit(1);
    }
  }

  template <typename T>
  static bool exsitInterSectionCoor(Coordinate<T>& one_start, Coordinate<T>& one_end, Coordinate<T>& two_start, Coordinate<T>& two_end)
  {
    if (one_start == two_start || one_start == two_end) {
      return true;
    } else if (one_end == two_start || one_end == two_end) {
      return true;
    } else {
      return false;
    }
  }

  static bool exsitInterSection(int& one_start_layer_idx, int& one_end_layer_idx, int& two_start_layer_idx, int& two_end_layer_idx)
  {
    if (one_start_layer_idx == two_start_layer_idx || one_start_layer_idx == two_end_layer_idx) {
      return true;
    } else if (one_end_layer_idx == two_start_layer_idx || one_end_layer_idx == two_end_layer_idx) {
      return true;
    } else {
      return false;
    }
  }

  static int getOffset(const int start, const int end)
  {
    int offset = 0;
    if (start < end) {
      offset = 1;
    } else if (start > end) {
      offset = -1;
    } else {
      LogInst.warning(Loc::current(), "The step == 0!");
    }
    return offset;
  }

  template <typename T>
  static std::queue<T> initQueue(const T& t)
  {
    std::queue<T> queue;
    queue.push(t);
    return queue;
  }

  template <typename T>
  static T getFrontAndPop(std::queue<T>& queue)
  {
    T node = queue.front();
    queue.pop();
    return node;
  }

  template <typename T>
  static void addListToQueue(std::queue<T>& queue, std::vector<T>& node_list)
  {
    for (size_t i = 0; i < node_list.size(); i++) {
      queue.push(node_list[i]);
    }
  }

  template <typename T>
  static bool sameSign(T a, T b)
  {
    return std::signbit(a) == std::signbit(b);
  }

  template <typename T>
  static bool diffSign(T a, T b)
  {
    return !sameSign(a, b);
  }

  template <typename Key, typename Compare = std::less<Key>>
  static bool exist(const std::set<Key, Compare>& set, const Key& key)
  {
    return (set.find(key) != set.end());
  }

  template <typename Key, typename Value, typename Compare = std::less<Key>>
  static bool exist(const std::map<Key, Value, Compare>& map, const Key& key)
  {
    return (map.find(key) != map.end());
  }

  template <typename T = nlohmann::json>
  static T getData(nlohmann::json value, std::vector<std::string> flag_list)
  {
    if (flag_list.empty()) {
      LogInst.error(Loc::current(), "The flag list is empty!");
    }
    for (size_t i = 0; i < flag_list.size(); i++) {
      value = value[flag_list[i]];
    }
    if (!value.is_null()) {
      return value;
    }
    std::string key;
    for (size_t i = 0; i < flag_list.size(); i++) {
      key += flag_list[i] + ".";
    }
    LogInst.error(Loc::current(), "The configuration file key = '", key, "' does not exist!");
    return value;
  }

  /**
   * @description: sigmoid
   * ---------------------
   * │ accuracy │ value  │
   * │  0.9999  │ 9.2102 │
   * │  0.999   │ 6.9068 │
   * │  0.99    │ 4.5951 │
   * │  0.9     │ 2.1972 │
   * ---------------------
   *
   * return 1.0 / { 1 + e ^ [ accuracy * (1 - 2 * value / threshold) ] }
   * notice : The closer the <value> is to the <threshold>, the closer the return value is to 1
   *
   */
  static double sigmoid(const double value, const double threshold)
  {
    double result = (1.0 / (1 + std::exp(4.5951 * (1 - 2 * value / std::max(threshold, 0.01)))));
    if (std::isnan(result)) {
      LogInst.error(Loc::current(), "The value is nan!");
    }
    return result;
  }

  template <typename T>
  static double getRatio(T a, T b)
  {
    return (b > 0 ? static_cast<double>(a) / b : 0.0);
  }

  template <typename T>
  static double getPercentage(T a, T b)
  {
    return getRatio(a, b) * 100.0;
  }

  static std::ifstream& getInputFileStream(std::string file_path) { return getFileStream<std::ifstream>(file_path); }

  static std::ofstream& getOutputFileStream(std::string file_path) { return getFileStream<std::ofstream>(file_path); }

  template <typename T>
  static void closeFileStream(T& t)
  {
    t.close();
  }

  template <typename T, typename... Args>
  static std::string splice(T value, Args... args)
  {
    std::stringstream oss;
    pushStream(oss, value, args...);
    std::string string = oss.str();
    oss.clear();
    return string;
  }

  template <typename Stream, typename T, typename... Args>
  static void pushStream(Stream& stream, T t, Args... args)
  {
    stream << t;
    pushStream(stream, args...);
    return;
  }

  template <typename Stream, typename T>
  static void pushStream(Stream& stream, T t)
  {
    stream << t;
  }

  static std::string escapeBackslash(std::string a)
  {
    std::regex re(R"(\\)");
    return std::regex_replace(a, re, "");
  }

  static bool isInteger(double a)
  {
    if (std::abs(a - static_cast<int>(a)) < 1E-6) {
      return true;
    }
    return false;
  }

  template <typename T>
  static bool rectContainBoundaryPoint(Rectangle<T> rect, Coordinate<T> coor)
  {
    return (rect.get_lb_x() <= coor.get_x() && coor.get_x() <= rect.get_rt_x())
           && (rect.get_lb_y() <= coor.get_y() && coor.get_y() <= rect.get_rt_y());
  }

  template <typename T>
  static bool rectContainPoint(Rectangle<T> rect, Coordinate<T> coor)
  {
    return (rect.get_lb_x() <= coor.get_x() && coor.get_x() < rect.get_rt_x())
           && (rect.get_lb_y() <= coor.get_y() && coor.get_y() < rect.get_rt_y());
  }

  template <typename T>
  static T manhattanDistance(Coordinate<T> coord1, Coordinate<T> coord2)
  {
    return abs(coord1.get_x() - coord2.get_x()) + abs(coord1.get_y() - coord2.get_y());
  }

 private:
  template <typename T>
  static T& getFileStream(std::string file_path)
  {
    T* file = new T(file_path);
    if (!file->is_open()) {
      LogInst.error(Loc::current(), "Failed to open file '", file_path, "'!");
    }
    return *file;
  }
};

}  // namespace irt
