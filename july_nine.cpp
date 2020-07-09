/*
 * July 9 Daily Challenge
 * 
 * code by: Chris Hamby 
 * 
 * ----------------------------------------------------------------------------------
 * Challenge:
 * Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, 
 * count the number of ways it can be decoded.
 * 
 * For example, the message '111' would give 3, since it could be decoded as 'aaa', 'ka', and 'ak'.
 * 
 * You can assume that the messages are decodable. For example, '001' is not allowed.
 * ----------------------------------------------------------------------------------
 *
 * 
 * ----------------------------------------------------------------------------------
 * Solution Notes
 * for a message "12345" the tree is formed (starting from the last index)
 * branches indicate the possible numbers that could precede a node 
 * 
 *                1
 *                  \
 *                x-- 2 
 *                      \
 *                  12 -- 3
 *                         \
 *                 1 -- 23-- 4
 *                    /        \
 *                  x       x--  5 \
 *                                   *
 *                               x /
 * 
 * count the bottom (left-most) branches that include the number '1' (first index)
 * that is how many possible messages may be formed from the encoded message 
*/



#include <iostream>
using namespace std;


int fun(string s, int i);

int main(){
    /* the encoded message */
    string test = "12345"; 

    /* how many messages it may be decoded into */
    int result = fun(test, test.size());

    cout << "\n\n\n";
    cout << "possible message count for " << test << " : " << result << endl;
    cout << "\n\n\n";
    
    return 0;
}


/*
 * rules:
 * the number 0 is only used in the 'ones' place
 * the number 1 may be followed by 0-9
 * the number 2 may be followed by 0-6
 * other numbers are either:
 * by themselves, or the 'ones' place of a larger number
 * 
 * a char-by-char analysis is used
 * 
*/
int fun(string s, int i){
    /* there are no more branches, which indicates a complete message */
    if(i==0)         return 1;

    /* branch 1 exists if the preceding number can be 1 digit  */
    /* branch 2 exists if the preceding number can be 2 digits */ 
    int b1_exists = 0;
    int b2_exists = 0;

    /* check for existence of branch 1 */
    /* check for numbers 0-9           */
    /* ONES is the char in the ones place of the preceding num */
    char ones = s[i-1];
    if( ones >= '1' && ones <= '9')         b1_exists = 1;

    /* check for existence of branch 2 */
    if( i > 1 ) {
        /* TENS is the char in the tens place of the preceding num */
        char tens = s[i-2];
        /* check for numbers 10-19 */
        if( tens == '1' )                   b2_exists = 1;
        /* check for numbers 20-26 */
        if( tens == '2' ) 
            if(ones >='0' && ones <='6' )   b2_exists = 1;
    }

    int sum = 0;
    if(b1_exists)   sum += fun(s, i-1);
    if(b2_exists)   sum += fun(s, i-2);

    return sum;
}