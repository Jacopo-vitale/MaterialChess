#include <QMessageBox>
#include <QGraphicsProxyWidget>
#include <iostream>
#include "ChessBoard.h"
#include "GodWindow.h"
#include "Move.h"
#include "King.h"
#include <utility>

ChessBoard::ChessBoard(int diff, bool newgame) {

    //initialize board
    _board = nullptr;
    
    //inizialize music
    _player = new QSound(":/sounds/Check.wav");
    _piecemoved = new QSound(":/sounds/TickMoved.wav");
    _Eaten = new QSound(":/sounds/Eat.wav");
    _Lose = new QSound(":/sounds/CheckMate2.wav");
    _error =new QSound(":/sounds/Error.wav");
    _selected=new QSound(":/sounds/TickSelected.wav");

    difficulty = diff;
    _newgame = newgame;
    
    //init turn circle and its background
    _circleTurn = new QGraphicsEllipseItem(-170,2,300,300);
    _contorno = new QGraphicsEllipseItem(-170,2,308,308);
    
    //init turn label
    _turnText = new QGraphicsTextItem("TURN");
    
    _rettangolo=new QGraphicsRectItem((8 * Square::cell_size)+246, Square::cell_size-54,408,108);


    //set scene
    _scene = new QGraphicsScene();
    _scene->setSceneRect(0, 0, Square::cell_size * 8, Square::cell_size * 8);
    _scene->setBackgroundBrush(QColor(188,194,221));

    //set view
    setScene(_scene);
    resizeEvent(nullptr);
    setInteractive(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _game=nullptr;
    
	//reset function
    reset();
}


ChessBoard::~ChessBoard() {

    if (_board != nullptr) {
        for (int i = 0; i < 8; i++)
            delete[] _board[i];
        delete[] _board;
    }
}

void ChessBoard::resizeEvent(QResizeEvent* e)
{
    fitInView(_scene->sceneRect(), Qt::KeepAspectRatio);
}

void ChessBoard::reset() {

    if (_board != nullptr) {
        for (int i = 0; i < 8; i++)
            delete[] _board[i];
        delete[] _board;
    }

    _scene->clear();

    //No moving to do
    piece_to_move = nullptr;
    piece_to_eat = nullptr;
    _lastaimovefrom = nullptr;
    _lastaimoveto = nullptr;
    _lastaicheck = nullptr;
    _lastcheck = nullptr;

	//set game
	_game = new Game(difficulty, _newgame);
	connect(_game, SIGNAL(notify(Move*)), this, SLOT(aimove(Move*)));

    _board = new Square**[8];
    int counter = 0;
    for (int i = 0; i < 8; i++)
    {
        _board[i] = new Square*[8];
        for (int j = 0; j < 8; j++)
        {
            _board[i][j] = new Square(i*Square::cell_size, j*Square::cell_size, (counter++) % 2);
            _scene->addItem(_board[i][j]);
			_scene->addItem(_board[i][j]->t());
            connect(_board[i][j], SIGNAL(clicked(int, int)), this, SLOT(squareSelected(int, int)));
        }
        counter++;
    }

    //draw pieces
	if (_newgame)
	{
		drawPieces(Game::board());
		_chrono = new Cronometro("00:00:00");
	}
	else load();
    

//    set chrono
    QGraphicsProxyWidget* item = (_scene->addWidget(_chrono));
    item->setPos((8 * Square::cell_size)+250, Square::cell_size-50);
    item->setMinimumSize(400, 100);
    item->setZValue(6);
    _chrono->start();
    
    _rettangolo->setBrush(QBrush(Qt::black));
    _rettangolo->setZValue(0);
    _scene->addItem(_rettangolo);
    
    QPen pen;
    QBrush brush;
    QPainter paint;
    QFont font;
    QPalette pal;
    //setting circle turn
    _circleTurn->setBrush(QBrush(QColor(207, 214, 229)));
    _circleTurn->setPos(-450,150);
    pen.setColor(QColor(207, 214, 229));
    _circleTurn->setPen(pen);
    _circleTurn->setZValue(6);
    _scene->addItem(_circleTurn);
    
    _contorno->setBrush(QBrush(Qt::black));
    _contorno->setPos(-454,146);
    pen.setColor(QColor(207, 214, 229));
    _contorno->setPen(pen);
    _contorno->setZValue(0);
    _scene->addItem(_contorno);
    
//    //setting turn text
//    font.setFamily("Arial Bound");
//    font.setPointSize(75);
//    _turnText->setDefaultTextColor(QColor(255, 255, 255));
//    _turnText->setZValue(6);
//    _turnText->setPos(-478,84);
//    _turnText->setFont(font);
//    _scene->addItem(_turnText);

}

void ChessBoard::drawPieces(logicPiece*** b)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (b[i][j] == nullptr)
				continue;
			b[i][j]->setGraphicPiece(new Piece(j*Square::cell_size, i*Square::cell_size, b[i][j]->check_color(), b[i][j]->name()));
			connect(b[i][j]->GraphicPiece(), SIGNAL(checked()), this, SLOT(pieceSelected()));
			_scene->addItem(b[i][j]->GraphicPiece());
		}
}


