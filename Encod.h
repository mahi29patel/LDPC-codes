#include<iostream>
#include"reader.h"
using namespace std;

class DigitalCommunication
{
public:
	int *msg,*code,k,n,**gen,**par,*erased,*flipped;
	double prob,zz;
	char filename[100]={"hmatrix.txt"};
	DigitalCommunication(int totalBits,int infoBits,int choice){
	    
	    gen = new int*[infoBits];
    	for(int i = 0; i < infoBits; ++i)
           gen[i] = new int[totalBits];

		if(choice==0)
		{
		 par = new int*[totalBits-infoBits];
		for(int i = 0; i < totalBits-infoBits; ++i)
    		par[i] = new int[totalBits];
		}
		if(choice==1)
		{
		Reader(filename);
		totalBits=col;
		infoBits=col-row;
		par = new int*[totalBits-infoBits];
		for(int i = 0; i < totalBits-infoBits; ++i)
    		par[i] = new int[totalBits];
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				par[i][j]=Hmatrix[i][j];
			}
		}
		}
		msg = new int[infoBits];
		code = new int[totalBits];
		flipped = new int[totalBits];
		erased = new int[totalBits];
		k = infoBits;
		n = totalBits;
		zz=rand();

	}

  void generateProbability(){
    zz=rand();
    zz=rand();
    prob=zz/RAND_MAX;
    cout<<"\nthe probability is "<<prob<<endl;
  }
  void generateProbability(double p){
    zz=rand();
    zz=rand();
    zz=RAND_MAX*p;
    prob=p;
    cout<<"\nthe probability is "<<prob<<endl;
  }

	void generatorMatrix(int y){

		for(int i=0;i<k;i++)
		{
			for(int j=0;j<k;j++)
			{
				if(j==i)
		        {gen[i][j]=1;}
				else
				{gen[i][j]=0;}
			}
		}
		for(int i=0;i<k;i++)
		{
			for(int j=k;j<n;j++)
			{
				if((j-k)==(i/y))
				{gen[i][j]=1;}
				else if((j-k)==(y+i%y))
				{gen[i][j]=1;}
				else if(j==n-1)
				{gen[i][j]=1;}
				else
				{gen[i][j]=0;}
			}
		}


	}

	void parityCheck (int y){
        for(int i=0;i<k;i++)
		{
			for(int j=k;j<n;j++)
			{
				if((j-k)==(i/y))
				{gen[i][j]=1;par[j-k][i]=1;}
				else if((j-k)==(y+i%y))
				{gen[i][j]=1;par[j-k][i]=1;}
				else if(j==n-1)
				{gen[i][j]=1;par[j-k][i]=1;}
				else
				{gen[i][j]=0;par[j-k][i]=0;}
			}
		}
		for(int i=0;i<n-k;i++)
		{
			for(int j=k;j<n;j++)
			{
				if((j-k)==i)
						{par[i][j]=1;}
				else
				{par[i][j]=0;}
			}
		}
        for(int i=0;i<n;i++)
        {
            if(i>=sqrt(n)*(sqrt(n)-1))par[n-k-1][i]=1;
            else par[n-k-1][i]=0;
        }

	}

	void printGen(){
		cout<<"The generator matrix"<<endl;
		for(int i=0;i<k;i++)
		{
			for(int j=0;j<n;j++)
			{
				cout<<gen[i][j]<<" ";
			}
			cout<<"\n";
		}

	}

	void printPar(){
		cout<<"\nThe parity check matrix"<<endl;
		for(int i=0;i<n-k;i++)
		{
			for(int j=0;j<n;j++)
			{
				cout<<par[i][j]<<" ";
			}
			cout<<"\n";
		}


	}

	void msgCode(int choice)
	{
	if(choice==0)
	{
	int z,s;
	for(int i=0;i<k;i++)
	{
		z=rand()%100+1;
		if(z>=50)msg[i]=1;
		else msg[i]=0;
	}
	generatorMatrix((int)sqrt(k));
	//cout<<"\n"<<"The randomly message is :";
	//display(msg,k);
	cout<<endl;
	for(int i=0;i<n;i++)
	{
	    s=0;
	    for(int j=0;j<k;j++)
	    {
	        s=(s+msg[j]*gen[j][i])%2;
	    }
	    code[i]=s;
	}

	//cout<<"\n"<<"The code is :";
	//display(code,n);
	cout<<endl;
	}
	else 
	{
		for(int i=0;i<n;i++)
		{
			code[i]=0;
		}	
	}
	}

void bsc(){
	long int z;
	for(int i=0;i<n;i++)
	{
	    z=rand();
	    if(z<=zz)flipped[i]=abs(code[i]-1);
	    else flipped[i]=code[i];
	}
//	cout<<"\n\n flipped bits:";
//	display(flipped,n);
}

void bec(){
	long int z;

	for(int i=0;i<n;i++)
	{
	    z=rand();
	    if(z<=zz)erased[i]=-1;
	    else erased[i]=code[i];
	}
//	cout<<"\n\n erased bits :";
//	display(erased,n);
 // cout<<endl;

}


void display(int array[],int n){
		for(int i =0;i<n;i++){
				if(array[i]!=-1)cout<<array[i]<<" ";
				else cout<<"? ";
			}

}

};
