/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
//CT111 20180135 to 045
//Generator Matrix and Parity Check Matrix

#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<time.h>
#include<bits/stdc++.h>
#include<fstream>
#include"Encoder.h"
#include"Decoder.h"
using namespace std;


int main()
{
int k=0,n,y,a,b,z,s,x1,kkk,suceess	;
float te,x,prob,suceess_prob;
ofstream Data;
srand(time(NULL));
srand(time(NULL));
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

DigitalCommunication message(n,k);
message.generatorMatrix(y);
message.parityCheck(y);

message.printGen();
message.printPar();
message.bec();
Decoder abc;
ofstream myFile;
myFile.open("SuccessData(bsc).csv");
for(int i=0;i<10;i++){
	message.generateProbability();
	suceess=0;
	for(int i=0;i<100;i++){
			message.msgCode();
			message.bsc();

			abc.NewDecoder(message);
			abc.Tanner(message);
			//abc.PrintTan();
			if(abc.decz(message,1)==0){
				cout<<"message cannot be decoded"<<endl;
			}
			else{
					cout<<"Decoded message :";
				for(kkk=0;kkk<abc.n;kkk++)

				{

					cout<<message.flipped[kkk]<<" ";
				}
				suceess++;
			}

}
cout<<"suceess : " <<suceess<<endl;
suceess_prob = (float)suceess/100;


myFile << message.prob << "," << suceess_prob<<endl;
}
}
