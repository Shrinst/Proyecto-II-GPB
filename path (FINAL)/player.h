//
// Created by kevin on 17/10/17.
//

#ifndef PATHFINDING_PLAYER_H
#define PATHFINDING_PLAYER_H
#include <vector>

class player {
public:
    int Xact;
    int dx;
    int Yact;
    int dy;
    vector<int> path;

    player(){

    }

    ~player(){}

    int getXact(){
        return Xact;
    }
    void setposI(int x, int y){
        Xact = x;
        Yact = y;
        dx = x;
        dy = y;
    }
    int getYact(){
        return Yact;
    }
    int selector(int x1, int y1, int x2, int y2){
        if(x2 > x1){
            if(y2>y1){
                return 9;
            }else{
                if(y2<y1){
                    return 3;
                }else{
                    return 6;
                }
            }
        }else{
            if(x2 < x1){
                if(y2>y1){
                    return 7;
                }else{
                    if(y2<y1){
                        return 1;
                    }else{
                        return 4;
                    }
                }
            }else{
                if(y2>y1){
                    return 8;
                }else{
                    return 2;
                }
            }
        }
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
