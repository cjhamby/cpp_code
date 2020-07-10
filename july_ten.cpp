/*
 * July 10 Daily Challenge
 * 
 * code by: Chris Hamby 
 * 
 * ----------------------------------------------------------------------------------
 * Challenge:
 * A unival tree (which stands for "universal value") is a tree where all nodes under it have the same value.
 *
 * Given the root to a binary tree, count the number of unival subtrees.
 * 
 * 
 * ----------------------------------------------------------------------------------
 * Solution Notes   
 * ASSUME:
 * (1) parents either have no children or two children nodes
 * (2) children nodes have to also match parent node 
 * (3) parents without children are unival
 * (4) empty nodes are 0, not NULL 
 * 
 * 
*/



#include <iostream>
#include "include/binary_tree.hpp"  /* binary tree nodes I created for a previous challenge */

using namespace std;

int unival_counter(node* t);
int unival_check(node* t);
node* init_tree();



int main(){
    node* top = init_tree();
    int result = unival_counter(top);
    cout << result;
    return 0;
}


/* create the following tree:
 * a           0
 * b        0     0
 * c       1 1   0 0
 * 
 * nodes are labeled according to row, then index 
 *             a0
 *         b0       b1 
 *       c0  c1   c2  c3 
 * 
*/
node* init_tree(){
    node* a0 = new node(0);
    node* b0 = new node(0);
    node* b1 = new node(0);
    node* c0 = new node(1);
    node* c1 = new node(1);
    node* c2 = new node(0);
    node* c3 = new node(0);

    a0 -> set_children(b0, b1);
    b0 -> set_children(c0, c1);
    b1 -> set_children(c2, c3);

    return a0;
}



/* returns the absolute value from the below function */
int unival_counter(node* t){
    return abs(unival_check(t));
}


/* a node is a "UNIVAL NODE" if every node below it contains the same value as the parent node    
 * this function is given a node, T
 * it returns how many "UNIVAL NODES" are below T
 * if T is unival, the return value is positive
 * if T is not,    the return value is negative
 */
int unival_check(node* t){
    /* null nodes shouldn't be passed to this function */
    if(t == NULL)                                                       return 0;

    /* LEAF NODES have no children nodes and are thus UNIVAL NODES */ 
    if( t->get_left() == NULL && t->get_right() == NULL )               return 1;

    /* check if only one child is NULL 
     * this case would violate assumption #1 */
    if( t-> get_left() == NULL || t->get_right() == NULL )              return 0;
    
    /* check if the children nodes are unival nodes */
    int left_count  = unival_check( t->get_left()  );
    int right_count = unival_check( t->get_right() );

    
    /* if the child is not unival, it will return -COUNT  */
    /* unival nodes cannot have non-unival children nodes */
    int unival_count = abs(left_count) + abs(right_count);
    if(left_count <=0 || right_count <= 0)                              return -unival_count;
    
    /* check that all values are equal     */
    /* variables are used for readability  */
    int my_val    = t->get_val();
    int left_val  = t->get_left() ->get_val();
    int right_val = t->get_right()->get_val();

    if(my_val == left_val && my_val == right_val)     unival_count++;         /* T is a unival node     */
    else                                              unival_count *= -1;     /* T is NOT a unival node */

    return (unival_count);
}