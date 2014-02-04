#ifndef ALLPIECELISTCOMMAND_H_INCLUDED
#define ALLPIECELISTCOMMAND_H_INCLUDED
#include <Command.h>
#include <CommandTraits.h>
class ChessBoard;
template <typename T>
class ConcreteOutput;
/** Tag spécifique à la commande d'affichage de toutes les pièces
  * actives ( = présentes sur l'échiquier)
  */
struct AllPiecesTag{
    /** La commande d'affichage de toutes les pièces actives
      * n'utilise que le système d'affichage.
      */
    using CtorPolicy = OutputAndChessboardTrait;
    /** La commande d'affichage de toutes les pièces actives n'a pas
      * besoin de mise à jour.
      */
    using UpdatePolicy = NoUpdateNeeded;
};
/** La commande provoquant l'affichage de toutes les pièces actives
  * mais indépendante du contexte d'entrées/sorties.
  *
  * Cette spécialisation totale définit le comportement
  * qui devra être observé lorsque le joueur veut obtenir
  * la liste des pièces d'une équipe qui sont encore en jeu
  * tout en laissant le soin à la spécialisation
  * de la classe ConcreteCommand d'indiquer la manière dont
  * le système d'affichage spécifique doit en tenir compte.
  */
template <>
class ExecutableCommand<AllPiecesTag> : public Command{
public:
    ExecutableCommand(ChessBoard const & board):
                      board(board){}
    /** L'échiquier utilisé par la partie en cours
      *
      * La commande devra être en mesure de récupérer
      * un grand nombre d'informations que seul l'échiquier
      * est susceptible de lui fournir.
      *
      * Elle devra en outre, si le déplacement est jugé valide,
      * être en mesure de répercuter le déplacement sur l'échiquier.
      */
    ChessBoard const & board;
    /** Provoque l'exécution de la commande
      *
      * Ne fait qu'une seule et unique chose : demander l'affichage
      * approprié.
      * @return resultNoMoved dans tous les cas
      */
    CommandResult execute() const{
        printMe();
        return resultNoMoved;
    }
private:
    /** Provoque l'affichage des pièces des deux équipes en présence
      *
      * Ce comportement doit être redéfini pour chaque
      * spécialisation de ConcreteCommand spécifique à un système
      * d'entrées/sorties particulier
      */
    virtual void printMe() const = 0;
};
/** Spécialisation partielle de la commande permettant d'afficher
  * toutes les pièces actives.
  */
template <typename ITag>
class ConcreteCommand<ITag, AllPiecesTag>:
      public ExecutableCommand<AllPiecesTag>{
public:
    ConcreteCommand(ConcreteOutput<ITag> & render,
                    ChessBoard const & board):
                    ExecutableCommand<AllPiecesTag>(board),
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
      * @note Contrairement aux autres classes similaires, nous
      * disposons déjà de tout ce qu'il faut pour implémenter cette
      * fonction, sans que cela ne risque de nuire à la souplesse du
      * système.
      */
    void printMe() const;
};
#endif
