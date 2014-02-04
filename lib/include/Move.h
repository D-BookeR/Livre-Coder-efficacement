#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED
#include <cassert>
#include <cstddef>
/** La représentation d'un déplacement.
  *
  * Un déplacement permet d'identifier sans doute possible
  * la case de départ et la case d'arrivée d'une pièce
  * qui bouge.
  */
struct Move{
    /** Constructeur par défaut
      *
      * Construit un déplacement clairement invalide
      */
    Move():start(indexMax),finish(indexMax){}
    /** Constructeur du déplacement.
      *
      * Permet la définition d'un déplacement valide.
      * @pre La case de départ est valide.
      * @pre La case d'arrivée est valide.
      * @param[in] start l'index de la case de départ du
      * déplacement.
      * @param[in] finish l'index de la case d'arrivée du
      * déplacement.
      */
    Move(size_t start, size_t finish):start(start),finish(finish){
        assert(isValid());
    }
    /** Représente un index invalide.
      *
      * Les déplacements sont représentés sous la forme de l'index
      * de départ et d'arrivée de la pièce déplacée.  Ces index
      * correspondent à ceux de la case telle qu'utilisée en interne
      * par l'échiquier.
      *
      * Cette valeur constante représente le premier index connu
      * pour être invalide (tout index égal ou supérieur à cette
      * valeur sera considéré comme un index invalide).
      */
    static const size_t indexMax = 64;
    /** Index correspondant à la position de départ de la pièce
      * à déplacer.
      */
    size_t start;
    /** Index correspondant à la position d'arrivée de la pièce
      * à déplacer.
      */
    size_t finish;
    /** Permet de s'assurer que le déplacement est valide
      *
      * @return true si les index de départ et d'arrivée
      * correspondent tous deux à des cases de l'échiquier,
      * false dans le cas contraire.
      */
    bool isValid() const{
        return start  < indexMax &&
               finish < indexMax;
    }
};
/** Permet de déterminer le nombre de cases traversées lors d'un
  * déplacement.
  *
  * La plupart des algorithmes basés sur les directions devront
  * disposer du nombre de cases traversées lors du déplacement.
  *
  * Cette fonction effectue le calcul du nombre de cases traversées.
  * @pre Le déplacement analysé est valide.
  * @pre Le déplacement s'effectue dans l'une des huit grandes
  * directions.
  * @param[in] move Le déplacement à prendre en compte.
  * @return Le nombre de cases traversées.
  * @post Aucun déplacement ne peut traverser plus de 7 cases.
  */
size_t traversedSquares(Move const & move);

#endif
