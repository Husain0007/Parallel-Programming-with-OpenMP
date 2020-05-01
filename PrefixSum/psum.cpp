#include <iostream>
#include <omp.h>
#include <ctime>

/*
	Program to generate a Prefix Sum from a given array of size "n"
	The program can be run with the following commands:
	(On Linux Machine) $ g++ -fopenmp psum.cpp -o psum
					   $ ./psum	
*/

using namespace std;

int power(int n, int p) // Exponentiation Function
{
	int i=1;
	while(p--)
	{
		i*=n;
	}
	return i;
}

int log(int n) // Base-2 Logarithmic Function
{
	int bits=0;

	while(n>>=1)
	{
		bits++;
	}
	return bits;
}

int main()
{

	cout<<"Input size of the array: ";
	int n;
	cin>>n;

	while(n<0)
	{
		cout<<"Size cannot be negative. Please provide input: ";
		cin>>n;
	}

	int depth = log(n);

	int new_n = (power(2,depth)==n)?n:power(2,depth+1);

	int* arr = new int[new_n];

	cout<<"Input "<<n <<" elements: ";

	for(int i=0; i<n; i++)
	{
		cin>>arr[i];
	}

	int last = arr[n-1];

	int new_depth = log(new_n);
	int right_child, left_child, step, temp;

	double time = omp_get_wtime();

	//First Pass: Bottom Up from Leaves to Root Node

	for(int d=0; d<new_depth; d++)
	{
		right_child = power(2,d+1) -1;
		left_child = power(2,d)-1;
		step = power(2,d +1);

		#pragma omp parallel for shared (arr, right_child, left_child)
		for(int i=0; i<new_n; i+=step)
		{
			arr[i+right_child] = arr[i+left_child] + arr[i+right_child];

		}
	}

	arr[new_n-1]=0;

	// Second Pass: Top Down from Root Node to Leaves

	for(int d= new_depth -1; d>=0; d--)
	{
		right_child = power(2,d+1) -1;
		left_child = power(2,d)-1;
		step = power(2, d+1);

		#pragma omp parallel for shared(arr, right_child, left_child) private (temp)
		for(int i=0; i< new_n; i+=step)
		{
			temp = arr[i+left_child];
			arr[i+left_child] = arr[i+right_child];
			arr[i+right_child] = temp + arr[i+right_child];
		}
	}

	time = omp_get_wtime() -time;
	cout<<"Time elapsed = "<<time<<endl;

	cout<<"Prefix sum : ";

	for(int i=1; i<n; ++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<arr[n-1]+last<<endl;

	return 0;


}