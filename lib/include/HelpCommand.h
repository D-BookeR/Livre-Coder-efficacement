#ifndef HELPCOMMAND_H_INCLUDED
#define HELPCOMMAND_H_INCLUDED
#include <Command.h>
#include <CommandTraits.h>
template <typename T>
class ConcreteOutput;
/** Tag spécifique à la commande d'affichage de l'aide.
  */
struct HelpTag{
    /** La commande d'affichage de l'aide n'utilise que le système
      * d'affichage.
      */
    using CtorPolicy = OnlyOutputTrait;
    /** La commande d'aide n'a pas besoin de mise à jour.
      */
    using UpdatePolicy = NoUpdateNeeded;
};
/** La commande provoquant l'affichage de l'aide
  * mais indépendante du contexte d'entrées/sorties.
  *
  * Cette spécialisation totale définit le comportement
  * qui devra être observé lorsque le joueur veut obtenir
  * de l'aide tout en laissant le soin à la spécialisation
  * de la classe ConcreteCommand d'indiquer la manière dont
  * le système d'affichage spécifique doit en tenir compte.
  */
template <>
class ExecutableCommand<HelpTag> : public Command{
public:
    /** Exécute la commande
      *
      * Une demande d'aide n'a aucun effet sur les
      * données métier.  Elle se contente de provoquer
      * une réaction au niveau du système d'affichage.
      * @return resultNoMoved dans tous les cas
      * @note La réaction au niveau du système d'affichage
      * dépend spécifiquement du système d'affichage utilisé par
      * la partie.
      */
    CommandResult execute() const{
        printMe();
        return resultNoMoved;
    }
private:
    /** Provoque la réaction du système d'affichage face à une
      * demande d'aide.
      *
      * Ce comportement doit être redéfini pour chaque
      * spécialisatIon de ConcreteCommand spécifique à
      * un système d'entrées/sorties particulier.
      */
    virtual void printMe() const = 0;
};
/** Spécialisation partielle de la commande concrète occasionnant
  * l'affichage spécifique à une commande d'aide.
  */
template <typename ITag>
class ConcreteCommand<ITag, HelpTag> :
      public ExecutableCommand<HelpTag>{
public:
    ConcreteCommand(ConcreteOutput<ITag> & render):render(render){}
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
      */
    void printMe() const;
};
#endif