void ChessBoard::pieceSelected()
{
    if (_game->isThinking())
        return;

    Piece* tmp = dynamic_cast<Piece*>(QObject::sender());
	int y = tmp->y() / Square::cell_size;
	int x = tmp->x() / Square::cell_size;

    if (piece_to_move == nullptr)
    {
        hide_moves(possible_move);
        possible_move = _game->get_moves(y * 8 + x);
        if (!possible_move.empty())
        {
            piece_to_move = tmp;
			piece_to_move->colorized(true);
            show_moves(possible_move);
        }
    }
    else
    {
        if (piece_to_move->black() == tmp->black())
        {
			piece_to_move->colorized(false);
            piece_to_move = tmp;
			piece_to_move->colorized(true);
            hide_moves(possible_move);
            possible_move = _game->get_moves((piece_to_move->y() / Square::cell_size) * 8 + (piece_to_move->x() / Square::cell_size));
            show_moves(possible_move);
        }
        else
        {
            piece_to_eat = tmp;
			int from_x = piece_to_move->x() / Square::cell_size;
			int from_y = piece_to_move->y() / Square::cell_size;
			int to_x = piece_to_eat->x() / Square::cell_size;
			int to_y = piece_to_eat->y() / Square::cell_size;

			if (_board[to_x][to_y]->movable())
				move(new Move(piece_to_move, piece_to_eat, from_y * 8 + from_x, to_y * 8 + to_x));
				
			else
			{
				piece_to_move->colorized(false);
				piece_to_eat = nullptr;
				piece_to_move = nullptr;
				hide_moves(possible_move);
			}
        }
    }
}

void ChessBoard::squareSelected(int x, int y)
{
    if (_game->isThinking())
        return;

    moveX = x;
    moveY = y;


	if (piece_to_move != 0)
	{
		int from = (piece_to_move->x() / Square::cell_size) + 8 * (piece_to_move->y() / Square::cell_size);
		int to = 8 * (moveY / Square::cell_size) + (moveX / Square::cell_size);
	
		if (_board[to % 8][to / 8]->movable())
			move(new Move(piece_to_move, nullptr, from, to));
		else
		{
			piece_to_move->colorized(false);
			piece_to_move = nullptr;
			hide_moves(possible_move);
		}
	}
}

void ChessBoard::show_moves(std::list<int> moves)
{
    for (auto &p : moves)
    {
		_board[p % 8][p / 8]->colorized(true);
        _board[p % 8][p / 8]->setMovable(true);
    }
}

void ChessBoard::hide_moves(std::list<int> moves)
{
    for (auto &p : moves)
    {
		_board[p % 8][p / 8]->colorized(false);
        _board[p % 8][p / 8]->setMovable(false);
    }
}

