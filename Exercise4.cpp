#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

ifstream inp("Inputs/INPARBGRAPH.txt");
ofstream out("Outputs/OUTARBGRAPH.txt");

void AdjMatrixSolution(void);
void AdjListSolution(void);

int nb_vertices = 0;
int nb_links = 0;

int main() 
{
    if (inp and out) 
    {
        AdjMatrixSolution();
        //AdjListSolution();
    } 
    //Error message in case the file didn't open or doesn't exist
    else 
    {
        cout << "Can't access files\n";
    }

    //Closing the access to the files
    inp.close();
    out.close();

    return 0;
}

void AdjMatrixSolution()
{
    //Getting the number of vertices and links from the txt file.
    inp >> nb_vertices >> nb_links;

    //Initalizing the adjacent matrix.
    vector<vector<int>> AdjMatrix(nb_vertices, vector<int>(nb_vertices));
    for(int i=0; i<nb_vertices; i++)
    {
        for(int j=0; j<nb_vertices; j++){AdjMatrix[i][j] = 0;}
    }


    //Placing ones where there is links between vertices.
    int row = 0;
    int col = 0;
    for(int i=0; i<nb_links; i++)
    {
        inp >> row >> col;
        AdjMatrix[row-1][col-1] = 1;
        AdjMatrix[col-1][row-1] = 1;
    }

    //Initializing the number of vertices still needing links
    int openVertices = nb_vertices-1;

    //These 2 lines are useless as path is used nowhere, but if we delete it, we get a segmentation fault systematically. So here they are.
    vector<int> path;
    path.push_back(1);
    
    //Initializing the inex of the row, the column and whether to go forward or backward.
    row = 0; col = 0;
    int temp = 0;
    int forward = 1;

    //Creating links as there are vertices that still possesses available links.
    while(openVertices > 0)
    {
        //Checking if we reach a linking point or exceeding the number of vertices possessed.
        while((AdjMatrix[row][col] != 1) && (col <= nb_vertices || 0 < col)){col = col+forward;}

        //If we reach the border right of the matrix, we start to go backward, considering every links done for this vertice.
        if(col > nb_vertices)
        {
            col--;
            forward = -1;
            for(int i=0; i<nb_vertices; i++)
            {
                AdjMatrix[i][row] = 0;
            }
        }
        //Else we reach a linking point, if we are going forward: it is a new link, if we are going backward: it is the way back to the previous vertice.
        else
        {
            //Going forward => link kept and add to the output txt file.
            if(forward == 1){out << row+1 << " " << col+1 << endl;}

            //Now heading back to the line of the vertice we want to create link with other vertices.
            AdjMatrix[row][col] = 0;
            temp = row+1;
            row = col;
            col = temp;

            //Going backward => we are going back to th previous vertice, it is needed to go forward now and to lock the vertice we just left.
            if(forward == -1)
            {
                forward = 1;
                openVertices--;

            }
        }
    }
}
