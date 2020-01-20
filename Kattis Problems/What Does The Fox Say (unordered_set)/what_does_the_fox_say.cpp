//Problem: https://open.kattis.com/problems/whatdoesthefoxsay

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("b-sample.in", "r", stdin);
    int T; cin >> T; cin.get();
    while(T--){
        string line; getline(cin, line);
        stringstream iss(line);
        string sound;
        vector<string> recording;
        recording.reserve(100);
        while(iss >> sound) recording.emplace_back(sound);
        unordered_set<string> sounds(100);
        while(true){
            getline(cin, line);
            if(line == "what does the fox say?") break;
            iss.str(line);
            iss.clear();
            iss >> sound; iss >> sound; iss >> sound;
            sounds.insert(sound);
        }
        for(string& s : recording){
            if(sounds.find(s) == sounds.end()) cout << s << " ";
            else continue;
        }
        cout << endl;
    }
    return 0;
}