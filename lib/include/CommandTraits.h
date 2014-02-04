#ifndef COMMANDTRAITS_H_INCLUDED
#define COMMANDTRAITS_H_INCLUDED
/** Tag représentant une politique de création de commande qui
  * n'utilise que le système de sorties comme paramètre
  *  à transmettre au constructeur de la commande.
  */
struct OnlyOutputTrait{};
/** Tag représentant une politique de création de commande qui
  * utilise le système de sorties et l'échiquier comme paramètre à
  * transmettre au constructeur de la commande.
  */
struct OutputAndChessboardTrait{};
/** Tag représentant une politique de création de commande qui
  * utilise le système de sorties et la partie comme paramètre à
  * transmettre au constructeur de la commande.
  */
struct OutputAndGameTrait{};

/** Tag représentant une politique d'utilisation de la commande ne
  * nécessitant pas la mise à jour d'informations.
  */
struct NoUpdateNeeded{};
/** Tag représentant une politique d'utilisation de la commande
  * nécessitant la mise à jour d'une couleur.
  */
struct NeedColorUpdate{};
/** Tag représentant une politique d'utilisation de la commande
  * nécessitant la mise à jour d'une couleur et d'un déplacement.
  */
struct NeedColorAndMoveUpdate{};
#endif
