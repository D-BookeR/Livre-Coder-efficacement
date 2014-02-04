#ifndef COMMANDSENDER_H_INCLUDED
#define COMMANDSENDER_H_INCLUDED
#include <NonCopyable.h>
class Command;
class InputSystem;
/** Abstraction d'une classe permettant d'émettre une commande.
*
*/
class CommandSender : public NonCopyable
{
public:
    CommandSender(InputSystem & input);
    virtual ~CommandSender();
    /** Emet la commande.
      */
    virtual Command const & emitCommand() const =0;
protected:
    /** Permet aux classes dérivées d'interroger le
      * système d'entrées afin d'en récupérer les données.
      */
    InputSystem & system_;
};
/** Déclaration anticipée des types concrets permettant d'envoyer
  * une commande.
  *
  * Nous devrons définir une spécialisation partielle de cette
  * classe pour chaque commande que nous pourrons envisager
  * @tparam ITag le tag représentant le contexte d'entrées/sortie
  * utilisé en cours de partie
  * @tparam CTag le tag représentant la commande à envoyer
  */
template <typename ITag, typename CTag>
class ConcreteCommandSender;
#endif
