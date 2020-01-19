#include<iostream>
#include"reader.h"
using namespace std;
int main()
{
	char filename[100];
	cout<<"enter filename: "<<endl;
	cin>>filename;
	Reader(filename);
	cout<<filename<<" is "<<row<<" X "<<col<<"matrix"<<endl;
	cout<<Hmatrix[23][1]<<" should be one ..."<<endl;
}
