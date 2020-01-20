//Problem: https://open.kattis.com/problems/thegrandadventure

#include <iostream>
#include <stack>
#include <map>
#include <string>

using namespace std;

int main(){
    //freopen("sample02.in","r", stdin);
    int n; cin >> n; cin.get();
    map<char, char> getItem = {{'b', '$'}, {'t', '|'}, {'j', '*'}};
    while (n--){
        string route;
        getline(cin, route);
        stack<char> bag;
        bool failed = false;
        for(char& c : route){
            if(c == '$' || c == '|' || c == '*') bag.push(c);
            else if (c == 'b' || c == 't' || c == 'j'){
                if (bag.empty() || getItem[c] != bag.top()){
                    cout << "NO" << endl;
                    failed = true;
                    break;
                }
                else bag.pop(); 
            }
            else if (c == '.') continue;
        }
        if (!failed) cout << (bag.empty() ? "YES" : "NO") << endl;    
    }
    return 0;
}

// Using switch
// int main() {
//   ios::sync_with_stdio(false); cin.tie(NULL);
//   int n; cin >> n; cin.get();
//   while (n--) {
//     string a; getline(cin, a);
//     stack<char> bag;
//     bool success = true; // assume Jim can complete his adventure
//     for (auto &ch : a) {
//       switch (ch) {
//         case '$': // Money
//         case '|': // Incense
//         case '*': // Gem
//           bag.push(ch); // either of those 3, put to my bag in LIFO (stack) order
//           break;
//         case 't': // a Trader, wants ... Incense
//         case 'j': // a Jeweler, wants Gem/Jewel
//         case 'b': // a Banker, wants $$$ Money
//           char wanted = '|'; // assume this person wants 'I' (a trader)
//           if (ch == 'j') wanted = '*'; // no, that person is a Jeweler, wants *
//           if (ch == 'b') wanted = '$'; // a banker, wants $

            // Unfortunately, Jim’s backpack isn’t very ergonomic and so he can only reach the item he most recently put in it. 
            // In other words, the items below are inaccessible until he’s given away the one on top
//           while (!bag.empty() && (bag.top() != wanted)) // frantically search for the req item // keep popping until either backpack is empty (failure) or top of backpack == want
//             bag.pop(); 
          
//           if (bag.empty())
//             success = false;
//           else
//             bag.pop(); // give that item (== wanted) to that person
//             // continue with adventure

//           break;
//       }
//     }
//     success &= bag.empty(); // bag must be empty at the end
//     cout << (success ? "YES" : "NO") << endl;
//   }
//   return 0;
// }
