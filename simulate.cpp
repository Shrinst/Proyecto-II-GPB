#include<bits/stdc++.h>

using namespace std;


//PATHFINDING


//Shortcut para int, int pair type
typedef pair<int, int> Pair;

//Shortcut para pair<int, pair<int, int>> type
typedef pair<double, pair<int, int>> pPair;

// La estructura que guarda los parametros necesitados
struct cell
{
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};


/*
 * @brief Revisa que el punto de columna y fila sean validos en la matriz
 * @param row la fila a revisar
 * @param col la columna a revisar
 * @return True si la fila y columna se encuentra en el rango de la matriz
 */
bool isValid(int row, int col)
{
    return (row >= 0) && (row < 10) &&
           (col >= 0) && (col < 12);
}

/*
 * @brief Revisa si una celda esta disponible o no
 * @param grid la matriz a revisar
 * @param row la fila a revisar
 * @param col la columna a revisar
 * @return True la celda no esta bloqueada
 */
bool isUnBlocked(int grid[][12], int row, int col)
{
    if (grid[row][col] == 1)
        return (true);
    else
        return (false);
}

/*
bool isSafe(int grid[][12], int row, int col)
{
    if(row == 0)
    {
        if(col == 11 || col == 0)
        {
            if(col == 0)
            {
                if(grid[row+1][col] == 1 && grid[row+1][col+1] == 1 && grid[row][col+1] == 1)
                {
                    return true;
                }
                return false;
            } else
            {
                if(grid[row+1][col] == 1 && grid[row+1][col-1] == 1 && grid[row][col-1] == 1)
                {
                    return true;
                }
                return false;
            }

        }
        else if (grid[row+1][col]== 1 && grid[row+1][col-1]== 1 && grid[row+1][col+1]== 1 && grid[row][col-1] ==1 && grid[row][col+1] == 1)
        {
            return true;
        }
        return false;

    }else if(row == 9)
    {
        if(col == 11 || col == 0)
        {
            if(col == 0)
            {
                if(grid[row-1][col] == 1 && grid[row-1][col+1] == 1 && grid[row][col+1] == 1)
                {
                    return true;
                }
                return false;
            } else
            {
                if(grid[row-1][col] == 1 && grid[row-1][col-1] == 1 && grid[row][col-1] == 1)
                {
                    return true;
                }
                return false;
            }

        }
        else if (grid[row-1][col]== 1 && grid[row-1][col-1]== 1 && grid[row-1][col+1]== 1 && grid[row][col-1] ==1 && grid[row][col+1] == 1)
        {
            return true;
        }
        return false;

    } else if (col==0)
    {
        if(grid[row-1][col]==1 && grid[row-1][col]==1 && grid[row][col+1]==1 && grid[row+1][col+1]==1 && grid[row-1][col+1]==1)
        {
            return true;
        } else
        {

        }
    } else if (col==11)
    {

    } else if (grid[row+1][col]==1 && grid[row][col+1]==1)
    {
        return true;
    } else
    {
        return false;
    }
}
*/

/*
 * @brief Funcion para verificar si se ha llegado al punto de destino o no
 * @param row la fila en la que se encuentra
 * @param col la columna en la que se encuentra
 * @param dest el par(fila,columna) a donde se desea llegar
 * @return True se encuentra en el destino
 */
bool isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

/*
 * @brief la funcion para encontrar los H heuristicos
 * @param row cantidad de filas
 * @param col cantidad de columnas
 * @param dest punto de destino
 * @return double con el valor de H
 */
