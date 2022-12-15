#include "GodWindow.h"


GodWindow* GodWindow::uniqueinstance=0;

GodWindow* GodWindow::instance(){
    
    if(uniqueinstance==0)
        uniqueinstance=new GodWindow();
    return uniqueinstance;
    
}


GodWindow::GodWindow() : QWidget()
{
	_widgetStack = new QStackedLayout(this);
	
	_first = new FirstWindow(this);
    _first->show();
	
	_chess = 0;
	
	_widgetStack->addWidget(_first);
	
	_widgetStack->setStackingMode(QStackedLayout::StackAll);


	_widgetStack->setAlignment(Qt::AlignCenter);
    
    setMinimumSize(1150,650);
	
}

GodWindow::~GodWindow()
{
}

void GodWindow::closeEvent(QCloseEvent *event)
{
	if(_chess)
		_chess->chiusura(event);
}

void GodWindow::end_game(QString time, bool turn)
{
	_first = new FirstWindow(this);
	_first->show();
	_widgetStack->addWidget(_first);
	_chess->deleteLater();
	_chess = nullptr;
}