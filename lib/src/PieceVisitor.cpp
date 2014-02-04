#include <PieceVisitor.h>
#include <ConcretePiece.h>
bool PieceVisitor::check(Piece const& piece){
    return piece.accept(*this);
}
bool PieceVisitor::visit(ConcretePiece<NotAPieceTag> const&) const{
    return false;
}
bool PieceVisitor::visit(ConcretePiece<PawnTag> const&) const{
    return false;
}
bool PieceVisitor::visit(ConcretePiece<TowerTag> const&) const{
    return false;
}
bool PieceVisitor::visit(ConcretePiece<KnightTag> const&) const{
    return false;
}
bool PieceVisitor::visit(ConcretePiece<BishopTag> const&) const{
    return false;
}
bool PieceVisitor::visit(ConcretePiece<QueenTag> const&) const{
    return false;
}
bool PieceVisitor::visit(ConcretePiece<KingTag> const&) const{
    return false;
}
