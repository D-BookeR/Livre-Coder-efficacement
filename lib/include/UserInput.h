#ifndef USERINPUT_H_INCLUDED
#define USERINPUT_H_INCLUDED
#include <InputSystem.h>
class CommandSender;
/** Abstraction représentant n'importe quel système d'introduction
  * de commande par un joueur humain.
  *
  * Cette classe intermédiaire définit le comportement commun à tout
  * système d'entrées de commande par l'utilisateur qui est
  * l'émission d'une commande, reportant à plus tard la gestion de
  * l'algorithme qui permettra de sélectionner la commande adaptée
  * au contexte d'entrées/sorties utilisé par la partie.
  */
class UserInput : public InputSystem
{
public:
    UserInput(Game & game);
    /** Permet de récupérer n'importe quel type de commande
      */
    virtual Command const & selectCommand();
private:
    /** Comportement de sélection de l'émetteur de commande
      * adéquat.
      *
      * Ce comportement utilise l'idiome NVI afin de permettre
      * au développeur des classes dérivées de préciser la logique
      * permettant de déterminer quelle commande sera émise.
      */
    virtual CommandSender const & selectSender() = 0;
};
/** Déclaration anticipée commune pour tous les types concrets
  * d'entrées utilisateur, dépendant du contexte d'entrées/sorties
  * utilisé par la partie
  */
template <typename Tag>
class ConcreteInput;

#endif
