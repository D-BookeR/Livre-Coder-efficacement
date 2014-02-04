#include <PermissiveRuleChecker.h>
#include <Move.h>
#include <Directions.h>
#include <ConcretePiece.h>
#include <cstdlib>
#include <cassert>
PermissiveRuleChecker::PermissiveRuleChecker(size_t destination):
    destination_(destination){
    assert(toCoordinate(destination).isValid());
}
bool PermissiveRuleChecker::
     visit(ConcretePiece<PawnTag> const& pawn) const{
    Move move(toIndex(pawn.x(), pawn.y()), destination_);
    Directions moveDirection =
        findDirection(move);
    size_t distance = traversedSquares(move);
    /* Refusons tous les déplacements "vers l'arrière". */
    if(moveDirection * pawn.multiplier() < 0)
        return false;
    /* Acceptons les déplacements en ligne droite. */
    if(abs(moveDirection) == front){
        /* Les déplacements d'une ou de deux cases sont autorisés
         * si le pion n'a pas encore bougé.
         */
        if(! pawn.hasMoved()){
            return distance == 1 || distance == 2;
        } else{
            /* Sinon, seuls les déplacement d'une seule case
             * sont autorisés
             */
            return distance == 1;
        }
    }
    /* Acceptons les déplacements d'une case en diagonale. */
    if(abs(moveDirection) == frontLeft ||
       abs(moveDirection) == frontRight ){
        return distance == 1;
    }
    /* Tous les autres déplacements sont interdits. */
    return false;
}
bool PermissiveRuleChecker::
     visit(ConcretePiece<TowerTag> const& tower) const{
    Move move(toIndex(tower.x(), tower.y()), destination_);
    Directions moveDirection =
        findDirection(move);
    size_t distance = traversedSquares(move);
    /* Seuls les déplacements en droite ligne sont autorisés pour
     * les tours.
     */
    return ( moveDirection == front ||
             moveDirection == back  ||
             moveDirection == left  ||
             moveDirection == right) &&
            distance > 0 &&
            distance < 8;
}
bool PermissiveRuleChecker::
     visit(ConcretePiece<KnightTag> const& knight) const
{
    /* Le cavalier dispose de 8 déplacements spécifiques, dont
     * la validité est plus facile à vérifier sous la forme de
     * coordonnées.
     */
    Coordinate positions[]={
                         Coordinate(knight.x() - 1, knight.y() -2),
                         Coordinate(knight.x() - 1, knight.y() +2),
                         Coordinate(knight.x() + 1, knight.y() -2),
                         Coordinate(knight.x() + 1, knight.y() +2),
                         Coordinate(knight.x() + 2, knight.y() +1),
                         Coordinate(knight.x() + 2, knight.y() -1),
                         Coordinate(knight.x() - 2, knight.y() -1),
                         Coordinate(knight.x() - 2, knight.y() +1)};
    static_assert(std::extent<decltype(positions)>::value == 8,
                  "Knight should have 8 possible destinations");
    /*Le cavalier peut accéder à n'importe laquelle de
     * ces coordonnées si elle est valide.
     */
    Coordinate finalCoordinate = toCoordinate(destination_);
    if (! finalCoordinate.isValid())
        return false;
    for(size_t index = 0; index <8; ++index){
        if( finalCoordinate == positions[index])
            return true;
    }
    /* Tout autre déplacement est interdit. */
    return false;
}
bool PermissiveRuleChecker::
     visit(ConcretePiece<BishopTag> const& bishop) const{
    Move move(toIndex(bishop.x(), bishop.y()), destination_);
    Directions moveDirection =
        findDirection(move);
    size_t distance = traversedSquares(move);
    /* Seuls les déplacements en diagonale sont autorisés pour les
     * fous.
     */
    return ( moveDirection == frontLeft  ||
             moveDirection == backLeft   ||
             moveDirection == frontRight ||
             moveDirection == backRight ) &&
            distance > 0 &&
            distance < 8;
}
bool PermissiveRuleChecker::
     visit(ConcretePiece<QueenTag> const& queen) const{
    Move move(toIndex(queen.x(), queen.y()), destination_);
    Directions moveDirection =
        findDirection(move);
    size_t distance = traversedSquares(move);

    /* Les huit grandes directions sont autorisées pour les dames.
     */
    return ( moveDirection == front ||
             moveDirection == back  ||
             moveDirection == left  ||
             moveDirection == right ||
             moveDirection == frontLeft  ||
             moveDirection == backLeft   ||
             moveDirection == frontRight ||
             moveDirection == backRight ) &&
            distance > 0 &&
            distance < 8;
}
bool PermissiveRuleChecker::
     visit(ConcretePiece<KingTag> const& king) const{
    Move move(toIndex(king.x(), king.y()), destination_);
    /* Quelle que soit la direction du déplacement,
     * le roi ne peut se déplacer que d'une seule case à la fois
     * (exception faite du roque qui est géré par ailleurs).
     */
    return traversedSquares(move) ==1;
}
