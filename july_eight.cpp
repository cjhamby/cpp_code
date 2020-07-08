/*
 * July 8 Daily Challenge
 * 
 * code by: Chris Hamby 
 * 
 * ----------------------------------------------------------------------------------
 * Challenge:
 * An XOR linked list is a more memory efficient doubly linked list. 
 * Instead of each node holding next and prev fields, it holds a field named both, 
 * which is an XOR of the next node and the previous node. 
 * 
 * Implement an XOR linked list; 
 * it has an add(element) which adds the element to the end, 
 * and a get(index) which returns the node at index.
 * ----------------------------------------------------------------------------------
 *
 * 
 * ----------------------------------------------------------------------------------
 * Solution Notes
 * 
 * a handy thing to know about XOR: 
 * if: 
 *     A ^ B = C 
 * then:
 *     A ^ C = B
 *     B ^ C = A 
 * 
 * using this, we can extract the pointer data from "both"  
 * 
 * 
 * logical operators don't seem to work on pointers
 * but I don't want to blindly typecast the pointers without knowing their size
 * my first instinct is to use sizeof(ptr) and then choose an int size accordingly
 * but there is another solution: uintptr_t     
 * 
*/


#include <iostream>
using namespace std;

/* XOR Linked List Node */
class node{
    public:   
        node(int d);          /* default constructor               */
        void add(node* top);  /* add the new element to the end    */
        node* get(int i);     /* get the node at index i           */
        int val();            /* return the data value             */

    private:
        node* both;           /* (node* NEXT) XOR (node* PREVIOUS) */
        int data;             /* to make testing easy              */
};



/* Node Constructor */
node::node(int d){
    data = d;             /* data is used to test the order of the nodes          */
    both = NULL;          /* the XOR operation occurs when the next node is added */
}




/* add a node to the bottom of the list 
 * this function is called on the node at the top of the list (i.e. TOP -> ADD) */
void node::add(node* n){
    /* find the bottom of the list */
    node* prev = NULL;
    node* end  = this;
    node* next = end->both;   /* this will be NULL if there are no more nodes left */

    while( next != NULL ){
        prev = end;
        end  = next;
        next = (node*)((uintptr_t)(end->both) ^ (uintptr_t)(prev));
    }

    /* END is the last node of the list        
     * for readability: NEXT will now be the node we're adding */ 
    next = n;

    /* add the "previous" component of BOTH to the new node    */
    next -> both = end;
                                       
    /* update the BOTH value of END to include the new node    */
    end -> both = (node*)((uintptr_t)(prev) ^ (uintptr_t)(next));
}




/* return a pointer to the node at index i */
node* node::get(int i){
    /* if needed, return the first node in the array */
    if(i == 0)                         return this;    


    /*the first node's BOTH value is the next node's address only      */
    node* my_node = this -> both; /* the pointer this function returns */

    /* check for if there is no second element */
    if(my_node == NULL)                return NULL;
    
    int j;
    node* prev = this;
    
    /* my_node is the element at index 1 
     * keep getting the next node until the desired index is reached */
    for(j=1; j<i; j++){

        /* previous ^ both == next */
        node* next = (node*) ( (uintptr_t)(prev) ^ (uintptr_t)(my_node->both) );

        /* if there is not a next node, then the BOTH var just holds the previous address 
         * the XOR operation above would then return NULL, or 0, since (A ^ A == 0)    
         * this checks to ensure the index is not out of bounds    
        */
        if(next == NULL)               return NULL;      
        
        /* update the pointers */
        prev = my_node;
        my_node = next;
    }

    return my_node;
}


/* keep data private */
int node::val(){
    return data;
}







int main(){
    int i;
    node* temp;

    node* linked_list = new node(0);      /* create the first item in the list   */
    for(i=1; i<10; i++)                   /* create the rest of the list         */
        linked_list-> add(new node(i*2)); /* each element's data is 2x the index */
    
    /* test the list by accessing every index, as well as some that are out-of-bounds */
    for(i=12; i>=0; i--){
        temp = linked_list->get(i);
        cout << "value at index " << i << ":   ";
        if(temp!=NULL)
            cout << temp->val() << endl;
        else
            cout << "none" << endl;
    }


    return 0;
}


