#ifndef EXITCOMMAND_H_INCLUDED
#define EXITCOMMAND_H_INCLUDED
#include <Colors.h>
#include <Command.h>
#include <CommandTraits.h>
#include <Game.h>
template <typename T>
class ConcreteOutput;
/** Tag spécifique à la commande permettant au joueur de
  * quitter le jeu
  */
struct ExitTag{
    /** La commande permettant de quitter l'application utilise le
      * système d'affichage et la partie
      */
    using CtorPolicy = OutputAndGameTrait;
    /** La commande permettant au joueur de quitter le jeu n'a pas
      * besoin de mise à jour
      */
    using UpdatePolicy = NoUpdateNeeded;
};
/** La commande permettant au joueur de quitter l'application
  * mais indépendante du contexte d'entrées/sorties.
  *
  * Cette spécialisation totale définit le comportement
  * qui devra être observé lorsque le joueur souhaite quitter
  * l'application tout en laissant le soin à la spécialisation
  * de la classe ConcreteCommand d'indiquer la manière dont
  * le système d'affichage spécifique doit en tenir compte.
  */
template <>
class ExecutableCommand<ExitTag> : public Command{
public:
    ExecutableCommand(Game & game):
                      game(game){}
    /** La partie en cours.
      *
      * La commande devra être en mesure de dialoguer avec la
      * partie en cours afin de lui signifier l'intention du joueur.
      */
    Game & game;
    /** Provoque l'exécution de la commande
      *
      * Provoque l'affichage d'un message de confirmation
      * et modifie la partie en conséquence.
      * @return resultNoMoved dans tous les cas.
      */
    CommandResult execute() const{
        bool reallyQuit = confirm();
        if(reallyQuit){
            game.quit();
            printMe();
        }
        return resultNoMoved;
    }
private:
    /** Demande la confirmation du souhait de quitter la partie.
      *
      * Ce comportement doit être redéfini pour chaque
      * spécialisation de ConcreteCommand spécifique à un système
      * d'entrées/sorties particulier.
      * @return true si le joueur souhaite vraiment quitter
      * la partie, false dans le cas contraire.
      */
    virtual bool confirm() const = 0;
    /** Affiche un dernier message avant de quitter la partie.
      *
      * Ce comportement doit être redéfini pour chaque
      * spécialisation de ConcreteCommand spécifique à un système
      * d'entrées/sorties particulier.
      */
    virtual void printMe() const = 0;
};
/** Spécialisation partielle de la commande permettant
  * au joueur de quitter l'application
  */
template <typename ITag>
class ConcreteCommand<ITag, ExitTag>:
      public ExecutableCommand<ExitTag>{
public:
    ConcreteCommand(ConcreteOutput<ITag> & render,
                    Game & game):
        ExecutableCommand<ExitTag>(game),render(render){}
    /** Le contexte d'affichage utilisé.
      *
      * La commande devra être en mesure d'envoyer ses instructions
      * au système d'affichage.  Ce membre permet à la commande
      * de s'adresser directement au système d'affichage concret,
      * sans avoir à passer par un intermédiaire.
      */
    ConcreteOutput<ITag> & render;
private:
    /** Demande la confirmation du souhait de quitter la partie.
      *
      * Ce comportement doit être redéfini pour chaque
      * spécialisation de ConcreteCommand spécifique à un système
      * d'entrées/sorties particulier.
      * @return true si le joueur souhaite vraiment quitter
      * la partie, false dans le cas contraire.
      */
    virtual bool confirm() const;
    /** Affiche un dernier message avant de quitter la partie.
      *
      * Ce comportement doit être redéfini pour chaque
      * spécialisation de ConcreteCommand spécifique à un système
      * d'entrées/sorties particulier.
      */
    virtual void printMe() const;
};
#endif
