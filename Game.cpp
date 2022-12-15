#include "Game.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Rook.h"
#include "Piece.h"
#include <QString>
#include <iostream>
#include <QPair>

logicPiece*** Game::_board = nullptr;
logicPiece* Game::w_k = nullptr;
logicPiece* Game::b_k = nullptr;

bool operator< (const std::pair<int, Move>& lhs, const std::pair<int, Move>& rhs) {
	return lhs.first > rhs.first;
}

Game::Game(int diff, bool new_game)
{
    //allocate the board
    _board = new logicPiece**[8];
    for (int i = 0; i < 8; i++) {
        _board[i] = new logicPiece*[8];
    }

    //initialize board
    if (new_game)
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                if (j >= 2 && j <= 5)
                    _board[j][i] = nullptr;

                //pawns
                if (j == 1)
                    _board[j][i] = new Pawn(j * 8 + i, true);
                if (j == 6)
                    _board[j][i] = new Pawn(j * 8 + i, false);
                //rooks
                if (j == 0 && (i == 0 || i == 7))
                    _board[j][i] = new Tower(j * 8 + i, true);
                if (j == 7 && (i == 0 || i == 7))
                    _board[j][i] = new Tower(j * 8 + i, false);
                //knights
                if (j == 0 && (i == 1 || i == 6))
                    _board[j][i] = new Knight(j * 8 + i, true);
                if (j == 7 && (i == 1 || i == 6))
                    _board[j][i] = new Knight(j * 8 + i, false);
                //bishops
                if (j == 0 && (i == 2 || i == 5))
                    _board[j][i] = new Bishop(j * 8 + i, true);
                if (j == 7 && (i == 2 || i == 5))
                    _board[j][i] = new Bishop(j * 8 + i, false);
                //queens
                if (j == 0 && i == 3)
                    _board[j][i] = new Queen(j * 8 + i, true);
                if (j == 7 && i == 3)
                    _board[j][i] = new Queen(j * 8 + i, false);
                //kings
                if (j == 0 && i == 4)
                    _board[j][i] = new King(j * 8 + i, true);
                if (j == 7 && i == 4)
                    _board[j][i] = new King(j * 8 + i, false);
            }

        //initialize turn
        turn_player = false; //mod
        w_k = _board[7][4];
        b_k = _board[0][4];
    }
    else
        loadSettings();

    _lastMove = nullptr;
    _difficulty = diff;
    _isThinking = false;

}

void Game::move(Move* v)
{
    _board[v->to() / 8][v->to() % 8] = _board[v->from() / 8][v->from() % 8];
    _board[v->to() / 8][v->to() % 8]->setPos(v->to());
    _board[v->from() / 8][v->from() % 8] = nullptr;
    
    turn_player = !turn_player;

	changeToQueen(v);

	allMoves.push_back(v);
	_lastMove = v;

}

Game::~Game() {

    for (int i = 0; i < 8; i++)
        delete[] _board[i];
    delete[] _board;
}

std::list<int> Game::get_moves(int pos)
{
    std::list<int> tmp;

    if (_board[pos / 8][pos % 8])
    {
        if (_board[pos / 8][pos % 8]->check_color() == turn_player)
            tmp = _board[pos / 8][pos % 8]->possibleMove();
    }

    return tmp;
}

std::list<int> Game::get_pseudomoves(int pos)
{
    std::list<int> tmp;

    if (_board[pos / 8][pos % 8])
    {
        if (_board[pos / 8][pos % 8]->check_color() == turn_player)
            tmp = _board[pos / 8][pos % 8]->pseudo_moves();
    }

    return tmp;
}

void Game::changeToQueen(Move* v)
{
    Pawn* piece = dynamic_cast<Pawn*> (v->piece());

    if (piece)
    {
        if ((v->to() >= 0 && v->to() <= 7) || (v->to() >= 56 && v->to() <= 63))
		{
			Piece* appo = _board[v->to() / 8][v->to() % 8]->GraphicPiece();
			v->setOldPiece(_board[v->to() / 8][v->to() % 8]);
            _board[v->to() / 8][v->to() % 8] = new Queen(v->to(), v->piece()->check_color());
			v->setPiece(_board[v->to() / 8][v->to() % 8]);
			v->piece()->setGraphicPiece(appo);
			v->setChangedToQueen(true);
        }
    }
}