void ChessBoard::move(Move* m)
{
	if (_game->lastMove() != nullptr && !_game->turn())
	{
		_board[_game->lastMove()->from() % 8][_game->lastMove()->from() / 8]->ai_colorized(false, true);
		_board[_game->lastMove()->to() % 8][_game->lastMove()->to() / 8]->ai_colorized(false, true);
	}

	if (_lastcheck != nullptr)
		_lastcheck->check_colorized(false);
	
	if (m->eaten())
	{
		addEatenPiece(m->eaten()->GraphicPiece());
		_player->play(":/sounds/Eat.wav");
	}
	else _player->play(":/sounds/TickMoved.wav");

	_game->move(m);
    m->piece()->GraphicPiece()->setPos((m->to() % 8)*Square::cell_size, (m->to() / 8)*Square::cell_size);

	if (_game->lastMove()->ChangedToQueen())
	{
		_scene->removeItem(_game->lastMove()->piece()->GraphicPiece());
		_game->lastMove()->piece()->setGraphicPiece(new Piece((m->to() % 8)*Square::cell_size, (m->to() / 8)*Square::cell_size, _game->lastMove()->piece()->check_color(), 'q'));
		_scene->addItem(_game->lastMove()->piece()->GraphicPiece());
		connect(_game->lastMove()->piece()->GraphicPiece(), SIGNAL(checked()), this, SLOT(pieceSelected()));
	}

	m->piece()->GraphicPiece()->colorized(false);
    piece_to_move = nullptr;
    hide_moves(possible_move);

	if (_game->check(_game->turn()))
	{
		King* k = static_cast<King*>(_game->turn() ? Game::black_king() : Game::white_king());
		_board[k->pos() % 8][k->pos() / 8]->check_colorized(true);
		_lastcheck = _board[k->pos() % 8][k->pos() / 8];
		_player->play(":/sounds/Check.wav");
	}

	if (_game->check_mate())
	{
        if(!_game->turn())
            _Lose->play();
		QMessageBox::information(this, "Check mate!", _game->turn() ? "Human wins!" : "AI wins!");
		GodWindow::instance()->end_game(_chrono->getOra(), !_game->turn());
	}

	changeColorTurn(_game->turn());

	if (_game->turn())
		_game->start();
}

void ChessBoard::aimove(Move* m)
{
	move(m);

	_board[m->from() % 8][m->from() / 8]->ai_colorized(true, true);
	_board[m->to() % 8][m->to() / 8]->ai_colorized(true, false);
}

void ChessBoard::undo()
{
    if (_game->lastMove() == nullptr)
        return;

	if (piece_to_move)
	{
		hide_moves(possible_move);
		piece_to_move->colorized(false);
		piece_to_move = nullptr;
	}

	//restore color square modified by ai moves
	_board[_game->lastMove()->from() % 8][_game->lastMove()->from() / 8]->ai_colorized(false, true);
	_board[_game->lastMove()->to() % 8][_game->lastMove()->to() / 8]->ai_colorized(false, true);

	//restore color square modified by check
	if (_lastcheck != nullptr)
		_lastcheck->check_colorized(false);

	Move* lastPos = _game->lastMove();

    int y = (lastPos->from() / 8)*Square::cell_size;
    int x = (lastPos->from() % 8)*Square::cell_size;

	if (lastPos->eaten() != nullptr)
	{
		removeEatenPiece(lastPos->eaten()->GraphicPiece());
		lastPos->eaten()->GraphicPiece()->setPos((lastPos->to() % 8)*Square::cell_size, (lastPos->to() / 8)*Square::cell_size);
	}

    if (lastPos->ChangedToQueen())
    {
		_scene->removeItem(lastPos->piece()->GraphicPiece());
		delete lastPos->piece()->GraphicPiece();
		lastPos->piece()->setGraphicPiece(lastPos->oldPiece()->GraphicPiece());
		lastPos->piece()->GraphicPiece()->colorized(false);
        _scene->addItem(lastPos->piece()->GraphicPiece());
        connect(lastPos->piece()->GraphicPiece(), SIGNAL(checked()), this, SLOT(pieceSelected()));
    }

	lastPos->piece()->GraphicPiece()->setPos(x, y);

    piece_to_move = nullptr;
	_game->undo();
	changeColorTurn(_game->turn());

	if (_game->check(_game->turn()))
	{
		King* k = static_cast<King*>(_game->turn() ? Game::black_king() : Game::white_king());
		_board[k->pos() % 8][k->pos() / 8]->check_colorized(true);
		_lastcheck = _board[k->pos() % 8][k->pos() / 8];
	}
	else _lastcheck = nullptr;

}

