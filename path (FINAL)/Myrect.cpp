#include "Myrect.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Falcon.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include "player.h"
#include "simulate.cpp"
void MyRect::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Space){
        int grid[10][12]={  //[Fila][Columna]
                { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                { 1, 8, 1, 1, 8, 1, 1, 8, 1, 8, 1, 1 },
                { 1, 8, 1, 8, 1, 1, 1, 1, 1, 1, 1, 1 },
                { 1, 1, 1, 1, 8, 8, 1, 1, 8, 8, 8, 8 },
                { 1, 8, 1, 8, 1, 8, 8, 8, 8, 1, 1, 1 },
                { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                { 1, 1, 1, 8, 1, 8, 1, 1, 8, 1, 1, 1 },
                { 1, 8, 8, 1, 1, 1, 8, 1, 1, 8, 8, 1 },
                { 1, 1, 8, 1, 1, 1, 1, 8, 1, 1, 1, 1 },
                { 1, 1, 1, 1, 1, 1, 1, 1, 8, 1, 8, 1 }
        };
        player jugador;
        vector<player> enemylist;

        player jugador1;
        jugador1.setposI(11,0);
        enemylist.push_back(jugador1);

        player jugador2;
        jugador2.setposI(10,1);
        enemylist.push_back(jugador2);

        jugador.setposI(0,9);
        Pair destino = make_pair(5,11);
        srand(NULL);

        while ( !jugador.finish(destino.second , destino.first) )
        {

            //MOVIMIENTO NAVE PRINCIPAL
            Pair pos = make_pair(jugador.Yact,jugador.Xact);
            Pair resultado = aStarSearch(grid,pos,destino);
            jugador.dx = resultado.second;
            jugador.dy = resultado.first;

            Pair destino1 = make_pair(jugador.dy,jugador.dx);

            jugador.path.push_back(jugador.selector(jugador.Xact,jugador.Yact,jugador.dx,jugador.dy));
            jugador.Xact = jugador.dx;
            jugador.Yact = jugador.dy;

            //Movimiento ENEMIGOS

            for(int i = 0; i < enemylist.size();i++){
                Pair pos1 = make_pair(enemylist.at(i).Yact, enemylist.at(i).Xact);
                Pair resultado1 = aStarSearch(grid,pos1,destino1);
                enemylist.at(i).dx = resultado1.second;
                enemylist.at(i).dy = resultado1.first;
                enemylist.at(i).path.push_back(enemylist.at(i).selector(enemylist.at(i).Xact,enemylist.at(i).Yact,enemylist.at(i).dx,enemylist.at(i).dy));
                enemylist.at(i).Xact = enemylist.at(i).dx;
                enemylist.at(i).Yact = enemylist.at(i).dy;
            }
            /*
            for(int i = 0;i < 10;i++){
                for(int j = 0;j < 12;j++){
                    cout << grid[i][j] << ",";
                }cout << "" <<endl;
            }cout << "_________________________" <<endl;
            */

        }
        //create asterooids
        for(int i = 0;i < 10;i++){
            for(int j = 0;j < 12;j++){
                if(grid[i][j] == 8){
                    QGraphicsPixmapItem *elemento = new QGraphicsPixmapItem;
                    elemento->setPos(j*50,i*50);
                    elemento->setPixmap(QPixmap(":/img/asteroid.png"));
                    scene()->addItem(elemento);
                }
            }
        }
        // create a bullet
        Bullet * bullet = new Bullet(jugador.path);
        bullet->setPos(x(),y()+450);
        scene()->addItem(bullet);

        Bullet * bullet1 = new Bullet(enemylist.at(0).path);
        bullet1->setPos(x()+550,y()+0);
        scene()->addItem(bullet1);

        Bullet * bullet2 = new Bullet(enemylist.at(1).path);
        bullet2->setPos(x()+500,y()+50);
        scene()->addItem(bullet2);
        /*
        for(int j = 0; j < jugador.path.size();j++){
            cout << jugador.path.at(j) << ", ";
        }cout << "" << endl;
        for(int i = 0; i < 2;i++){
            for(int j = 0; j < enemylist[i].path.size();j++){
                cout << enemylist[i].path.at(j) << ", ";
            }cout << "" << endl;
        }*/
    }
}
