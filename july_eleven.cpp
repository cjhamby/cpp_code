/*
 * July 11 Daily Challenge
 * 
 * code by: Chris Hamby 
 * 
 * ----------------------------------------------------------------------------------
 * Challenge:
 * Given a list of integers, write a function that returns the largest sum of non-adjacent numbers. 
 * Numbers can be 0 or negative.
 * 
 * Can you do this in O(N) time and constant space?
 * 
 * 
 * ----------------------------------------------------------------------------------
 * Solution Notes   
 * "non-adjacent numbers" refers to their position in the list 
 * 
 * {1, 3, 2}   >>    (1,3) are adjacent, but (1,2) are not 
 * 
 * if we find the largest 4 numbers...?
 * 
*/


#include <iostream>
using namespace std;


int fun(int*, int);


int main(){
    int list[6] = {-1, -2, -4, -7, -1, -1};

    cout << "desired sum: " << fun(list, 6);
    return 0;
}




int fun(int* list, int size){
    /* no non-adjacent numbers */
    if (size < 3)       return 0;

    /* only one pair of non-adjacent numbers */
    if (size == 3)      return list[0] + list[2];
    
    int i , j , k , sum = 0;

    /* index 0 = largest value index */
    int large_index[4] = { -1, -1, -1, -1};
    int large_value[4] = {  0,  0,  0,  0};

    
    /* find the largest 4 numbers in the list 
     * the required sum is going to be a combination of these */
    for(i=0; i<size; i++){
        int num_at_i = list[i];
        
        /* find where to put the number if it's large */
        for(j=0; j<4; j++){

            /* fill an empty container index */
            if( large_index[j] == -1){
                large_index[j] = i;
                large_value[j] = num_at_i;
                break;
            }

            /* greater than the value in the container */
            if(num_at_i > large_value[j]){

                /* shift the numbers to the right */
                for(k=3; k>j; k--){
                    large_value[k] = large_value[k-1];
                    large_index[k] = large_index[k-1];
                }

                large_value[j] = num_at_i;
                large_index[j] = i;
                break;
            }
            
        }
    }

    /* LARGE_VALUE now contains the largest 4 numbers in LIST
     * sorted from greatest -> least 
     * LARGE_INDEX contains the indeces of these numbers
     * two of these numbers will produce the desired sum 
    */

   sum = large_value[0];
   for(i=1; i<3; i++)
       /* get the largest non-adjacent number */
       if(abs(large_index[i]-large_index[0]) > 1){
           sum += large_value[i];
           break;
       }
   

   /* there could be a second sum greater than the first */
   int sum2 = large_value[1];

   for(i=2; i<4; i++)
        if(abs(large_index[1] - large_index[i]) > 1)
            sum2 += large_value[i];
   

   if(sum2 > sum)   return sum2; 
                    return sum;
}