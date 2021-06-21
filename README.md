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

int num_weights; // the number of total weight
double ST[1000001];    //Initializing our segment tree.
int first_fit;




