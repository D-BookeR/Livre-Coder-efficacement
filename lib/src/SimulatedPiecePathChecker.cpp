#include <SimulatedPiecePathChecker.h>
#include <SimulatedPermissiveRuleChecker.h>
#include <SimulationFunctions.h>
#include <Directions.h>
#include <ChessBoard.h>
#include <ConcretePiece.h>
SimulatedPiecePathChecker::
    SimulatedPiecePathChecker(ChessBoard const & board,
                              Move const & simulated,
                              size_t destination):
                                  destination_(destination),
                                  board_(board),
                                  simulated_(simulated){
}
bool SimulatedPiecePathChecker::
     visit(ConcretePiece<PawnTag> const& pawn) const{
    if(!SimulatedPermissiveRuleChecker(simulated_,
                                       destination_).check(pawn))
        return false;
    size_t simulatedPawn =
           simulatedIndex(simulated_, toIndex(pawn.x(),pawn.y()));
    size_t simulatedDestination =
           simulatedIndex(simulated_, destination_);
    Move move(simulatedPawn, simulatedDestination);
    Directions moveDirection = findDirection(move);
    if(moveDirection * pawn.multiplier() == 8)
        return testPath(pawn.color(),move);
    Color ennemyColor(pawn.color()== colorWhite?
                      colorBlack : colorWhite);
    return board_.pieceColor(simulatedDestination) == ennemyColor;
}
bool SimulatedPiecePathChecker::
     visit(ConcretePiece<TowerTag> const& tower) const{
    if(!SimulatedPermissiveRuleChecker(simulated_,
                                       destination_).check(tower))
        return false;
    size_t simulatedTower =
           simulatedIndex(simulated_, toIndex(tower.x(),tower.y()));
    size_t simulatedDestination =
           simulatedIndex(simulated_, destination_);
    Move move(simulatedTower, simulatedDestination);
    return testPath(tower.color(),move);
}
bool SimulatedPiecePathChecker::
     visit(ConcretePiece<KnightTag> const& knight) const{
    if(!SimulatedPermissiveRuleChecker(simulated_,
                                       destination_).check(knight))
        return false;
    size_t simulatedDestination =
           simulatedIndex(simulated_, destination_);
    return board_.pieceColor(simulatedDestination)!= knight.color();
}
bool SimulatedPiecePathChecker::
     visit(ConcretePiece<BishopTag> const& bishop) const{
    if(!SimulatedPermissiveRuleChecker(simulated_,
                                       destination_).check(bishop))
        return false;
    size_t simulatedBishop =
           simulatedIndex(simulated_, toIndex(bishop.x(),
                                              bishop.y()));
    size_t simulatedDestination =
           simulatedIndex(simulated_, destination_);
    Move move(simulatedBishop, simulatedDestination);
    return testPath(bishop.color(),move);
}
bool SimulatedPiecePathChecker::
     visit(ConcretePiece<QueenTag> const& queen) const{
    if(!SimulatedPermissiveRuleChecker(simulated_,
                                       destination_).check(queen))
        return false;
    size_t simulatedQueen =
           simulatedIndex(simulated_, toIndex(queen.x(),
                                              queen.y()));
    size_t simulatedDestination =
           simulatedIndex(simulated_, destination_);
    Move move(simulatedQueen, simulatedDestination);
    return testPath(queen.color(),move);
}
bool SimulatedPiecePathChecker::
     visit(ConcretePiece<KingTag> const& king) const{
    if(!SimulatedPermissiveRuleChecker(simulated_,
                                       destination_).check(king))
        return false;
    size_t simulatedDestination =
           simulatedIndex(simulated_, destination_);
    return board_.pieceColor(simulatedDestination) != king.color();
}
bool SimulatedPiecePathChecker::
     testPath(Color color, Move const& move) const{
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
