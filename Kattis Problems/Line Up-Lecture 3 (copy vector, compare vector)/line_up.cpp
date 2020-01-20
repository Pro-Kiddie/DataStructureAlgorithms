//Problem: https://nus.kattis.com/problems/lineup

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){ //Whole program is O(N log N)
    freopen("1.in", "r", stdin);
    int n; cin >> n; cin.get();
    vector<string> names;
    while(n--){
        string name;
        cin >> name;
        names.push_back(name);
    }
    vector<string> sorted_names(names);
    sort(sorted_names.begin(), sorted_names.end()); //O(N log n)
    if(names == sorted_names) cout << "INCREASING"; //O(N) due to names == sorted_names comparision
    else {
        reverse(sorted_names.begin(), sorted_names.end()); //O(N)
        cout << (names == sorted_names ? "DECREASING" : "NEITHER"); //O(N)
    }
    // for (string& name : names){
    //     cout << name << endl;
    // }


    return 0;
}