void ChessBoard::keyPressEvent(QKeyEvent* e)
{
    if (_game->isThinking())
        return;

	if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Z)
        undo();
}


void ChessBoard::chiusura(QCloseEvent *event)
{
	_chrono->stop();
    QMessageBox::StandardButton choice = QMessageBox::warning(this, "Uscita", "Vuoi davvero uscire?", QMessageBox::Yes | QMessageBox::No);

    if (choice == QMessageBox::No)
    {
		_chrono->start();
        event->ignore();
        return;
    }
    else
    {
        event->accept();
        QMessageBox::StandardButton choice = QMessageBox::question(this, "Salvataggio", "Vuoi salvare la partita?", QMessageBox::Yes | QMessageBox::No);
        if (choice == QMessageBox::No)
            return;
		emit toSave();
        _game->saveSettings(save_eaten(true),save_eaten(false),_chrono->getOra());
    }
}

void ChessBoard::load()
{
    QSettings setting;

	//init chrono
	_chrono = new Cronometro(setting.value("time", "00:00:00").toString());
	_chrono->stop();

	bool checked = setting.value("KingChecked", false).toBool();
	if (checked)
	{
		logicPiece* k = _game->turn() ? Game::black_king() : Game::white_king();
		_board[k->pos() % 8][k->pos() / 8]->setBrush(QColor(176, 0, 32));
		_board[k->pos() % 8][k->pos() / 8]->setOpacity(1.0);
			_lastcheck = _board[k->pos() % 8][k->pos() / 8];
	}

	drawPieces(Game::board());

	size_t size = setting.beginReadArray("white_p");
	std::vector<QChar> _piece;
	Piece* p;
	for (int i = 0; i < size; i++)
	{
		setting.setArrayIndex(i);
		_piece.push_back(setting.value("piece_w").toChar());
	}
	setting.endArray();

	_whiteEaten.clear();
	for (auto &l : _piece)
	{
		p = new Piece(0, 0, false, l);
		addEatenPiece(p);
		_scene->addItem(p);
	}

	size = setting.beginReadArray("black_p");
	_piece.clear();
	for (int i = 0; i < size; i++)
	{
		setting.setArrayIndex(i);
		_piece.push_back(setting.value("piece_b").toChar());
	}
	setting.endArray();

	_blackEaten.clear();
	for (auto &l : _piece)
	{
		p = new Piece(0, 0, true, l.toLower());
		addEatenPiece(p);
		_scene->addItem(p);
	}
}

void ChessBoard::addEatenPiece(Piece *p)
{
	if (!p->black())
	{
		if (_whiteEaten.size() == 0)
			p->setPos( -900, 900);
		else if (_whiteEaten.size() % 3 != 0)
			p->setPos(_whiteEaten.back()->x() + 300, _whiteEaten.back()->y());
		else
			p->setPos(-900, _whiteEaten.back()->y() + 300);

		_whiteEaten.push_back(p);
	}
	else
	{
		if (_blackEaten.size() == 0)
			p->setPos(8*Square::cell_size + 10, 900);
		else if (_blackEaten.size() % 3 != 0)
			p->setPos(_blackEaten.back()->x() + 300, _blackEaten.back()->y());
		else
			p->setPos(8*Square::cell_size + 10, _blackEaten.back()->y() + 300);

		_blackEaten.push_back(p);
	}

	p->setDied(true);		
}

void ChessBoard::removeEatenPiece(Piece* p)
{
	if (_blackEaten.empty() && _whiteEaten.empty())
		return;

	if (p->black())
		_blackEaten.pop_back();
	else _whiteEaten.pop_back();

	p->setDied(false);
}

void ChessBoard::changeColorTurn(bool turn) {
    
    if (!turn)
        _circleTurn->setBrush(QBrush(QColor(207, 214, 229)));
    else
        _circleTurn->setBrush(QBrush(QColor(41, 58, 86)));
}

std::vector<QChar> ChessBoard::save_eaten(bool black)
{
	std::vector<QChar> tmp;

	if (black)
		for (auto& p : _blackEaten)
			tmp.push_back(p->name().toUpper());
	else
		for (auto& p : _whiteEaten)
			tmp.push_back(p->name());

	return tmp;
}
