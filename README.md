# Bin-packing-problem
 with segment tree
 
 ## Project Subject: 
 Bin Packing Problem with First-Fit and Best-Fit Algorithms
	In this Project, we have aimed to implement First-Fit and Best-Fit Algorithms in a proper way. 
Our First-Fit Algorithm utilizes a greedy approach by using a Segment Tree data structure to quickly find the first bin that has enough space for our weight. Our time complexity for our algorithm is O(logn).

## The Usage 
Our program uses input and output text files included in to source files.
![image](https://user-images.githubusercontent.com/78648500/122786697-3da7ef80-d2bd-11eb-865d-73f07c1d1f72.png)

Our input data must be put in the input.txt file as float numbers and write them line by line

#### Example

![image](https://user-images.githubusercontent.com/78648500/122786790-59ab9100-d2bd-11eb-874e-9e9315ffcd79.png)

The output of the program is written in the output.txt file.

#### Example

![image](https://user-images.githubusercontent.com/78648500/122786872-6b8d3400-d2bd-11eb-89bf-d59eec354c06.png)

## Code

### Macros

```cpp
#define MIDDLE (left+right)/2 //Defining a macro to get the middle of the range
```

The MIDDLE macro finds the middle of a certain range of [left, right].

```cpp
int num_weights; // the number of total weight
double ST[1000001];    //Initializing our segment tree.
int first_fit;
```

### Global Variables

Our num_weights variable holds the total number of weights user has entered. (Line 1)
Our segment tree is initialized as a global variable named ST. Because a segment tree is a “almost complete binary tree”, we can represent it as an array. (Line 2)
Our first_fit variable holds the ID of a certain bin which our weight is assiged to.

### Main Function

```cpp
    ofstream ofs;   
    ofs.open("output.txt", ios::out | ios::trunc);  
    ofs.close();
```

Our main function starts with truncating or cleaning our output text file to get rid of our previous results.

```cpp
    ifstream infile;
    infile.open("input.txt");
    string fileString;
    int i = 0;
    while (getline(infile, fileString))  
    {
        num_weights++;  
    }
```

This code snippet, reads the input file and calculates the total number of weights user has entered, then we increment our num_weights variable accordingly.
```cpp
float* weightArr = new float[num_weights];    
    infile.close();
    infile.open("input.txt");   

    while (getline(infile, fileString)) 
    {
        istringstream iss(fileString);
        iss >> f[i]; //Read data into our array.
        //cout << f[i] << endl;
        i++;
    }
```

We create a dynamic array named weightArr with the size of num_weights for holding the weights. (Line1)
We open our input file for reading, then we fill our array with weight values from the input.txt file. (Lines 5-10)
We have used istringstream class to get float data from input.txt file.

```cpp
fstream outfile;
    outfile.open("output.txt", ios::app);
    outfile << "********--------Bin Packing (First Fit)--------********"<<endl<<endl;
    outfile.close();
    ```
    
    We open our output.txt to write the header.
    
    ```cpp
    for (int i = 0; i < num_weights; i++) 
    {
        FirstFit(weightArr[i]);
    }
    ```
    
    This loop sends the each value from our weights array to our FirstFit function one by one. With every loop, we pass the i’th item to the function for calculations.
    
    ```cpp
    outfile.open("output.txt", ios::app);
    outfile << "\tTotal number of bins required for first fit: " << first_fit << endl;
    outfile <<endl<< "********--------Bin Packing (Best Fit)--------********"<<endl<<endl;
    outfile.close();
    ```
    
    We open our output.txt to write the header and the total of bins required for first fit, which is stored in our first_fit variable.
    
    ```cpp
    BestFit(weightArr); //Passing the array pointer to our BestFit function

    delete[] weightArr; //Deleting our dynamically created array.
    infile.close(); //Closing our file
    return 0;
```

	In the lines of our main function, we send our weightArr array to our BestFit function. 
	Then we delete our dynamic array and close our input file. 

### FirstFit Function

```cpp
void FirstFit(double val)
{
    first_fit = Query(1, val, 1, num_weights);  //first_fit holds the binID 
    Update(1, first_fit, val, 1, num_weights); 

    fstream outfile;
    outfile.open("output.txt", ios::app);
    outfile << "\tPlaced item of value " << val << " in bin ID " << first_fit << endl;
    outfile.close();
}
```
Our FirstFit function is our base function that calls both our Query and Update Functions. This Function is for writing the placements for each item with it’s bin. 
Our parameter val holds a single weight value that was sent from a loop in our main function. The first_fit variable holds the bin ID which our val weight value will eventually be placed in. This calculation is done by Query function which is called with the initialization of out  first_fit variable. (Line 2)
After we have our bin ID (namely the first-fit bin that our val can be placed in), the Update function is called. (Line 4) 
After the update function, the placement of the item and it’s bin is printed into our output.txt file. (Lines 6-10)

### Query Function
```cpp
int Query(int idx, double val, int left, int right)     
{                                                       
    if (left == right) //Check if leaf node.
    {
        //This is the first bin that our 'val' can fit into.
        return left;
    }
    // check whether the left subtree contains a fitting bin
    if (ST[2 * idx] <= 1.001 - val) {
        return Query(2 * idx, val, left, MIDDLE);   
    }
    else {  //check the right subtree
        return Query(2 * idx + 1, val, MIDDLE + 1, right); 
    }
}
```

This function finds the first leaf node (bin) that has enough space for our value val. Then it returns that leaf node/bin. 
First if condition (Line 3) checks if the left and right range are equal or not. If those are equal, it means that we are on a leaf node and there is a bin that our val can fit into. It returns left because it is the first available bin. 
Second if statement (Line 9) checks whether the left subtree contains a fitting bin. 
With our first recursive function (Line 10), we check the left subtree. Our idx becomes 2*idx (coming from our 2*n for left child formula). And our right becomes our MIDDLE because we have to split our range. Our new range must become [left, MIDDLE] because we are looking and recursing in the left subtree.
The second recursive function (Line 13) is for checking the right subtree and child. Our idx must be 2*idx+1 according to our formula (2*n+1 finds the right child). And we have to change our range again to [MIDDLE + 1, right] because we are looking in the right subtree. 
Thanks to this recursive algorithm, we can search both left and right sub trees quickly and find the first fitting bin for our val.

### Update Function

```cpp
void Update(int idx, int x, double val, int left, int right)
{                                                               
    if (left == right) //Check if leaf node
    {
        ST[idx] += val; //We add our 'val' to that bin.
        return;
    }

    //This part is for to check which subtree the x'th bin.
    if (x <= MIDDLE) {
        Update(2 * idx, x, val, left, MIDDLE); //Recurse for the left child 
    }   
    else {
        Update(2 * idx + 1, x, val, MIDDLE + 1, right);   //Recurse for the right child
    }
    ST[idx] = min(ST[2 * idx], ST[2 * idx + 1]);    //Updating the parent with the minimun value of it's children.
}
```

This function is for updating the weights inside the bins. The function adds the value of    val in our segment tree array ST in the position idx if the bin at that idx is available.
The first if statement (Line 2) checks whether we are in leaf node or not. If we are in a leaf node then, it means that we have found a bin that has enough space for our item. After that, we add the value to that bin.
For the second if statement (Line 9), it checks which subtree our x (first_fit) is in. Left or right. If it is on the left, we recurse for the left child. We use 2 * idx (According to 2*n formula). because we want to find the left child. And our right becomes our middle because we have split our range. Our new range is now [left, MIDDLE].
	For the second recursive function (Line 13) in our else statement, we recurse for the right child. We use 2 * idx + 1 (According to 2*n+1 formula). And our right becomes our middle because we have split our range. Our new range is now [MIDDLE+1, right].
The last line of code aims to find the minimum value between right and left child. After that, it written as the new parent of those two child nodes.

### BestFit Function

```cpp
void BestFit(float* val)
{                           
    fstream outfile;
    outfile.open("output.txt", ios::app);
    int best_fit = 0; 
    float* REMarray = new float[num_weights]; 

    for (int i = 0; i < num_weights; i++) 

        int min = 1 + 1;    //Minimum space
        int bin_idx = 0;    //Current bin index
        int j;

        for (j = 0; j < best_fit; j++) {    
            if (REMarray[j] >= val[i] && REMarray[j] - val[i] < min) {      
                bin_idx = j;    //Reset index
                min = REMarray[j] - val[i];     
            }
        }

        if (min == 1 + 1) {     
            REMarray[best_fit] = 1 - val[i]; 
            best_fit++; 
        }
        else // Assign the item to best bin
            REMarray[bin_idx] -= val[i];

        outfile << "\tPlaced item of value " << val[i] << " in bin ID " << best_fit << endl;


    }
    //cout << "Number of Bins Required for Best Fit: " << best_fit;
    outfile << "\tTotal number of bins required for best fit: " << best_fit << endl;
    outfile.close();

}
```

Our BestFit function is implemented with a brute force algorithm. The time complexity for this function is O(n^2) because we have nested loops and we check every space in our REMarray with every weight inserted.
	Our best_fit variable holds the number of bins used for best bin packing. (Line 4)
	Our REMarray is a dynamic array that stores the remaining sizes of each bin to calculate later according to the best fit packing’s algorithm. (Line 5)
	Our first for loop (Line 7) cycles for every item.
	We declare our minimum space variable min. This is used later in our condition statement to see if our minimum space is greater than our calculated remain. This is later stored in the same variable min (Line 16) to store the previous minimum space.
	Our second for loop (Line 13) loops as many times as our current bin amount to check every available bin for remaining sizes.
	Our if statement (Line 14) checks if our remaining of the j’th bin is enough for our val, AND if the remaining from that calculation is less than our previous minimum remaining.
	The statement (Line 16) stores the minimum remaining in our min variable.
If our value can’t fit any bin, then we create a new bin (Lines 20-23). First we store the remaining from the substraction from 1 with our value in our REMarray array at the index of best_fit. For example, at the start of the program we don’t have any bins. So, we need to create a new one. If our value is 0.6, we calculate the remaining as 0.4 (1 - 0.6) and store that value in our REMarray[best_fit] = 0.4. So, our array becomes REMarray = {0.4}. Then we increment out best_fit variable because we have just created a new bin.
In our else statement (Line 24 -25) we substract our current value from our remaining array. We do this because it means that we have put a new weight into that bin so we have to reduce the remaining size. Therefore, we calculate the new remaining in that bin.
On the final lines of code (Lines 27-35) we write our output into our output.txt file.






