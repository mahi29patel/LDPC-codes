#include <iostream>
#include<cstdio>
#include <cstdlib>
#include<fstream>
#include<string>

using namespace std;
int **Hmatrix,row,col;
void Reader(char filename[])
{
    long long int i;
    FILE *fptr1;
    char c;


    fptr1 = fopen(filename, "r");
    if (fptr1 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }
    fscanf (fptr1, "%d", &row);
    fscanf (fptr1, "%d", &col);
    Hmatrix = new int*[row];
    for(int i = 0; i < row; ++i) {
        Hmatrix[i] = new int[col];
    }
    long long int s=0;
    while (fscanf(fptr1,"%lld",&i)!=EOF && s<row*col)
    {
        int a = s/col;
        int b = s%col;
        Hmatrix[a][b]=i;
        fscanf (fptr1, "%c", &c);
        s++;
    }
    fclose (fptr1);
}

