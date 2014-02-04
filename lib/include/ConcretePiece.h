#ifndef CONCRETEPIECE_H_INCLUDED
#define CONCRETEPIECE_H_INCLUDED
#include <PieceTags.h>
#include <Piece.h>
#include <type_traits>
#include <cassert>
/** Permet de représenter n'importe quelle pièce
  * susceptible de prendre place sur l'échiquier.
  */
template <typename TAG>
class ConcretePiece : public Piece{
    public:
        using tag_type = TAG;
        static_assert(std::is_base_of<PieceTag, tag_type>::value,
        "Les seuls tags admis doivent hériter de PieceTag");
        template < typename T = TAG,
                    typename  = typename
                    std::enable_if<
                    !std::is_same<T, NotAPieceTag>::value>::type>
        ConcretePiece(Color col,
                      size_t x,
                      size_t y,
                      bool moved = false): Piece(col, x, y, moved){
        }
        template < typename T = TAG,
                   typename   = typename
                        std::enable_if<
                        std::is_same<T, NotAPieceTag>::value>::type>
        ConcretePiece(): Piece(){
        }
        virtual bool accept(PieceVisitor const & v) const{
            return v.visit(*this);
        }
};
/** Spécialisation totale de la pièce concrète pour les
  * pions.
  *
  * Les pions présentent la particularité par rapport aux
  * autres pièces de ne pouvoir se déplacer que dans un
  * seul sens, déterminé par leur couleur.
  *
  * La spécialisation que voici rajoute la possibilité de
  * déterminer le sens du déplacement du pion.
  */
template <>
class ConcretePiece<PawnTag> : public Piece{
    public:
        using tag_type = PawnTag;
        ConcretePiece(Color col, size_t x, size_t y,
                      bool moved = false): Piece(col, x, y, moved){
        }
        virtual bool accept(PieceVisitor const & v) const{
            return v.visit(*this);
        }
        /** Permet à l'utilisateur de connaitre le sens de
          * déplacement d'un pion particulier
          *
          * Le multiplicateur renvoyé permet d'obtenir une valeur
          * absolue correspondant à la direction du déplacement
          * @return 1 pour les pions blancs, -1 pour les pions noirs
          */
        int multiplier() const{
            return (color() == colorWhite ? 1 : -1);
        }
};
/** Alias de type pour les "non pièce", fourni pour la
  * facilité.
  */
using NoPiece = ConcretePiece<NotAPieceTag>;
/** Alias de type pour les pions, fourni pour la
  * facilité.
  */
using Pawn    = ConcretePiece<PawnTag>;
/** Alias de type pour les tours, fourni pour la
  * facilité.
  */
using Tower   = ConcretePiece<TowerTag>;
/** Alias de type pour les cavaliers, fourni pour la
  * facilité.
  */
using Knight  = ConcretePiece<KnightTag>;
/** Alias de type pour les fous, fourni pour la
  * facilité.
  */
using Bishop = ConcretePiece<BishopTag>;
/** Alias de type pour les dames, fourni pour la
  * facilité.
  */
using Queen   = ConcretePiece<QueenTag>;
/** Alias de type pour les rois, fourni pour la
  * facilité.
  */
using King    = ConcretePiece<KingTag>;
#endif
