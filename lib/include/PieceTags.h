#ifndef PIECETAGS_H_INCLUDED
#define PIECETAGS_H_INCLUDED
/** Classe de base pour les traits de politique associés aux
  * différents types de pièces.
  *
  * Cette classe de base a, essentiellement, pour but de nous
  * permettre certaines vérifications au moment de la
  * compilation.
  */
struct PieceTag{};
/** Trait de politique spécifique pour les pions
  */
struct PawnTag : public PieceTag{};
/** Trait de politique spécifique pour les tours
  */
struct TowerTag : public PieceTag{};
/** Trait de politique spécifique pour les cavaliers
  */
struct KnightTag : public PieceTag{};
/** Trait de politique spécifique pour les fous
  */
struct BishopTag : public PieceTag{};
/** Trait de politique spécifique pour les dames
  */
struct QueenTag : public PieceTag{};
/** Trait de politique spécifique pour les rois
  */
struct KingTag : public PieceTag{};
/** Trait de politique spécifique pour "non pièces"
  */
struct NotAPieceTag : public PieceTag{};
#endif
