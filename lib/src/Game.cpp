#include <Game.h>
#include <cassert>
#include <PieceFactory.h>
#include <Command.h>
#include <Piece.h>
#include <KingInCheckFunctions.h>
#include <PlayerAllowedMoves.h>
Game::Game():
    exitGame_(false),surrendered_(false),
    gameFinished_(false),
    whites_(colorWhite),blacks_(colorBlack){
reinitialize();
}
void Game::clear(){
    allPieces_.clear();
    firstPlayer(colorWhite);
}
void Game::firstPlayer(Color color){
    assert(color==colorBlack || color ==  colorWhite);
    current_ = &whites_;
    next_ = &blacks_;
    if(color == colorBlack)
        altenatePlayers();
}
void Game::reinitialize(){
    board_.reinitialize();
    clear();
    PieceFactory factory;
    for(size_t index = 0;index < board_.indexMax; ++index){
        Piece * newPiece = factory.createDefaultPositionPiece(index);
        if(newPiece != nullptr){
            allPieces_.emplace_back(std::unique_ptr<Piece>(newPiece));
            board_.pieceComes(newPiece,index);
        }
    }
}
void Game::run(){
    assert(areContextDefined());
    while(exitGame_ == false){
        while(exitGame_ == false &&
              surrendered_ == false &&
              gameFinished_ == false){
            render().playerTurn(currentColor());
            Command const & command = current_->inputs().selectCommand();
            CommandResult result = command.execute();
            if(result == resultMoved){
                if(isKingInCheck(board(),nextColor())){
                    render().kingisInCheck();
                    if(!hasPlayerAllowedMove(board(),nextColor())){
                        render().kingIsMat();
                        render().winnerIs(currentColor());
                        gameFinished_ = true;
                    }
                }else if(!hasPlayerAllowedMove(board(),nextColor())){
                    render().patSituation();
                    gameFinished_ = true;
                }
                altenatePlayers();
            }
        }
        if(surrendered_ == true){
            render().hasSurrendered(currentColor());
            altenatePlayers();
        }
        if(gameFinished_ == true){
            render().winnerIs(currentColor());
        }
    }
}
void Game::defineInputSystem(Color color, InputSystem * input){
    assert(color == colorWhite || color == colorBlack);
    if(color == colorWhite)
        whites_.changeInputs(input);
    else
        blacks_.changeInputs(input);
}
