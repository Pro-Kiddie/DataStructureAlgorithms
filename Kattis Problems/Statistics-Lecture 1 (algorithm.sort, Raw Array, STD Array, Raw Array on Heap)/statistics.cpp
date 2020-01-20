//Problem: https://nus.kattis.com/problems/statistics
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
//Solution using Vector:
int main(){
    //Read from file line by line
    //std::ifstream infile("sample.in");
    //Read in 1st number which equals to size of array
    int size, n, index = 1;
    //Construct array with the size
    std::vector<int> a;
    while (std::cin >> size){
        //Initialize array by reading in N numbers equal to size
        for (int i=0; i < size; i++){
            std::cin >> n;
            a.push_back(n);
        }
        //Sort the array
        std::sort(a.begin(), a.end());
        //Output the Case X: MIN MAX RANGE 
        std::cout << "Case " << index++ << ": " << a[0] << " " << a[size-1] << " " << a[size-1] - a[0] << std::endl;
        //Clear the vector for next line
        a.clear();
    }
    //infile.close();
    return 0;
}

//Solution Using Array:
//Does not work because std:array or raw array (e.g. int a[5]) requires to know the size at compile time which will be pushed onto the stack
//However, only know the size at runtime when reading the size from a file
// int main(){
//     //Read from file line by line
//     std::ifstream infile("sample.in");
//     //Read in 1st number which equals to size of array
//     int size, n, index = 1;
//     while (infile >> size){
//         int a[size];
//         //Initialize array by reading in N numbers equal to size
//         for (int i=0; i < size; i++){
//             infile >> n;
//             a[i] = n;
//         }
//         //Sort the array
//         std::sort(a, a+size);
//         //Output the Case X: MIN MAX RANGE 
//         std::cout << "Case " << index++ << ": " << a[0] << " " << a[size-1] << " " << a[size-1] - a[0] << std::endl;
//     }
//     infile.close();
//     return 0;
// }

//Solution Using Dynamically Allocated (Heap) Array:
// int main(){
//     //Read from file line by line
//     std::ifstream infile("sample.in");
//     //Read in 1st number in a line which is the no. of integers in this line which is equal to size of array
//     int size, n, index = 1;
//     while (infile >> size){
//         int *a = new int[size];
//         //Initialize array by reading in N numbers equal to size
//         for (int i=0; i < size; i++){
//             infile >> n;
//             a[i] = n;
//         }
//         //Sort the array
//         std::sort(a, a+size);
//         //Output the Case X: MIN MAX RANGE 
//         std::cout << "Case " << index++ << ": " << a[0] << " " << a[size-1] << " " << a[size-1] - a[0] << std::endl;
//         delete [] a;
//     }
//     infile.close();
//     return 0;
// }

//Lecture 1
//int cur_min = 1e9; //10^9
//freopen("in.txt", "r", stdin); //Read from in.txt and redirect to the stdin as somebody is typing
//#include <bits/stdc++.h //Include every library you have in your C++ distribution


