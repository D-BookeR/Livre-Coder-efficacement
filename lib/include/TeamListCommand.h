#ifndef TEAMLISTCOMMAND_H_INCLUDED
#define TEAMLISTCOMMAND_H_INCLUDED
#include <Colors.h>
#include <Command.h>
#include <CommandTraits.h>
template <typename T>
class ConcreteOutput;
class ChessBoard;
/** Tag spécifique à la commande d'affichage d'une équipe
  * particulière.
  */
struct TeamTag{
    /** La commande d'affichage des pièces d'une équipe utilise le
      * système d'affichage et l'échiquier
      */
    using CtorPolicy = OutputAndChessboardTrait ;
    /** La commande d'affichage d'une équipedoit permettre la mise à
      * jour de la couleur de l'équipe concernée.
      */
    using UpdatePolicy = NeedColorUpdate;
};
/** La commande provoquant l'affichage de toutes les pièces d'une
  * équipe donnée mais indépendante du contexte d'entrées/sorties.
  *
  * Cette spécialisation totale définit le comportement
  * qui devra être observé lorsque le joueur veut obtenir
  * la liste des pièces d'une équipe qui sont encore en jeu
  * tout en laissant le soin à la spécialisation
  * de la classe ConcreteCommand d'indiquer la manière dont
  * le système d'affichage spécifique doit en tenir compte.
  */
template <>
class ExecutableCommand<TeamTag> : public Command{
public:
    ExecutableCommand(ChessBoard const & board):
                      board(board){}
    ChessBoard const & board;
    Color color;
    /** Provoque l'exécution de la commande
      *
      * Ne fait qu'une seule et unique chose : demander l'affichage
      * approprié.
      * @return resultNoMoved dans tous les cas.
      */
    CommandResult execute() const{
        for(size_t i = 0; i< board.indexMax; ++i){
            if(board.pieceColor(i)==color)
                printMe(board.pieceAt(i));
        }
        return resultNoMoved;
    }
private:
    /** Provoque la réaction du système d'affichage face à la pièce
      * sélectionnée
      *
      * Ce comportement doit être redéfini pour chaque
      * spécialisaiton de ConcreteCommand spécifique à un système
      * d'entrées/sorties particulier.
      * @param[in] toShow la pièce dont on veut afficher les
      * informations
      */
    virtual void printMe(Piece const & toShow) const = 0;
};
/** Spécialisation partielle de la commande permettant d'afficher
  * les pièces actives d'une équipe donnée.
  */

template <typename ITag>
class ConcreteCommand<ITag, TeamTag>:
      public ExecutableCommand<TeamTag>{
public:
    ConcreteCommand(ConcreteOutput<ITag> & render,
                    ChessBoard const & board):
                    ExecutableCommand<TeamTag>(board),
                        render(render){}
    /** Le contexte d'affichage utilisé.
      *
      * La commande devra être en mesure d'envoyer ses instructions
      * au système d'affichage.  Ce membre permet à la commande
      * de s'adresser directement au système d'affichage concret,
      * sans avoir à passer par un intermédiaire.
      */
    ConcreteOutput<ITag> & render;
private:

    /** Définition spécifique du comportement d'affichage.
      *
      * @note Ce comportement spécifique devra être défini sous la
      * forme d'une spécialisation totale de la fonction afin
      * d'utiliser les possibilités propres au système d'affichage
      * spécifique utilisé par l'application.
      * @param[in] toShow La pièce dont on veut afficher les
      * informations.
      */
    void printMe(Piece const & toShow) const;
};
#endif
