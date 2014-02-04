#ifndef KINGIDENTIFIER_H_INCLUDED
#define KINGIDENTIFIER_H_INCLUDED
#include <PieceVisitor.h>
class ChessBoard;
/** Permet de savoir si la pièce envisagée est un roi.
  *
  * Nous aurons régulièrement besoin d'identifier le roi parmi les
  * autres pièces.
  *
  * Cette classe nous permet de savoir si la pièce considérée est
  * un roi ou non.
  */
class KingIdentifier : public PieceVisitor
{
    public:
        KingIdentifier(Color color = colorNone);
        bool visit(ConcretePiece<KingTag> const & king) const;
    private:
        /** La couleur du roi recherché.
          *
          * Les valeur possibles sont :
          * - colorNone : permet d'identifier n'importe quel roi
          * - colorWhite : permet d'identifier le roi blanc
          * - colorBlack : permet d'identifier le roi noir
          */
        Color color_;
};
/** Détermine la position du roi d'une couleur donnée sur
  * l'échiquier
  *
  * Nous aurons régulièrement besoin de déterminer la position d'un
  * roi sur l'échiquier afin de pouvoir repérer les situations
  * d'échec.
  *
  * Cette fonction permet de récupérer la position recherchée.
  * @pre La couleur du roi recherchée correspond à une équipe
  * (colorWhite ou colorBlack uniquement).
  * @param[in] board L'échiquier à prendre en compte.
  * @param[in] color La couleur du roi recherché.
  * @return L'indice de la case de l'échiquier sur laquelle se
  * trouve le roi recherché.
  * @post L'indice recherché est un indice valide (compris dans
  * l'intervalle [0,64[ ).
  */
size_t findKing(ChessBoard const & board, Color color);
#endif
