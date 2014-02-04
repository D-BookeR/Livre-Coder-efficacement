#ifndef PIECEVISITOR_H_INCLUDED
#define PIECEVISITOR_H_INCLUDED
#include <Piece.h>
#include <PieceTags.h>
template <typename T>
class ConcretePiece;
/** Abstraction du visiteur de pièces.
  *
  * Cette classe est destinée à servir de classe de base à toute
  * classe ayant besoin de recourir au double dispatch afin de
  * prendre en compte le type réel des pièces qu'elle manipule.
  */
class PieceVisitor : private NonCopyable{
    public:
        bool check(Piece const & );
        /** Permet de manipuler spécifiquement une pièce qui n'en
          * est pas une (objet nul).
          *
          * Voici la seule surcharge de la fonction visit() qui ne
          * sera jamais redéfinie, tous les visiteurs renverront
          * false à chaque fois qu'ils croiseront une pièce qui n'en
          * est pas une.
          * @param[in] nopiece La pièce inexistante.
          * @return false dans tous les cas.
          */
        bool visit(ConcretePiece<NotAPieceTag> const &
                   nopiece) const;
        /** Permet de manipuler un pion de manière spécifique.
          *
          * @param[in] pawn Le pion à visiter.
          * @return false dans tous les cas (comportement par
          * défaut, à redéfinir selon les besoins).
          */
        virtual bool visit(ConcretePiece<PawnTag>   const &
                           pawn) const;
        /** Permet de manipuler une tour de manière spécifique.
          *
          * @param[in] tower La tour à visiter.
          * @return false dans tous les cas (comportement par
          * défaut, à redéfinir selon les besoins)
          */
        virtual bool visit(ConcretePiece<TowerTag>  const &
                           tower) const;
        /** Permet de manipuler un cavalier de manière spécifique.
          *
          * @param[in] knight le cavalier à visiter.
          * @return false dans tous les cas (comportement par
          * défaut, à redéfinir selon les besoins).
          */
        virtual bool visit(ConcretePiece<KnightTag> const &
                           knight) const;
        /** Permet de manipuler un fou de manière spécifique.
          *
          * @param[in] bishop le fou à visiter.
          * @return false dans tous les cas (comportement par
          * défaut, à redéfinir selon les besoins).
          */
        virtual bool visit(ConcretePiece<BishopTag> const &
                           bishop) const;
        /** Permet de manipuler une dame de manière spécifique.
          *
          * @param[in] queen la reine à visiter.
          * @return false dans tous les cas (comportement par
          * défaut, à redéfinir selon les besoins).
          */
        virtual bool visit(ConcretePiece<QueenTag>  const &
                           queen) const;
        /** Permet de manipuler un roi de manière spécifique.
          *
          * @param[in] king le roi à visiter.
          * @return false dans tous les cas (comportement par
          * défaut, à redéfinir selon les besoins).
          */
        virtual bool visit(ConcretePiece<KingTag>   const &
                           king) const=0;
    protected:
        /** Constructeur par défat, protégé car accessible
          * uniquement aux classes dérivées.
          */
        PieceVisitor(){
        }
        /** Destructeur, protégé car accessible uniquement
          * aux classe dérivées.
          */
        ~PieceVisitor(){
        }
};
#endif
