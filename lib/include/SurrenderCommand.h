#ifndef SURRENDERCOMMAND_H_INCLUDED
#define SURRENDERCOMMAND_H_INCLUDED
#include <Colors.h>
#include <Command.h>
#include <CommandTraits.h>
#include <Game.h>
template <typename T>
class ConcreteOutput;
/** Tag spécifique à la commande permettant au joueur
  * d'abandonner la partie en cours.
  */
struct SurrenderTag{
    /** La commande permettant d'abandonner la partie utilise le
      *  système d'affichage et la partie.
      */
    using CtorPolicy = OutputAndGameTrait;
    /** La commande permettant au joueur d'abandonner n'a pas besoin
      * de mise à jour.
      *
      * C'est toujours le joueur dont c'est le tour qui prend cette
      * décision.
      */
    using UpdatePolicy = NoUpdateNeeded;
};
/** La commande permettant au joueur d'abandonner la partie en cours
  * mais indépendante du contexte d'entrées/sorties.
  *
  * Cette spécialisation totale définit le comportement
  * qui devra être observé lorsque le joueur souhaite abandonner la
  * partie en cours tout en laissant le soin à la spécialisation
  * de la classe ConcreteCommand d'indiquer la manière dont
  * le système d'affichage spécifique doit en tenir compte.
  */
template <>
class ExecutableCommand<SurrenderTag> : public Command{
public:
    ExecutableCommand(Game & game):
                      game(game){}
    /** La partie en cours.
      *
      * La commande devra être en mesure de dialoguer avec la
      * partie en cours afin de lui signifier l'intention du joueur.
      */
    Game & game;
    /** Provoque l'exécution de la commande.
      *
      * Provoque l'affichage d'un message de confirmation
      * et modifie la partie en conséquence.
      * @return resultNoMoved dans tous les cas.
      */
    CommandResult execute() const{
        bool really = confirm();
        if(really){
            game.surrender();
            printMe();
        }
        return resultNoMoved;
    }
private:
    /** Demande la confirmation du souhait d'abandonner la partie.
      *
      * Ce comportement doit être redéfini pour chaque
      * spécialisation de ConcreteCommand spécifique à un système
      * d'entrées/sorties particulier.
      * @return true si le joueur souhaite vraiment abandonner la
      * partie, false dans le cas contraire.
      */
    virtual bool confirm() const = 0;
    /** Affiche le vainqueur de la partie.
      *
      * Ce comportement doit être redéfini pour chaque
      * spécialisation de ConcreteCommand spécifique à un système
      * d'entrées/sorties particulier.
      * Le vainqueur par forfait d'une partie dans laquelle un
      * joueur a abandonné est son adversaire. Nous devons donc
      * signaler que l'adversaire est le vainqueur.
      */
    virtual void printMe() const = 0;
};
/** Spécialisation partielle de la commande permettant
  * au joueur d'abandonner la partie en cours.
  */
template <typename ITag>
class ConcreteCommand<ITag, SurrenderTag>:
      public ExecutableCommand<SurrenderTag>{
public:
    ConcreteCommand(ConcreteOutput<ITag> & render,
                    Game & game):
        ExecutableCommand<SurrenderTag>(game), render(render){}
    /** Le contexte d'affichage utilisé.
      *
      * La commande devra être en mesure d'envoyer ses instructions
      * au système d'affichage.  Ce membre permet à la commande
      * de s'adresser directement au système d'affichage concret,
      * sans avoir à passer par un intermédiaire.
      */
    ConcreteOutput<ITag> & render;
private:
    /** Demande la confirmation du souhait d'abandonner la partie.
      *
      * @return true si le joueur souhaite vraiment abandonner la
      * partie, false dans le cas contraire.
      */
    virtual bool confirm() const;
    /** Affiche le vainqueur de la partie.
      *
      * Le vainqueur par forfait d'une partie dans laquelle un
      * joueur a abandonné est son adversaire. Nous devons donc
      * signaler que l'adversaire est le vainqueur.
      */
    virtual void printMe() const;
};
#endif
