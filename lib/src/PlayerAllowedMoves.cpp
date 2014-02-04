#include <PlayerAllowedMoves.h>
#include <ChessBoard.h>
#include <PiecePathChecker.h>
#include <KingInCheckFunctions.h>
#include <cassert>
std::list<Move> fillAllowedMoveList(ChessBoard const & board,
                                    Color color){
    assert(color == colorBlack || color == colorWhite);
    std::list<Move> found;
    for(size_t index = 0; index <board.indexMax; ++ index){
        if(board.pieceColor(index) == color){
            for(size_t destination = 0; destination <board.indexMax;
                ++ destination){
                PiecePathChecker checker(board, destination);
                if(board.pieceColor(destination) != color &&
                   checker.check(board.pieceAt(index))){
                    found.push_back(Move(index, destination));
                }
            }
        }
    }
    return found;
}
bool hasPlayerAllowedMove(ChessBoard const & board, Color color){
    assert(color == colorBlack || color == colorWhite);
    std::list<Move> potentials(fillAllowedMoveList(board, color));
    if(potentials.empty())
        return false;
    for(auto it : potentials){
        if(!simulatedIsKingInCheck(board,it,color))
            return true;
    }
    return false;
}
