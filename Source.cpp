#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include <fstream>

using namespace std;

/*
                    _______________________________________________
                   |                                               |
                   |    Data Structures and Algorithms Project by, |
                   |                                               |
                   |  * Gizem TURAN                 1800002414     |
                   |  * Buðra Meriç DEÐÝRMENCÝ      1800003317     |
                   |_______________________________________________|

*/

//************************************MACROS*******************************************//
#define MIDDLE (left+right)/2  //Defining a macro to get the middle of the range
//*************************************************************************************//

//*******************************GLOBAL VARIABLES**************************************//
int num_weights; // the number of total weight
double ST[1000001];    //Initializing our segment tree.
int first_fit;
int ffmax = 0;
//*************************************************************************************//

void Update(int idx, int x, double val, int left, int right)    //This function is for updating the weights inside the bins. The function adds the value of 'val' in our segment tree array 'ST' in the position 'idx' if the bin at that idx is available.
{                                                               //The time complexity for this function is O(logn)
    if (left == right) //Check if leaf node
    {
        // We have our leaf node. So we have an appropriate bin that has enough empty space. 
        ST[idx] += val; //We add our 'val' to that bin.
        return;
    }

    //This part is for to check which subtree the x'th bin.
    //If it is smaller/equal to our range's middle, we have to recurse from the left child in order to find that bin.
    if (x <= MIDDLE) {
        Update(2 * idx, x, val, left, MIDDLE); //Recurse for the left child 
    }
    else {
        Update(2 * idx + 1, x, val, MIDDLE + 1, right);   //Recurse for the right child
    }

    ST[idx] = min(ST[2 * idx], ST[2 * idx + 1]);    //Updating the parent with the minimun value of it's children.
}

int Query(int idx, double val, int left, int right)     //This function finds the first leaf node (bin) that fits together with our value 'val'. Then it returns that leaf node/bin.
{                                                       //The time complexity for this function is O(logn)
    if (left == right) //Check if leaf node.
    {
        //This is the first bin that our 'val' can fit into.
        return left;
    }
    // check whether the left subtree contains a fitting bin
    if (ST[2 * idx] <= 1.001 - val) {
        return Query(2 * idx, val, left, MIDDLE);   //We recurse in order to find an appropriate leaf node. Our right becomes our middle. [left, MIDDLE] becomes our range.
    }
    else {  //check the right subtree
        return Query(2 * idx + 1, val, MIDDLE + 1, right); //We recurse We recurse in order to find an appropriate leaf node. Our left becomes our MIDDLE + 1. [MIDDLE+1,right] becomes our range.
    }
}

void FirstFit(double val) //Function that calls Query and Update functions, then prints the item placements.
{
    first_fit = Query(1, val, 1, num_weights);  //first_fit holds the bin ID that our val will be placed into.
    Update(1, first_fit, val, 1, num_weights);  //Update the weights in the bins

    if (ffmax <= first_fit)
    {
        ffmax = first_fit;
    }

    fstream outfile;
    outfile.open("output.txt", ios::app);
    outfile << "\tPlaced item of value " << val << " in bin ID " << first_fit << endl;
    outfile.close();
}

void BestFit(float* val)
{                           //The time complexity fot this function is O(n^2). Because for each item, it checks every previous bin.
    fstream outfile;
    outfile.open("output.txt", ios::app);
    int best_fit = 0; //Initializing the best_fit variable. This holds the number of bins used for best fit packing.

    float* REMarray = new float[num_weights]; //Dynamically created array to store the remaining sizes of each bin to calculate later according to the best fit packing's algorithm.

    for (int i = 0; i < num_weights; i++) {     //Loop for checking all bins one by one.

        int min = 1 + 1;    //Minimum space
        int bin_idx = 0;    //Current bin index
        int j;

        for (j = 0; j < best_fit; j++) {    //Loop as many times as our current bin amount.
            if (REMarray[j] >= val[i] && REMarray[j] - val[i] < min) {      //Check if the remaining space in a certain bin  is greater than our current value and it is smaller than the minimum required space after it is substracted with our current value..
                bin_idx = j;    //Reset index
                min = REMarray[j] - val[i];     //Recalculate minimum space according to our weight.
            }
        }

        if (min == 1 + 1) {     //If our value can't fit any bin, then we create a new bin.
            REMarray[best_fit] = 1 - val[i]; // Store the remaining to the newly created bin
            best_fit++;
        }
        else // Assign the item to best bin
            REMarray[bin_idx] -= val[i];

        //outfile << "\tPlaced item of value " << val[i] << " in bin ID " << best_fit << endl;
        //cout << "Placed item of value" << val[i] << " placed in bin number " << best_fit << endl;

    }
    //cout << "Number of Bins Required for Best Fit: " << best_fit;
    outfile << "\tTotal number of bins required for best fit: " << best_fit << endl;
    outfile.close();

}

int main()
{

    ofstream ofs;   //For truncating the output file everytime the program starts.
    ofs.open("output.txt", ios::out | ios::trunc);  //ios:trunc for truncating
    ofs.close();

    //This part reads the input.txt file to an array as float values  
    ifstream infile;
    infile.open("input.txt");
    string fileString;
    int i = 0;
    while (getline(infile, fileString)) //This loop is for dynamically getting the number of weights which the user has entered 
    {
        num_weights++;  //Incrementing the total number of weights user has entered
    }

    float* weightArr = new float[num_weights];    //Initializing a new dynamic array with the size of the number of weights
    infile.close();
    infile.open("input.txt");   //Open the input.txt file again for reading

    while (getline(infile, fileString)) //This loop reads the txt file line by line. The istringstream class is used to cast the string values as float values because those values will be used in calculations.
    {
        istringstream iss(fileString);
        iss >> weightArr[i]; //Read data into our array.
        //cout << f[i] << endl;
        i++;
    }

    fstream outfile;
    outfile.open("output.txt", ios::app);
    outfile << "********--------Bin Packing (First Fit)--------********" << endl << endl;
    outfile.close();

    for (int i = 0; i < num_weights; i++) //This loop is for sending the individual values from our array to our FirstFit function.
    {
        FirstFit(weightArr[i]); //Passing the i'th item on our array to the First Fit Function
    }

    outfile.open("output.txt", ios::app);
    outfile << "\tTotal number of bins required for first fit: " << ffmax << endl;
    outfile << endl << "********--------Bin Packing (Best Fit)--------********" << endl << endl;
    outfile.close();

    BestFit(weightArr); //Passing the array pointer to our BestFit function

    delete[] weightArr; //Deleting our dynamically created array.
    infile.close(); //Closing our file
    return 0;
}