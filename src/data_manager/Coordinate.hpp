#pragma once

#include <iostream>

namespace irt
{

    template <typename T>
    class Coordinate
    {
    public:
        Coordinate() {}
        Coordinate(const T x, const T y)
        {
            _x = x;
            _y = y;
        }
        Coordinate(const Coordinate &other)
        {
            _x = other._x;
            _y = other._y;
        }
        Coordinate(Coordinate &&other)
        {
            _x = std::move(other._x);
            _y = std::move(other._y);
        }
        ~Coordinate() {}
        Coordinate &operator=(const Coordinate &other)

        {
            _x = other._x;
            _y = other._y;
            return (*this);
        }
        Coordinate &operator=(Coordinate &&other)

        {
            _x = std::move(other._x);
            _y = std::move(other._y);
            return (*this);
        }
        bool operator==(const Coordinate &other) const { return (_x == other._x && _y == other._y); }
        bool operator!=(const Coordinate &other) const { return !((*this) == other); }
        // getter
        T get_x() const
        {
            return _x;
        }
        T get_y() const { return _y; }
        // setters
        void set_x(const T &x)
        {
            _x = x;
        }
        void set_y(const T &y) { _y = y; }
        void set_x_y(const T &x, const T &y)

        {
            _x = x;
            _y = y;
        }
        // function

    private:
        T _x = -1;
        T _y = -1;
    };

    template <typename T>
    struct cmpCoordinateXASC
    {
        bool operator()(const Coordinate<T> &a, const Coordinate<T> &b) const

        {
            return a.get_x() != b.get_x() ? a.get_x() < b.get_x() : a.get_y() < b.get_y();
        }
    };

    template <typename T>
    struct cmpCoordinateYASC
    {
        bool operator()(const Coordinate<T> &a, const Coordinate<T> &b) const

        {
            return a.get_y() != b.get_y() ? a.get_y() < b.get_y() : a.get_x() < b.get_x();
        }
    };

}