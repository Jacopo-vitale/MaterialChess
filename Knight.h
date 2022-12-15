#pragma once
#include "LogicPiece.h"

class Knight : public logicPiece
{

public:

    Knight(int pos,bool black);
    virtual std::list<int> possibleMove();
    virtual std::list<int> pseudo_moves();
};

