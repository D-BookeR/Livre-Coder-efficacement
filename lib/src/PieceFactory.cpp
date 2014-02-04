#include <PieceFactory.h>
#include <PieceVisitor.h>
#include <ConcretePiece.h>
Piece * PieceFactory::create(NotAPieceTag const&) const{
    return new NoPiece;
}
Piece * PieceFactory::create(PawnTag const&,
                             Color col,
                             size_t x, size_t y, bool moved) const{
    return new Pawn(col, x, y, moved);
}
Piece * PieceFactory::create(TowerTag const&,
                             Color col,
                             size_t x, size_t y, bool moved) const{
    return new Tower(col, x, y, moved);
}
Piece * PieceFactory::create(KnightTag const&,
                             Color col,
                             size_t x, size_t y, bool moved) const{
    return new Knight(col, x, y, moved);
}
Piece * PieceFactory::create(BishopTag const&,
                             Color col,
                             size_t x, size_t y, bool moved) const{
    return new Bishop(col, x, y, moved);
}
Piece * PieceFactory::create(QueenTag const&,
                             Color col,
                             size_t x, size_t y, bool moved) const{
    return new Queen(col, x, y, moved);
}
Piece * PieceFactory::create(KingTag const&,
                             Color col,
                             size_t x, size_t y, bool moved) const{
    assert(col == colorWhite || col == colorBlack);
    return new King(col, x, y, moved);
}
Piece * PieceFactory::createDefaultPositionPiece(size_t index) const{
    Coordinate coord(toCoordinate(index));
    assert(coord.isValid());
    Color color;
    if(coord.y()>1 && coord.y() < 6)
        return nullptr;
    if(coord.y() == 0 || coord.y() == 1)
        color = colorWhite;
    if(coord.y() == 6 || coord.y() == 7)
        color = colorBlack;
    assert(color == colorWhite || color == colorBlack);
    if(coord.y() == 1 ||
       coord.y() == 6){
        return create(PawnTag(), color, coord.x(),coord.y());
    }
    if(coord.y() == 0 ||
       coord.y() == 7){
        if(coord.x() == 0 || coord.x() == 7){
            return create(TowerTag(),color,coord.x(),coord.y());
        }
        if(coord.x() == 1 || coord.x() == 6){
            return create(KnightTag(),color,coord.x(),coord.y());
        }
        if(coord.x() == 2 || coord.x() == 5){
            return create(BishopTag(),color,coord.x(),coord.y());
        }
        if(coord.x() == 3 ){
            return create(QueenTag(),color,coord.x(),coord.y());
        }
        if(coord.x() == 4 ){
            return create(KingTag(),color,coord.x(),coord.y());
        }
    }
    assert(!"you should never come here");
    return nullptr;
}
