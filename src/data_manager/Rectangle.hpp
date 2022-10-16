#pragma once

#include <vector>
#include "Coordinate.hpp"

namespace irt {

template <typename T>
class Rectangle
{
 public:
  Rectangle() {}
  Rectangle(const T lb_x, const T lb_y, const T rt_x, const T rt_y)
  {
    set_lb(lb_x, lb_y);
    set_rt(rt_x, rt_y);
  }
  Rectangle(const Rectangle& other)
  {
    _lb = other._lb;
    _rt = other._rt;
  }
  Rectangle(Rectangle&& other)
  {
    _lb = std::move(other._lb);
    _rt = std::move(other._rt);
  }
  ~Rectangle() {}
  Rectangle& operator=(const Rectangle& other)
  {
    _lb = other._lb;
    _rt = other._rt;
    return (*this);
  }
  Rectangle& operator=(Rectangle&& other)
  {
    _lb = std::move(other._lb);
    _rt = std::move(other._rt);
    return (*this);
  }
  bool operator==(const Rectangle& other) { return (_lb == other._lb && _rt == other._rt); }
  bool operator!=(const Rectangle& other) { return !((*this) == other); }
  // getter
  Coordinate<T>& get_lb() { return _lb; }
  Coordinate<T>& get_rt() { return _rt; }
  Coordinate<T> get_lb()  const { return _lb; }
  Coordinate<T> get_rt() const { return _rt; }
  T get_lb_x() const { return _lb.get_x(); }
  T get_lb_y() const { return _lb.get_y(); }
  T get_rt_x() const { return _rt.get_x(); }
  T get_rt_y() const { return _rt.get_y(); }
  // setters
  void set_lb(Coordinate<T> coord) { _lb = coord; }
  void set_rt(Coordinate<T> coord) { _rt = coord; }
  void set_lb(const T x, const T y)
  {
    _lb.set_x(x);
    _lb.set_y(y);
  }
  void set_rt(const T x, const T y)
  {
    _rt.set_x(x);
    _rt.set_y(y);
  }
  // function
  T getLength() const;
  T getWidth() const;
  T getHalfPerimeter() const;
  T getPerimeter() const;
  T getArea() const;
  Coordinate<T> getMidPoint() const;
  bool isOnRTEdge(const Coordinate<T>& coord) const;

 private:
  Coordinate<T> _lb;
  Coordinate<T> _rt;
};

template <typename T>
inline T Rectangle<T>::getLength() const
{
  return get_rt_x() - get_lb_x();
}

template <typename T>
inline T Rectangle<T>::getWidth() const
{
  return get_rt_y() - get_lb_y();
}

template <typename T>
inline T Rectangle<T>::getHalfPerimeter() const
{
  return getLength() + getWidth();
}

template <typename T>
inline T Rectangle<T>::getPerimeter() const
{
  return getHalfPerimeter() * 2;
}

template <typename T>
inline T Rectangle<T>::getArea() const
{
  return getLength() * getWidth();
}


template <typename T>
inline Coordinate<T> Rectangle<T>::getMidPoint() const
{
  return Coordinate<T>((get_lb_x() + get_rt_x()) / 2, (get_lb_y() + get_rt_y()) / 2);
}

/**
 * @brief is the coordinate located on the right or top edge of the rectangle
 */
template <typename T>
inline bool Rectangle<T>::isOnRTEdge(const Coordinate<T>& coord) const
{
  return (coord.get_x() == get_rt_x() || coord.get_y() == get_rt_y());
}

template <typename T>
struct CmpRectangleByXASC
{
  bool operator()(const Rectangle<T>& left, const Rectangle<T>& right) const
  {
    if (left.get_lb() == right.get_lb()) {
      return cmpCoordinateXASC<T>()(left.get_rt(), right.get_rt());
    } else {
      return cmpCoordinateXASC<T>()(left.get_lb(), right.get_lb());
    }
  }
};

}
