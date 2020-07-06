/*
 * July 3 Daily Challenge
 * 
 * code by: Chris Hamby 
 * 
 * Given a list of numbers (L) and a number (K)
 * return true (1) if any two numbers in L sum to equal K
 * 
 */

#include <iostream>
using namespace std;

int july_three_challenge(int*, int, int);


int main(){
    int size = 5;
    int list[5] = {1, 2, 3, 4, 5};
    int target = 7;

    july_three_challenge(list, size, target);

    return 0;
}



/*
 * Given a list of numbers (L) and a number (K)
 * return true (1) if any two numbers in L sum to equal K
 *
 * l  points to the list
 * s  size of the list
 * k  number to sum to
 *
 */
int july_three_challenge(int* l, int s, int k){
	int i, j;
	for(i=0; i<s; i++){
		// see what number would be needed to equal the sum
		int needed = (k - l[i]);

		// see if that number is somewhere in the rest of the list
		// no need to check indexes before 'I'
		for(j=i; j<s; j++)
			if(l[j] == needed) {
					cout << l[i] << " + " << l[j] << " = " << k << "           we got dice baby!!!" << endl;
					return 1;
				}
	}
	cout << "no dice" << endl;
	return 0;
}