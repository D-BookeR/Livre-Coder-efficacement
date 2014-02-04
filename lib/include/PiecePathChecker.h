#ifndef PIECEPATHCHECKER_H_INCLUDED
#define PIECEPATHCHECKER_H_INCLUDED
#include <PieceVisitor.h>
class ChessBoard;
class Move;
/** Vérifie que le trajet effectué par une pièce lui permet
  * d'atteindre sa destination.
  *
  * Un dépalcement ne peut être définitivement validé et
  * reporté sur l'échiquier que si le déplacement est
  * admissible pour la pièce particulière qui tente le déplacement
  * et que la situation sur l'échiquier n'empêche pas la pièce
  * d'atteidnre sa destination.
  *
  * Cette classe s'assure que la disposition sur l'échiquier
  * n'empêche pas une pièce d'un type particulier d'atteindre la
  * destination d'un déplacement admis pour le type de pièce en
  * question.
  */
class PiecePathChecker : public PieceVisitor
{
    public:
        PiecePathChecker(ChessBoard const & board,
                        size_t destination);
        /** Valide le déplacement pour les pions en fonction de la
          * situation sur l'échiquier.
          *
          * @param[in] pawn Le pion visité.
          * @return true si le pion peut atteindre sa destination,
          * false dans le cas contraire.
          */
        bool visit(ConcretePiece<PawnTag>   const & pawn) const;
        /** Valide le déplacement pour les tours en fonction de
          * la situation sur l'échiquier.
          *
          * @param[in] tower La tour visitée.
          * @return true si la tour peut atteindre sa
          * destination, false dans le cas contraire.
          */
        bool visit(ConcretePiece<TowerTag>  const & tower) const;
        /** Valide le déplacement pour les cavaliers en fonction de
          * la situation sur l'échiquier.
          *
          * @param[in] knight Le cavalier visité.
          * @return true si le cavalier peut atteindre sa
          * destination, false dans le cas contraire.
          */
        bool visit(ConcretePiece<KnightTag> const & knight ) const;
        /** Valide le déplacement pour les fous en fonction de la
          * situation sur l'échiquier.
          *
          * @param[in] bishop Le fou visité.
          * @return true si le fou peut atteindre sa destination,
          * false dans le cas contraire.
          */
        bool visit(ConcretePiece<BishopTag> const & bishop) const;
        /** Valide le déplacement pour les dames en fonction de la
          * situation sur l'échiquier.
          *
          * @param[in] queen La dame visitée.
          * @return true si la dame peut atteindre sa destination,
          * false dans le cas contraire.
          */
        bool visit(ConcretePiece<QueenTag>  const & queen) const;
        /** Valide le déplacement pour les rois en fonction de la
          * situation sur l'échiquier.
          *
          * @param[in] king Le roi visité.
          * @return true si le roi peut atteindre sa destination,
          * false dans le cas contraire.
          */
        bool visit(ConcretePiece<KingTag>   const & king) const;
    private:
        /** Teste le trajet entre la position de départ et la
          * position d'arrivée
          *
          * @param[in] color La couleur de la pièce déplacée.
          * @param[in] move Le déplacement à effectuer.
          * @return true si la pièce peut accéder à sa destination,
          * false dans le cas contraire.
          */
        bool testPath(Color color, Move const & move) const;
        /** La position de destination à prendre en compte pour le
          * déplacement.
          */
        size_t destination_;
        /** L'échiquier utilisé lors de la vérification.
          */
        ChessBoard const &board_;
};
#endif
