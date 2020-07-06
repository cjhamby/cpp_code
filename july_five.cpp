/*
 * July 5 Daily Challenge
 * functions to (de)serialize a binary tree recursively
 * 
 * code by: Chris Hamby 
 * 
 *
 * for the tree:
 *         a
 *        / \ 
 *      b     c
 *     / \   / \
 *    d  e   
 * 
 * 
 * the resulting serialization will look like:
 * a b d , , e , , c , , 
 * 
 * the commas will help to deserialize it later 
 * and eliminate ambiguity
*/



#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;




/* NODE CLASS ========================================================
 * a binary tree node 
 * each node has two children - left and right */
class node{
    node* left;
    node* right;
    int val;

    public:
    node(int);
    int get_val()             { return val;   };
    node* get_left()          { return left;  };
    node* get_right()         { return right; };
    void set_val(int v)       { val   = v;    };
    void set_left(node* ptr)  { left  = ptr;  };
    void set_right(node* ptr) { right = ptr;  };
};

/* constructor for nodes */
node::node(int v){
    val = v;
    left = NULL;    /* for the time being, these are null pointers */
    right = NULL;   /* they will have to be assigned later         */
}
/*=================================================================*/





/* declare these functions after NODE class is defined */
node* init_tree();
void serialize_tree(node* top);
string get_file_data(string s);
node* deserialize_string(string s, int n);

ofstream myfile;  /* global file output stream, multiple functions write to it */
int dsi = 0;      /* deserialization index, globally loved (and feared)        */


int main() {
    node* t_ptr = init_tree();
    string s;

    /*---  SERIALIZATION TEST  ---*/
    /* open the file stream first */
    cout << "\nSERIALIZATION TEST" << endl;
    myfile.open("output_jul_5.txt");    /* where the data is sent             */
    serialize_tree(t_ptr);              /* stores the serialization to myfile */
    myfile << endl;                     /* cap the output with a newline char */ 
    myfile.close();                     /* what is opened, must be closed     */

    /* verify the results */
    s = get_file_data("output_jul_5.txt");         /* where data is read from */
    cout << "OUT: " << s << endl;                  /* you could also open txt */



    /*---  DE-SERIALIZATION TEST  ---*/
    cout << "\n\nDESERIALIZATION TEST"<< endl;

    s = get_file_data("test_input_jul_5.txt"); /* open a manually-created serialization */
    cout << "IN:  " << s << endl;
    t_ptr = deserialize_string(s, dsi);        /* create a new tree, with t_ptr as top  */

    /* using serialization is currently the best text representation
     * so we use that to verify that nothing changed                          */
    myfile.open("output2_jul_5.txt");   /* where the data is sent             */
    serialize_tree(t_ptr);              /* stores the serialization to myfile */
    myfile << endl;                     /* cap the output with a newline char */ 
    myfile.close();                     /* what is opened, must be closed     */

    /* verify the results */
    s = get_file_data("output2_jul_5.txt");
    cout << "OUT: " << s << endl;
    return 0;
}


node* init_tree(){
    node* t_ptr = new node(1);
    t_ptr->set_left(new node(2));
    t_ptr->set_right(new node(5));
    t_ptr->get_left()->set_left(new node(3));
    t_ptr->get_left()->set_right(new node(4));
    return t_ptr;
};




/* serialize a node and its children 
 * FILE STREAM MUST BE OPEN 
*/
void serialize_tree(node* top){
    if(top == NULL){     /* there isn't a node here      */
        myfile << ", ";  /* indicate the end of a branch */
        return;
    }

    int v = top -> get_val();             /* get, and               */
    myfile << v << " ";                   /* print the node's value */
    serialize_tree(top -> get_left());    /* recursion, you say?    */
    serialize_tree(top -> get_right());   /* recursion, you say?    */
}


/* get the serialized data from a file
 * return it as a string                 */
string get_file_data( string file ){
    string s;
    ifstream myfile(file);                     /* input file is specified as the function arg.   */ 
    if(myfile.is_open())
        getline(myfile, s);                    /* all serialized data should be on a single line */
    myfile.close();                            /* the file is no longer needed   */
    return s;
}


/* 
 * process a string (or a substring)
 * to generate nodes
 *  
 * S is a string containing the serialized data
 * N is the index to start reading it at 
*/
node* deserialize_string(string s, int n){
    int val=0;              /* the value read from the file, put this in a node   */
    node* temp_ptr = NULL;  /* return a null pointer if the for loop is exited    */

    /* char-by-char analysis is safer for my ability level... */
    for(dsi=n; dsi<s.size(); dsi++){ /* DSI is the deserialization index (recursion-friendly) */
        char c = s[dsi];             /* C is the char at DSI */

        if( c == ',')                /* the break character indicates end of a branch */
            return NULL;             /* return a NULL pointer if the node has no children */

        if( c >= '0' && c <= '9'){   /* the char is between '0' and '9' */
            int n = c-'0';           /* convert from ascii -> int      */
            val*=10;                 /* shift val over by 1 digit place */
            val+=n;                  /* add the num to the 1s place     */
        }

        if(c == ' '){                /* the char is a space */
            if(val!=0){              /* a number is ready to be stored in a node */
                node* temp_ptr = new node(val); 
                temp_ptr -> set_left(deserialize_string(s, ++dsi));  /* recursion */
                temp_ptr -> set_right(deserialize_string(s, ++dsi)); /* recursion */
                return temp_ptr;
            }
            /* if val == 0 , a number hasn't been read yet; keep going */
        }
    }
    return temp_ptr;
}