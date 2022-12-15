#pragma once
#include "LogicPiece.h"
#include "Piece.h"

class Move {
private:
    logicPiece* _piece;
    logicPiece* _eaten;
	logicPiece* _oldpiece; //when a pawn become a queen starage his old pointer
    int _from;
    int _to;
    bool _changed_to_queen;

    Piece* toPiece(logicPiece* piece);
    logicPiece* tologicPiece(Piece* piece);
public:
    Move(logicPiece* piece, logicPiece* eaten, int from, int to);
    Move(Piece* piece, Piece* eaten, int from, int to);
    Move(const Move &o);
	~Move();

    Move& operator=(const Move &o);
    //getter
    int to() { return _to; }
    int from() { return _from; }
    logicPiece* piece();
    logicPiece* eaten();
    bool ChangedToQueen() { return _changed_to_queen; }
	logicPiece* oldPiece() { return _oldpiece; }

    //setter
    void setTo(int to) { _to = to; }
    void setFrom(int from) { _from = from; }
    void setPiece(logicPiece* piece) { _piece = piece; }
    void setEaten(logicPiece* eaten) { _eaten = eaten; }
    void setChangedToQueen(bool changed) { _changed_to_queen = changed; }
	void setOldPiece(logicPiece* p) { _oldpiece = p; }
};
