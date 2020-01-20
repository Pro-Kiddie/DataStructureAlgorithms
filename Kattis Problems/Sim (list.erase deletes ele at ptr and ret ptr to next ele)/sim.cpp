//Matric number:  
//Full name:  
//Lab group number:  
//Lab group TA:  

#include <iostream>
#include <list>

using namespace std;

int main(){
    freopen("2.in","r",stdin);
    int tc; cin >> tc; cin.ignore();
    while(tc--){
        string line;
        getline(cin, line);
        //int index = 0;
        list<char> result;
        list<char>::iterator itr;
        itr = result.end();
        // cout << (itr == result.begin()) << endl; --> When list empty, begin() = end()
        for(char& c : line){
            if((result.empty() && c == '<') || (itr==result.begin() && c == '<') ) continue;  // Case where result not empty and itr at begin and '<' is pressed 
            else if(c == '<') {
                if(itr == result.end()) result.pop_back();
                else {
                    itr = result.erase(--itr); //list.erase() earses the ele pointing by ptr and return an itr to the ele after the ele being erased
                }
            }
            else if(c == ']') itr = result.end();
            else if(c == '[') itr = result.begin();
            else result.insert(itr, c);
        }
        for(auto itr = result.begin(); itr != result.end(); itr++){
            cout << *itr;
        }
        cout << endl;
    }
    return 0;
}