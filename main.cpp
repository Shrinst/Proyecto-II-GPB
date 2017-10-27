#include "simulate.cpp"
#include "player.h"
#include "asteroid.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

//Lista para objeto T
template <class T>
struct Node{
    T data;
    struct Node* next;
};

/*
 * @brief Agrega un T al final de la lista
 * @param Node<T>** head_ref es la head de la lista(&head)
 * @param new_data objeto T a agregar
 */
template <class T>
void listAppend(struct Node<T>** head_ref, T new_data)
{
    struct Node<T>* new_node = (struct Node<T>*) malloc(sizeof(struct Node<T>));
    struct Node<T> *last = *head_ref;
    new_node->data  = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;
}

/*
 * @brief obtiene el largo de la lista
 * @param head la head de la lista(head)
 * @return int con el tamano de la lista
 */
template <class T>
int listSize(struct Node<T>* head)
{
    int count = 0;
    struct Node<T>* current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

/*
 * @brief obtiene un puntero a T de acuerdo a la posicion de la lista
 * @param *head la head de la lista(head)
 * @param num el int de la posicion en la lista a obtener
 * @return T de esa posicion en la lista
 */             //REVISAR EL FUNCIONAMIENTO DE METODO Y SI VERDADERAMENTE DA UN PUNTERO
template <class T>
T getByPos(struct Node<T>* head, int num){
    struct Node<T>* current = head;
    while(num!=0 && current!=NULL){
        current = current->next;
        num--;
    }
    return *(current->data);
}


/*
 * @brief Genera un numero random, el numero no sera 0 ni MaxValue-1
 * @param MaxValue el mayor numero de columna o fila segun sea el caso
 * @return un numero X tal que 1<X<(MaxValue-1)
 */
int getRandom(int MaxValue){
    return 1+rand()%(MaxValue-1);
}

/*
 * @brief Genera un numero random guia
 * @return 1 o 0
 */
int getSeccion(){
    return rand()%2;
}

/*
 * @brief genera los asteroides y los agrega a la lista de estos
 * @param SaleDeX si es 1, los asteroides salen del borde horizontal
 * @param AoD si es 1, los asteroides salen de arriba o la derecha segun el SaleDeX
 */
void generateAsteroids(int SaleDeX,int AoD){
    if(SaleDeX == 1){
        if (AoD == 1){  //Sale del borde superior
            asteroid ast(getRandom(11),0,8);
            //Add a lista de meteoritos
        }else{          //Sale del borde inferior
            asteroid ast(getRandom(11),9,2);
            //Add a lista de meteoritos
        }
    }else{
        if (AoD == 1){  //Sale del borde de la derecha
            asteroid ast(11,getRandom(9),4);
            //Add a lista de meteoritos
        }else{          //Sale del borde de la izquierda
            asteroid ast(0,getRandom(9),6);
            //Add a lista de meteoritos
        }
    }
}

void moveAsteroids(){
    //Se mueve cada asteroide de la lista de asteroides y se analiza si choca o no
}

int main()
{
    int numAsteroides = 8;


    // 1 = Celda Vacia
    // 8 = Asteroide
    // 9 = Futuro Asteroide
    // 5 = Nave enemiga y su barrera
    int grid[10][12]={  //[Fila][Columna]
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };


    player jugador;
    Pair destino = make_pair(9,11);
    srand(NULL);

    int x = 0;

    while (x!=numAsteroides){   //Se crean y agregan los asteroides a la lista
        generateAsteroids(getSeccion(),getSeccion());
        //Tomar de la lista de asteroides el asteroide que se acaba de crear
        // y colocarlo en la matriz, ademas se marca la futura posicion del
        // asteroide en esta
        x++;
    }


    while ( !jugador.finish(destino.second , destino.first) )
    {

        //MOVIMIENTO NAVE PRINCIPAL
        Pair pos = make_pair(jugador.Yact,jugador.Xact);
        Pair resultado = aStarSearch(grid,pos,destino);
        jugador.dx = resultado.second;
        jugador.dy = resultado.first;

        cout<<"Moverse a Fila: "<< jugador.dy << " Moverse a Columna: " << jugador.dx << endl;
        cout<<"Aqui va la funcion para "<< "mover la nave"<<endl;

        jugador.Xact = jugador.dx;
        jugador.Yact = jugador.dy;


        //Desbloquear barrera de naves enemigas
        cout<<"Aqui va la funcion para "<< "quitar los 'muros' alrededor de los enemigos"<<endl;

        //MOVIMIENTO ASTEROIDES
        moveAsteroids();
        cout<<"Aqui va la funcion para "<< "mover los asteroides"<<endl;


        //MOVIMIENTO NAVES ENEMIGAS
        cout<<"Aqui va la funcion para "<< "mover las naves enemigas"<<endl;

        //Bloquear barrera de naves enemigas
        cout<<"Aqui va la funcion para "<< "agregar los 'muros' alrededor de los enemigos"<<endl;

        cout<<""<<endl;
    }


    return(0);
}