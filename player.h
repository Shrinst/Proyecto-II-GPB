//
// Created by kevin on 17/10/17.
//

#ifndef PATHFINDING_PLAYER_H
#define PATHFINDING_PLAYER_H


class player {
public:
    int Xact;
    int dx;
    int Yact;
    int dy;

    player(){
        Xact = 0;
        Yact = 0;
        dx = 0;
        dy = 0;
    }

    ~player(){}

    int getXact(){
        return Xact;
    }

    int getYact(){
        return Yact;
    }

    //Revisa si los parametros dados son los que ha guardado el objeto
    bool finish(int X, int Y){
        if (Xact == X && Yact == Y){
            return true;
        }
        return false;
    }

};


#endif //PATHFINDING_PLAYER_H
