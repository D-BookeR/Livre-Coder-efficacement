#ifndef PLAYERALLOWEDMOVES_H_INCLUDED
#define PLAYERALLOWEDMOVES_H_INCLUDED
#include <Colors.h>
#include <Move.h>
#include <list>
class ChessBoard;
/** Remplit une liste avec tous les déplacements autorisés
  * pour un joueur donné.
  *
  * Afin de déterminer les situations d'échec et mat ou les
  * situations de pat, il est nécessaire de vérifier tous les
  * déplacements qu'un joueur peut envisager afin de déterminer
  * s'il y en a un qui ne le place pas en situation d'échec.
  *
  * Le meilleur moyen pour y parvenir est de dresser la liste
  * exhaustive des déplacements que peuvent entreprendre les pièces
  * de ce joueur afin de les vérifier un à un.
  *
  * Cette fonction crée la liste exhaustive de tous les déplacements
  * autorisés pour les différentes pièces d'un joueur donné.
  * @pre La couleur testée est la couleur d'une équipe (colorWhite
  * ou colorBlack).
  * @param[in] board L'échiquier à prendre en compte.
  * @param[in] color La couleur du joueur concerné.
  * @return la liste de tous les déplacements possibles
  * pour le joueur concerné.
  */
std::list<Move> fillAllowedMoveList(ChessBoard const & board,
                                    Color color);
/** Permet de déterminer si un joueur dispose d'un seul
  * déplacement qui ne le place pas en situation d'échec.
  *
  * Toute partie ne peut continuer que si le joueur est
  * en mesure d'effectuer un déplacement qui ne le place
  * pas en situation d'échec.
  *
  * Cette fonction vérifie tous les déplacements potentiels
  * d'un joueur dans l'espoir d'en trouver au moins un qui
  * soit dans le cas.
  * @pre La couleur testée est la couleur d'une équipe (colorWhite
  * ou colorBlack).
  * @param[in] board L'échiquier à prendre en compte.
  * @param[in] color La couleur du joueur concerné.
  * @return true s'il existe ne serait-ce qu'un déplacement qui
  * ne place pas le joueur en situation d'échec, false dans le
  * cas contraire.
  */
bool hasPlayerAllowedMove(ChessBoard const & board, Color color);

#endif
