#pragma once
#include "LogicPiece.h"
#include <list>

class Queen : public logicPiece
{
public:
    Queen(int pos, bool black);
    virtual std::list<int> possibleMove();
    virtual std::list<int> pseudo_moves();
};
