#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED
#include <NonCopyable.h>
/** Le résultat de la commande.
  *
  * Nous ne pouvons pas nous contenter d'un booléen comme résultat
  * de la commande.
  *
  * Il se peut en effet que la commande ne soit pas un déplacement,
  * ce qui implique que le joueur n'a simplement pas joué.
  *
  * Par contre, il peut aussi avoir introduit un déplacement non
  * autorisé, et dans ce cas, nous nous attendons à ce que la
  * partie réagisse en le lui signalant
  */
enum CommandResult{
    resultUnallowed, /**< Le déplacement n'était pas autorisé.
                       *
                       */
    resultMoved,     /**< La commande a effectué un déplacement avec
                       * succès.
                       *
                       */
    resultNoMoved    /**< La commande s'est correctement exécutée
                       * mais n'a pas occasionné de déplacement.
                       */
};
/** Abstraction de base représentant n'importe quelle commande.
  *
  * Quelle que puisse être la commande introduite par le joueur, la
  * partie n'aura jamais connaissance de la commande que comme étant
  * une commande de base.
  */
class Command : private NonCopyable
{
    public:
        virtual ~Command();
    /** Permet à la partie d'exécuter la commande
      *
      * @return resultMoved si la commande a provoqué un
      * déplacement.
      * @return resultUnallowed si le déplacement souhaité n'est pas
      * autorisé.
      * @return resultNoMoved pour les commandes qui ne provoquent
      * pas de déplacement.
      */
    virtual CommandResult execute() const = 0 ;
};
/** Déclaration anticipée relative à n'importe quelle commande
  * susceptbile d'être exécutée
  *
  * @tparam Tag Le tag représentant la commande à exécuter.
  *
  * Pour chaque commande pour laquelle on envisage de permettre
  * l'exécution, il suffira de fournir une spécialisation totale
  * de cette classe afin de définir le comportement que la commande
  * doit présenter au moment de son exécution.
  *
  * @note Chaque spécialisation totale de cette classe définira le
  * comportement CommandResult execute() const adapté à la commande
  * à définir et déclarera, le cas échéant, un certain nombre de
  * comportements utiles à l'affichage sous la forme de fonctions
  * virtuelles pures.
  */
template <typename CTag>
class ExecutableCommand;
/** Déclaration anticipée pour toute commande susceptible d'être
  * exécutée dans un contexte d'entrées/sorties spécifique.
  *
  * @tparam ITag contexte d'entrées/sorties spécifique dans lequel
  * la commande est exécutée
  * @tparam CTag Le tag représentant la commande exécutée.
  *
  * Pour chaque commande réellement exécutée, nous spécialiserons
  * les comportements déclarés dans les spécialisations totales de
  * ExecutableCommand spécifiquement par rapport au contexte de
  * sortie utilisé.
  */
template <typename ITag, typename CTag>
class ConcreteCommand;
#endif
