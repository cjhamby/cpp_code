/*
 * July 4 Daily Challenge
 * 
 * code by: Chris Hamby 
 * 
 * Given an array of numbers, L
 * return a new array, M, where:
 * M[i] >> product of every element in L except for L[i]
 */
#include <iostream>
using namespace std;

void july_four_challenge(int*, int, int*);
void july_four_test();

int main() {
	july_four_test();
	return 0;
}


/*
 * Given an array of numbers, L
 * return a new array, M, where:
 * M[i] >> product of every element in L except for L[i]
 *
 * INPUTS
 * L  array of integers
 * N  size of array
 *
 * OUTPUT
 * M  output array
 */
void july_four_challenge(int* L, int N, int* M){
	int i, j, product;

	for(i=0; i<N; i++){
		product = 1;				// initialize product to 1
		for(j=0; j<N; j++){			// then multiply it by every int in L
			if(j != i)				// except for L[i]
				product *= L[j];
		}

		M[i] = product;				// assign value to the output array
	}
}



void july_four_test(){
	int i;
	const int n = 5;

	int  in[n] = {1, 2, 3, 4, 5};
	int out[n] = {0, 0, 0, 0, 0};

	cout << "input:  ";
	for(i=0; i<n; i++)
		cout << in[i] << " ";

	july_four_challenge(in, n, out);

	cout << "\noutput: ";
	for(i=0; i<n; i++)
		cout << out[i] << " ";
}
