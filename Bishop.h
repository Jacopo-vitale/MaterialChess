#pragma once
#include "LogicPiece.h"

class Bishop : public logicPiece
{

public:

    Bishop(int pos, bool black);
    virtual std::list<int> possibleMove();
    virtual std::list<int> pseudo_moves();
};
