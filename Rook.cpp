#include "Rook.h"
#include "Game.h"
#include "ChessBoard.h"
#include "King.h"
#include <iostream>

Tower::Tower(int pos,bool black):logicPiece(pos,black){
    _pos=pos;
    _black=black;
    _name = 't';

    int rook[8][8] = {
        {0,  0,  0,  0,  0,  0,  0,  0},
        {5, 10, 10, 10, 10, 10, 10,  5},
        {-5,  0,  0,  0,  0,  0,  0, -5},
        {-5,  0,  0,  0,  0,  0,  0, -5},
        {-5,  0,  0,  0,  0,  0,  0, -5},
        {-5,  0,  0,  0,  0,  0,  0, -5},
        {-5,  0,  0,  0,  0,  0,  0, -5},
        {0,  0,  0,  5,  5,  0,  0,  0}
    };

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            _bonus[i][j] = rook[i][j];
}

std::list<int> Tower::possibleMove(){

    std::list<int> possible_move;
    int move=_pos;
    int riga=_pos/8;
    int i=1;
    int j=8;
    bool finished=false;;

    //spostamento a sinistra
    while((move)>=(riga*8) && finished==false){

        if(Game::board()[move/8][move%8]!=nullptr && _black!=Game::board()[move/8][move%8]->check_color()){
            if (!verify_check(move))
                possible_move.push_back(move);
            finished=true;
        }
        else if(Game::board()[move/8][move%8]!=nullptr && Game::board()[move/8][move%8]!=this && _black==Game::board()[move/8][move%8]->check_color()){
            finished=true;
        }

        else if(Game::board()[move/8][move%8]==nullptr && move>=(riga*8)){
            if (!verify_check(move))
                possible_move.push_back(move);
        }

        move=_pos-i;
        i++;
    }

    i=1;
    finished=false;
    move=_pos;

    //spostamento a destra
    while((move)<(riga+1)*8 && finished==false){

        if(Game::board()[move/8][move%8]!=nullptr && _black!=Game::board()[move/8][move%8]->check_color()){
            if (!verify_check(move))
                possible_move.push_back(move);
            finished=true;
        }
        else if(Game::board()[move/8][move%8]!=nullptr && Game::board()[move/8][move%8]!=this && _black==Game::board()[move/8][move%8]->check_color()){
            finished=true;
        }

        if(Game::board()[move/8][move%8]==nullptr && move<(riga+1)*8){
            if (!verify_check(move))
                possible_move.push_back(move);
        }

        move=_pos+i;
        i++;
    }

    finished=false;
    move=_pos;

    //spostamento verso l'alto
    while((move)>=0 && finished==false){

        if(Game::board()[move/8][move%8]!=nullptr && _black!=Game::board()[move/8][move%8]->check_color()){
            if (!verify_check(move))
                possible_move.push_back(move);
            finished=true;
        }
        else if(Game::board()[move/8][move%8]!=nullptr && Game::board()[move/8][move%8]!=this && _black==Game::board()[move/8][move%8]->check_color()){
            finished=true;
        }

        if(Game::board()[move/8][move%8]==nullptr && move>=0){
            if (!verify_check(move))
                possible_move.push_back(move);
        }

        move=_pos-j;
        j=j+8;
    }

    j=8;
    finished=false;
    move=_pos;

    //spostamento verso il basso
    while((move)<=63 && finished==false){

        if(Game::board()[move/8][move%8]!=nullptr && _black!=Game::board()[move/8][move%8]->check_color()){
            if (!verify_check(move))
                possible_move.push_back(move);
            finished=true;
        }
        else if(Game::board()[move/8][move%8]!=nullptr && Game::board()[move/8][move%8]!=this && _black==Game::board()[move/8][move%8]->check_color()){
            finished=true;
        }

        if(Game::board()[move/8][move%8]==nullptr && move<=63){
            if(!verify_check(move))
                possible_move.push_back(move);
        }

        move=_pos+j;
        j=j+8;
    }


    return possible_move;
}

std::list<int> Tower::pseudo_moves(){

    std::list<int> possible_move;
    int move=_pos;
    int riga=_pos/8;
    int i=1;
    int j=8;
    bool finished=false;;

    //spostamento a sinistra
    while((move)>=(riga*8) && finished==false){

        if(Game::board()[move/8][move%8]!=nullptr && _black!=Game::board()[move/8][move%8]->check_color()){
            possible_move.push_back(move);
            finished=true;
        }
        else if(Game::board()[move/8][move%8]!=nullptr && Game::board()[move/8][move%8]!=this && _black==Game::board()[move/8][move%8]->check_color()){
            finished=true;
        }

        else if(Game::board()[move/8][move%8]==nullptr && move>=(riga*8)){
            possible_move.push_back(move);
        }

        move=_pos-i;
        i++;
    }

    i=1;
    finished=false;
    move=_pos;

    //spostamento a destra
    while((move)<(riga+1)*8 && finished==false){

        if(Game::board()[move/8][move%8]!=nullptr && _black!=Game::board()[move/8][move%8]->check_color()){
            possible_move.push_back(move);
            finished=true;
        }
        else if(Game::board()[move/8][move%8]!=nullptr && Game::board()[move/8][move%8]!=this && _black==Game::board()[move/8][move%8]->check_color()){
            finished=true;
        }

        if(Game::board()[move/8][move%8]==nullptr && move<(riga+1)*8){
            possible_move.push_back(move);
        }

        move=_pos+i;
        i++;
    }

    finished=false;
    move=_pos;

    //spostamento verso l'alto
    while((move)>=0 && finished==false){

        if(Game::board()[move/8][move%8]!=nullptr && _black!=Game::board()[move/8][move%8]->check_color()){
            possible_move.push_back(move);
            finished=true;
        }
        else if(Game::board()[move/8][move%8]!=nullptr && Game::board()[move/8][move%8]!=this && _black==Game::board()[move/8][move%8]->check_color()){
            finished=true;
        }

        if(Game::board()[move/8][move%8]==nullptr && move>=0){
            possible_move.push_back(move);
        }

        move=_pos-j;
        j=j+8;
    }

    j=8;
    finished=false;
    move=_pos;

    //spostamento verso il basso
    while((move)<=63 && finished==false){

        if(Game::board()[move/8][move%8]!=nullptr && _black!=Game::board()[move/8][move%8]->check_color()){
            possible_move.push_back(move);
            finished=true;
        }
        else if(Game::board()[move/8][move%8]!=nullptr && Game::board()[move/8][move%8]!=this && _black==Game::board()[move/8][move%8]->check_color()){
            finished=true;
        }

        if(Game::board()[move/8][move%8]==nullptr && move<=63){
            possible_move.push_back(move);
        }

        move=_pos+j;
        j=j+8;
    }


    return possible_move;
}
