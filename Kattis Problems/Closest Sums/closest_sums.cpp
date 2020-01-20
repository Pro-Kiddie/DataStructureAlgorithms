//Problem: https://nus.kattis.com/problems/closestsums

#include <iostream>
#include <vector>
#include <math.h> //abs()

using namespace std;

int main(){
    // freopen("F.0.in","r",stdin);
    int n, index=1;
    while(cin >> n){
        vector<int> nums(n);
        for(int& num : nums){
            cin >> num;
        }
        //Initialize all the possible sums
        vector<int> sums;
        for(int i = 0; i < n; ++i){
            for(int j = i + 1; j < n; ++j){
                sums.push_back(nums[i] + nums[j]);
            }
        }
        cout << "Case " << index++ << ":" << endl;
        int m; cin >> m;
        while(m--){
            int sum; cin >> sum;
            //find closest sum
            int closest_sum = sums[0];
            for(int i = 1; i < sums.size(); ++i){
                if (abs(sums[i] - sum) < abs(closest_sum - sum)) closest_sum = sums[i];
            }
            cout << "Closest sum to " << sum << " is " << closest_sum << "." << endl;
        }
        
    }
    return 0;
}