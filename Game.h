#pragma once
#include <vector>
#include <QThread>
#include <QSettings>
#include <QList>
#include "LogicPiece.h"
#include "Move.h"

typedef std::pair<int, Move> pairmove;

class Game : public QThread
{
    Q_OBJECT

protected:
    static logicPiece*** _board;
    bool turn_player;                       //true for black
    std::vector<Move*> allMoves;
    Move* _lastMove;

    static logicPiece* w_k;                 //puntatore al re bianco
    static logicPiece* b_k;                 //puntatore al re nero

    //peso del materiale
    const int pawn_val = 100;
    const int knight_val = 330;
    const int bishop_val = 330;
    const int rook_val = 520;
    const int queen_val = 980;
    const int king_val = 10000;
	const int tot_val = 12260;

    int _difficulty;
    bool _isThinking;

	int manhattan(int i, int j);

    void run();

public:
    Game(int diff=3, bool new_game=false);
    ~Game();

    //getter
    static logicPiece*** board() { return _board; }
    static logicPiece* white_king() { return w_k; }
    static logicPiece* black_king() { return b_k; }
    bool turn() { return turn_player; }
    std::list<int> get_moves(int pos);
    std::list<int> get_pseudomoves(int pos);
	QList<Move*> captures();
    QList<Move> allmoves();
	QList<pairmove> allmoves_ordinate();
    std::list<Move*> allpseudomoves();
    Move* lastMove() { return _lastMove; }
    bool isThinking() { return _isThinking; }

    //make/undo moves
    void move(Move* v);
    void undo();

    void changeToQueen(Move* v);


    //evaluation of the state of the game
    bool check(bool black);
    bool check_mate();
    int evaluate();
    int utility();
	int Quiesce(int alpha, int beta, int d, bool max_player);


    int negamax(int d, bool max_player, int a, int b, Move &best_move);

	void print_board();

    //metadata
    void loadSettings();
    void saveSettings(std::vector<QChar> black_p, std::vector<QChar> white_p, QString time);

signals:
    void notify(Move*);
};
