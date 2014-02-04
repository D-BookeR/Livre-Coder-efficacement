#ifndef INPUTSYSTEM_H_INCLUDED
#define INPUTSYSTEM_H_INCLUDED
#include <NonCopyable.h>
#include <Colors.h>
#include <Move.h>
class Game;
class Command;
/** Abstraction de base pour les différents type de systèmes
  * d'entrées.
  *
  * Le système d'entrées peut varier de différentes manières:
  * - en fonction du système utilisé pour récupérer l'entrée du
  * joueur.
  * - afin de permettre la mise en place d'une intelligence
  * artificielle.
  * - afin de permettre la lecture de données enregistrées
  * - afin de permettre la réception de données reçues
  * par ailleurs
  * - ...
  *
  * Ces différentes variations ne doivent pas nous faire oublier que
  * les systèmes d'entrées seront connus par la partie
  * comme étant ... des systèmes d'entrées, sans plus de précision
  */
class InputSystem : private NonCopyable
{
public:
    InputSystem(Game & game):game_(game){}
    virtual ~InputSystem();
    /** Permet de récupérer n'importe quel type de commande.
      */
    virtual Command const & selectCommand() = 0;
    /** Permet de s'assurer que le système d'entrées est purgé
      * de toute commande.
      *
      * @note Un comportement par défaut qui ne fait rien est tout
      * à fait cohérent avec la plupart des systèmes d'entrées.
      * @note Ce comportement devra cependant être redéfini pour
      * certains systèmes d'entrées afin d'éviter d'entrer dans une
      * boucle de mauvais aloi si tous les éléments introduits n'ont
      * pas été "consommés".
      */
    virtual void clear();
    /** Permet de récupérer la partie en cours.
      *
      * Certaines commandes auront besoin de la partie en cours pour
      * être en mesure de récupérer certaines informations que seule
      * la partie est susceptible de leur fournir ou de la modifier.
      *
      * Pour que les instructions soient en mesure de disposer de
      * la partie, il faut que le système d'entrées soit en mesure
      * de la fournir.
      */
    Game & game() {return game_;}
    /** Permet de récupérer la partie en cours.
      *
      * Certaines commandes auront besoin de la partie en cours pour
      * être en mesure de récupérer certaines informations que seule
      * la partie est susceptible de leur fournir ou de la modifier.
      *
      * Pour que les instructions soient en mesure de disposer de
      * la partie, il faut que le système d'entrées soit en mesure
      * de la fournir.
      */
    Game const & game() const {return game_;}
    /** Permet de récupérer le déplacement sélectionné par
      * l'utilisateur.
      */
    Move const & selectedMove() const{return move_;}
    /** Permet de récupérer la couleur du joueur dont c'est le tour.
      */
    Color playerColor() const ;
protected:
    /** Le déplacement utilisé lors de l'émission de la commande.
      */
    Move move_;
private:
    /** La partie à laquelle le système d'entrée est rattaché.
      */
    Game & game_;
};
#endif
