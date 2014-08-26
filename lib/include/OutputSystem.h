#ifndef OUTPUTSYSTEM_H_INCLUDED
#define OUTPUTSYSTEM_H_INCLUDED
#include <NonCopyable.h>
#include <Colors.h>
class ChessBoard;
class Coordinate;
struct Move;
class Piece;
class Game;
/** Abstraction de base représentant n'importe quel système de
  * sorties.
  *
  * N'importe quel système de sorties devra, au minimum, être en
  * mesure de traiter l'ensemble de nos données métier.
  */
class OutputSystem : public NonCopyable
{
    public:
        OutputSystem(ChessBoard const & board);
        virtual ~OutputSystem();
        /** Permet de représenter le joueur dont c'est le tour
          * de jouer.
          *
          * @param[in] color La couleur du joueur
          * à utiliser.
          */
        virtual void playerTurn(Color color) =0;
        /** Permet de représenter le vainqueur.
           *
           * @param[in] color La couleur de l'équipe du
           * vainqueur.
           */
        virtual void winnerIs(Color color) = 0;
        /** Premet de représenter une situation d'échec.
          *
          * Typiquement, le joueur qui place sont adversaire
          * en situation d'échec annonce le terme "échec"
          * à voix haute.
          *
          * Cette fonction permet de provoquer un comportement
          * similaire au niveau du système de sortie utilisé.
          */
        virtual void kingisInCheck() = 0;
        /** Permet de représenter une situation d'échec et mat.
          *
          * Typiquement, le joueur qui place sont adversaire
          * en situation d'échec et mat annonce le terme
          * "échec et mat" à voix haute.  Cette annonce est
          * souvent suivie du vainqueur de la partie
          *
          * Cette fonction permet de provoquer un comportement
          * similaire au niveau du système de sortie utilisé.
          */
        virtual void kingIsMat() = 0;
        /** Permet de représenter une situation de pat.
          *
          * Typiquement, les situations de pat sont anoncées
          * en exrpimant à voix haute le terme "pat" afin que
          * les joueurs n'ignorent rien de la siutaiton.
          *
          * Cette fonction permet de provoquer un comportement
          * similaire au niveau du système de sortie utilisé.
          */
        virtual void patSituation() = 0;
        /** Permet de représenter l'abandon d'un joueur.
          *
          * Typiquement, le joureur qui décide d'abandonner
          * l'annonce de manière explicite, soit en le disant
          * à voix haute, soit en faisant basculer son roi sur
          * l'échiquier.
          *
          * Cette fonction permet de provoquer un comportement
          * similaire au niveau du système de sortie utilisé.
          * @param[in] color la couleur de l'équipe du joueur
          * qui abandonne.
          */
        virtual void hasSurrendered(Color color) = 0;
    protected:
        /** Référence vers l'échiquier utilisé.
          */
        ChessBoard const & board;
};
/** Déclaration anticipée commune pour tous les types concrets
  * d'affichage, dépendant du contexte d'entrées/sorties utilisé
  * par la partie
  */
template <typename Tag>
class ConcreteOutput;
#endif
