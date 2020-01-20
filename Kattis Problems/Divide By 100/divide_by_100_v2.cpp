//Problem: https://open.kattis.com/problems/divideby100

#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main(){
    // freopen("divideby100-04.in", "r", stdin);
    string n, m;
    cin >> n >> m;
    int length = m.size() - 1;
    deque<char> results;
    if (n.length() >= m.length()){
        for(int i = n.size()-1, j=0 ; i >= 0; i--, j++){
            if (j == length) results.push_front('.');
            results.push_front(n[i]);
        }
    }
    else{ // n.length() < m.length()
        results.push_back('0');
        results.push_back('.');
        unsigned int diff = length - n.length();
        for(int i = 0; i < diff; i++){
            results.push_back('0');
        }
        for(char& c : n){
            results.push_back(c);
        }
    }
    
    while(results.back() != '.' && results.back() == '0'){
        results.pop_back();
    }
    if (results.back() == '.') results.pop_back();

    for(char& c : results) cout << c;

    return 0;
}