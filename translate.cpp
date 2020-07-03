/*
 * translate.cpp
 *
 * Created on: Jun 29, 2020
 * Author: Chris Hamby
 *
 * Demonstrates basic input processing with strings
 * Converts human language to guinea pig speak
 *
 */


#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void translate_h_to_g();

int main() {
	while(1)
		translate_h_to_g();
	return EXIT_SUCCESS;
}



/*
 * translate human language to guinea pig speak
*/
void translate_h_to_g() {
	string mystr;
	string new_word = "WeeEeeeEEeeeEe";
	char last_char = 'k';
	int i, j, k;
	int phrase_length;
	int word_begin = 0;

	// get a line of input from the user
	cout << "Type a phrase: ";
	getline(cin, mystr);
	phrase_length = (int)mystr.size();  // how many chars are in the phrase


	/*
	 * replace each word in the phrase with the new word
	 * in this case, the new word is a wheek of varying length
	 * that is, after all, the language of guinea pigs :-)
	 */
	for(i=0; i<=phrase_length; i++){
		if( i==phrase_length || mystr[i] == ' '){	 // check if the char is a space, or if end of phrase reached
			k=0;									                   // index of the char being pulled from NEW_WORD
			for(j=word_begin; j<i; j++) 			       // replace this phrase word with NEW_WORD
				mystr[j] = new_word[k++];			         // char by char

			mystr[i-1] = last_char;                  // cap the end of the new word
			word_begin = i+1;			                   // where the next word begins
		}
	}

	// lastly, print the new, translated phrase
	cout << "translated:    " << mystr << endl;
}
