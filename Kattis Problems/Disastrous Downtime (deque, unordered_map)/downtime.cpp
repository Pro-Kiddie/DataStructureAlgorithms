//Problem: https://nus.kattis.com/problems/downtime

//Find maximum number of request that exists between any 2 requests that are within 1 sec apart

#include <iostream>
#include <deque>
#include <math.h>

using namespace std;

void delete_front(deque<int>& requests){
    if(requests.empty() || requests.back() - requests.front() < 1000) return;
    else{
        requests.pop_front();
        delete_front(requests);
    }
}

int main(){
    //freopen("2.in","r",stdin);
    int n; cin >> n;
    int k; cin >> k;
    deque<int> requests;
    int best = 0;
    for(int i = 0; i < n; ++i){
        int t; cin >> t;
        requests.push_back(t);
        //cout << requests.front() << " " << requests.back();
        // When pushed only 1 element, request.front() == request.back()
        if(requests.back() - requests.front() >= 1000){
            // The t that was just pushed in this iteration caused the exceed >= 1000
            // The maximum requests is just the current size - 1 
            best = requests.size()-1 > best ? requests.size()-1 : best;
            delete_front(requests);
        }
        else if (i == n-1){
            // Need to update best when last round
            // As the difference between back and front might be < 1000 but the size of deque is > best
            delete_front(requests);
            best = requests.size() > best ? requests.size() : best;
        }
    }
    //cout << best << endl;
    cout << ceil(best/(double)k);
    return 0;
}

// Another Solution:
// Each millisec is a key in the unordered_map
// The value of the unordered_map will be frequency of requests appear at that particular sec
// since 0 < t < 100,000 -> Not a lot! Can use array too
// Unordered map is implemented using Hash_table
// On average, the cost of search, insert and delete from hash table is O(1)
// unordered_map vs map : 
// map (like set) is an ordered sequence of unique keys whereas in unordered_map key can be stored in any order, so unordered.
// Map is implemented as balanced tree structure that is why it is possible to maintain an order between the elements (by specific tree traversal)

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, m;
//     cin >> n >> m;

// Populate the unordered_map with different t
//     unordered_map<int,int> seen;
//     for(int i = 0; i < n; i++) {
//         int temp;
//         cin >> temp;
//         seen[temp]++;
//     }

// For the first 1000 millisec, get the total number of requests
//     int processing = 0;
//     for(int i = 0; i <= 999; i++) {
//         processing += seen[i];
//     }

// Process the rest of millisec 1 by 1 until 100 000, 
// if a request exists add to no of requests within the 1000 millisec
// Also minus the no of requests from the beginning of the 1000 millisec
// This will give the curr no of requests within the 1000 millisec
//     int best = processing;
//     for(int i = 1000; i <= 100000; i++) {
//         processing += seen[i];
//         processing -= seen[i-1000];
//         best = max(best, processing);
//     }

//     cout << ceil(best/(double)m) << endl;
// }