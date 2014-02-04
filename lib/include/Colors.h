#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED
/** représente les différentes couleurs
  *
  * Dans la plupart des cas, nous avons uniquement besoin de
  * connaître la couleur des pièces, afin de savoir s'il s'agit
  * d'une pièce "alliée" ou "ennemie", les comportements
  * polymorphes nous permettant de déterminer le reste.
  *
  * Nous aurons cependant aussi besoin de pouvoir représenter
  * l'absence de pièce sur certaines cases.
  */
enum Color{
    colorNone, /**< Représente l'absence de couleur.
                 *
                 * Permet de représenter l'absence de pièce lorsque
                 * l'on souhaite obtenir la couleur d'une pièce se
                 * trouvant sur une case inoccupée
                 */
    colorWhite, /**< Représente la couleur blanche.
                  *
                  * Permet de représenter tout ce qui est de couleur
                  * blanche, que ce soit les cases ou les pièces de
                  * l'équipe des blancs.
                  */
    colorBlack, /**< Représente la couleur noire.
                  *
                  * Permet de représenter tout ce qui est de couleur
                  * noire, que ce soit les cases ou les pièces de
                  * l'équipe des noirs.
                  */
    colorMax /**< Valeur maximale à ne jamais atteindre
               *
               * Permet de représenter, par exemple, la taille d'un
               * tableau de couleurs de taille fixe.
               */
};

#endif
