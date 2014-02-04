#ifndef SIMULATEDPIECEPATHCHECKER_H_INCLUDED
#define SIMULATEDPIECEPATHCHECKER_H_INCLUDED
#include <PieceVisitor.h>
#include <Move.h>
class ChessBoard;
/** Vérifie que le trajet effectué par une pièce lui permet
  * d'atteindre sa destination en simulation.
  *
  * @sa PiecePathChecker pour plus d'information sur
  * les déplacements autorisés
  */
class SimulatedPiecePathChecker : public PieceVisitor
{
    public:
        SimulatedPiecePathChecker(ChessBoard const & board,
                                  Move const & simulated_,
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
          * @param[in] queen visitée.
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
    protected:
    private:
        /** Teste le trajet entre la position de départ et la
          * position d'arrivée.
          *
          * @param[in] color La couleur de la pièce déplacée.
          * @param[in] move Le déplacement à effectuer.
          * @return true si la pièce peut accéder à sa destination,
          * false dans le cas contraire.
          */
        bool testPath(Color color, Move const & move) const;
        size_t destination_;
        ChessBoard const &board_;
        Move simulated_;
};
#endif
