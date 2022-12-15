#include "Move.h"
#include "Square.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"

Move::Move(logicPiece* piece, logicPiece* eaten, int from, int to) {

    _piece = piece;
    _eaten = eaten;
    _from = from;
    _to = to;
    _changed_to_queen = false;
	_oldpiece = nullptr;
}

Move::Move(Piece* piece, Piece* eaten, int from, int to) {

    _piece = tologicPiece(piece);
    _eaten = tologicPiece(eaten);
    _from = from;
    _to = to;
    _changed_to_queen = false;
	_oldpiece = nullptr;
}

Move::Move(const Move &o)
{
    _piece = o._piece;
    _eaten = o._eaten;
    _from = o._from;
    _to = o._to;
    _changed_to_queen = o._changed_to_queen;
	_oldpiece = o._oldpiece;
}

Move& Move::operator=(const Move &o)
{
    if (this != &o)
    {
        _piece = o._piece;
        _eaten = o._eaten;
        _from = o._from;
        _to = o._to;
        _changed_to_queen = o._changed_to_queen;
		_oldpiece = o._oldpiece;
    }

    return *this;
}

Move::~Move()
{
	//delete _piece;
	//delete _eaten;
}

Piece* Move::toPiece(logicPiece* piece)
{
    if(piece == nullptr)
        return nullptr;
   
	return piece->GraphicPiece();
}

logicPiece* Move::tologicPiece(Piece* piece)
{
    if(piece == nullptr)
        return nullptr;

    logicPiece* tmp =nullptr;
    int x = piece->x()/Square::cell_size;
    int y = piece->y()/Square::cell_size;
    QChar c = piece->name();
    int pos = y*8+x;
    bool black=piece->black();

    if(c == 'p')
        tmp = new Pawn(pos,black);
    else if (c == 'c')
        tmp = new Knight(pos,black);
    else if (c == 'a')
        tmp = new Bishop(pos,black);
    else if (c == 't')
        tmp = new Tower(pos,black);
    else if (c == 'q')
        tmp = new Queen(pos,black);
    else if (c == 'k')
        tmp = new King(pos,black);

	tmp->setGraphicPiece(piece);
    return tmp;
}

logicPiece* Move::eaten()
{
    return _eaten;
}


logicPiece* Move::piece()
{
    return _piece;
}
