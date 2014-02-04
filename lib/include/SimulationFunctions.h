#ifndef SIMULATIONFUNCTIONS_H_INCLUDED
#define SIMULATIONFUNCTIONS_H_INCLUDED
class ChessBoard;
/** Permet d'obtenir l'index d'une position qui nous intéresse
  * dans le cadre d'une simulation.
  *
  * @pre Le déplacement doit être valide (les positions de départ
  * et d'arrivée du déplacement doivent être des positions valides
  * sur l'échiquier).
  * @param[in] move Le déplacement à simuler.
  * @param[in] position La position qui nous intéresse.
  * @return Un index invalide si la position qui nous intéresse
  * correspond à la position de départ du déplacement à simuler.
  * @return L'index de la position de départ du déplacement si la
  * position qui nous intéresse correspond à la position de
  * destination du déplacement à simuler.
  * @return position si la position qui nous intéresse n'entre pas
  * en ligne de compte dans le déplacement à simuler.
  */
size_t simulatedIndex(Move const & move, size_t position);
/** Permet de savoir si la case indiquée est libre
  * dans une situation simulée.
  *
  * @pre Le déplacement doit être valide (les positions de départ
  * et d'arrivée du déplacement doivent être des positions valides
  * sur l'échiquier).
  * @param[in] board L'échiquier à utiliser.
  * @param[in] move Le déplacement à simuler.
  * @param[in] index L'index de la case qui nous intéresse.
  * @return true s'il n'y a aucune pièce sur la case
  * indiquée, false dans le cas contraire.
  */
bool isSimulatedSquareEmpty(ChessBoard const & board,
                            Move const & move,
                            size_t index);
/** Permet de récupérer la couleur de la pièce se trouvant
  * sur la case indiquée dans une situation simulée.
  *
  * @pre Le déplacement doit être valide (les positions de départ
  * et d'arrivée du déplacement doivent être des positions valides
  * sur l'échiquier).
  * @param[in] board L'échiquier à utiliser.
  * @param[in] move Le déplacement à simuler.
  * @param[in] index L'index de la case qui nous intéresse.
  * @return colorWhite ou colorBlack selon l'équipe à
  * laquelle appartient la pièce s'il y en a une,
  * colorNone dans le cas contraire.
  */
Color simulatedPieceColor(ChessBoard const & board,
                          Move const & move,
                          size_t index);
/** Permet de récupérer la pièce qui se trouve sur la case
  * indiquée dans une situation simulée.
  *
  * @pre Le déplacement doit être valide (les positions de départ
  * et d'arrivée du déplacement doivent être des positions valides
  * sur l'échiquier).
  * @param[in] board L'échiquier à utiliser.
  * @param[in] move Le déplacement à simuler.
  * @param[in] index L'index de la case qui nous intéresse.
  *
  * @return la pièce se trouvant sur la case
  */
const Piece & simulatedPieceAt(ChessBoard const & board,
                               Move const & move,
                               size_t index);

#endif