double calculateHValue(int row, int col, Pair dest)
{
    return ((double)sqrt ((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
}

/*
 * @brief la funcion para encontrar el camino del origen al destino
 * @param celda de la matriz con los valores correspondientes
 * @param dest un Pair con los puntos de destino
 * @return un pair con (fila, columna) a la cual debe dirigirse
 */
Pair tracePath(cell cellDetails[][12], Pair dest)
{
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col ))
    {
        Path.push (make_pair (row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push (make_pair (row, col));
    int origenFound = 0;
    while (!Path.empty() && origenFound!=1)
    {
        pair<int,int> p = static_cast<pair<int, int> &&>(Path.top());
        Path.pop();
        origenFound++;
    }

    pair<int,int> p = static_cast<pair<int, int> &&>(Path.top());
    Path.pop();
    return p;
}

/*
 * @brief escuentra el camino mas corto el una matriz entre 2 puntos
 * @param grid la matriz del mapa a trabajar
 * @param src punto de inicio
 * @param dest punto final
 * @return un pair con (fila, columna) a la cual debe dirigirse
 */
Pair aStarSearch(int grid[][12], Pair src, Pair dest)
{
    if (isValid (src.first, src.second) == false)
    {
        cout<<"Origen invalido"<<endl;
        return make_pair(-1,-1);
    }

    if (isValid (dest.first, dest.second) == false)
    {
        cout<<"Destino invalido"<<endl;
        return make_pair(-1,-1);
    }

    if (isUnBlocked(grid, src.first, src.second) == false ||
        isUnBlocked(grid, dest.first, dest.second) == false)
    {
        cout<<"Origen o Destino estan bloqueados"<<endl;
        return make_pair(-1,-1);
    }

    if (isDestination(src.first, src.second, dest) == true)
    {
        cout<<"Ya se encuentra en el destino"<<endl;
        return make_pair(-1,-1);
    }

    bool closedList[10][12];
    memset(closedList, false, sizeof (closedList));

    cell cellDetails[10][12];

    int i, j;

    for (i=0; i<10; i++)
    {
        for (j=0; j<12; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    set<pPair> openList;

    openList.insert(make_pair (0.0, make_pair (i, j)));

    bool foundDest = false;

    while (!openList.empty())
    {
        pPair p = *openList.begin();

        openList.erase(openList.begin());

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;


        double gNew, hNew, fNew;


        if (isValid(i-1, j) == true)
        {

            if (isDestination(i-1, j, dest) == true)
            {
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;

                return tracePath (cellDetails, dest);

            }
            else if (closedList[i-1][j] == false && isUnBlocked(grid, i-1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i-1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i-1][j].f == FLT_MAX ||
                    cellDetails[i-1][j].f > fNew)
                {
                    openList.insert( make_pair(fNew, make_pair(i-1, j)));

                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        // Only process this cell if this is a valid one
        if (isValid(i+1, j) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i+1, j, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;

                return tracePath(cellDetails, dest);

            }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
            else if (closedList[i+1][j] == false &&
                     isUnBlocked(grid, i+1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i+1][j].f == FLT_MAX ||
                    cellDetails[i+1][j].f > fNew)
                {
                    openList.insert( make_pair (fNew, make_pair (i+1, j)));
                    // Update the details of this cell
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }

        if (isValid (i, j+1) == true)
        {

            if (isDestination(i, j+1, dest) == true)
            {

                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                return tracePath(cellDetails, dest);
            }

            else if (closedList[i][j+1] == false &&
                     isUnBlocked (grid, i, j+1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i, j+1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j+1].f == FLT_MAX || cellDetails[i][j+1].f > fNew)
                {
                    openList.insert( make_pair(fNew, make_pair (i, j+1)));

                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }

        if (isValid(i, j-1) == true)
        {

            if (isDestination(i, j-1, dest) == true)
            {

                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                return tracePath(cellDetails, dest);
            }

            else if (closedList[i][j-1] == false && isUnBlocked(grid, i, j-1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j-1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j-1].f == FLT_MAX ||
                    cellDetails[i][j-1].f > fNew)
                {
                    openList.insert( make_pair (fNew, make_pair (i, j-1)));

                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }

        if (isValid(i-1, j+1) == true)
        {

            if (isDestination(i-1, j+1, dest) == true)
            {
                cellDetails[i-1][j+1].parent_i = i;
                cellDetails[i-1][j+1].parent_j = j;
                return tracePath (cellDetails, dest);
            }

            else if (closedList[i-1][j+1] == false &&
                     isUnBlocked(grid, i-1, j+1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i-1, j+1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i-1][j+1].f == FLT_MAX ||
                    cellDetails[i-1][j+1].f > fNew)
                {
                    openList.insert( make_pair (fNew, make_pair(i-1, j+1)));

                    cellDetails[i-1][j+1].f = fNew;
                    cellDetails[i-1][j+1].g = gNew;
                    cellDetails[i-1][j+1].h = hNew;
                    cellDetails[i-1][j+1].parent_i = i;
                    cellDetails[i-1][j+1].parent_j = j;
                }
            }
        }

        if (isValid (i-1, j-1) == true)
        {

            if (isDestination (i-1, j-1, dest) == true)
            {

                cellDetails[i-1][j-1].parent_i = i;
                cellDetails[i-1][j-1].parent_j = j;
                return tracePath (cellDetails, dest);
            }

            else if (closedList[i-1][j-1] == false && isUnBlocked(grid, i-1, j-1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i-1, j-1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i-1][j-1].f == FLT_MAX ||
                    cellDetails[i-1][j-1].f > fNew)
                {
                    openList.insert( make_pair (fNew, make_pair (i-1, j-1)));
                    cellDetails[i-1][j-1].f = fNew;
                    cellDetails[i-1][j-1].g = gNew;
                    cellDetails[i-1][j-1].h = hNew;
                    cellDetails[i-1][j-1].parent_i = i;
                    cellDetails[i-1][j-1].parent_j = j;
                }
            }
        }

        if (isValid(i+1, j+1) == true)
        {

            if (isDestination(i+1, j+1, dest) == true)
            {
                cellDetails[i+1][j+1].parent_i = i;
                cellDetails[i+1][j+1].parent_j = j;
                return tracePath (cellDetails, dest);
            }

            else if (closedList[i+1][j+1] == false &&
                     isUnBlocked(grid, i+1, j+1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i+1, j+1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i+1][j+1].f == FLT_MAX ||
                    cellDetails[i+1][j+1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                                              make_pair (i+1, j+1)));

                    cellDetails[i+1][j+1].f = fNew;
                    cellDetails[i+1][j+1].g = gNew;
                    cellDetails[i+1][j+1].h = hNew;
                    cellDetails[i+1][j+1].parent_i = i;
                    cellDetails[i+1][j+1].parent_j = j;
                }
            }
        }

        if (isValid (i+1, j-1) == true)
        {

            if (isDestination(i+1, j-1, dest) == true)
            {
                cellDetails[i+1][j-1].parent_i = i;
                cellDetails[i+1][j-1].parent_j = j;
                return tracePath(cellDetails, dest);

            }

            else if (closedList[i+1][j-1] == false &&
                     isUnBlocked(grid, i+1, j-1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i+1, j-1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i+1][j-1].f == FLT_MAX ||
                    cellDetails[i+1][j-1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i+1, j-1)));

                    cellDetails[i+1][j-1].f = fNew;
                    cellDetails[i+1][j-1].g = gNew;
                    cellDetails[i+1][j-1].h = hNew;
                    cellDetails[i+1][j-1].parent_i = i;
                    cellDetails[i+1][j-1].parent_j = j;
                }
            }
        }
    }

    if (foundDest == false)
        cout<<"No se puede llegar al objetivo"<<endl;
        return make_pair(-1,-1);

}
