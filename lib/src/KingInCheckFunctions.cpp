#include <KingInCheckFunctions.h>
#include <KingIdentifier.h>
#include <Move.h>
#include <PiecePathChecker.h>
#include <ChessBoard.h>
#include <SimulationFunctions.h>
#include <SimulatedPiecePathChecker.h>
#include <cassert>
bool isKingInCheck(ChessBoard const & board, Color color){
    assert(color == colorBlack || color == colorWhite);
    Color ennemyColor(color == colorWhite ?
                               colorBlack:
                               colorWhite);
    size_t kingPos = findKing(board, color);
    assert(kingPos < 64);
    PiecePathChecker checker(board, kingPos);
    for(size_t index = 0 ; index < 64; ++index){
        if(board.pieceColor(index) == ennemyColor){
            if(checker.check(board.pieceAt(index)))
                return true;
        }
    }
    return false;
}
size_t simulatedIndex(Move const & move, size_t position){
    assert(move.isValid());
    if(position == move.start)
        return 64;
    if(position == move.finish)
        return move.start;
    return position;
}
bool isSimulatedSquareEmpty(ChessBoard const & board, Move const & move,
                            size_t index){
    return board.isSquareEmpty(simulatedIndex(move, index));
}
Color simulatedPieceColor(ChessBoard const & board, Move const & move,
                            size_t index){
    return board.pieceColor(simulatedIndex(move,index));
}
const Piece & simulatedPieceAt(ChessBoard const & board, Move const & move,
                      size_t index){
    return board.pieceAt(simulatedIndex(move, index));
}
bool simulatedIsKingInCheck(ChessBoard const& board,
                            Move const& simulated,
                            Color color){
    assert(color == colorBlack || color == colorWhite);
    Color ennemyColor(color == colorWhite ?
                               colorBlack:
                               colorWhite);
    size_t kingPos = findKing(board, color);
    assert(kingPos < 64);
    SimulatedPiecePathChecker checker(board,simulated, kingPos);
    for(size_t index = 0 ; index < 64; ++index){
        if(board.pieceColor(index) == ennemyColor){
            if(checker.check(board.pieceAt(index)))
                return true;
        }
    }
    return false;
}
