#include "cronometro.h"
#include <iostream>

Cronometro::Cronometro(QString init_time, QWidget *parent):QLCDNumber(parent){

	setOra(init_time);
    
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    
    showTime();
}


void Cronometro::showTime(){
    
    secondi++;
    
    
    if(secondi==60){
        secondi=0;
        minuti++;
    }
    if(secondi==60 && minuti==60){
        secondi=0;
        minuti=0;
        ore++;
    }
    
    this->setDigitCount(8);
    
    QString risultato = tr("%3:%2:%1").arg(secondi,2,10,QLatin1Char('0')).arg(minuti,2,10,QLatin1Char('0')).arg(ore,2,10,QLatin1Char('0'));

    display(risultato);
    
}

void Cronometro::reset(){
    
    ore=0;
    minuti=0;
    secondi=0;
    
}


QString Cronometro::getOra(){
    
    QString risultato = tr("%3:%2:%1").arg(secondi,2,10,QLatin1Char('0')).arg(minuti,2,10,QLatin1Char('0')).arg(ore,2,10,QLatin1Char('0'));
    
    return risultato;

}

void Cronometro::setOra(QString newOra){
    
    ore=newOra.split(":")[0].toInt();
    minuti=newOra.split(":")[1].toInt();
    secondi=newOra.split(":")[2].toInt();
    
}

void Cronometro::stop(){
    
    timer->stop();
    
}

void Cronometro::start(){
    
    timer->start(1000);
    
}
