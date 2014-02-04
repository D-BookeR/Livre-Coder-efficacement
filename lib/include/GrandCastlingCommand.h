#ifndef GRANDCASTLINGCOMMAND_H_INCLUDED
#define GRANDCASTLINGCOMMAND_H_INCLUDED
/** Tag spécifique à la commande permettant au joueur
  * d'effectuer un grand roque.
  */
struct GrandCastlingTag{
    /** La commande permettant au joueur de roquer utilise
      * le système d'affichage et l'échiquier.
      */
    using CtorPolicy = OutputAndChessboardTrait;
    /** La commande permettant au joueur roquer nécessite
      * la mise à jour de la couleur du joueur.
      *
      * C'est toujours le joueur dont c'est le tour qui prend la
      * décision de roquer.
      */
    using UpdatePolicy = NeedColorUpdate;
};
/** La commande permettant au joueur de jouer le grand roque
  * mais indépendante du contexte d'entrées/sorties.
  *
  * Cette spécialisation totale définit le comportement
  * qui devra être observé lorsque le joueur souhaite effectuer un
  * grand roque tout en laissant le soin à la
  * spécialisation de la classe ConcreteCommand d'indiquer la
  * manière dont le système d'affichage spécifique doit en tenir
  * compte.
  */
template <>
class ExecutableCommand<GrandCastlingTag> : public Command{
public:
    ExecutableCommand(ChessBoard & board):board(board){
    }

    /** L'échiquier utilisé par la partie en cours
      *
      * La commande devra être en mesure de récupérer
      * un grand nombre d'informations que seul l'échiquier
      * est susceptible de lui fournir.
      *
      * Elle devra en outre, si le déplacement est jugé valide,
      * être en mesure de répercuter le déplacement sur l'échiquier.
      */
    ChessBoard & board;
    /** La couleur du joueur qui souhaîte roquer.
      *
      */
    Color color;
    /** Provoque l'exécution de la commande
      *
      * Vérifie la légalité du déplacement et le
      * reporte sur l'échiquier s'il est légal.
      * @return result resultMoved si le déplacement est
      * légal, resultUnallowed dans le cas contraire.
      */
    CommandResult execute() const{
        /* La couleur du joueur nous permet de déterminer
         * la ligne de base sur laquelle devraient se trouver
         * le roi et la tour impliqués dans le roque.
         *
         */
        size_t line(color == colorWhite? 0:7);
        /* La ligne de base nous permet de déterminer la position
         * du roi et de la tour.
         *
         */
        size_t kingPos(toIndex(4,line));
        size_t towerPos(toIndex(7,line));
        /* Si la tour ou le roi ont déjà bougé, le roque est
         * interdit.
         */
        if( board.pieceAt(kingPos).hasMoved() ||
            board.pieceAt(towerPos).hasMoved() ){
            invalidMove();
            return resultUnallowed;
        }
        /* La ligne de base nous permet de déterminer
         * la position finale du roi et de la tour.
         */
        size_t finalKing(toIndex(1,line));
        size_t finalTower(toIndex(2,line));
        /* Si le roi passe par une position dans laquelle
         * il serait en échec, le roque est interdit.
         */
        for(size_t temp = finalKing; temp <= kingPos; ++temp){
           Move simulated(kingPos, temp);
           if(simulatedIsKingInCheck(board, simulated, color)){
               invalidMove();
               return resultUnallowed;
           }
        }
        /* Arrivé ici, peut afficher le déplacement ...*/
        printMe();
        Move kingMove(kingPos, finalKing);
        Move towerMove(towerPos, finalTower);
        /* ... Et reporter le déplacement du roi et de la tour
         * sur l'échiquier.
         */
        board.movePiece(kingMove);
        board.movePiece(towerMove);
        /* et renvoyer un statut de réussite */
        return resultMoved;
    }
private:
    /** Provoque l'affichage d'un message en cas de déplacement
      * invalide.
      */
    virtual void invalidMove() const = 0;
    /** Provoque l'affichage d'un message du déplacement
      * qui a été validé.
      */
    virtual void printMe() const = 0;
};
/** Spécialisation partielle de la commande permettant
  * au joueur de jouer le grand roque
  */
template <typename ITag>
class ConcreteCommand<ITag, GrandCastlingTag> :
    public ExecutableCommand<GrandCastlingTag>{
public:
    ConcreteCommand(ConcreteOutput<ITag> & render,
                    ChessBoard & board):
        ExecutableCommand<GrandCastlingTag>(board), render(render){}
        ConcreteOutput<ITag> & render;
private:
    /** Provoque l'affichage d'un message en cas de déplacement
      * invalide.
      */
    virtual void invalidMove()const;
    /** Provoque l'affichage d'un message du déplacement
      * qui a été validé.
      */
    virtual void printMe() const;
};
#endif
