//Problem: https://open.kattis.com/problems/baconeggsandspam

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("sample.in", "r", stdin);
    int n; cin >> n; cin.get();
    while(n != 0){
        string line, name, dish;
        map<string, set<string>> report;
        for(int i = 0; i < n; i++){
            getline(cin, line);
            stringstream iss(line);
            iss >> name;
            while(iss >> dish){
                auto itr = report.find(dish);
                if(itr == report.end()){
                    set<string> names;
                    names.insert(name);
                    report[dish] = names;  
                }
                else{
                    itr->second.insert(name);
                }
            }
        }
        for(auto& p : report){
            cout << p.first << " ";
            for(auto& name : p.second) cout << name << " ";
            cout << endl;
        }
        cout << endl;
        cin >> n; cin.get();
    }
    return 0;
}