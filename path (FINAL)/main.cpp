#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Myrect.h"
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
/*void generateAsteroids(int SaleDeX,int AoD){
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
*/
void moveAsteroids(){
    //Se mueve cada asteroide de la lista de asteroides y se analiza si choca o no
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
}/*
vector<int> getpath(int num){
    if(num == 0){
        return jugador.path;
    }else{
        if(num == 1){
            enemylist.at(0).path;
        }else{
            enemylist.at(1).path;
        }
    }
}*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    int numAsteroides = 8;

        // 1 = Celda Vacia
        // 8 = Asteroide
        // 9 = Futuro Asteroide
        // 5 = Nave enemiga y su barrera
        int grid[10][12]={  //[Fila][Columna]
                { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                { 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 8, 8 },
                { 1, 1, 1, 1, 1, 8, 8, 8, 1, 1, 1, 1 },
                { 1, 1, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1 },
                { 1, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1, 1 },
                { 1, 1, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                { 1, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 1 }
        };


        for(int i = 0;i < 2;i++){
            int x = rand()%2+1;
            player jugador;
            jugador.setposI(11,x*1);
            enemylist.push_back(jugador);
        }

        jugador.setposI(0,9);
        Pair destino = make_pair(5,11);
        srand(NULL);

        int x = 0;
        /*
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

            Pair destino1 = make_pair(jugador.dy,jugador.dx);

            jugador.path.push_back(selector(jugador.Xact,jugador.Yact,jugador.dx,jugador.dy));
            jugador.Xact = jugador.dx;
            jugador.Yact = jugador.dy;

            //Movimiento ENEMIGOS

            for(int i = 0; i < enemylist.size();i++){
                Pair pos1 = make_pair(enemylist.at(i).Yact, enemylist.at(i).Xact);
                Pair resultado1 = aStarSearch(grid,pos1,destino1);
                enemylist.at(i).dx = resultado1.second;
                enemylist.at(i).dy = resultado1.first;
                enemylist.at(i).path.push_back(selector(enemylist.at(i).Xact,enemylist.at(i).Yact,enemylist.at(i).dx,enemylist.at(i).dy));
                enemylist.at(i).Xact = enemylist.at(i).dx;
                enemylist.at(i).Yact = enemylist.at(i).dy;
            }/*
            for(int j = 0; j < jugador.path.size();j++){
                cout << jugador.path.at(j) << ", ";
            }cout << "" << endl;
            for(int i = 0; i < 2;i++){
                for(int j = 0; j < enemylist[i].path.size();j++){
                    cout << enemylist[i].path.at(j) << ", ";
                }cout << "" << endl;
            }
            //Desbloquear barrera de naves enemigas
            //cout<<"Aqui va la funcion para "<< "quitar los 'muros' alrededor de los enemigos"<<endl;

            //MOVIMIENTO ASTEROIDES
            //moveAsteroids();
            //cout<<"Aqui va la funcion para "<< "mover los asteroides"<<endl;

            //Bloquear barrera de naves enemigas
            //cout<<"Aqui va la funcion para "<< "agregar los 'muros' alrededor de los enemigos"<<endl;

            //cout<<""<<endl;
        }
        return(0);
    */
    // create a scene
    QGraphicsScene * scene = new QGraphicsScene();

    // create an item to add to the scene
    MyRect * rect = new MyRect();
    rect->setRect(0,0,0,0); // change the rect from 0x0 (default) to 100x100 pixels

    // add the item to the scene
    scene->addItem(rect);

    // make rect focusable
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();

    // create a view to visualize the scene
    QGraphicsView * view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsPixmapItem *fondo = new QGraphicsPixmapItem;
    fondo->setPos(0,0);
    fondo->setPixmap(QPixmap(":/img/space.jpg"));
    scene->addItem(fondo);

    // show the view
    view->show();
    view->setFixedSize(600,500);
    scene->setSceneRect(0,0,600,500);
    return a.exec();
}