void Game::undo()
{
    Move* v=allMoves.back();

    turn_player = !turn_player;
    _board[v->from() / 8][v->from() % 8] = _board[v->to() / 8][v->to() % 8];
    _board[v->from() / 8][v->from() % 8]->setPos(v->from());

	if (v->ChangedToQueen())
	{
		delete _board[v->from() / 8][v->from() % 8];
		v->oldPiece()->setPos(v->from());
		_board[v->from() / 8][v->from() % 8] = v->oldPiece();
	}

    if (v->eaten())
        _board[v->to() / 8][v->to() % 8] = v->eaten();
    else _board[v->to() / 8][v->to() % 8] = nullptr;

    allMoves.pop_back();

    if (!allMoves.empty())
        _lastMove = allMoves[allMoves.size() - 1];
    else _lastMove = nullptr;
}

bool Game::check_mate()
{
    King* k = dynamic_cast<King*> (turn_player ? b_k : w_k);

    if (k->isChecked() && allmoves().empty()){
        return true;
    }
    else return false;
}

int Game::manhattan(int i, int j)
{
	int re_r = i / 8;
	int re_c = i % 8;
	int x_r = j / 8;
	int x_c = j % 8;

	if ((x_r >= re_r - 1) && (x_r <= re_r + 1) && (x_c >= re_c - 1) && (x_c <= re_c + 1))
		return 8;
	else if ((x_r >= re_r - 2) && (x_r <= re_r + 2) && (x_c >= re_c - 2) && (x_c <= re_c + 2))
		return 4;
	else if ((x_r >= re_r - 3) && (x_r <= re_r + 3) && (x_c >= re_c - 3) && (x_c <= re_c + 3))
		return 2;
	else if ((x_r >= re_r - 4) && (x_r <= re_r + 4) && (x_c >= re_c - 4) && (x_c <= re_c + 4))
		return 1;
	return 0;
}

int Game::evaluate()
{
	int value = 0;
	int number_w = 0;
	int number_b = 0;
	int queen_w = 0;
	int queen_b = 0;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (_board[i][j] == 0)
				continue;

			Pawn* p = dynamic_cast<Pawn*>(_board[i][j]);
			if (p)
			{
				value = p->check_color() ? (value - pawn_val) : (value + pawn_val);
				p->check_color() ? number_b++ : number_w++;
			}

			Knight* k = dynamic_cast<Knight*>(_board[i][j]);
			if (k)
			{
				value = k->check_color() ? (value - knight_val) : (value + knight_val);
				k->check_color() ? number_b++ : number_w++;
			}

			Bishop* b = dynamic_cast<Bishop*>(_board[i][j]);
			if (b)
			{
				value = b->check_color() ? (value - bishop_val) : (value + bishop_val);
				b->check_color() ? number_b++ : number_w++;
			}

			Tower* t = dynamic_cast<Tower*>(_board[i][j]);
			if (t)
			{
				value = t->check_color() ? (value - rook_val) : (value + rook_val);
				t->check_color() ? number_b++ : number_w++;
			}

			Queen* q = dynamic_cast<Queen*>(_board[i][j]);
			if (q)
			{
				value = q->check_color() ? (value - queen_val) : (value + queen_val);
				q->check_color() ? number_b++ : number_w++;
				q->check_color() ? queen_b++ : queen_w++;
			}

			/*
			King* kk = dynamic_cast<King*>(_board[i][j]);
			if (kk)
			{
				value = kk->check_color() ? (value - king_val) : (value + king_val);
				kk->check_color() ? number_b++ : number_w++;
			}
			*/

			if ((queen_b == 0 && queen_w == 0) || (queen_b == 1 && number_b <= 3) || (queen_w == 1 && number_w <= 3))
			{
				King* kw = dynamic_cast<King*>(w_k);
				King* kb = dynamic_cast<King*>(b_k);
				if (kw)
					kw->setEndGame(true);
				if (kb)
					kb->setEndGame(true);
			}

			value += _board[i][j]->bonus();
		}

	if (_difficulty == 3)
	{
		size_t m_w = 0;
		size_t m_b = 0;

		if (turn_player)
			m_b = allmoves().size();
		else m_w = allmoves().size();

		turn_player = !turn_player;
		if (turn_player)
			m_b = allmoves().size();
		else m_w = allmoves().size();
		turn_player = !turn_player;
		value += 10 * (m_w - m_b);
	}

	return value;
}

int Game::utility()
{
    return turn_player ? -10000 : 10000;
}

int Game::Quiesce(int alpha, int beta, int d, bool max_player)
{
	int standingPat = (max_player ? 1 : -1)*evaluate();

	if (standingPat >= beta)
	{
		return beta;
	}

	if (alpha < standingPat)
	{
		alpha = standingPat;
	}

	if (d == 0)
		return alpha;

	int score;

	for (auto &p: captures())
	{
		move(p);

		score = -Quiesce(-beta, -alpha, d-1, max_player);

		undo();

		if (score >= beta)
		{
			return beta;
		}
		if (score > alpha)
		{
			alpha = score;
		}
	}
	return alpha;
}

