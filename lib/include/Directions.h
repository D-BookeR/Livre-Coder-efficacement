#ifndef DIRECTIONS_H_INCLUDED
#define DIRECTIONS_H_INCLUDED
class Move;
enum Directions{
    dirUnset    = 65, /**< une direction invalide
                        *
                        * représente le fait qu'un déplacement ne
                        * s'effectue pas dans l'une des huit grandes
                        * directions
                        */
    front       =  8,
    back        = -8,
    left        = -1,
    right       =  1,
    frontLeft   =  7,
    frontRight  =  9,
    backLeft    = -9,
    backRight   = -7
};
/** Détermine la direction d'un déplacement.
  *
  * @pre Le déplacement analysé est valide.
  * @param[in] move Le déplacement à analyser.
  * @return La valeur énumérée correspondant à la direction du
  * déplacement, dirUnset si le déplacement ne suit pas une
  * direction particulière.
  */
Directions findDirection(Move const & move);
#endif
