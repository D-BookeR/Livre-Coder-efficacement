#ifndef COORDINATE_H_INCLUDED
#define COORDINATE_H_INCLUDED
#include <cstddef>
/** Représente une position dans un référentiel à deux
  * dimensions.
  *
  * Cette classe servira énormément à fournir une
  * représentation compréhensible au joueur mais
  * elle interviendra également dans certains algorithmes
  * qui seront réellement plus faciles à implémenter s'ils
  * peuvent être basés sur une abscisse et une ordonnée que
  * s'ils avaient dû être basés sur la représentation interne
  * des cases au niveau de l'échiquier.
  *
  * Elle permet en outre de faire la distinction entre une case
  * (qui représente la partie "physique" de l'échiquier) et une
  * position (qui n'est qu'une information de "localisation").
  */
class Coordinate{
    public:
        Coordinate():x_(valueMax_),y_(valueMax_){}
        Coordinate(size_t x, size_t y):x_(x),y_(y){}
        /**permet de récupérer l'abscisse dans le référentiel à
          * deux dimensions.
          */
        size_t x() const{return x_;}
        /**permet de récupérer l'ordonnée dans le référentiel à
          * deux dimensions.
          */
        size_t y() const{return y_;}
        /** Permet de savoir si la coordonnée est valide.
          *
          * Une coordonnée n'est valide que si son abscisse et son
          * ordonnée sont comprises dans l'intervalle [0,8[.
          *
          *
          * Il est cependant régulièrement nécessaire de
          * représenter une coordonnée invalide (par exemple,
          * lorsqu'il s'agit de représenter une pièce "hors jeu").
          *
          * Cette fonction permet de savoir si la coordonnée est
          * valide ou non.
          * @return true si l'abscisse et l'ordonnée sont toutes
          * deux comprises dans l'intervalle [0,8[, false autrement.
          */
        bool isValid() const{
            return x_< valueMax_ && y_ < valueMax_;
        }
    private:
        /**Valeur interne représentant une valeur invalide.
          *
          * Les seules valeurs possibles pour l'abscisse et
          * l'ordonnée sont comprises dans l'intervalle [0,7[.
          * valueMax correspond donc à la première
          * valeur hors intervalle.
          */
        static const size_t valueMax_ = 8;
        /** L'absice de la coordonnée.
          */
        size_t x_;
        /**
          * L'ordonnée de la coordonnée.
          */
        size_t y_;
};
/** Permet la comparaison par égalité de deux coordonnées.
  *
  * Nous devrons régulièrement savoir si deux coordonnées sont
  * identiques.
  *
  * Cet opérateur permet de nous en assurer.
  * @param[in] first la première coordonnée à comparer
  * @param[in] second la deuxième coordonnée à comparer
  * @return true si les deux coordonnées sont invalides ou
  * si l'abscisse et l'ordonnée de la première coordonnée
  * sont respectivement égales à l'abscisse et à l'ordonnée
  * de la deuxième, false autrement.
  */
inline bool operator == (Coordinate const & first,
                         Coordinate const & second){
    if(!first.isValid())
        return !second.isValid();
    return first.x() == second.x() &&
           first.y() == second.y();
}
/** Convertit une abscisse et une ordonnée en index.
  *
  * Nous devrons régulièrement convertir une abscisse et une
  * ordonnée en index afin d'être en mesure d'accéder à une
  * case spécifique de l'échiquier.
  *
  * Cette fonction effectue la conversion.
  * @param[in] x L'abscisse à prendre en compte.
  * @param[in] y L'ordonnée à prendre en compte.
  * @return L'index correspondant à la case recherchée au niveau de
  * l'échiquier, un index invalide (64) si les abscisses et
  * ordonnées ne sont pas comprises dans l'intervalle [0,7[.
  */
size_t toIndex(size_t x, size_t y);
/** Convertit un index en coordonnée.
  *
  * Nous devrons régulièrement convertir un index utilisé par
  * l'échiquier pour accéder à une case spécifique en coordonnée.
  *
  * Cette fonction effectue la conversion.
  * @param[in] index L'index à convertir.
  * @return La coordonnée correspondant à la case recherchée au
  * niveau de l'échiquier.
  * @note Cette fonction renvoie une coordonnée connue pour être
  *  invalide si l'index est lui-même invalide ( supérieur ou égal
  *  à 64).
  */
Coordinate toCoordinate(size_t index);
#endif
