#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

int main(){
    vector<list<string>> strings(2);
    strings[0].push_back("hello");
    strings[1].push_back("world");
    strings[0].splice(strings[0].end(), strings[1]);
    for(auto s : strings[1]){
        cout << s << endl;
    }
    return 0;
}