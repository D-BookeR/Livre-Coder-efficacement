#include <ConcreteInput.h>
#include <ConsoleOutput.h>
#include <ChessBoard.h>
#include <toConcreteOutput.h>
#include <UnexpectedCommand.h>
#include <HelpCommand.h>
#include <TeamListCommand.h>
#include <AllPieceListCommand.h>
#include <ExitCommand.h>
#include <SurrenderCommand.h>
#include <NewGameCommand.h>
#include <MoveCommand.h>
#include <CastlingCommand.h>
#include <GrandCastlingCommand.h>
#include <ConcreteCommandSender.h>
#include <NeedInitCommand.h>
#include <toUpperFunction.h>
class Game;
/** Les valeurs énumérées représentant les différents
  * émetteurs de commandes qui seront utilisés.
  */
enum consoleSenders{
    unexpected,
    help,
    team,
    allPieces,
    exitGame,
    surrender,
    newGame,
    needInit,
    movement,
    castling,
    grandCastling,
    CONSOLE_INPUT_MAX
};
size_t toIndex(std::string const & str){
    assert(str.size() == 2);
    size_t x(str[0]-'A');
    size_t y(str[1]-'1');
    return y*8+x;
}
template <>
ConcreteInput<ConsoleTag>::
    ConcreteInput(Game & game):UserInput(game){
    allSenders_.emplace_back(
        std::unique_ptr<CommandSender>
        ( new ConcreteCommandSender<ConsoleTag,
                                    UnexpectedTag>
          (*this,UnexpectedTag::CtorPolicy())));
    allSenders_.emplace_back(
        std::unique_ptr<CommandSender>
        ( new ConcreteCommandSender<ConsoleTag,
                                    HelpTag>
          (*this,HelpTag::CtorPolicy())));
    allSenders_.emplace_back(
        std::unique_ptr<CommandSender>
        ( new ConcreteCommandSender<ConsoleTag,
                                    TeamTag>
          (*this,TeamTag::CtorPolicy())));
    allSenders_.emplace_back(
        std::unique_ptr<CommandSender>
        ( new ConcreteCommandSender<ConsoleTag,
                                    AllPiecesTag>
         (*this,AllPiecesTag::CtorPolicy())));
    allSenders_.emplace_back(
        std::unique_ptr<CommandSender>
        ( new ConcreteCommandSender<ConsoleTag,
                                    ExitTag>
          (*this,ExitTag::CtorPolicy())));
    allSenders_.emplace_back(
        std::unique_ptr<CommandSender>
        ( new ConcreteCommandSender<ConsoleTag,
                                    SurrenderTag>
          (*this,SurrenderTag::CtorPolicy())));
    allSenders_.emplace_back(
        std::unique_ptr<CommandSender>
        ( new ConcreteCommandSender<ConsoleTag,
                                    NewGameTag>
          (*this,NewGameTag::CtorPolicy())));
    allSenders_.emplace_back(
        std::unique_ptr<CommandSender>
        ( new ConcreteCommandSender<ConsoleTag,
                                    NeedInitTag>
          (*this,NeedInitTag::CtorPolicy())));
    allSenders_.emplace_back(
        std::unique_ptr<CommandSender>
        ( new ConcreteCommandSender<ConsoleTag,
                                    MoveTag>
          (*this,MoveTag::CtorPolicy())));
    allSenders_.emplace_back(
        std::unique_ptr<CommandSender>
        ( new ConcreteCommandSender<ConsoleTag,
                                    CastlingTag>
          (*this,CastlingTag::CtorPolicy())));
    allSenders_.emplace_back(
        std::unique_ptr<CommandSender>
        ( new ConcreteCommandSender<ConsoleTag,
                                    GrandCastlingTag>
          (*this,GrandCastlingTag::CtorPolicy())));
    assert(allSenders_.size() == CONSOLE_INPUT_MAX);
}
template<>
CommandSender const & ConcreteInput<ConsoleTag>::selectSender(){
    move_=Move();
    color_=colorMax;
    std::string str;
    std::getline(std::cin, str);
    consoleSenders toSend;
    toUpper(str);
    /* la commande d'aide */
    if(game().needInit()){
       toSend = needInit;
    } else if(str=="AIDE" || str=="?"){
        toSend =help;
    }else if(str=="QUITTER"){
        toSend = exitGame;
    }else if(str=="NOUVELLE"){
        toSend = newGame;
    }else if(str=="BLANCS"){
        color_ = colorWhite;
        toSend = team;
     }else if(str=="NOIRS"){
         color_ = colorBlack;
        toSend = team;
     }else if(str=="TOUTES"){
         toSend = allPieces;
     }else if (str == "ABANDON"){
         toSend = surrender;
     }else if(str.size() == 4 && str!="AIDE" ){
        std::string first=str.substr(0,2);
        std::string second = str.substr(2);
        move_.start = toIndex(first);
        move_.finish = toIndex(second);
        if(! move_.isValid()){
            toSend = unexpected;
        }
        toSend = movement;
    }else if(str=="O-O"){
        toSend = castling;
    }else if(str=="O-O-O"){
        toSend = grandCastling;
    }else{
        toSend = unexpected;
    }
    return *(allSenders_[toSend].get());
}