int Game::negamax(int d, bool max_player, int a, int b, Move& best_move)
{
    // return utility if game is ended
    if (check_mate())
        // verificare perché non riesce a mettere scacco matto ma solo scacco
       return (max_player ? 1: -1)*(-utility());
    
	// return evaluation if maximum game depth has been reached
    if (d == 0)
        return Quiesce(a,b,(_difficulty == 3 ? 8 : 5),max_player);

    // initialize maximum evaluation
    int eu = std::numeric_limits<int>::min();
	//initialize move
	logicPiece* p = nullptr;
	Move mossa(p, p, 0, 0);
	int proof = 0;

	if (d == _difficulty)
	{
		for (auto &v : allmoves_ordinate())
		{
			// make the move corresponding to 'v'
			move(&v.second);

			// maximise utility and store best move so far
			int ev = -negamax(d - 1, !max_player, -b, -a, mossa);
			if (ev > eu)
			{
				eu = ev;
				best_move = v.second;
			}

			// restore previous game state / undo the move
			undo();
			// update best move
			a = std::max(a, eu);

			// alpha-beta pruning
			if (a >= b)
				return a;
		}
	}
    // loop over children 'v' of current game node 'u'
    for (auto & v : allmoves())
    {
        // make the move corresponding to 'v'
        move(&v);

        // maximise utility and store best move so far
        int ev = -negamax(d - 1, !max_player, -b, -a,mossa);
		if (ev > eu)
		{
			eu = ev;
			best_move = v;
		}

        // restore previous game state / undo the move
        undo();
        // update best move
        a = std::max(a, eu);

        // alpha-beta pruning
        if (a >= b)
            return a;
    }

    return eu;
}

void Game::run()
{
    // nothing to do if game is ended
    if (check_mate())
        return;

    // begin thinking
    _isThinking = true;
    //AI
	logicPiece* p = nullptr;
	Move *best_move = new Move(p, p, 0, 0);
	
	/*
	if (negamax(1, false, -10000, 10000, *best_move) == 10000)
	{
		_isThinking = false;
		emit notify(best_move);
		return;
	}
	*/
	/*
	if (_difficulty == 5 && negamax(3, false, -10000, 10000, *best_move) == 10000)
	{
		_isThinking = false;
		emit notify(best_move);
		return;
	}
	*/

    negamax(_difficulty, false, -10000, 10000, *best_move);
    //end thinking
    _isThinking = false;
    emit notify(best_move);
}

QList<Move> Game::allmoves()
{
	QList<Move> l;
    logicPiece* eaten = nullptr;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (_board[i][j] == nullptr)
                continue;

            for (auto &p : get_moves(i * 8 + j))
            {
                if (_board[p / 8][p % 8] != nullptr)
                    eaten = _board[p / 8][p % 8];
                else eaten = nullptr;
                l.push_back(Move(_board[i][j], eaten, i * 8 + j, p));
            }
        }
	
	return l;
}

QList<pairmove> Game::allmoves_ordinate()
{

	QList< pairmove > tmp;

	int eu = std::numeric_limits<int>::min();

	for (auto &p : allmoves())
	{
		// make the move corresponding to 'v'
		move(&p);
		// maximise utility and store best move so far
		if (check_mate())
			tmp.push_back(std::pair<int,Move>(10000,p));
		else tmp.push_back(std::pair<int, Move>(-evaluate(),p));
		// restore previous game state / undo the move
		undo();
	}

	std::sort(tmp.begin(), tmp.end());

	return tmp;
}

QList<Move*> Game::captures()
{
	QList<Move*> l;
	logicPiece* eaten = nullptr;
	Pawn* pa = nullptr;
	bool first = false;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (_board[i][j] == nullptr)
				continue;

			for (auto &p : get_moves(i * 8 + j))
			{
				if (_board[p / 8][p % 8] == nullptr)
					continue;
				if (_board[p / 8][p % 8] != nullptr)
					eaten = _board[p / 8][p % 8];
				else eaten = nullptr;
				l.push_back(new Move(_board[i][j], eaten, i * 8 + j, p));
			}
		}

	return l;
}

std::list<Move*> Game::allpseudomoves()
{
    std::list<Move*> l;
    logicPiece* eaten = nullptr;
    Pawn* pa = nullptr;
    bool first = false;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (_board[i][j] == nullptr)
                continue;

            for (auto &p : get_pseudomoves(i * 8 + j))
            {
				if (_board[p / 8][p % 8] != nullptr)
                    eaten = _board[p / 8][p % 8];
                else eaten = nullptr;

                l.push_back(new Move(_board[i][j], eaten, i * 8 + j, p));
            }
        }

    return l;
}

