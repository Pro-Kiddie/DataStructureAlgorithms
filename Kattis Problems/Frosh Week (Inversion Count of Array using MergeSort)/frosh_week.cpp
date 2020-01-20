//Problem: https://open.kattis.com/problems/froshweek

#include <bits/stdc++.h>

using namespace std;

long long INVERSION_COUNT = 0;

void merge(int a[], int low, int mid, int high) {
    // subarray1 = a[low..mid], subarray2 = a[mid+1..high], both sorted
    int N = high-low+1;
    int b[N];
    int left = low, right = mid+1, bIdx = 0;
    while (left <= mid && right <= high) {
        if(a[left] <= a[right]){ 
            b[bIdx++] = a[left++];
        }
        else{
            b[bIdx++] = a[right++];
            // Everytime ele in right subarray is being placed in b[]
            // All ele from current left to mid all need to be swapped with the ele on right in Bubble/Insertion sort
            // Or can form an inversion pair with the right ele which just being placed in b[]
            INVERSION_COUNT += (mid - left + 1); // Must add 1; E.g. low=0, mid=1, high=2 -> 1st element inserted into b[] is from right, then mid-left=1 which infact is 2
        }    
    }
    while (left <= mid) b[bIdx++] = a[left++]; // leftover, if any
    while (right <= high) b[bIdx++] = a[right++]; // leftover, if any
    for (int k = 0; k < N; k++) a[low+k] = b[k]; // copy back
}

void mergeSort(int a[], int low, int high) {
    // the array to be sorted is a[low..high]
    if (low < high) { // base case: low >= high (0 or 1 item)
        int mid = (low+high) / 2;	
        mergeSort(a, low  , mid ); // divide into two halves
        mergeSort(a, mid+1, high); // then recursively sort them
        merge(a, low, mid, high); // conquer: the merge subroutine
    }
}

int main(){ //O(N log N) -> Accepted!
    // freopen("E.0.in", "r", stdin);
    int n; cin >> n;
    vector<int> v(n);
    for(int& i : v){
        cin >> i;
    }
    int* a = v.data();
    mergeSort(a, 0, v.size()-1); //O(N log N)
    cout << INVERSION_COUNT;
    return 0;
}


//Attempt 1: -> Insertion Sort
// int main(){ //O(N^2) -> Time Limit Exceeded
//     // freopen("E.0.in", "r", stdin);
//     int n; cin >> n;
//     vector<int> v(n);
//     long long swaps = 0; //if input 10^5, and O(N^2) might result in 10^10 swaps, must use long long
//     for(int i = 0; i < n; i++){ //O(N)
//         int stu; cin >> stu;
//         int j = i-1;
//         for(; j >= 0 && v[j] > stu; j--){ //O(N)
//             v[j+1] = v[j];
//             swaps++;
//         }
//         v[j+1] = stu;   
//     }
//     cout << swaps;
//     return 0;
// }