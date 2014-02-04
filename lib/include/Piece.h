#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED
#include <NonCopyable.h>
#include <Colors.h>
#include <Coordinate.h>
class PieceVisitor;
/** Abstraction permettant de représenter n'importe quel type de
  * pièce que nous allons manipuler.
  *
  * L'ensemble de notre projet veillera à n'utiliser que cette
  * abstraction et les services qu'elle fournit afin d'obtenir les
  * résultats escomptés.
  */
class Piece : private NonCopyable{
    public:
        /** Constructeur par défaut.
          *
          * Le constructeur par défaut crée une pièce dont toutes
          * les informations tendent à la rendre invalide : aucune
          * couleur ni position valide n'est définie pour la pièce
          * ainsi créée.
          *
          * Il sera donc exclusivement utilisé par le seul type réel
          * de pièce susceptible d'être invalide : la classe dérivée
          * ConcretePiece<NotAPieceTag>.
          *
          * @sa NotAPieceTag
          * @sa template<typename Tag> class ConcretePiece
          */
        Piece():hasMoved_(true), color_(colorNone),
                coordinate_(){}
        /** Le constructeur.
          *
          * La seule information indispensable lors de la création
          * d'une pièce réelle est la couleur de l'équipe dont elle
          * fait partie. Les paramètres suivants sont uniquement là
          * pour permettre de positionner la pièce et pour permettre
          * d'indiquer qu'elle a déjà bougé le cas échéant.
          * @pre la couleur de la pièce doit être une couleur valide
          * (colorBlack ou colorWhite uniquement.
          * @param[in] color la couleur de la pièce créée.
          * @param[in] x l'abscisse de la coordonnée à laquelle
          * positionner la pièce créée.
          * @param[in] y l'ordonnée de la coordonnée à laquelle
          * positionner la pièce créée.
          * @param[in] moved permet de déterminer si la pièces créée
          * est sensée avoir déjà été déplacée.
          */
        explicit Piece(Color color, size_t x, size_t y,
              bool moved = false);
        /** Le destructeur.
          *
          * Virtuel et public, comme il se doit pour les classes
          * ayant sémantique d'entité étant donné que les pièces
          * concrètes seront connues comme des pièces
          */
        virtual ~Piece();
        /** Permet de savoir si la pièce a déjà bougé.
          *
          * @return true si la pièce a déjà bougé, false autrement.
          */
        bool hasMoved() const{return hasMoved_;}
        /** Permet de récupérer la couleur de la pièce.
          */
        Color color() const{return color_;}
        /** Permet de récupérer l'abscisse de la position à
          * laquelle se trouve la pièce.
          */
        size_t x() const{return coordinate_.x();}
        /** Permet de récupérer l'ordonnée de la position à
          * laquelle se trouve la pièce.
          */
        size_t y() const{return coordinate_.y();}
        /** Permet de savoir si la pièce est active.
          */
        bool isActive(){return coordinate_.isValid();}
        /** Permet de déplacer une pièce.
          *
          * @param[in] newCoord la nouvelle position de la pièce
          */
        void moveTo(Coordinate const & newCoord){
            coordinate_ = newCoord;
            hasMoved_ = true;
        }
        /** Permet d'indiquer à la pièce qu'elle a été prise.
          */
        void ejected(){
            moveTo(Coordinate(0,0));
        }
        /** Comportement polymorphe permettant d'avoir
          * recours au double dispatch.
          *
          * Nous aurons régulièrement besoin du double
          * dispatch pour spécialiser certains comportements
          * en fonction du type réel de la pièce.
          *
          * Cette fonction, basée sur le patron de conception
          * Visiteur nous offre cette possibilité
          * @param[in] visitor le visiteur utilisé
          */
        virtual bool accept(PieceVisitor const & visitor) const = 0;
    private:
        /** garde en mémoire le fait que la pièce a bougé ou non.
          */
        bool hasMoved_;
        /** La couleur de la pièce.
          */
        Color color_;
        /** La position actuelle de la pièce sur l'échiquier.
          */
        Coordinate coordinate_;
};
#endif