bool Game::check(bool black)
{
    King* k = dynamic_cast<King*>(black ? b_k : w_k);

    return k->isChecked();
}

void Game::loadSettings()
{
    QSettings setting;

    turn_player = setting.value("turn", true).toBool();
	_difficulty = setting.value("difficulty", 3).toInt();

    //lettura scacchiera
    std::vector<QChar> _piece;
    int size = setting.beginReadArray("pieces");
    for (int i = 0; i < size; i++)
    {
        setting.setArrayIndex(i);
        _piece.push_back(setting.value("piece").toChar());
    }
    setting.endArray();


    for (size_t i = 0; i < _piece.size(); i++)
    {
        if (_piece[i] == '0')
            _board[i / 8][i % 8] = nullptr;
        else if (_piece[i] == 'a')
            _board[i / 8][i % 8] = new Bishop(i, false);
        else if (_piece[i] == 'A')
            _board[i / 8][i % 8] = new Bishop(i, true);
        else if (_piece[i] == 'p')
            _board[i / 8][i % 8] = new Pawn(i, false);
           
        else if (_piece[i] == 'P')
            _board[i / 8][i % 8] = new Pawn(i, true);
        else if (_piece[i] == 'c')
            _board[i / 8][i % 8] = new Knight(i, false);
        else if (_piece[i] == 'C')
            _board[i / 8][i % 8] = new Knight(i, true);
        else if (_piece[i] == 'k')
        {
            _board[i / 8][i % 8] = new King(i, false);
            w_k = _board[i / 8][i % 8];
        }
        else if (_piece[i] == 'K')
        {
            _board[i / 8][i % 8] = new King(i, true);
            b_k = _board[i/8][i%8];
        }
        else if (_piece[i] == 'q')
            _board[i / 8][i % 8] = new Queen(i, false);
        else if (_piece[i] == 'Q')
            _board[i / 8][i % 8] = new Queen(i, true);
        else if (_piece[i] == 't')
            _board[i / 8][i % 8] = new Tower(i, false);
        else if (_piece[i] == 'T')
            _board[i / 8][i % 8] = new Tower(i, true);
    }
}

void Game::saveSettings(std::vector<QChar> black_p, std::vector<QChar> white_p, QString time)
{
    QSettings setting;
    std::vector<QChar> _piece(64);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (_board[i][j] == nullptr)
                _piece[i * 8 + j] = '0';
            else if (_board[i][j]->name() == 'p')
                _piece[i*8 + j]=_board[i][j]->check_color() ? 'P' : 'p';
            else if (_board[i][j]->name() == 'c')
                _piece[i*8 + j] =_board[i][j]->check_color() ? 'C' : 'c';
            else if (_board[i][j]->name() == 'a')
                _piece[i*8 + j] = _board[i][j]->check_color() ? 'A' : 'a';
            else if (_board[i][j]->name() == 'k')
                _piece[i*8 +j] = _board[i][j]->check_color() ? 'K' : 'k';
            else if (_board[i][j]->name() == 'q')
                _piece[i*8 +j] = _board[i][j]->check_color() ? 'Q' : 'q';
            else if (_board[i][j]->name() == 't')
                _piece[i*8 +j] = _board[i][j]->check_color() ? 'T' : 't';
        }

    setting.setValue("turn", turn_player);
	setting.setValue("difficulty", _difficulty);
	setting.setValue("time", time);
	King* k = dynamic_cast<King*>(turn_player ? b_k : w_k);
	setting.setValue("KingChecked", k->isChecked());

    //_piece.clear();

    setting.beginWriteArray("pieces");
    int count = 0;
    for (auto & f : _piece)
    {
        setting.setArrayIndex(count++);
        setting.setValue("piece", f);
    }
    setting.endArray();

	setting.beginWriteArray("white_p");
	count = 0;
	for (auto & f : white_p)
	{
		setting.setArrayIndex(count++);
		setting.setValue("piece_w", f);
	}
	setting.endArray();

	setting.beginWriteArray("black_p");
	count = 0;
	for (auto & f : black_p)
	{
		setting.setArrayIndex(count++);
		setting.setValue("piece_b", f);
	}
	setting.endArray();
}

void Game::print_board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			if (_board[i][j] == nullptr)
				std::cout << 'v';
			else std::cout << (_board[i][j]->check_color() ? _board[i][j]->name().toUpper().toLatin1() : _board[i][j]->name().toLatin1());
		std::cout << std::endl;
	}
}