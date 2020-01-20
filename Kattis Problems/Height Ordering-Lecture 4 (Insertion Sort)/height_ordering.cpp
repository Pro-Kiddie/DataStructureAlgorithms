//Problem: https://nus.kattis.com/problems/height

//The worse case of insertion sort is the array is reversely sorted
//Every insertion will happen at the front of the array
//The inner loop will run 1 + 2 + 3 + 4 + ... + N
//Sum of AP = N/2(2a + (n-1)d)
//In this case, a = 1, d = 1 -> N/2 (N+1)
//Test case 2 is an inversely sorted array, 19/2(19+1) = 190

#include <iostream>

using namespace std;

int main(){ //This program = O(PN^2)
    //freopen("sample.in","r",stdin);
    int datasets; cin >> datasets;
    while(datasets--){ //O(P) which can be <= 1000
        int k; cin >> k;
        int heights[20];
        for(int i=0; i < 20; i++){
            cin >> heights[i]; 
        }
        int step_back = 0;
        for(int i=1; i < 20; ++i){ //O(20) for this case, but exam will be very big -> O(N)
            int X = heights[i];
            int j=i-1;
            for(; j >= 0 && X < heights[j]; --j){ //O(N)
                heights[j+1] = heights[j]; //step back to make room for shorter kids
                step_back++;
            }
            //break out of for loop, j will be at index where a[j] < X
            //Insertion point at j+1
            heights[j+1] = X;
        }
        cout << k << " " << step_back << endl;
    }
    return 0;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(NULL);
  freopen("height/sample.in","r",stdin);
  int P; cin >> P;
  while (P--) { // O(P*n^2), but n is exactly 20 here, so 20^2 = 400, so O(400*P)...
    int K; cin >> K; cout << K << " ";
    int ans = 0;
    int H[30]; // just my habit to declare array about 10 cells larger than necessary
    for (int i = 0; i < 20; ++i) { // insertion sort simulation
      cin >> H[i]; // read next number
      int j = i; //When i = 0, the following while loop will not execute as j > 0 condition
      while ((j > 0) && (H[j] < H[j-1])) { // do (j > 0) check first to prevent crash, then check if we need to swap
        //While loop will happen when H[j] > H[j-1], bigger than the previous
        swap(H[j], H[j-1]); // yes, we need to swap these two, H[j] now at H[j-1]
        //H[j] which is the number need to be inserted is always at H[j] after swap as j-- 
        ++ans; // moved 1 back to make space
        --j; 
      }
    }
    cout << ans << endl; // number of swaps (steps taken back) needed for this test case
    for(int i = 0 ; i < 20; i++){
      cout << H[i] << " ";
    }
    cout << endl;
  }
  return 0;
}
