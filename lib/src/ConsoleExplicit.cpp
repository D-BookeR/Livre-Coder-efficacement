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
#include <NeedInitCommand.h>
#include <MoveCommand.h>
#include <CastlingCommand.h>
#include <GrandCastlingCommand.h>
#include <toUpperFunction.h>
#include <iomanip>
#include <vector>
#include <tuple>
#include <string>
#include <cassert>
#include <limits>
/** Un tableau spécifique à l'affichage en modue console
  *  reprenant l'ensemble des commandes comprises par ce mode
  */
static const std::vector<std::pair<std::string,
                                   std::string>> consoleHelpStrings={
    {"aide ou ?", "affiche l'aide"},
    {"nouvelle","lance une nouvelle partie" },
    {"blancs","dresse la liste des pieces blanches actives" },
    {"noirs","dresse la liste des pieces noires actives" },
    {"toutes","dresse la liste de toutes les pieces actives" },
    {"abandon","permet au joueur d'abandonner la partie" },
    {"<C1><C2>","Deplace la pièce de la coordonnee <C1> vers la"
                " coordonnee <C2>"},
    {"O-O","petit roque" },
    {"O-O-O","grand roque" },
};
std::ostream & operator <<(std::ostream & os, Coordinate const & coord){
    char x('A'+ coord.x());
    char y('1'+coord.y());
    os<<x<<y;
    return os;
}
std::ostream & operator <<(std::ostream & os, Color color){
    switch(color){
        case colorNone: os <<" aucun ";
        break;
        case colorBlack: os <<" noirs   ";
        break;
        case colorWhite: os <<" blancs ";
            break;
        case colorMax:
            assert(!"You should never come here!");
    }
    return os;
}
std::ostream & operator<< (std::ostream & os, Move const & move ){
    os<<toCoordinate(move.start)<<"-"<<toCoordinate(move.finish);
    return os;
}
template<>
void ConcreteCommand<ConsoleTag, UnexpectedTag>::printMe() const{
    std::cout<< "Commande non reconnue."<<std::endl
             << "Choisissez help ou ? pour obtenir de l'aide"
             << std::endl;
}
template<>
void ConcreteCommand<ConsoleTag, HelpTag>::printMe() const{
    for(auto it :consoleHelpStrings){
        std::cout<<std::setw(15)<<std::setfill(' ')
                 <<std::left<<it.first
                 <<it.second<<std::endl;
    }
}
template<>
void ConcreteCommand<ConsoleTag,TeamTag>::
     printMe(Piece const & piece) const{
    render.show(Coordinate(piece.x(),piece.y()));
    std::cout<<" : ";
    render.show(piece);
    render.show(piece.color());
    std::cout<<std::endl;
}
template<>
void ConcreteCommand<ConsoleTag,AllPiecesTag>::printMe() const{
    ConcreteCommand<ConsoleTag, TeamTag> whiteShow(render, board);
    whiteShow.color = colorWhite;
    ConcreteCommand<ConsoleTag, TeamTag> blackShow(render, board);
    blackShow.color = colorBlack;
        whiteShow.execute();
        blackShow.execute();
}
template <>
bool ConcreteCommand<ConsoleTag, ExitTag>::confirm()const{
    std::string result;
    while( result!="O" && result!="N" &&
           result!="OUI" && result!= "NON" ){
        std::cout<<"Voulez-vous vraiment quitter la partie?"
                 <<" (oui, non)";
        std::getline(std::cin,result);
        toUpper(result);
        if( result!="O" && result!="N" &&
            result!="OUI" && result!= "NON"){
            std::cout<<"Veuillez choisir \"oui\" "
                     <<"ou \"non\""<<std::endl;
        }
    }
    return result=="O" || result=="OUI";
}
template <>
void ConcreteCommand<ConsoleTag, ExitTag>::printMe() const{
    std::cout<<"Merci d'avoir joue, a bientot."<<std::endl
             <<"Appuyez sur enter pour quitter.";
    std::cin.ignore(
       std::numeric_limits<std::streamsize>::max(), '\n' );
}
template <>
bool ConcreteCommand<ConsoleTag, SurrenderTag>::confirm()const{
    std::string result;
    while( result!="O"||result!="N" ||
           result!="OUI" || result!= "NON" ){
        std::cout<<"Voulez-vous vraiment abandonner la partie?"
                 <<" (oui, non)";
        std::getline(std::cin,result);
        if( result!="O" && result!="N" &&
            result!="OUI" && result!= "NON"){
            std::cout<<"Veuillez choisir \"oui\""
                     <<" ou \"non\""<<std::endl;
        }
    }
    return result=="O" || result=="OUI";
}

template <>
void ConcreteCommand<ConsoleTag, SurrenderTag>::printMe() const{
    render.show(game.nextColor());
    std::cout<<" gagne"<<std::endl;
}
template <>
bool ConcreteCommand<ConsoleTag, NewGameTag>::confirm()const{
    std::string result;
    while( result!="O"||result!="N" ||
           result!="OUI" || result!= "NON" ){
        std::cout<<"Voulez-vous vraiment debuter une nouvelle"
                 <<" partie? (oui, non)";
        std::getline(std::cin,result);
        if( result!="O" && result!="N" &&
            result!="OUI" && result!= "NON"){
            std::cout<<"Veuillez choisir \"oui\""
                     <<" ou \"non\""<<std::endl;
        }
    }
    return result=="O" || result=="OUI";
}
template <>
void ConcreteCommand<ConsoleTag, NewGameTag>::printMe() const{
    std::cout<<"L'echiquier a ete reinitialise, amusez-vous bien."
             <<std::endl<<"Appuyez sur enter pour jouer";
    std::cin.ignore(
         std::numeric_limits<std::streamsize>::max(), '\n' );
}
template <>
void ConcreteCommand<ConsoleTag, MoveTag>::invalidMove() const{
    render.show(move);
    std::cout<<": Mouvement invalide"<<std::endl;
}
template <>
void ConcreteCommand<ConsoleTag, MoveTag>::printMove() const{
    Piece const & piece =board.pieceAt(move.start);
    render.show(piece);
    render.show(piece.color());
    std::cout<<" de ";
    render.show(toCoordinate(move.start));
    std::cout<<" vers ",
    render.show(toCoordinate(move.finish));
    std::cout<<std::endl;
}
template <>
void ConcreteCommand<ConsoleTag, CastlingTag>::invalidMove() const{
    std::cout<<"Petit roque : Mouvement invalide"<<std::endl;
}
template <>
void ConcreteCommand<ConsoleTag, CastlingTag>::printMe() const{
    render.show(color);
    std::cout<<": petit roque"<<std::endl;
}
template <>
void ConcreteCommand<ConsoleTag, GrandCastlingTag>::invalidMove() const{
    std::cout<<"Grand roque : Mouvement invalide"<<std::endl;
}
template <>
void ConcreteCommand<ConsoleTag, GrandCastlingTag>::printMe() const{
    render.show(color);
    std::cout<<": Grand roque"<<std::endl;
}
template <>
void ConcreteCommand<ConsoleTag, NeedInitTag>::printMe() const{
    std::cout<<"La partie doit etre reinitialisee."<<std::endl
             <<"Choisissez \"nouvelle\" pour lancer"
             <<" une nouvelle partie."<<std::endl
             <<"Choisissez \"quitter\" pour quitter le jeu."
             <<std::endl
             <<"Choisissez \"help\" ou \"?\" pour d'autres"
             <<" options."<<std::endl;
}
