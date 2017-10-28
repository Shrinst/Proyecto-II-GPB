//
// Created by kevin on 17/10/17.
//

#ifndef PATHFINDING_ASTEROID_H
#define PATHFINDING_ASTEROID_H


class asteroid {
public:
    int Xact;
    int dx;
    int Yact;
    int dy;
    int direccion;

    /*
     * @brief Constructor de asteroide
     * @param X la posicion en X(columna) en la que se encuentra
     * @param Y la posicion en Y(fila) en la que se encuentra
     * @param d la direccion hacia la que se mueve el asteroide
     *          2(arriba)
     *  4(izquierda)    6(derecha)
     *          8(abajo)
     */
    asteroid(int x, int y, int d){
        Xact = x;
        Yact = y;
        dx = 0;
        dy = 0;
        direccion = d;
    }
};


#endif //PATHFINDING_ASTEROID_H
