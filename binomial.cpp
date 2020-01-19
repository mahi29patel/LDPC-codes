#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<time.h>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

int main()
{
	ofstream myFile;
	myFile.open("binomialdistribution.csv");
	int zz;
	int N=49;
	long long int z,counter=0,arr[N]={0};
	srand(time(NULL));
	z=rand();
	for(int i=0;i<1000;i++)
	{
		counter=0;
		for(int j=0;j<N;j++)
		{
			zz=rand();
			if(zz<z)
			{
				counter++;
			}
		}
		arr[counter]++;
	}
	cout<<(float)z/RAND_MAX;
	for(int i=0;i<N;i++)
	{
		myFile << i << "," << arr[i]<<endl;
	}
}

