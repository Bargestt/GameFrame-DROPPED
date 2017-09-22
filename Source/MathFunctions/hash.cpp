#include "hash.h"

bool operator==(const Point &left, const Point &right) noexcept
{
    return (left.x == right.x && left.z == right.z);
}
