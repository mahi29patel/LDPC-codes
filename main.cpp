/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
//CT111 201801035 to 045
//Generator Matrix and Parity Check Matrix

#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<time.h>
#include<bits/stdc++.h>
#include<fstream>
#include"Encod.h"
#include"Decod.h"
using namespace std;


int main()
{
int k=0,n=0,y,a,b,z,s,x1,kkk,suceess,Nsim=10000,Nx=100;
int choice1,choice2;
cout<<"enter the code to be executed:\n 0-Product Code \n 1-LDPC Code"<<endl;
cin>>choice1;
float te,x,p=0,suceess_prob,div=1.0/Nx;
ofstream Data;
srand(time(NULL));
srand(time(NULL));
if(choice1==0)
{
cout<<"Please input the value for k:";
ss1:
cin>>k;
te=sqrt(k);
x=(int)te;
y=(int)x;
if(x*x!=k)
{
cout<<"The value for k is not a perfect square. Enter again:";
goto ss1;
}
n=k+2*sqrt(k)+1;
cout<<"The value of n is "<<n<<" and the value of k is "<<k<<"."<<endl;
}

DigitalCommunication message(n,k,choice1);
if(choice1==0)
{

message.generatorMatrix(y);
message.parityCheck(y);

message.printGen();
message.printPar();
}
cout<<"Enter the channel\n 0-Binary Erasure Channel \n 1-Binary Symmertric Channel"<<endl;
cin>>choice2;
//message.bec();
Decoder abc(message);
ofstream myFile;
if(choice2==1)
{
	myFile.open("SuccessData(bsc).csv");
}
else
{
	myFile.open("SuccessData(bec).csv");
}
for(int i=0;i<=Nx;i++){
	message.generateProbability((double)p);
	suceess=0;
	p=p+div;
	for(int i=0;i<Nsim;i++){
			message.msgCode(choice1);
			if(choice2==1)message.bsc();
			else message.bec();

			//abc.NewDecoder(message);
			abc.Tanner(message);
			//abc.PrintTan();
			if(abc.decz(message,choice2)==0){
//temp				cout<<"message cannot be decoded"<<endl;
			}
			else{
//temp					cout<<"Decoded message :";
				for(kkk=0;kkk<abc.n;kkk++)

				{

//temp					if(choice2==1)cout<<message.flipped[kkk]<<" ";
//temp					else cout<<message.erased[kkk]<<" ";
				}
				suceess++;
			}

}
cout<<"suceess : " <<suceess<<endl;
suceess_prob = (float)suceess/Nsim;


myFile << message.prob << "," << suceess_prob<<endl;
}
}
