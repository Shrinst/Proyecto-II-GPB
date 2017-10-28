#include "Falcon.h"
#include <QTimer>
using namespace std;

Bullet::Bullet(vector<int> path_){
    path = path_;
    // drew the rect

    //setRect(0,0,50,50);
    // connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(5);
}

void Bullet::move(){
    // move bullet up
    if(path.size() > 0){
        if(path.front() == 1){
            setPixmap(QPixmap(":/img/naveIZ.png"));
            setPos(x()-1,y());
            setPixmap(QPixmap(":/img/naveAR.png"));
            setPos(x(),y()-1);
        }
        else if(path.front() == 2){
            setPixmap(QPixmap(":/img/naveAR.png"));
            setPos(x(),y()-1);
        }
        else if(path.front() == 3){
            setPixmap(QPixmap(":/img/naveDE.png"));
            setPos(x()+1,y());
            setPixmap(QPixmap(":/img/naveAR.png"));
            setPos(x(),y()-1);
        }
        else if(path.front() == 4){
            setPixmap(QPixmap(":/img/naveIZ.png"));
            setPos(x()-1,y());
        }
        else if(path.front() == 6){
            setPixmap(QPixmap(":/img/naveDE.png"));
            setPos(x()+1,y());
        }
        else if(path.front() == 7){
            setPixmap(QPixmap(":/img/naveIZ.png"));
            setPos(x()-1,y());
            setPixmap(QPixmap(":/img/naveAB.png"));
            setPos(x(),y()+1);
        }
        else if(path.front() == 8){
            setPixmap(QPixmap(":/img/naveAB.png"));
            setPos(x(),y()+1);
        }
        else{
            setPixmap(QPixmap(":/img/naveDE.png"));
            setPos(x()+1,y());
            setPixmap(QPixmap(":/img/naveAB.png"));
            setPos(x(),y()+1);
        }
        if(contador == 49){
            path.erase(path.begin());
            contador = 0;
        }else{
            contador+=1;
        }
    }
}
