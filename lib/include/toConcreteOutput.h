#ifndef TOCONCRETEOUTPUT_H_INCLUDED
#define TOCONCRETEOUTPUT_H_INCLUDED
#include <Game.h>
/** Renvoie le render adapté au contexte d'entrées/sorties
  * utilisé
  *
  * @tparam ITag tag correspondant au contexte d'entrées/sorties à
  * utiliser
  * @param game partie à partir de laquelle récupérer le render
  * @param tag à utiliser, permettant de faire varier le
  * comportement de la fonction sur base du contexte
  * d'entrées/sorties à utiliser
  * @return une référence sur l'instance du type réel du render
  * utilisé
  */
template <typename ITag>
inline ConcreteOutput<ITag>& toConcreteOutput(Game & game, ITag const &){
    return static_cast<ConcreteOutput<ITag>&>(game.render());
}
#endif
