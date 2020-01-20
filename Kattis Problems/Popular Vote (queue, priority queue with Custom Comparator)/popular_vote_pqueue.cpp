
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

class Compare {
public:
    bool operator() (const pair<int,int>& lhs, const pair<int,int>& rhs) const {
        //learn to use typedefine pair<int,int> p;
        return lhs.second < rhs.second;
    }
};

int main(){
    freopen("vote-01.in","r",stdin);
    int t; cin >> t;
    //pair(candidate_number, votes)
    //customer comparator when comparing pairs -> Candidate with higher vote has higher priority
    while(t--){
        //Template of Priority Queue <class Type, class Container=vector<Type>,class Compare=less<typename Container::value_type>>
        //Queue in std template implemented using vector
        priority_queue<pair<int,int>, vector<pair<int,int>>, Compare> results;
        int n; cin >> n;
        double sum;
        for(int i = 1; i <= n; ++i){
            int vote; cin >> vote;
            results.push(make_pair(i,vote));
            sum += vote;
        }
        auto top = results.top();
        results.pop();
        if(top.second == results.top().second) cout << "no winner";
        else if(top.second/sum > 0.5) cout << "majority winner " << top.first;
        else cout << "minority winner " << top.first;
        cout << endl;
    }
    return 0;
}