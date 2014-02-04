#include <Piece.h>
#include <cassert>
Piece::Piece(Color color, size_t x, size_t y, bool moved):
    hasMoved_(moved), color_(color),coordinate_(x,y){
    assert(color_ == colorBlack ||
           color_ == colorWhite);
}
Piece::~Piece(){
}
