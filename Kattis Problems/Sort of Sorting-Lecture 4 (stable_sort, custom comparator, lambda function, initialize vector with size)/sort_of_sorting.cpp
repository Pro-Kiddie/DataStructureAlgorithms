//Problem: https://nus.kattis.com/problems/sortofsorting

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() { // the whole thing is O(N log N)
  freopen("in.txt", "r", stdin);
  bool FirstTestCase = true;
  int n;
  while (cin >> n, n) { // probably new "technique" to many of you: we can chain two C++ commands into one line using a comma, the last value (n here) is used as the test condition for the while loop, the while loop stops when n == 0
    vector<string> names(n); // declare locally so that it is fresh per test case :D
    for (auto &name : names) // C++11 way to read this input
      cin >> name;
    // study the difference of sort vs stable_sort in cppreference
    // stable_sort(names.begin(), names.end(), cmp); // old, pre C++11 way
    stable_sort(names.begin(), names.end(), [](string a, string b) { // using C++11 lambda function, note that you have to compile this file using g++ -std=c++11 sortofsorting.cpp
      if (a[0] != b[0]) return a[0] < b[0];
      return a[1] < b[1];
    }); // O(N log N)
    if (!FirstTestCase) printf("\n");
    FirstTestCase = false;
    for (auto &name : names) // O(N), I am using C++11 range-based for loop, I use & to avoid copying the value
      cout << name << endl;
  }
  return 0;
}

//Custom comparator: https://www.geeksforgeeks.org/stable_sort-c-stl/
//By default, sorting returns ascending order
//Therefore, default comparator returns true if 1st item is smaller
//Your custom comparator MUST return true if the 1st item is smaller
bool compareTwoChar(const string& s1, const string& s2){
    char a1 = s1[0], a2 = s2[0], b1 = s1[1], b2 = s2[1];
    if (a1 < a2 || a1 > a2) 
        return a1 < a2;
    else // (a1 == a2) 
        return b1 < b2;
}

int main(){
    // freopen("sample.in", "r", stdin);
    int n;
    while (cin >> n){ //while(cin >> n , n) -> Read n and use n as the test case for while loop 
        if(n == 0) break;
        vector<string> names(n);
        //When initializing vector with size, the vector is initialized to be the size with each element initialized to default value
        //In this case, empty string
        //To initalize the value you cannot do names.push_back() because all the elements will be pushed to the end of vector
        //This will cause the extra elements to be inserted besides the originally initialized elements (empty strings)
        //This will cause the size of vector to be larger than the size you intended
        //To initalize, do the below way OR use name[0] = "string", name[1] = "string" .... with for loop
        for(string& name : names){
            cin >> name;
            //cout << name << endl;
        }
        stable_sort(names.begin(), names.end(), compareTwoChar);
        for(string& name : names){
            cout << name << endl;
        }
        cout << endl;
    }

    return 0;
}

