#ifndef 2DARRAY_H
#define 2DARRAY_H

#include <array>

template<class T, std::size_t Rows, std::size_t Cols>
using TArray2D = std::array< std::array< T, Cols >, Rows >;

#endif // 2DARRAY_H
