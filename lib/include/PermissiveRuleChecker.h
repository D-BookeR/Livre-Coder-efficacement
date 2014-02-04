#ifndef PERMISSIVERULECHECKER_H_INCLUDED
#define PERMISSIVERULECHECKER_H_INCLUDED
#include <PieceVisitor.h>
/** Permet de vérifier si un déplacement est admissible, indépendamment
  * de la situation sur l'échiquier.
  *
  * Un déplacement peut être admis pour un type de pièce particulier
  * si la situation sur l'éhciquier ne l'interdit pas.  Cette classe
  * vérifie si un dépalcement donné pourrait être envisagés pour une
  * pièce d'un type donné sans prendre en compte les restrictions
  * imposées par la situation sur l'échiquier.
  */
class PermissiveRuleChecker : public PieceVisitor
{
    public:
        PermissiveRuleChecker(size_t destination);
        /** Valide la règle générale de déplacement pour les pions.
          *
          * @param[in] pawn Le pion visité.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false autrement.
          */
        bool visit(ConcretePiece<PawnTag>   const & pawn) const;
        /** Valide la règle générale de déplacement pour les tours.
          *
          * @param[in] tower La tour visitée.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false autrement.
          */
        bool visit(ConcretePiece<TowerTag>  const & tower) const;
        /** Valide la règle générale de déplacement pour les
          * cavaliers.
          *
          * @param[in] knight Le cavalier visité.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false autrement.
          */
        bool visit(ConcretePiece<KnightTag> const & knight ) const;
        /** Valide la règle générale de déplacement pour les fous.
          *
          * @param[in] bishop Le fou visité.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false autrement.
          */
        bool visit(ConcretePiece<BishopTag> const & bishop) const;
        /** Valide la règle générale de déplacement pour les dames.
          *
          * @param[in] queen La dame visitée.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false autrement.
          */
        bool visit(ConcretePiece<QueenTag>  const & queen) const;
        /** Valide la règle générale de déplacement pour les rois.
          *
          * @param[in] king Le roi visité.
          * @return true si le déplacement est admis indépendamment
          * de la situation sur l'échiquier, false autrement.
          */
        bool visit(ConcretePiece<KingTag>   const & king) const;
    private:
        /** L'index de destination à utiliser pour vérifier
          * la validité du déplacement.
          */
        size_t destination_;
};
#endif
