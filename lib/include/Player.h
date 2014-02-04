#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <Colors.h>
#include <InputSystem.h>
#include <cassert>
#include <memory>
/** La représentation de n'importe quel joueur.
  *
  * Le joueur s'occupe essentiellement de maintenir un pointeur
  * vers le système qui lui permettra d'émettre une commande à
  * destination de la partie.
  *
  * Il prend pleine et entière possession de ce système et doit
  * veiller à faire correctement le ménage lorsqu'il part ou
  * lorsqu'on lui donne un nouveau système d'entrées.
  *
  * Il est essentiellement identifiable par la couleur des pièces
  * avec lesquelles il joue.
  */
class Player : private NonCopyable
{
public:
    Player(Color color): color_(color){
        assert(color_ == colorBlack ||
               color_ == colorWhite);
    }
    /** Permet de récupérer la couleur de l'équipe du joueur.
      */
    Color color() const{return color_;}
    InputSystem & inputs(){
        return *(inputs_.get());
    }
    void changeInputs(InputSystem * newInput){
        inputs_.reset(newInput);
    }
    /** Permet de s'assurer que le joueur dispose d'un
      * système d'entrées.
      */
    bool hasInputSystem() const{
        return inputs_.get()!= nullptr;
    }
private:
    /** Le système d'entrées spécifique au joueur
      */
    std::unique_ptr<InputSystem> inputs_;
    /** La couleur de l'équipe du joueur.
      */
    Color color_;
};
#endif
