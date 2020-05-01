#include <iostream>
#include <omp.h>
#include <ctime>

using namespace std;
/*
	Program to generate Product of Two matrices of dimensions (m*n) and(n*p)
	The program can be run with the following commands:
	(On Linux Machine) $ g++ -fopenmp mul.cpp -o mul
					   $ export OMP_NUM_THREADS=(?)
					   $ ./mul
					   
	(?)==> Any arbitrary number

*/

int main()
{

	int a[100][100];
	int b[100][100];
	int c[100][100];


	cout<<"Enter dimensions of Matrix A: ";
	int r1, c1;
	cin>>r1>>c1;


	cout<<"Enter dimensions of Matrix B: ";
	int r2, c2;
	cin>>r2>>c2;

	while(c1!=r2)
	{
		cout<<"Error! Dimension of A and B don't match"<<endl;
		cout<<"Enter dimensions of Matrix A: ";
		cin>>r1>>c1;
	
		cout<<"Enter dimensions of Matrix B: ";
		cin>>r2>>c2;
	}


	int thread_num;
	double time;



	thread_num = omp_get_max_threads();
	cout<<"The number of processors available = "<< omp_get_num_procs()<<endl;
	cout<<"The number of threads available = "<<thread_num<<endl;


	cout<<"Enter values for A"<<endl;
	for(int i=0; i<r1; i++)
	{
		for(int j=0; j<c1; j++)
		{
			cin>>a[i][j];
		}
	}
	


	cout<<"Enter values for B"<<endl;
	for(int i=0; i<r2; i++)
	{
		for(int j=0; j<c2; j++)
		{
			cin>>b[i][j];
		}
	}

	time = omp_get_wtime();

	#pragma omp  parallel for shared(a, b, c)
	

	for(int i=0; i<r1; i++)
	{
		for(int j=0; j<c2; j++)
		{
			c[i][j]=0.0;
			for(int k=0; k<c1; k++)
			{
				c[i][j] = c[i][j] + a[i][k]*b[k][j];
			}
		}
	}

	time = omp_get_wtime() - time;
	cout<<"Elapsed seconds = "<<time<<endl;

	cout<<"Product of A & B"<<endl;

	for(int i=0; i<r1; i++)
	{
		for(int j=0; j<c2; j++)
		{
			cout<<c[i][j]<<" ";

		}
		cout<<endl;
	}


	return 0;
}

