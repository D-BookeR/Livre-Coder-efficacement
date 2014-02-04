#include <Directions.h>
#include <Coordinate.h>
#include <Move.h>
#include <cstdlib>
#include <cassert>
Directions findDirection(Move const & move){
    assert(move.isValid());
    Coordinate start = toCoordinate(move.start);
    Coordinate finish = toCoordinate(move.finish);
    int diffx(finish.x() - start.x());
    int diffy(finish.y() - start.y());
    if(diffx == 0 && diffy <0)
        return back;
    else if( diffx == 0 && diffy > 0 )
        return front;
    else if( diffx < 0 && diffx == 0 )
        return left;
    else if ( diffx > 0 && diffx == 0 )
        return right;
    else if( diffx < 0 && abs(diffx) == diffy )
        return frontLeft;
    else if( diffx > 0 && diffy == diffx )
        return frontRight;
    else if( diffx < 0  && diffx == diffy )
        return backLeft;
    else if ( diffy < 0 && abs(diffy) == diffx)
        return backRight;
    return dirUnset;
}
size_t traversedSquares(Move const & move){
    assert(move.isValid());
    Coordinate start = toCoordinate(move.start);
    Coordinate finish = toCoordinate(move.finish);
    int diffx(finish.x() - start.x());
    int diffy(finish.y() - start.y());
    assert(abs(diffx) <8);
    assert(abs(diffy) <8);
    if(diffx == 0)
        return abs(diffy);
    if(diffy == 0)
        return abs(diffx);
    if(abs(diffx) == abs(diffy))
        return abs(diffx);
    return 0;
}
