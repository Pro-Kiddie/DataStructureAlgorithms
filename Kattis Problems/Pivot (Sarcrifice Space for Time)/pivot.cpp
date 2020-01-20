//Problem: https://open.kattis.com/problems/pivot

#include <bits/stdc++.h>

using namespace std;

// Attempt 2:
int main(){ //O(3N) -> Accepted!
    // freopen("2.in","r",stdin);
    int N; cin >> N;
    vector<int> v(N);
    for(int& i : v){
        cin >> i;
    }

    //Compute a running max array from left; a[i] = max element from left
    vector<int> rMax(N); 
    int curMax = v[0];
    rMax[0] = curMax;
    for(int i = 1; i < N; i++){ //O(N)
        //Update curMax
        if(v[i] > curMax) curMax = v[i];
        rMax[i] = curMax;
    }

    //Computer a runnming min array from the right; a[i] = min element from the right
    vector<int> rMin(N);
    int curMin = v[N-1];
    rMin[N-1] = curMin;
    for(int i = N-2; i >= 0; i--){ //O(N)
        if(v[i] < curMin) curMin = v[i];
        rMin[i] = curMin;
    }

    int count = 0;
    for(int i = 0; i < N; i++){ //O(N)
        bool pivot = true;
        if(i != 0){
            //Access the left index of i in rMax to get the currMax
            if(rMax[i-1] > v[i]) pivot = false;
        }
        if (i != N-1 && (rMin[i+1] <= v[i])) pivot = false;
        if (pivot) count++;
    }

    cout << count;

    return 0;
}


// Attempt 1:
// int main(){ //O(N^2) -> Time Limit Exceeded
//     int N; cin >> N;
//     vector<int> v(N);
//     for(auto& i : v){
//         cin >> i;
//     }
    
//     int count = 0;
//     for(int i=0; i < N; i++){ //O(N) -> Cannot be speed up as you need to check each element if it is pivot
//         bool pivot = true;
//         int low = 0, high = N-1;
//         for(; low < i; low++){ //O(N) -> Can be speed up by sarcrificing space -> precompute a running max array from left
//             if(v[low] > v[i]) {
//                 pivot = false;
//                 break;
//             }
//         }
//         if (!pivot) continue;
//         while(high > i){ //O(N) -> precompute a running min array from the right
//             if(v[high] <= v[i]) {
//                 pivot = false;
//                 break;
//             }
//             high--;
//         }
//         if (pivot) count++;
//     }
//     cout << count;
//     return 0;
// }