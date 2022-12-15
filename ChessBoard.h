#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QSound>
#include <list>
#include <vector>
#include <QChar>
#include <QCloseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsEffect>
#include "Game.h"
#include "cronometro.h"
#include "Move.h"
#include "LogicPiece.h"
#include "Square.h"
#include "Piece.h"

class ChessBoard : public QGraphicsView {

    Q_OBJECT

private:
    Square*** _board;
    Piece* piece_to_move;
    Piece* piece_to_eat;
    QGraphicsScene* _scene;
    int moveX;
    int moveY;
    QGraphicsEllipseItem* _circleTurn;
    QGraphicsEllipseItem* _contorno;
    QGraphicsTextItem* _turnText;
    QGraphicsRectItem* _rettangolo;
    std::list<int> possible_move;
    QSound* _player;
    QSound* _piecemoved;
    QSound* _Eaten;
    QSound* _Lose;
    QSound* _error;
    QSound* _selected;
    Game* _game;
    int difficulty;
    bool _newgame;
    std::vector<Piece*> _whiteEaten;
	std::vector<Piece*> _blackEaten;
    Cronometro *_chrono;
    Square* _lastaimovefrom;	//for restauring the color of ai moving squares
    Square* _lastaimoveto;		//for restauring the color of ai moving squares
    Square* _lastaicheck;		//for restauring the color of ai check
	Square* _lastcheck;			//for restauring the color of player check

public:
    ChessBoard(int diff = 3, bool newgame = true);
    ~ChessBoard();
	void drawPieces(logicPiece*** b);

	Square*** square() { return _board; }

    void show_moves(std::list<int> moves);
    void hide_moves(std::list<int> moves);
   

    virtual void resizeEvent(QResizeEvent* e);

    void reset();
    void load();

    virtual void keyPressEvent(QKeyEvent* e);
    logicPiece*** getBoard() { return Game::board(); }

    void chiusura(QCloseEvent* event);
    
	void addEatenPiece(Piece *p);
	void removeEatenPiece(Piece* p);
	std::vector<QChar> save_eaten(bool black);

public slots:

    void pieceSelected();
    void squareSelected(int x, int y);

    void setDifficulty(int diff) { difficulty = diff; }
	void move(Move* m);
	void aimove(Move* m);
    void undo();
    
    void changeColorTurn(bool turn);

signals:
	void wins(QString time, bool turn);
	void toSave();
};


