#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream inp("Inputs/INPMONOSEQ.txt");
ofstream out("Outputs/OUTMONOSEQ.txt");

int n;

int main() 
{
    if (inp and out) 
    {
        inp >> n;
        vector<int> a(n);

        for (int i = 0; i < n; ++i) 
        {
            inp >> a[i];
        }

        // Tableau pour stocker la longueur de la sous-séquence monotone à chaque index
        vector<int> lisLength(n, 1);

        // Tableau pour stocker l'index précédent de la sous-séquence monotone à chaque index
        vector<int> previousIndex(n, -1);

        // Recherche de la sous-séquence monotone la plus longue
        for (int i = 1; i < n; ++i) 
        {
            for (int j = 0; j < i; ++j) 
            {
                if (a[i] > a[j] && lisLength[i] < lisLength[j] + 1) 
                {
                    lisLength[i] = lisLength[j] + 1;
                    previousIndex[i] = j;
                }
            }
        }

        // Trouver l'index de l'élément avec la longueur maximale
        int maxLengthIndex = 0;
        for (int i = 1; i < n; ++i) 
        {
            if (lisLength[i] > lisLength[maxLengthIndex]) {
                maxLengthIndex = i;
            }
        }

        // Afficher la longueur de la sous-séquence trouvée
        out << lisLength[maxLengthIndex] << endl;

        // Afficher la sous-séquence trouvée et l'index des éléments sélectionnés
        vector<int> result;
        int currentIndex = maxLengthIndex;
        while (currentIndex != -1) 
        {
            result.push_back(currentIndex);
            currentIndex = previousIndex[currentIndex];
        }

        // Afficher les résultats dans l'ordre inverse
        for (int i = result.size() - 1; i >= 0; --i) 
        {
            out << "a[" << result[i] + 1 << "] = " << a[result[i]] << endl;
        }
    } 
    else 
    {
        cout << "Can't access files\n";
    }

    inp.close();
    out.close();

    return 0;
}
