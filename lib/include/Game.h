#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <Player.h>
#include <NonCopyable.h>
#include <OutputSystem.h>
#include <ChessBoard.h>
#include <list>
#include <memory>
#include <utility>
/** Représente le concept de partie.
  *
  * Met deux joueurs en présence et leur fournit tout
  * ce dont ils ont besoin pour pouvoir jouer aux échecs,
  * à savoir :
  * - un échiquer
  * - les pièces pour chaque équipe ;
  * - un contexte d'entrées spécifique à chaque joueur ;
  * - un contexte de sorties (sans doute d'affichage)
  *   commun aux deux joueurs ;
  * - un système d'arbitrage, dont une partie est déléguée
  *   à l'exécution des différentes commandes et dont l'autre
  *   échoit à l'exécution de la partie elle-même.
  */
class Game : private NonCopyable{
public:
    Game();
    /** Permet de récupérer le contexte d'affichage.
      */
    OutputSystem & render(){return *(render_.get());}
    /** Permet d'indiquer la volonté de quitter l'application.
      */
    void quit(){exitGame_ = true;}
    /** Permet d'indiquer la volonté d'un joueur d'abandonner
      * la partie en cours.
      *
      * @note Le joueur qui décide d'abandonner la partie est
      * alors déclaré vaincu par forfait.
      */
    void surrender(){
        surrendered_ = true;
        gameFinished_ = true;
    }
    /** Permet de récupérer la couleur de l'équipe du joueur
      * à qui c'est le tour de jouer.
      */
    Color currentColor() const{return current_->color();}
    /** Permet de récupérer la couleur de l'équipe du joueur
      * qui attend son tour pour jouer.
      */
    Color nextColor()    const{return next_->color();}
    /** Réinitialise toutes les données de la partie et
      * les place dans une situation classique de début
      * de partie.
      */
    void reinitialize();
    /** Permet de récupérer l'échiquier utilisé pour
      * la partie.
      */
    ChessBoard const & board() const{return board_;}
    /** Permet de récupérer l'échiquier utilisé pour
      * la partie.
      */
    ChessBoard  & board() {return board_;}
    /** Permet de déterminer si la partie doit
      * être réinitialisée.
      */
    bool needInit() const{return surrendered_ || gameFinished_;}
    /** Boucle principale dans laquelle on entre dans le jeu.
      *
      * Toute la logique de jeu est mise en place dans cette
      * fonction dont on ne sort que lorsque l'utilisateur
      * décide de quitter l'application.
      */
    void run();
    /** Permet de définir un contexte d'entrées spécifique
      * pour un joueur particulier.
      *
      * Si, dans l'état actuel des spécifications, les seuls
      * joueurs que nous envisageons sont des joueurs humains,
      * et qu'ils jouent tous les deux avec le clavier, les
      * évolutions futures ont de grandes chances de nécessiter
      * la possibilité de changer le contexte d'entrées pour l'un
      * ou l'autre des joueurs.
      *
      * Cette fonction permet de définir un contexte d'entrées
      * spécifique pour chaque joueur.
      * @pre color est une couleur d'équipe valide (colorWhite ou
      * colorBlack).
      * @para[in] color La couleur du joueur concerné.
      * @para[in] system Le système d'entrées spécifique au joueur.
      * @note Le système d'entrées doit avoir été créé en ayant
      * recours à l'allocation dynamique de la mémoire car
      * sa durée de vie est intégralement prise en charge par
      * le joueur qui en devient dépositaire.
      */
    void defineInputSystem(Color color, InputSystem * input);
    /** Permet de définir un contexte de sortie pour la partie.
      *
      * @para[in] output le système de sorties (d'affichage?)
      * utilisé par la partie.
      *
      * @note Le système de sortie doit avoir été créé en ayant
      * recours à l'allocation dynamique de la mémoire car
      * sa durée de vie est intégralement prise en charge par
      * la partie qui en devient le propriétaire légal.
      */
    void defineOutputSystem(OutputSystem * output){
        render_.reset(output);
    }
    /** Permet de s'assurer que les contextes d'entrées et de
      * sorties ont été correctement définis.
      *
      * @return true si chaque joueur dispose de son contexte
      * d'entrées et que le contexte de sorties est correctement
      * défini, false si ce n'est pas le cas.
      */
    bool areContextDefined() const{
        return whites_.hasInputSystem() &&
               blacks_.hasInputSystem() &&
               render_.get() != nullptr;
    }
private:
    /** supprime toutes les données de la partie courante.
      *
      * - efface les joueurs ;
      * - efface l'historique, s'il en existe une ;
      * - réinitialise le tour pour les blancs.
      */
    void clear();
    /** Permet de définir le premier jouer à jouer.
      */
    void firstPlayer(Color color);
    bool exitGame_;
    bool surrendered_;
    bool gameFinished_;
    void altenatePlayers(){
        std::swap(current_, next_);
    }
    std::unique_ptr<OutputSystem> render_;
    std::list<std::unique_ptr<Piece>> allPieces_;
    Player whites_;
    Player blacks_;
    Player * current_;
    Player * next_;
    ChessBoard board_;
};
#endif
