//Problem: https://open.kattis.com/problems/compoundwords

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("sample.in", "r", stdin);
    string word;
    set<string> results;
    vector<string> words;
    while(cin >> word){
        words.push_back(word);
    }
    for(int i = 0; i < words.size(); i++){
        for(int j = 0; j < words.size(); j++){
            if(j == i) continue;
            string cw = words[i];
            cw.append(words[j]);
            results.insert(cw); // log N
        }
    }
    // for(auto& s : words) cout << s << endl;
    auto itr = results.begin();
    for(; itr != results.end(); itr++){
        cout << *itr << endl;
    }
    return 0;
}