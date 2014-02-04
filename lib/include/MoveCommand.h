#ifndef MOVECOMMAND_H_INCLUDED
#define MOVECOMMAND_H_INCLUDED
#include <Colors.h>
#include <Command.h>
#include <CommandTraits.h>
#include <Move.h>
#include <PiecePathChecker.h>
#include <KingInCheckFunctions.h>
#include <iostream>
/** Tag spécifique à la commande permettant au joueur
  * d'effectuer un déplacement normal.
  */
struct MoveTag{
    /** La commande permettant de déplacer une pièce utilise le
      * système d'affichage et la partie.
      */
    using CtorPolicy = OutputAndChessboardTrait;
    /** La commande permettant au joueur de déplacer une pièce a
      * besoin de la mise à jour d'un déplacement.
      *
      * Le déplacement doit toujours correspondre à celui qui a été
      * introduit par l'utilisateur.
      */
    using UpdatePolicy = NeedColorAndMoveUpdate;
};
/** La commande permettant au joueur de déplacer une pièce
  * mais indépendante du contexte d'entrées/sorties.
  *
  * Cette spécialisation totale définit le comportement
  * qui devra être observé lorsque le joueur souhaite déplacer une
  * de ses pièces sur l'échiquier tout en laissant le soin à la
  * spécialisation de la classe ConcreteCommand d'indiquer la
  * manière dont le système d'affichage spécifique doit en tenir
  * compte.
  */
template <>
class ExecutableCommand<MoveTag> : public Command{
public:
    ExecutableCommand(ChessBoard & board):board(board){
    }
    /** L'échiquier utilisé par la partie en cours.
      *
      * La commande devra être en mesure de récupérer
      * un grand nombre d'informations que seul l'échiquier
      * est susceptible de lui fournir.
      *
      * Elle devra en outre, si le déplacement est jugé valide,
      * être en mesure de répercuter le déplacement sur l'échiquier.
      */
    ChessBoard & board;
    /** Le déplacement qui doit être effectué.
      */
    Move move;
    /** La couleur du joueur dont c'est le tour.
     */
    Color color;
    /** Provoque l'exécution de la commande.
      *
      * Vérifie la légalité du déplacement et le
      * reporte sur l'échiquier s'il est légal.
      * @return result resultMoved si le déplacement est
      * légal, resultUnallowed dans le cas contraire.
      */
    CommandResult execute() const{
        /* Le déplacement doit être valide et
         * s'appliquer à une pièce de la bonne couleur.
         */
        if(!move.isValid() ||
           color!= board.pieceColor(move.start)){
            invalidMove();
            return resultUnallowed;
        }
        /* Si la pièce ne sait pas atteindre la position
         * de destination, le déplacement est refusé.
         */
        PiecePathChecker pathChecker(board, move.finish);
        if(!pathChecker.check(board.pieceAt(move.start))){
            invalidMove();
            return resultUnallowed;
        }
        /* Si le déplacement met le joueur en situation
         * d'échec, il est refusé.
         */
        if(simulatedIsKingInCheck(board,move,color)){
            invalidMove();
            return resultUnallowed;
        }
        /* Arrivé ici, le déplacement est considéré comme
         * légal : on peut en afficher le résultat et le
         * reporter au niveau de l'échiquier.
         *
         */
        printMove();
        board.movePiece(move);
        /* La commande résulte bien en un déplacement valide. */
        return resultMoved;
    }
private:
    /** Provoque l'affichage d'un message en cas de déplacement
      * invalide.
      */
    virtual void invalidMove() const = 0;
    /** Provoque l'affichage d'un message du déplacement
      * qui a été validé.
      */
    virtual void printMove() const = 0;
};
/** Spécialisation partielle de la commande permettant
  * au joueur de déplacer n'importe quelle pièce.
  */
template <typename ITag>
class ConcreteCommand<ITag, MoveTag> :
    public ExecutableCommand<MoveTag>{
public:
    ConcreteCommand(ConcreteOutput<ITag> & render,
                    ChessBoard & board):
        ExecutableCommand<MoveTag>(board), render(render){}
    /** Le contexte d'affichage utilisé.
      *
      * La commande devra être en mesure d'envoyer ses instructions
      * au système d'affichage.  Ce membre permet à la commande
      * de s'adresser directement au système d'affichage concret,
      * sans avoir à passer par un intermédiaire.
      */
    ConcreteOutput<ITag> & render;
private:
    /** Provoque l'affichage d'un message en cas de déplacement
      * invalide.
      */
    virtual void invalidMove() const;
    /** Provoque l'affichage d'un message du déplacement
      * qui a été validé.
      */
    virtual void printMove() const;
};
#endif
