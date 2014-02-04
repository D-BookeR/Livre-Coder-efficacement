#ifndef SIMULATEDPERMISSIVERULECHECKER_H_INCLUDED
#define SIMULATEDPERMISSIVERULECHECKER_H_INCLUDED
#include <PieceVisitor.h>
#include <Move.h>
/** Vérifie si les règles permissives sont respectées lors d'une
  * simulation.
  *
  * @sa href PermissiveRuleChecker pour plus d'informations.
  */
class SimulatedPermissiveRuleChecker : public PieceVisitor
{
    public:
        SimulatedPermissiveRuleChecker(Move const & move,
                                       size_t destination);
        /** Valide la règle générale de déplacement pour les pions.
          *
          * @param[in] pawn Le pion visité.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false dans le cas
          * contraire.
          */
        bool visit(ConcretePiece<PawnTag>   const & pawn) const;
        /** Valide la règle générale de déplacement pour les tours.
          *
          * @param[in] tower La tour visitée.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false dans le cas
          * contraire.
          */
        bool visit(ConcretePiece<TowerTag>  const & tower) const;
        /** Valide la règle générale de déplacement pour les
          * cavaliers.
          *
          * @param[in] knight Le cavalier visité.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false dans le cas
          * contraire.
          */
        bool visit(ConcretePiece<KnightTag> const & knight ) const;
        /** Valide la règle générale de déplacement pour les fous.
          *
          * @param[in] bishop Le fou visité.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false dans le cas
          * contraire.
          */
        bool visit(ConcretePiece<BishopTag> const & bishop) const;
        /** Valide la règle générale de déplacement pour les dames.
          *
          * @param[in] queen La dame visitée.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false dans le cas
          * contraire.
          */
        bool visit(ConcretePiece<QueenTag>  const & queen) const;
        /** Valide la règle générale de déplacement pour les rois.
          *
          * @param[in] king Le roi visité.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false dans le cas
          * contraire.
          */
        bool visit(ConcretePiece<KingTag>   const & king) const;
    protected:
    private:
        size_t destination_;
        Move simulated_;
};
#endif
