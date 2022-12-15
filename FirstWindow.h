#pragma once

#include <QWidget>
#include <QEvent>
#include <QPushButton>
#include <QLayout>
#include <QStackedLayout>
#include <QLabel>

class FirstWindow : public QWidget
{
	Q_OBJECT

private:

	QPushButton*      _newGame;
	QPushButton*      _continue;
	QLabel*           _startText;
	QVBoxLayout*      _layout;
	QPushButton*      _ranking; 
	
public:
	FirstWindow(QWidget* parent = nullptr);
	~FirstWindow();
		

public slots:
	void NewGame();
	void ResumeGame();

};
