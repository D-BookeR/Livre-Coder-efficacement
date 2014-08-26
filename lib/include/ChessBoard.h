#ifndef CHESSBOARD_H_INCLUDED
#define CHESSBOARD_H_INCLUDED
#include <NonCopyable.h>
#include <Colors.h>
#include <memory>
#include <vector>
class Piece;
struct Move;
/** L'échiquier utilisé en cours de partie.
  *
  * L'échiquier est la partie centrale du jeu d'échecs autour de
  * laquelle tout le reste s'articule.
  *
  * C'est en effet l'élément qui permet d'avoir une vue d'ensemble
  * de la situation telle qu'elle apparaît tout au long de la
  * partie.
  */
class ChessBoard : private NonCopyable
{
    friend class Game;
    /** Une case de l'échiquier.
      *
      * La case est la subdivision de l'échiquier sur laquelle une
      * pièce peut prendre position.
      *
      * Ce concept peut être réduit à sa plus simple expression car
      * il ne sera utilisé que par l'échiquier afin d'assurer la
      * représentation interne de ses subdivisions.
      */
    struct Square{
        Square( size_t index = 0):
               color(index%2==0? colorWhite : colorBlack),
            piece(nullptr){}
        /** La couleur de la case.
          *
          * Dans certaines circonstances, cette couleur peut
          * s'avérer utile (essentiellement pour les évolutions
          * prévues comme le fait d'avoir un affichage plus
          * "user-friendly").
          */
        Color color;
        /** La pièce qui se trouve sur la case
          *
          * Il est régulièrement nécessaire de pouvoir déterminer
          * quelle pièce se trouve sur une case donnée. Ce pointeur
          * permet de le savoir.
          */
        Piece * piece;
    };
    public:
        ChessBoard();
        /** Déplace une pièce sur l'échiquier.
          *
          * @param[in] from La position de départ de la pièce.
          * @param[in] to La position de destination de la pièce.
          * @pre Le mouvement indiqué par les deux coordonnées doit
          * être légal.
          * @note Toute pièce se trouvant à la position de
          * destination est éjectée de la partie (prise).
          */
        void movePiece(Move const & move);
        /** Permet de récupérer la couleur de la case indiquée.
          *
          * @param[in] index L'index de la case qui nous intéresse.
          * @return La couleur de la case en question.
          */
        Color squareColor(size_t index) const;
        /** Permet de savoir si la case indiquée est libre.
          *
          * @param[in] index L'index de la case qui nous intéresse.
          * @return @c true s'il n'y a aucune pièce sur la case
          *  indiquée,@c false autrement.
          */
        bool isSquareEmpty(size_t index) const;
        /** Permet de récupérer la couleur de la pièce se trouvant
          * sur la case indiquée.
          *
          * @param[in] index L'index de la case qui nous intéresse.
          * @return colorWhite ou colorBlack selon l'équipe à
          * laquelle appartient la pièce s'il y en a une,
          * colorNone autrement.
          */
        Color pieceColor(size_t index) const;
        /** Permet de récupérer la pièce qui se trouve sur la case
          * indiquée situation réelle (version non constante).
          *
          * @param[in] index L'index de la case qui nous intéresse.
          * @return Une référence sur la pièce se trouvant à la
          * case indiquée.
          * @return Une référence sur l'objet nul si la case
          * est inoccupée.
          */
        Piece & pieceAt(size_t index);
        /** Permet de récupérer la pièce qui se trouve sur la case
          * indiquée (version constante).
          *
          * @param[in] index L'index de la case qui nous intéresse.
          * @return Une référence sur la pièce se trouvant à la
          * case indiquée.
          * @return Une référence sur l'objet nul si la case
          * est inoccupée.
          */
        const Piece & pieceAt(size_t index) const;
        /** La valeur du premier index invalide.
          *
          * Permet d'utiliser une boucle passant les index dont la
          * valeur est strictement inférieure à celle-ci, les index
          * étant basés sur 0.
          */
        static const size_t indexMax = 64;
    protected:
    private:
        /** Permet de signaler qu'une pièce arrive à une case
          * donnée.
          *
          * @param[in] piece La pièce qui arrive sur la case
          * indiquée.
          * @param[in] index L'index de la case sur laquelle
          * la pièce se pose.
          * @note Si la case correspondant à la coordonnée indiquée
          * n'est pas libre, la pièce qui se trouve sur cette case
          * est sortie du jeu.
          */
        void pieceComes(Piece * piece, size_t index);
        /** Permet d'indiquer que la pièce qui se trouve sur la case
          * indiquée la quitte.
          *
          * @param[in] index la L'index de la case quittée par la
          * pièce.
          */
        void pieceLeaves(size_t index);
        /** Représente une pièce qui n'en est pas une.
          *
          * Permet de disposer d'une "non pièce" dont il est
          * possible de renvoyer une référence quand une case
          * est inoccupée.
          */
        std::unique_ptr<Piece> noPiece_;
        /** Permet de récupérer la case correspondant à l'index.
          *
          * @pre Index est un index valide (compris dans
          * l'intervale [0, indexMax[ ).
          * @param[in] index L'index recherché.
          * @return La case correspondant à l'index recherché.
          */
        Square & squareAt(size_t index);
        /** Permet de récupérer la case correspondant à l'index.
          *
          * @pre Index est un index valide (compris dans
          * l'intervale [0, indexMax[ ).
          * @param[in] index L'index recherché.
          * @return La case correspondant à l'index recherché.
          */
        Square const & squareAt(size_t index) const;
        /** Supprime toutes les pièces de l'échiquier.
          *
          * Comportement interne qui permet de supprimer toutes
          * les pièces de l'échiquier.  Cela permet de le préparer
          * afin de placer une nouvelle série de pièces, soit lors
          * du début d'une nouvelle partie, soit lors du chargement
          * d'une partie sauvegardée.
          */
        void reinitialize();
        /** L'ensemble des cases de l'échiquier.
          *
          * Un échiquier est composé d'un nombre bien précis (64)
          * de cases. Il faut bien être en mesure de les contenir
          * quelque part.  Ce "quelque part", c'est le membre que
          * voici
          */
        std::vector<Square> squares_;
};

#endif
