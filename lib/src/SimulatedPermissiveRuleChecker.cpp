#include <SimulatedPermissiveRuleChecker.h>
#include <ConcretePiece.h>
#include <SimulationFunctions.h>
#include <Directions.h>

#include <cstdlib>
SimulatedPermissiveRuleChecker::
SimulatedPermissiveRuleChecker(Move const & move,
                               size_t destination):
                               destination_(destination),
                               simulated_(move){
}
bool SimulatedPermissiveRuleChecker::
    visit(ConcretePiece<PawnTag> const& pawn) const{
    size_t pawnPos=simulatedIndex(simulated_,
                                  toIndex(pawn.x(),pawn.y()));
    size_t finalPos = simulatedIndex(simulated_, destination_);
    Move move(pawnPos, finalPos);
    Directions moveDirection = findDirection(move);
    size_t distance = traversedSquares(move);
    /* Refusons tous les déplacements "vers l'arrière". */
    if(moveDirection * pawn.multiplier() > 63)
        return false;
    /* acceptons les déplacement en ligne droite */
    if(abs(moveDirection) == 8){
        /* Les déplacements d'une ou de deux cases sont autorisés
         * si le pion n'a pas encore bougé.
         */
        if(! pawn.hasMoved()){
            return distance == 1 || distance == 2;
        } else{
            return distance == 1;
        }
    }
    /* Acceptons les déplacements d'une case en diagonale. */
    if(abs(moveDirection) == frontLeft ||
       abs(moveDirection) == frontRight){
        return distance == 1;
    }
    /* Tous les autres déplacements sont interdits. */
    return false;
}
bool SimulatedPermissiveRuleChecker::
     visit(ConcretePiece<TowerTag> const& tower) const{
    size_t towerPos=simulatedIndex(simulated_,
                                  toIndex(tower.x(),tower.y()));
    size_t finalPos = simulatedIndex(simulated_, destination_);

    Move move(towerPos, finalPos);
    Directions moveDirection = findDirection(move);
    size_t distance = traversedSquares(move);
    /* Seuls les déplacements en droite ligne sont autorisés
     * pour les tours.
     */
    return ( moveDirection == front ||
             moveDirection == back  ||
             moveDirection == left  ||
             moveDirection == right) &&
            distance > 0 &&
            distance < 8;
}
bool SimulatedPermissiveRuleChecker::
    visit(ConcretePiece<KnightTag> const& knight) const{
    size_t knightPos = simulatedIndex(simulated_,
                       toIndex(knight.x(),knight.y()));
    Coordinate realCoord = toCoordinate(knightPos);
    /* Le cavalier dispose de 8 déplacements spécifiques, dont
     * la validité est plus facile à vérifier sous la forme de
     * coordonnées.
     */
    Coordinate positions[]={
               Coordinate(realCoord.x() - 1, realCoord.y() -2),
               Coordinate(realCoord.x() - 1, realCoord.y() +2),
               Coordinate(realCoord.x() + 1, realCoord.y() -2),
               Coordinate(realCoord.x() + 1, realCoord.y() +2),
               Coordinate(realCoord.x() + 2, realCoord.y() +1),
               Coordinate(realCoord.x() + 2, realCoord.y() -1),
               Coordinate(realCoord.x() - 2, realCoord.y() -1),
               Coordinate(realCoord.x() - 2, realCoord.y() +1)
    };
    static_assert(std::extent<decltype(positions)>::value == 8,
                  "Knight should have 8 possible destinations");
    /*Le cavalier peut accéder à n'importe laquelle de
     * ces coordonnées si elle est valide.
     */
    size_t simulatedPosition = simulatedIndex(simulated_,
                                              destination_);
    Coordinate finalCoordinate = toCoordinate(simulatedPosition);
    if (! finalCoordinate.isValid())
        return false;
    for(size_t index = 0; index <8; ++index){
        if( finalCoordinate == positions[index])
            return true;
    }
    /* Tout autre déplacement est interdit. */
    return false;
}
bool SimulatedPermissiveRuleChecker::
    visit(ConcretePiece<BishopTag> const& bishop) const{
    size_t bishopPos=simulatedIndex(simulated_,
                                  toIndex(bishop.x(),bishop.y()));
    size_t finalPos = simulatedIndex(simulated_, destination_);
    Move move(bishopPos, finalPos);
    Directions moveDirection = findDirection(move);
    size_t distance = traversedSquares(move);
    /* Seuls les déplacements en diagonale sont autorisés pour les
     * fous
     */
    return ( moveDirection == frontLeft  ||
             moveDirection == backLeft   ||
             moveDirection == frontRight ||
             moveDirection == backRight ) &&
            distance > 0 &&
            distance < 8;
}
bool SimulatedPermissiveRuleChecker::
     visit(ConcretePiece<QueenTag> const& queen) const{
    size_t queenPos=simulatedIndex(simulated_,
                                  toIndex(queen.x(),queen.y()));
    size_t finalPos = simulatedIndex(simulated_, destination_);
    Move move(queenPos, finalPos);
    Directions moveDirection = findDirection(move);
    size_t distance = traversedSquares(move);
    /* les huit grandes directions sont autorisées pour les dames
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
bool SimulatedPermissiveRuleChecker::
    visit(ConcretePiece<KingTag> const& king) const{
    size_t kingPos=simulatedIndex(simulated_,
                                  toIndex(king.x(),king.y()));
    size_t finalPos = simulatedIndex(simulated_, destination_);
    Move move(kingPos, finalPos);
    /* Quelle que soit la direction du déplacement,
     * le roi ne peut se déplacer que d'une seule case à la fois
     * (exception faite du roque qui est géré par ailleurs).
     */
    return traversedSquares(move) ==1;
}
