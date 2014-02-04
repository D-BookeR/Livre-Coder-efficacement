#include <KingIdentifier.h>
#include <ConcretePiece.h>
#include <ChessBoard.h>
#include <cassert>
KingIdentifier::KingIdentifier(Color color):color_(color){
    assert(color!= colorMax);
}

bool KingIdentifier::visit(ConcretePiece<KingTag> const & king) const{
    if(color_ != colorNone)
        return king.color() == color_;
    return true;
}
size_t findKing(ChessBoard const & board, Color color){
    assert(color == colorBlack || color == colorWhite );
    KingIdentifier identifier(color);
    for(size_t index = 0; index < 64; ++index){
        if(identifier.check(board.pieceAt(index))){
            return true;
        }
    }
    /* Nous ne devrions jamais arriver ici, mais sait-on
     * jamais ...
     */
    assert(!"no king found, what did you do?");
    return 64;
}
