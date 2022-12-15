#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "MyLabel.h"

class DifficultyWindow : public QWidget
{
	Q_OBJECT
private:
	QLabel* _chooseDiff;
	MyLabel* _easy;
	MyLabel* _mid;
	MyLabel* _hard;
	QVBoxLayout* _ly;

public:
	DifficultyWindow(QWidget* parent = nullptr);
	~DifficultyWindow();

public slots:
	void Chosen();
	
};
