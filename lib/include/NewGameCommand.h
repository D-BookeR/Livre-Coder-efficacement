#ifndef NEWGAMECOMMAND_H_INCLUDED
#define NEWGAMECOMMAND_H_INCLUDED
#include <Colors.h>
#include <Command.h>
#include <CommandTraits.h>
#include <Game.h>
template <typename T>
class ConcreteOutput;
/** Tag spécifique à la commande permettant au joueur
  * de lancer une nouvelle partie.
  */
struct NewGameTag{
    /** La commande permettant de lancer une nouvelle partie utilise
      * le  système d'affichage et la partie.
      */
    using CtorPolicy = OutputAndGameTrait;
    /** La commande permettant au joueur de démarrer une nouvelle
      * partie n'a pas besoin de mise à jour.
      */
    using UpdatePolicy = NoUpdateNeeded;
};
/** La commande permettant au joueur de lancer une nouvelle partie
  * mais indépendante du contexte d'entrées/sorties.
  *
  * Cette spécialisation totale définit le comportement
  * qui devra être observé lorsque le joueur souhaite abandonner la
  * partie en cours tout en laissant le soin à la spécialisation
  * de la classe ConcreteCommand d'indiquer la manière dont
  * le système d'affichage spécifique doit en tenir compte.
  */
template <>
class ExecutableCommand<NewGameTag> : public Command{
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
      * Demande confirmation du souhait de lancer une
      * nouvelle partie et reinitialise la partie si
      * nécessaire.
      * @return resultNoMoved dans tous les cas.
      */
    CommandResult execute() const{
        bool really = confirm();
        if(really){
            game.reinitialize();
            printMe();
        }
        return resultNoMoved;
    }
private:
    /** Demande la confirmation du souhait de lancer une nouvelle
      * partie.
      *
      * @return true si le joueur souhaite vraiment lancer une
      * nouvelle partie, false dans le cas contraire.
      */
    virtual bool confirm() const = 0;
    /** Affiche (éventuellement) un message indiquant qu'une
      * nouvelle partie est engagée.
      */
    virtual void printMe() const = 0;
};
/** Spécialisation partielle de la commande permettant
  * au joueur de lancer une nouvelle partie
  */
template <typename ITag>
class ConcreteCommand<ITag, NewGameTag>:
      public ExecutableCommand<NewGameTag>{
public:
    ConcreteCommand(ConcreteOutput<ITag> & render,
                    Game & game):
        ExecutableCommand<NewGameTag>(game),render(render){}
    /** Le contexte d'affichage utilisé.
      *
      * La commande devra être en mesure d'envoyer ses instructions
      * au système d'affichage.  Ce membre permet à la commande
      * de s'adresser directement au système d'affichage concret,
      * sans avoir à passer par un intermédiaire.
      */
    ConcreteOutput<ITag> & render;
private:
    /** Demande la confirmation du souhait de lancer une nouvelle
      * partie
      *
      * @return true si le joueur souhaite vraiment lancer une
      * nouvelle partie, false dans le cas contraire
      */
    virtual bool confirm() const;
    /** Affiche une confirmation visuelle du fait que la nouvelle
      * partie a bien été initialisée.
      */
    virtual void printMe() const;
};
#endif
