#include<iostream>
#include<fstream>
using namespace std;

class Decoder
{
public:
int **tanner,**tannerval,**varcon,n,k,maxconvar,maxconcheck,*rdecoded,errorcount=0,nitr=0;
  Decoder(DigitalCommunication a){

		int i,j,s=0;
	    n=a.n;
	    k=a.k;
	    maxconvar=0;
	    maxconcheck=0;
	    for(i=0;i<n-k;i++)
        {
            s=0;
            for(j=0;j<n;j++)
            {
               if(a.par[i][j]==1)s++;
            }
            if(s>maxconcheck){maxconcheck=s;}
        }
        for(j=0;j<n;j++)
        {
            s=0;
            for(i=0;i<n-k;i++)
            {
               if(a.par[i][j]==1)s++;
            }
            if(s>maxconvar){maxconvar=s;}
        }

		tanner= new int*[n-k];
		for(i=0; i<n-k; ++i)
		tanner[i]= new int[(int)maxconcheck+1];

		varcon= new int*[maxconvar+1];
		for( i=0; i<maxconvar+1; ++i)
		varcon[i]= new int[n];

		tannerval= new int*[n-k];
		for( i=0; i<n-k; ++i)
		tannerval[i]= new int[(int)maxconcheck+1];


  };

  void NewDecoder(DigitalCommunication a)
	{
	  

		
	}


	void Tanner(DigitalCommunication a)
	{
		int i,j,kk;
		for(i=0;i<n-k;i++)
        {
            for(j=0;j<maxconcheck+1;j++)
                tanner[i][j]=-1;
                tannerval[i][j]=-2;
        }
        for(i=0;i<maxconvar+1;i++)
        {
            for(j=0;j<n;j++)
                varcon[i][j]=-1;
        }
        //check nodes with variable nodes
		for(i=0;i<n-k;i++)
		{
		    j=1;
			tanner[i][0]=i;
				for(kk=0;kk<n;kk++)
				{
					if(a.par[i][kk]==1){tanner[i][j]=kk;j++;}
				}
		}


		//variable nodes with check nodes
		for(j=0;j<n;j++)
        {
            i=1;
            varcon[0][j]=j;
                for(kk=0;kk<n-k;kk++)
				{
					if(a.par[kk][j]==1){varcon[i][j]=kk;i++;}
				}
        }

	}
	void PrintTan()
	{


		cout<<"Tanner:"<<endl;
		int i,j;
		for(i=0;i<n-k;i++)
		{
			for(j=0;j<maxconcheck+1;j++)
			{
				cout<<tanner[i][j]<<" ";
			}
			cout<<endl;
		}

		cout<<"VARCON:"<<endl;

		for(i=0;i<maxconvar+1;i++)
		{
			for(j=0;j<n;j++)
			{
				cout<<varcon[i][j]<<"\t";

			}
			cout<<endl;
		}
cout<<endl;

	}

