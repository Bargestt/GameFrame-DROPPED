#ifndef ARRAY_2D_H
#define ARRAY_2D_H

#include <cstddef>
#include <array>

template<class T, std::size_t Rows, std::size_t Cols>
struct Array_2D
{
    typedef std::array< std::array< T, Cols >, Rows> type;
private:
    Array_2D();
};

template<class T, std::size_t Rows, std::size_t Cols>
using Array2D_T = std::array< std::array< T, Cols >, Rows >;



#endif // ARRAY_2D_H
