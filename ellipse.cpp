/* 
 * ellipse.cpp
 * chris hamby
 * 16-Sept-2020
 * 
 * this program is meant to help with generating ellipses for a cad project 
 * the ellipses are rotated but must fit inside of a container with a fixed width
 * they must touch the container wall (i.e. take up the whole width)
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>


float get_input_num();
int generate_rotated_ellipse(float, float, float);
using namespace std;


int main() {
    int running = 1;
    cout << "\n\n";
    cout << "ELLIPSE HELPER" << endl;
    cout << "press q to quit" << endl;

    /* rotated ellipses will have the same width as the non-rotated ellipse */
    cout << "enter a container width: ";
    float width = get_input_num();
    if(width == -1) running = 0;

    /* eccentricity describes the shape of the ellipse */
    cout << "for golden ratio, ecc = 0.786" << endl;
    cout << "enter an eccentricity value (0 - 1): ";
    float ecc = get_input_num();
    if(ecc == -1)   running = 0;


    while(running){
        /* K describes where the ellipse hits the container wall 
         *
         * when K=0, the ellipse touches the container at x=0
         *      i.e. the top of the ellipse, or rotate by 90 degrees
         * when K=1, the ellipse touches the container at y=0
         *      i.e. no rotation 
        */
        cout << "\nplease enter a K value (0 - 1): ";
        float K = get_input_num();
        if(K == -1) break;
        generate_rotated_ellipse(width, ecc, K);
    }

    return 0;
}



/* find the slope of an ellipse at a given point P
   'P_X' coordinate is given as a percentage of the a variable 
   X = K*a, where K is between 0 and 1
   'P_Y' coordinate is found using the ellipse definition formula
*/
int generate_rotated_ellipse(float width, float ecc, float K){
    // ellipse dimensions 
    float a = width / 2;                        /* ellipse "x radius" */
    float c = ecc * a;                          /* see definition of eccentricity */
    float b = sqrt( pow(a, 2) - pow(c, 2) );    /* ellipse "y radius" */
    float height = b * 2;

    // point where the ellipse will hit the container
    float P_X = K * a;
    float P_Y = sqrt( pow(b,2) * ( 1 - pow(P_X/a, 2)) ) ;

    // vector from each foci to point of interest
    float V1_X = P_X - c;
    float V1_Y = P_Y;

    float V2_X = P_X + c;
    float V2_Y = P_Y;

    // angle that each vector forms with the x axis 
    float V1_theta = atan2(V1_Y, V1_X);
    float V2_theta = atan2(V2_Y, V2_X);
    float P_Normal = (V1_theta + V2_theta) / 2;

    float dist_to_P = sqrt( pow(P_X, 2) + pow(P_Y, 2) );
    float angle_to_P = atan2( P_Y, P_X );

    float projection_theta = P_Normal - angle_to_P;
    float projection_L = dist_to_P * cos(projection_theta);
    float scale_amt = a / projection_L;
    //cout << "P_X: " << P_X << endl;
    //cout << "P_Y: " << P_Y << endl;
    //cout << "V1_theta: " << V1_theta << " radians" << endl;
    //cout << "V2_theta: " << V2_theta << " radians" << endl;
    //cout << "scale amount: " << scale_amt << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "K == " << K << endl;
    cout << "Rotation Amount: " << P_Normal << " radians" << endl;
    cout << "Width:  " << width * scale_amt  << endl;
    cout << "Height: " << height * scale_amt << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
    return 0;
};



/* only works for positive numbers */
float get_input_num() {
	string mystr;
	float mynum =-1;
	getline(cin, mystr);			// get a whole line of input
	stringstream(mystr) >> mynum;   // try to extract a number from it
	//	cout << "entered " << mynum << endl;
    return mynum;
}