	int calcxor(int row,int index)
	{
	    int s,j;
            s=0;

            for(j=1;j<maxconcheck+1;j++)
            {
                if(tannerval[row][j]==-2)break;
                if(index!=tanner[row][j])
                {
                        if(tannerval[row][j]==-1){return -1;}
                        s=(s+tannerval[row][j])%2;

                }
            }

		return s;
	}
	int Maj(int matrix[],int n)
	{
		int i,one=0,zero=0,eraz=0,pb;
		for(i=0;i<n;i++)
		{
			if(matrix[i]==1)one++;
			else if (matrix[i]==0)zero++;
		}
		if(one>zero)return 1;
		else if(one<zero)return 0;
		else if(one==zero && (one!=0 && zero!=0))
		{
			pb=rand();
			if(pb>RAND_MAX/2)return 1;
			else return 0;
		}
		else return -1;
	}
	int decz(DigitalCommunication a,int choice)
	{
		ofstream myFile;
		myFile.open("ErrorData(bec).csv");
		int i,j,kk,c,b,majority[1+maxconvar],s,rdecoded[n],passing[maxconvar+1][n],rreceived[n],check=0,tempm[1+maxconvar],check2=0,nerror=0;
		here:
		if(choice==0)
		{
		    for(i=0;i<n;i++)
		    {
		        rreceived[i]=a.erased[i];
		    }
		}
		else
		{
		    for(i=0;i<n;i++)
		    {
		        rreceived[i]=a.flipped[i];
		    }
		}
		for(i=0;i<maxconvar+1;i++)
		{
		    majority[i]=-1;
			for(j=0;j<n;j++)
			{
				passing[i][j]=-1;
			}
		}
		for(i=0;i<n-k;i++)
		{
			tanner[i][0]=i;
				for(j=1;j<maxconcheck+1;j++)
				{
					tannerval[i][j]=rreceived[tanner[i][j]];
				}
		}
		for(check=0;check<50 && check2<100;check++)
		{
		nitr++;
		int syn=0;
                for(int y=0;y<n;y++)
                {
                    if(rreceived[y]==-1)syn++;
                }
		errorcount=syn;
		myFile << nitr << "," << errorcount<<endl;
		for(i=0;i<n;i++)
		{
		
			s=0;
			for(j=1;j<maxconvar+1;j++)
			{
				if(varcon[j][i]==-1)break;
				majority[s]=calcxor(varcon[j][i],i);
				passing[s][i]=majority[s];
				s++;
			}
			majority[s]=rreceived[i];
			passing[s][i]=majority[s];
			rdecoded[i]=Maj(majority,1+s);
			if(choice==0)
            		{
		        for(c=0;c<n-k;c++)
		        {
		            tanner[c][0]=i;
		                for(b=1;b<maxconcheck+1;b++)
		                {
		                    tannerval[c][b]=rreceived[tanner[c][b]];
		                }
		        }
            		}
            		rreceived[i]=rdecoded[i];
		}




		if(choice==1)
			{
			  for(j=0;j<n;j++)
				{
				    int tempm[maxconvar];
					int kkk=0;
					for(int k=0;k<maxconvar+1;k++)
					{   if(k>=maxconvar-1)
					      {
					          tempm[kkk]=passing[k][j];
					      }
					     else
					{
					    if(varcon[k+1][j]!=k && varcon[k+1][j]!=-1)
						{
							tempm[kkk]=passing[k][j];
							kkk++;
						}
					}



					}
				for(int g=0;g<maxconvar+1;g++)
					    {
					      for(int h=0;h<n;h++)
					      {
						   tannerval[g][h]=Maj(tempm,kkk);

					      }

					    }
				}
			}
			if(choice==1)
            {
                int syn=0;
                for(int y=0;y<n-k;y++)
                {   s=0;
                    for(int yy=0;yy<n;yy++)
                    {
                        s=(a.par[y][yy]*rreceived[yy]+s)%2;

                    }

                    syn=s+syn;

                }
                if(syn==0)
                {
                    for(int y=0;y<n;y++)
                    {
                        a.flipped[y]=rreceived[y];
                    }
                    for(int y=0;y<n;y++)
                    {
                        if(a.flipped[y]!=a.code[y])
			{
				return 0;
			}
                    }
                    return 1;
                }
            }
			if(choice==0)
            {
                int syn=0;
                for(int y=0;y<n;y++)
                {
                    if(rreceived[y]==-1)syn++;
                }

                if(syn==0)
                {
		nitr++;
		int syn=0;
                for(int y=0;y<n;y++)
                {
                    if(rreceived[y]==-1)syn++;
                }
		errorcount=syn;
		myFile << nitr << "," << errorcount<<endl;
                    for(int y=0;y<n;y++)
                    {
                        a.erased[y]=rreceived[y];
                    }
                    return 1;
                }
		else if(syn==nerror)
		{
			return 0;
		}
		else nerror=syn;
            }
            if(check==49)
            {
                check2++;
                goto here;
            }

		}
		if(choice==0)
        {
            for(int y=0;y<n;y++)
            {
                a.erased[y]=rreceived[y];
            }
        }
        else
        {
            for(int y=0;y<n;y++)
            {
                a.flipped[y]=rreceived[y];
            }
        }
		return 0;
	}
};
