#include <PiecePathChecker.h>
#include <ConcretePiece.h>
#include <Move.h>
#include <ChessBoard.h>
#include <Directions.h>
#include <PermissiveRuleChecker.h>
PiecePathChecker::PiecePathChecker(ChessBoard const & board,
                                   size_t destination):
                                   destination_(destination),
                                        board_(board){
}
bool PiecePathChecker::visit(ConcretePiece<PawnTag> const&
                             pawn) const{
    if(!PermissiveRuleChecker(destination_).check(pawn))
        return false;
    Move move(toIndex(pawn.x(), pawn.y()), destination_);
    Directions moveDirection = Directions(int(findDirection(move))*
                               pawn.multiplier());
    if(moveDirection == front)
        return testPath(pawn.color(),move);
    Color ennemyColor(pawn.color()== colorWhite?
                      colorBlack : colorWhite);
    assert(moveDirection == frontLeft ||
           moveDirection == frontRight);
    return board_.pieceColor(destination_) == ennemyColor;
}
bool PiecePathChecker::visit(ConcretePiece<TowerTag> const&
                             tower) const{
    if(!PermissiveRuleChecker(destination_).check(tower))
        return false;
    Move move(toIndex(tower.x(), tower.y()), destination_);
    return testPath(tower.color(),move);
}
bool PiecePathChecker::visit(ConcretePiece<KnightTag> const&
                             knight) const{
    if(!PermissiveRuleChecker(destination_).check(knight))
        return false;
    return board_.pieceColor(destination_)!= knight.color();

}
bool PiecePathChecker::visit(ConcretePiece<BishopTag> const&
                             bishop) const{
    if(!PermissiveRuleChecker(destination_).check(bishop))
        return false;
    Move move(toIndex(bishop.x(), bishop.y()), destination_);
    return testPath(bishop.color(),move);
}

bool PiecePathChecker::visit(ConcretePiece<QueenTag> const&
                             queen) const{
    if(!PermissiveRuleChecker(destination_).check(queen))
        return false;
    Move move(toIndex(queen.x(), queen.y()), destination_);
    return testPath(queen.color(),move);
}
bool PiecePathChecker::visit(ConcretePiece<KingTag> const&
                             king) const{
    if(!PermissiveRuleChecker(destination_).check(king))
        return false;
    return board_.pieceColor(destination_) != king.color();
}
bool PiecePathChecker::testPath(Color color,
                                Move const & move) const{
    Directions moveDirection = findDirection(move);
    size_t distance = traversedSquares(move);
    size_t stepIndex = move.start;
    for(size_t step = 0; step < distance; ++ step){
        stepIndex += moveDirection;
        if(stepIndex == move.finish){
           return  board_.pieceColor(stepIndex) != color;
        }else{
            if(board_.pieceColor(stepIndex) != colorNone)
                return false;
        }
    }
    return false;
}
