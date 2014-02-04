#include <ChessBoard.h>
#include <PieceFactory.h>
#include <Piece.h>
#include <Move.h>
ChessBoard::ChessBoard():squares_(indexMax){
    PieceFactory factory;
    noPiece_.reset(factory.create(NotAPieceTag()));
}
void ChessBoard::movePiece(Move const& move){
    assert(move.isValid());
    squareAt(move.finish).piece->ejected();
    Piece * piece =squareAt(move.start).piece;
    piece->moveTo(toCoordinate(move.finish));
    pieceLeaves(move.start);
    pieceComes(piece,move.finish);
}
Color ChessBoard::squareColor(size_t index) const{
    return squareAt(index).color;
}

bool ChessBoard::isSquareEmpty(size_t index) const{
    return pieceColor(index) == colorNone;
}

Color ChessBoard::pieceColor(size_t index) const{
    return pieceAt(index).color();
}
Piece  & ChessBoard::pieceAt(size_t index){
    return *(squareAt(index).piece);
}
Piece const & ChessBoard::pieceAt(size_t index) const{
    return *(squareAt(index).piece);
}
void ChessBoard::pieceComes(Piece* piece, size_t index){
    squareAt(index).piece = piece;
}
void ChessBoard::pieceLeaves(size_t index){
    squareAt(index).piece = noPiece_.get();
}
ChessBoard::Square & ChessBoard::squareAt(size_t index){
    assert(index < indexMax);
    return squares_[index];
}
const ChessBoard::Square & ChessBoard::squareAt(size_t index) const{
    assert(index < indexMax);
    return squares_[index];
}
void ChessBoard::reinitialize(){
    for(size_t index= 0; index<indexMax;++index)
        pieceLeaves(index);
}
