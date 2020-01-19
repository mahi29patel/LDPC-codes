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
int k=0,n=0,y,a,b,z,s,x1,kkk,suceess,Nsim=100,Nx=40,choice2,choice1;
float te,x,p=0,suceess_prob,div=1.0/Nx;
ofstream Data;
srand(time(NULL));
srand(time(NULL));
cout<<"Enter the type of code to be executed \n (0:to execute product code and 1: to execute LDPC Code)"<<endl;
cin>>choice1;
DigitalCommunication message(n,k,choice1);
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
cout<<"The value of n is "<<n<<" and the value of k is "<<k<<" . "<<endl;


}



message.generateProbability();
message.msgCode(choice1);
Decoder abc;
abc.NewDecoder(message);
abc.Tanner(message);
cout<<"Enter from which channel the code is to be passed\n (0:Binary Erasure Channel and 1:Binary Symmetric channel)"<<endl;
cin>>choice2;

ofstream myFile;
if(choice2==0)
{
myFile.open("SuccessData(bec).csv");
}
else
{ 
 myFile.open("SuccessData(bsc).csv");
}
for(int i=0;i<Nx;i++){
	message.generateProbability((double)p);
	suceess=0;
	p=p+div;
	for(int i=0;i<Nsim;i++){
			message.msgCode(choice1);
			if(choice2==0)
			{ 
			    message.bec();
			  
               
			}
			else
			{ 
			    message.bsc();   
			}
                       abc.NewDecoder(message);
			abc.Tanner(message);
			//abc.PrintTan();
			if(abc.decz(message,choice2)==0)
			{
				cout<<"message cannot be decoded"<<endl;
			}
			else{
					cout<<"Decoded message :";
					if(choice2==0)
					{
			        	for(kkk=0;kkk<abc.n;kkk++)
			        	{
			        	    cout<<message.erased[kkk]<<" ";
			          	}
					}
					else
					{
					    for(kkk=0;kkk<abc.n;kkk++)
			        	{
			        	    cout<<message.flipped[kkk]<<" ";
			          	}
					}
				suceess++;
		     	}
	}
	
cout<<"suceess : " <<suceess<<endl;
suceess_prob = (float)suceess/Nsim;


myFile<<message.prob<<","<<suceess_prob<<endl;
}
}
