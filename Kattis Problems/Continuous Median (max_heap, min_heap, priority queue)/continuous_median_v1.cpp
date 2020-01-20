//Matric number:  
//Full name:  
//Lab group number:  
//Lab group TA:  

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <queue>
#include <time.h>
// #include <cstdlib>
// #include <ctime>

using namespace std;

typedef unsigned int ui;

string simple_addition(string& n1, string& n2){
    //Make sure n2's length is longer or equal to n1
    if (n1.length() > n2.length()) swap(n1, n2); //swap content of variables

    //Reverse the two strings, so smallest digit at the start
    reverse(n1.begin(), n1.end()); 
    reverse(n2.begin(), n2.end());

    string result = "";

    int carry = 0;

    //Add the two numbers digit by digit and set carry accordingly
    for(int i=0; i < n1.length(); ++i){
        int sum = (int)(n1[i] - '0') + (int)(n2[i] - '0') + carry;
        //Push the digit to the result string
        result.push_back((char)(sum % 10 + '0'));
        //Calculate if carry should be set
        carry = sum/10;
    } 

    //Add the rest of the longer number
    for(int i=n1.length(); i < n2.length(); ++i){
        int sum = (int)(n2[i] - '0') + carry;
        result.push_back((char)(sum % 10 + '0'));
        //Should still calculate carry because if first digit is 9 and carry is set from previous for loop last iteration
        carry = sum/10;
    }

    //If two strings same length, 2nd loop will not be executed and carry is set
    if (carry){
        result.push_back((char)(1 + '0'));
    }

    //Reverse the result
    reverse(result.begin(), result.end());
    return result;
}

int main(){ //O(N^2) -> EXCEED TIME LIMIT! 
    freopen("1.in","r",stdin); 
    clock_t begin = clock();
    int tc; cin >> tc;
    int n;
    while(tc--){
        cin >> n;
        vector<ui> a(n);
        string sum = "0";
        for(int i = 0; i < n; ++i){ //O(N)
            cin >> a[i];
            if (i != 0) {
                ui num = a[i];
                int j = i - 1;
                for(; j >= 0 && num < a[j]; --j){ //O(N) -> Insertion sort
                    a[j+1] = a[j];
                }
                a[j+1] = num;
            }
            // for(ui& num: a){
            //     cout << num << " ";
            // }
            // cout << endl;
            //Calculate the median 
            int size = i + 1;
            ui median;
            if(size%2 == 1){
                median = a[size/2];
            }else{
                ui num1 = a[size/2];
                ui num2 = a[size/2-1];
                median = (ui)floor((num1 + num2)/(double)2);
            }
            string median_s = to_string(median);
            sum = simple_addition(sum, median_s);
        }
        cout << sum;
        if (tc != 0) cout << endl;
        //qSort(a, 0, a.size()); //O(N log N)
       
    }
    printf("\nRuntime = %fs\n",(double)(clock()-begin)/CLOCKS_PER_SEC);
    return 0;
}

// int partition(vector<ui>& a, int low, int high) {
//     ui p = a[low]; // p is the pivot, the 1st item
//     int m = low; // S1 and S2 are initially empty
//     for (int i = low+1; i <= high; i++) { // explore the unknown region to distribute item into S1 & S2
//         if (a[i] < p) { 
//             m++;
//             swap(a[i], a[m]);
//         } 
//     }
//     swap(a[low], a[m]); // final step, swap pivot with a[m]
//     return m; // return the index of pivot
// }

// int r_partition(vector<ui>& a, int i, int j) {
//     //Random Quick Sort randomly choose the pivot instead of always using a[i]
//     srand(time(NULL));
//     int index = (rand() % (j-i+1)) + i; 
//     int temp = a[index];
//     a[index] = a[i];
//     a[i] = temp;
//     //First item is now the randomly chosen Pivot
//     return partition(a, i, j);
// }

// void qSort(vector<ui>& a, int low, int high) {
//     if (low < high) {
//         int m = r_partition(a, low, high); // O(N)
//         qSort(a, low, m-1); // recursively sort left subarray
//         // a[m] = pivot is already sorted after partition
//         qSort(a, m+1, high); // then sort right subarray
//     }
// }