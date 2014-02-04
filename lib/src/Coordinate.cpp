#include <Coordinate.h>
size_t toIndex(size_t x, size_t y){
    if( x>=8 || y>=8 )
        return 64;
    return (y* 8) + x;
}
Coordinate toCoordinate(size_t index){
    if( index >= 64)
        return Coordinate();
    size_t y = index / 8;
    size_t x = index % 8;
    return Coordinate(x,y);
}
