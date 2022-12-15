#pragma once
#include "LogicPiece.h"

class Pawn : public logicPiece
{
private:
public:
    Pawn(int pos, bool black);

    virtual std::list<int> possibleMove();
    virtual std::list<int> pseudo_moves();
};
