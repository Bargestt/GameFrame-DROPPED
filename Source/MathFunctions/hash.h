#ifndef HASH_H
#define HASH_H

#include <functional>

struct Point
{
    int x;
    int z;

    Point(int x1, int z1): x(x1), z(z1)
    { }

    bool operator ==(const Point& other){
        return (x == other.x && z == other.z);
    }
    bool operator()(const Point& left, const Point& right) const {
        return (left.x == right.x && left.z == right.z);
    }
};
bool operator ==(const Point& left, const Point& right) noexcept;

namespace std {
    template<> struct hash<Point>
    {
        typedef Point argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& p) const
        {
            result_type const h1 ( std::hash<float>{}(p.x) );
            result_type const h2 ( std::hash<float>{}(p.z) );

            return h1 ^ (h2 << 1);
        }
    };
}

#endif // HASH_H
