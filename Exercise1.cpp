#include <iostream>
#include "math.h"
using namespace std;
int in;
int i,out = 1;
int limite = 100; // Limite de passages en boucle pour les cas sans solutions.
string sortie = "1";

int foisDeux(int);
int foisDeux(int out) // Fonction multipliant par 2 et mettant à jour le string de sortie
{
    out *= 2;
    sortie += "*2";
    return out;
}
int foisTrois(int);
int foisTrois(int out) // Fonction divisant par 3 et mettant à jour le string de sortie
{
    out = floor(out/3);
    sortie += "/3";
    return out;
}
int main()
{
    cout << "Enter your number here:\n";
    cin >> in; // Entrée du user
    while((out!=in) and i<limite) // Boucle qui fini soit au bon résultat, soit à la limite
    {
        if(out<in)
        {
            out = foisDeux(out);
            //cout << to_string(out);
        }
        else
        out = foisTrois(out);
        i++;

    }
    if(i<limite) // Si le résultat est bon on renvoie au user le string à jour
    {cout << sortie+"="+to_string(in)<< endl;}
    else {cout << "Out of bounds\n";} // Sinon le calcul n'a pas été fait dans les limites
    return 0;
}