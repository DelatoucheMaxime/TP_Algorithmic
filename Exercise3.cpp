#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

ifstream inp("Inputs/INPDIVSEQ.txt");
ofstream out("Outputs/OUTDIVSEQ.txt");

int n;
int k;
int somme = 0;

int main() 
{
    if (inp and out) 
    {
        // We get the length of the list and the divider required
        inp >> n;
        inp >> k;

        //We create a vector to stock the values
        vector<int> val(n,-1);
        for(int i=0; i<n; i++)
        {
            inp >> val[i];
        }

        //Carry the historic of lengths
        vector<vector<int>> lenTab(n, vector<int>(k));
        //Carry the maximum length for a given modulo result
        vector<int> lenList(k);
        //Temporary copy of lenList
        vector<int> lenList2(k);

        //Initialisation of the vectors.
        for(int i=0; i<k; i++)
        {
            for(int j=0; j<n; j++)
            {
                    lenTab[j][i] = 0;
            }
            lenList[i] = 0;
            lenList2[i] = 0;
        }


        //Loop to complete the lenTab properly an record the lists of maximum length for every modulo results to k.
        for(int i=0; i<n; i++)
        {
            //Case i == 0 to initiate the calcul
            if(i==0)
            {
                lenTab[i][val[i]%k]= 1; 
                lenList[(val[i]%k)]++;
                lenList2[(val[i]%k)]++;
            }
            else
            {
                //Checking for every modulo results if the new value ioncreases the chain.
                for(int j=0; j<k; j++)
                {
                    if((lenList[j]>0) && (lenList[(j+val[i])%k] < lenList[j]+1))
                    {
                        lenList2[(j+val[i])%k]=lenList[j]+1;
                        lenTab[i][(j+val[i])%k] = lenList2[(j+val[i])%k];
                    }
                }

                //Copy results to lenList.
                for(int j=0; j<k; j++)
                {
                    lenList[j] = lenList2[j];
                }
            }

        }

        //Retrieving part (decreasing from the bottom of the list)
        //Getting the maximum length for a sum that remain a multiple of k.
        int length = lenList[0];
        
        //initializing the indexes.
        int i = n-1;
        int j = 0;

        //Adding the length to the output file.
        out << length << endl;

        //Loop to retrieve the values in the chain and to add them to the output file.
        while(length > 0 && i>=0)
        {
            while(lenTab[i][j] != length)
            {
                i--;
            }
            somme += val[i];
            j = (5+j-val[i]%k)%k;
            length--;
            out << "a[" << i << "] = " << val[i] << endl;
        }

        //Adding the value of the sum to the output file.
        out << "Sum = " << somme << endl;
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
