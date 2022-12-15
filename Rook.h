#pragma once
#include "LogicPiece.h"

class Tower:public logicPiece{

public:
    Tower(int pos,bool black);
    virtual std::list<int> possibleMove();
    virtual std::list<int> pseudo_moves();
};
