#ifndef CONSOLEOUTPUT_H_INCLUDED
#define CONSOLEOUTPUT_H_INCLUDED
#include <PieceVisitor.h>
#include <OutputSystem.h>
#include <Colors.h>
#include <ConsoleTag.h>
#include <iostream>
class Coordinate;
/** surcharge de l'opérateur de flux << adaptée aux coordonnées.
  */
std::ostream & operator <<(std::ostream & os, Coordinate const & coord);
/** surcharge de l'opérateur de flux << adaptée aux couleurs
  */
std::ostream & operator <<(std::ostream & os, Color color);
/** surcharge de l'opérateur de flux << adaptée aux déplacements
  */
std::ostream & operator <<(std::ostream & os, Move const & move);
/** Spécialisation de la classe ConcreteOutput dans
  * un contexte d'affichage en mode console
  */
template <>
class ConcreteOutput<ConsoleTag> : public OutputSystem{
    /** Permet l'affichage du type réel d'une pièce
      * donnée.
      */
    class PieceShower : public PieceVisitor{
    public:
        bool visit(ConcretePiece<PawnTag> const &  )const {
            std::cout<<"Pion     ";
            return true;
        }
        bool visit(ConcretePiece<TowerTag> const & )const {
            std::cout<<"Tour     ";
            return true;
        }
        bool visit(ConcretePiece<KnightTag> const & )const {
            std::cout<<"Cavalier ";
            return true;
        }
        bool visit(ConcretePiece<BishopTag> const & )const {
            std::cout<<"Fou      ";
            return true;
        }
        bool visit(ConcretePiece<QueenTag> const & )const {
            std::cout<<"Dame     ";
            return true;
        }
        bool visit(ConcretePiece<KingTag> const & )const {
            std::cout<<"Roi      ";
            return true;
        }

    };
public:
    ConcreteOutput(ChessBoard const & board):OutputSystem(board){
    }
    /** Permet l'affichage d'une coordonnée.
      */
    void show(Coordinate const & coord){
        std::cout<<coord;
    }
    /** permet l'affichage d'une couleur.
      */
    void show(Color color){
        std::cout<<color;
    }
    /** Permet l'affichage d'un déplacement.
      */
    void show(Move const & move){
        std::cout<<move;
    }
    /** Permet l'affichage d'une pièce donnée
      * sans distinction de son type réel.
      */
    void show(Piece const & piece){
        PieceShower shower;
        piece.accept(shower);
    }
    /** Permet de représenter le joueur dont c'est le tour
      * de jouer.
      *
      * @param[in] color la couleur du joueur
      * à utiliser
      */
    virtual void playerTurn(Color color){
        std::cout<<color<<" joue : ";
    }
    /** Permet de représenter le vainqueur.
       *
       * @param[in] color La couleur représentant l'équipe du
       * vainqueur.
       */
    virtual void winnerIs(Color color){
        std::cout<<color<<" gagne."<<std::endl;
    }
    /** Permet de représenter une situation d'échec.
      */
    virtual void kingisInCheck(){
        std::cout<<"Echec"<<std::endl;
    }
    /** Permet de représenter une situation d'échec et mat.
      */
    virtual void kingIsMat(){
        std::cout<<"Echec et mat"<<std::endl;
    }
    /** Permet de représenter une situation de pat.
      */
    virtual void patSituation(){
        std::cout<<"Pat "<<std::endl
                 <<"Egalite "<<std::endl;
    }
    /** Permet de représenter l'abandon d'un joueur.
      *
      * @param[in] color la couleur représentant l'équipe du joueur
      * qui abandonne
      */
    virtual void hasSurrendered(Color color){
        std::cout<<color<<" a abandonné."<<std::endl;
    }
};
#endif
