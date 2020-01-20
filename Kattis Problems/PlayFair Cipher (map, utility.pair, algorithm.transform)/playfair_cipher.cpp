//Problem: https://github.com/mpfeifer1/Kattis/blob/master/playfair.cpp

#include <iostream>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    freopen("2.in", "r", stdin);
    string key, plaintext;
    getline(cin, key);
    getline(cin, plaintext);

    //Construct a map to store the encryption table
    //With key=alphabet, value={x-coord, y-coord} -> When loop through plaintext char, look for its coordinate in the table
    map<char, pair<int, int>> enc_table;
    //One more map to store the reverse encryption table
    //Key={x-coord, y-coord}, value=alphabet -> After getting the correct coordinate of ciphertext alphabet, retrive the alphabet
    map<pair<int, int>, char> rev_enc_table;

    //initialize the encryption table
    int x = 0, y = 0;
    for (char& c : key) {
        if (c == ' ')
            continue;
        if (enc_table.count(c) == 0) {
            enc_table[c] = make_pair(x, y);
            rev_enc_table[{x, y}] = c;  //Both way of initialization of a pair is fine
            //rev_enc_table[make_pair(x, y)] = c;
            y++;  //move to next posistion in enc_table;
            if (y > 4) {
                x++;  //move to next row
                y = 0;
            }
        }
    }
    for (char i = 'a'; i <= 'z'; ++i) {
        if (i == 'q')  // no 'q' will appear in plaintext
            continue;
        if (enc_table.count(i) == 0) {
            enc_table[i] = pair<int,int> (x, y);
            rev_enc_table[{x, y}] = i;
            y++;
            if (y > 4) {
                x++;
                y = 0;
            }
        }
    }

    //Print out the reverse encryption table; Iterate the map
    // for(auto itr = rev_enc_table.begin(); itr != rev_enc_table.end(); ++itr ){
    //     //for reverse enc table, key is coordinate
    //     cout << "(" << itr->first.first << "," << itr->first.second << ") character: " << itr->second << endl;
    // }

    //Remove all spaces in plaintext
    string s;
    for (char& c : plaintext) {
        if (c == ' ')
            continue;
        else
            s.push_back(c);
    }
    plaintext = s;

    //Insert 'x' if plaintext alphabet pair is same character
    s.clear();
    for (int i = 0; i < plaintext.length(); i += 2) {
        if (i == plaintext.length() - 1) {
            s.push_back(plaintext[i]); //If reach last character just push it to the back cannot compare with the next character
        } else {
            if (plaintext[i] == plaintext[i + 1]) {
                s.push_back(plaintext[i]);
                s.push_back('x');
                i--;
            } else {
                s.push_back(plaintext[i]);
                s.push_back(plaintext[i + 1]);
            }
        }
    }
    //Also insert 'x' if odd no
    if (s.length() % 2 == 1) s.push_back('x');
    plaintext = s;
    //cout << plaintext << endl;

    string ciphertext;
    for(int i = 0; i < plaintext.length(); i+=2){
        char a, b;
        a = plaintext[i];
        b = plaintext[i+1];
        int x1, y1, x2, y2;
        x1 = enc_table[a].first;
        y1 = enc_table[a].second;
        x2 = enc_table[b].first;
        y2 = enc_table[b].second;
        if (x1 == x2){ //two alphabet in same row
            ciphertext.push_back(rev_enc_table[{x1, (y1 + 1) % 5}]);
            ciphertext.push_back(rev_enc_table[{x1, (y2 + 1) % 5}]);
        }
        else if(y1 == y2){ //two alphabet in same column
            ciphertext.push_back(rev_enc_table[{(x1 + 1) % 5, y1}]);
            ciphertext.push_back(rev_enc_table[{(x2 + 1) % 5, y1}]);
        }
        else{ //two alphabet in different row and column
            ciphertext.push_back(rev_enc_table[{x1, y2}]);
            ciphertext.push_back(rev_enc_table[{x2, y1}]);
        }
    }
    //transform : Performs a transformation on given array/string
    //transform(Iterator inputBegin1, Iterator inputEnd1, Iterator inputBegin2, Iterator OutputBegin, binary_operation) 
    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::toupper);

    cout << ciphertext << endl;

    return 0;
}