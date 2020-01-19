#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<time.h>
#include<bits/stdc++.h>
#include<fstream>
#include"Encod.h"
#include"Decodd.h"
using namespace std;
int main()
{
int k=0,n,y,a,b,z,s,x1,kkk,suceess,Nsim=10000,Nx=50;
float te,x,p=0,suceess_prob,div=1.0/Nx;
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
//message.printGen();
//cout<<"mahi"<<endl;
//message.printPar();
/*message.bec();
Decoder abc;
ofstream myFile;
myFile.open("SuccessData(bsc).csv");
for(int i=0;i<Nx;i++){
	message.generateProbability((double)p);
	suceess=0;
	p=p+div;
	for(int i=0;i<Nsim;i++){
			message.msgCode(1);
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
suceess_prob = (float)suceess/Nsim;


myFile << message.prob << "," << suceess_prob<<endl;
}*/
DigitalCommunication message(n,k,1);
message.generateProbability((double)0.65);
message.msgCode(1);
message.bec();
Decoder abc(message);
abc.Tanner(message);
if(abc.decz(message,0)==0){
				cout<<"message cannot be decoded"<<endl;
			}
			else{
					cout<<"Decoded message :";
				for(kkk=0;kkk<abc.n;kkk++)

				{

					cout<<message.erased[kkk]<<" ";
				}
				//suceess++;
			}
}
