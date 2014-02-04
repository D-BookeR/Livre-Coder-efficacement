#ifndef NEEDINITCOMMAND_H_INCLUDED
#define NEEDINITCOMMAND_H_INCLUDED

#include <Command.h>
#include <CommandTraits.h>
#include <Game.h>
template <typename T>
class ConcreteOutput;
/** Tag spécifique à la commande qui indique la nécessité
  * de réinitialiser la partie.
  */
struct NeedInitTag{
    /** La commande qui indique la nécessité de lancer
      * une nouvelle partie n'utilise que le système
      * d'affichage.
      */
    using CtorPolicy = OnlyOutputTrait;
    /** La commande indiquant au joueur la nécessité
      * de lancer une nouvelle partie n'a pas besoin
      * de mise à jour.
      */
    using UpdatePolicy = NoUpdateNeeded;
};
/** La commande indiquant au joueur la nécessité de
  * lancer une nouvelle partie, indépendante du
  * contexte d'entrées/sorties.
  *
  * Cette spécialisation totale définit le comportement
  * qui devra être observé lorsque le joueur souhaite effectuer un
  * petit roque tout en laissant le soin à la
  * spécialisation de la classe ConcreteCommand d'indiquer la
  * manière dont le système d'affichage spécifique doit en tenir
  * compte.
  */
template <>
class ExecutableCommand<NeedInitTag> : public Command{
public:
    ExecutableCommand(){
    }
    /** Provoque l'exécution de la commande
      *
      * Se contente de provoquer l'affichage approprié
      * @return resultNoMoved dans tous les cas.
      */
    CommandResult execute() const{
        printMe();
        return resultNoMoved;
    }
private:
    /** Provoque l'affichage d'un message indiquant au
      * joueur qu'il doit réinitialiser la partie.
      */
    virtual void printMe() const = 0;
};
/** Spécialisation partielle de la commande qui
  * indique la nécessité de réinitialiser la partie.
  */
template <typename ITag>
class ConcreteCommand<ITag, NeedInitTag> :
    public ExecutableCommand<NeedInitTag>{
public:
    ConcreteCommand(ConcreteOutput<ITag> & render):
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

    /** Provoque l'affichage d'un message indiquant au
      * joueur qu'il doit réinitialiser la partie.
      */
    virtual void printMe() const;
};
#endif
