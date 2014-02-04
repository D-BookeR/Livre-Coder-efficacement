#ifndef PIECEFACTORY_H_INCLUDED
#define PIECEFACTORY_H_INCLUDED
#include <PieceTags.h>
#include <Colors.h>
#include <cstddef>
class Piece;
/** La fabrique de pièces
  *
  * Cette classe a pour but de permettre à n'importe quel objet
  * d'obtenir un pointeur sur une pièce sans avoir à s'inquiéter
  * du type réel de la pièce qu'il reçoit
  */
class PieceFactory
{
    public:
        /** Permet la création spécifique d'une "non pièce".
          *
          * Les non pièces sont particulièrement utiles
          * dans le cadre de l'idiome de l'objet nul et
          * permettent de renvoyer une référence sur une
          * pièce qui n'existe pas.
          *
          * @param[in] tag le tag NotAPieceTag représentant
          * spécifiquement la "non pièce".
          * @return un pointeur sur la non pièce crééee,
          * connue comme étant simplement du type Piece.
          */
        Piece * create(NotAPieceTag const & tag) const;

        /** Permet la création spécifique d'un pion.
          *
          * Permet la création d'un pion en précisant
          * sa couleur et sa position.
          * @param[in] tag Le tag spécifique représentant
          * le pion.
          * @param[in] col La couleur du pion souhaité.
          * @param[in] x L'abscisse correspondant à sa position.
          * @param[in] y L'ordonnée correspondant à sa position.
          * @param[in] moved information permettant de définir si
          * le pion a déjà été déplacé ou non.
          * @return un pointeur sur le pion créé,
          * connu comme étant simplement du type Piece
          */
        Piece * create(PawnTag const &tag, Color col,
                       size_t x, size_t y,
                       bool moved = false) const;
        /** Permet la création spécifique d'une tour.
          *
          * Permet la création d'une tour en précisant
          * sa couleur et sa position.
          * @param[in] tag Le tag spécifique représentant
          * la tour.
          * @param[in] col La couleur du pion souhaité.
          * @param[in] x L'abscisse correspondant à sa position.
          * @param[in] y L'ordonnée correspondant à sa position.
          * @param[in] moved Information permettant de définir si
          * la tour a déjà été déplacée ou non.
          * @return un pointeur sur la tour créée,
          * connue comme étant simplement du type Piece.
          */
        Piece * create(TowerTag const &, Color col,
                       size_t x, size_t y,
                       bool moved = false) const;
        /** Permet la création spécifique d'un cavalier.
          *
          * Permet la création d'un cavalier en précisant
          * sa couleur et sa position.
          * @param[in] tag Le tag spécifique représentant
          * le cavalier.
          * @param[in] col La couleur du cavalier souhaité.
          * @param[in] x L'abscisse correspondant à sa position.
          * @param[in] y L'ordonnée correspondant à sa position.
          * @param[in] moved Information permettant de définir si
          * le cavalier a déjà été déplacé ou non.
          * @return un pointeur sur le cavalier créé,
          * connu comme étant simplement du type Piece.
          */
        Piece * create(KnightTag const &, Color col,
                       size_t x, size_t y,
                       bool moved = false) const;
        /** Permet la création spécifique d'un fou.
          *
          * Permet la création d'un fou en précisant
          * sa couleur et sa position.
          * @param[in] tag Le tag spécifique représentant
          * le fou.
          * @param[in] col La couleur du fou souhaité.
          * @param[in] x L'abscisse correspondant à sa position.
          * @param[in] y L'ordonnée correspondant à sa position.
          * @param[in] moved Information permettant de définir si
          * le fou a déjà été déplacé ou non.
          * @return un pointeur sur le fou créé,
          * connu comme étant simplement du type Piece.
          */
        Piece * create(BishopTag const &, Color col,
                       size_t x, size_t y,
                       bool moved = false) const;
        /** Permet la création spécifique d'une dame.
          *
          * Permet la création d'une dame en précisant
          * sa couleur et sa position.
          * @param[in] tag Le tag spécifique représentant
          * la dame.
          * @param[in] col La couleur du pion souhaité.
          * @param[in] x L'abscisse correspondant à sa position.
          * @param[in] y L'ordonnée correspondant à sa position.
          * @param[in] moved Information permettant de définir si
          * la dame a déjà été déplacée ou non.
          * @return un pointeur sur la dame créée,
          * connue comme étant simplement du type Piece.
          */
        Piece * create(QueenTag const &, Color col,
                       size_t x, size_t y,
                       bool moved = false) const;
        /** Permet la création spécifique d'un roi.
          *
          * Permet la création d'un roi en précisant
          * sa couleur et sa position.
          * @param[in] tag Le tag spécifique représentant
          * le roi.
          * @param[in] col La couleur du roi souhaité.
          * @param[in] x L'abscisse correspondant à sa position.
          * @param[in] y L'ordonnée correspondant à sa position.
          * @param[in] moved Information permettant de définir si
          * le roi a déjà été déplacé ou non.
          * @return un pointeur sur le roi créé,
          * connu comme étant simplement du type Piece.
          */
        Piece * create(KingTag const &, Color col,
                       size_t x, size_t y,
                       bool moved = false) const;
        /** Permet la création de pièces à leur position d'origine.
          *
          * @param[in] index L'index auquel se trouve la pièce
          * attendue.
          * @return Un pointeur sur une nouvelle pièce correspondant
          * au type qui doit se trouver à la position indiquée s'il
          * échoit, nullptr si la position indiquée est libre par
          * défaut.
          */
        Piece * createDefaultPositionPiece(size_t index) const;
};
#endif
