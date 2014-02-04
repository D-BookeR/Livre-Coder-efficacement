#ifndef KINGINCHECKFUNCTIONS_H_INCLUDED
#define KINGINCHECKFUNCTIONS_H_INCLUDED
#include <Colors.h>
class ChessBoard;
class Move;
/** Permet de déterminer si le roi d'une couleur particulière
  * est en situation d'échec.
  *
  * @pre La couleur testée représente la couleur d'une équipe (colorWhite
  * ou colorBlack).
  * @param[in] board L'échiquier représentant la situation à tester.
  * @param[in] color La couleur du roi à tester.
  * @return true si le roi de la couleur indiquée est en situation
  * d'échec, false dans le cas contraire.
  */
bool isKingInCheck(ChessBoard const & board, Color color);
/** Permet de déterminer anticipativement si le roi d'une couleur
  * particulière est en situation d'échec.
  *
  * @pre Le déplacement doit être valide (les positions de départ
  * et d'arrivée du déplacement doivent être des positions valides
  * sur l'échiquier).
  * @pre La couleur testée est la couleur d'une équipe (colorWhite
  * ou colorBlack).
  * @param[in] board L'échiquier représentant la situation à tester.
  * @param[in] simulated Le déplacement devant être simulé.
  * @param[in] color La couleur du roi à tester.
  * @return true si le roi de la couleur indiquée est en situation
  * d'échec, false dans le cas contraire.
  */
bool simulatedIsKingInCheck(ChessBoard const & board,
                            Move const & simulated,
                            Color color);
#endif
