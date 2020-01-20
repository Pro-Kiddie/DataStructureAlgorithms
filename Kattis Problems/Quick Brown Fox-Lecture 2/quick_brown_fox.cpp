//Problem: https://nus.kattis.com/problems/quickbrownfox

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(){
    //Read in the file
    //std::ifstream infile("a.in");
    //Ignore first line, which is the size of strings in the file
    //infile.ignore(1, '\n'); //Ignore max 1 character until '\n' delimiter is met; delimiter will be ignore too
    int size;
    std::cin >> size;
    std::cin.ignore();//Skip the newline character followed after size
    //Create an vector of strings 
    std::vector<std::string> data;
    std::string line;
    //Store each line in the vector as an element
    while(size > 0){
        std::getline(std::cin, line);
        data.push_back(line);
        //std::cout << line << std::endl;
        size--;
    }
    //Create a 1D boolean array of size 26; index 0 represents "a"; False not present, True present
    //Loop through the vector
    for(std::string& s : data){
        //Loop through each character of the string
        bool alphabets[26] = {false};    
        int set = 0;
        for(char c : s){
            //If it is non-alphabetical, continue
            //Convert to lowercase
            //tolower() Converts c to its lowercase equivalent if c is an uppercase letter and has a lowercase equivalent. If no such conversion is possible, the value returned is c unchanged.
            int temp = std::tolower(c) - 'a';
            //Characters before 'a' will have a value < 0 and Characters after 'z' will have a value => 26 -> Obtained index
            //Set the character's value to True
            if(temp >= 0 && temp < 26 && !alphabets[temp]){
                alphabets[temp] = true;
                set++;
            }
        }
        //If set is equal to 26, all alphabets has being set/used
        if(set == 26) std::cout << "pangram" << std::endl;
        else{
            std::cout << "missing ";
            //Loop through the boolean array, if False, print out the missing character
            for(int i=0; i<26; i++){
                if(!alphabets[i]){
                    std::cout << (char)(i + 'a');
                }
            }
            std::cout << std::endl;
        }
    }
    //std::cout << data.size() << std::endl;
    //infile.close();
    return 0;
}

//Lecture 2
//ios::sync_with_stdio(false); cin.tie(NULL);
//C++ io routines are slower than C
//Use the above line to speed up C++ iostream -> Optimization

// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//   ios::sync_with_stdio(false); cin.tie(NULL);
//   int N; cin >> N; cin.get(); // consume \n
//   while (N--) {
//     string line; getline(cin, line); // read entire line
//     bool char_exist[26];
//     for (int i = 0; i < 26; ++i)
//       char_exist[i] = false;
//     for (int i = 0; i < line.length(); ++i) { // check each char
//       char ch = tolower(line[i]); // convert to lowercase
//       if (!isalpha(ch)) continue; // not ['a'..'z'], skip
//       char_exist[ch-'a'] = true;
//     }
//     bool is_pangram = true;
//     for (int i = 0; i < 26; i++)
//       is_pangram = is_pangram & char_exist[i];
//     if (is_pangram)
//       cout << "pangram" << endl;
//     else {
//       cout << "missing ";
//       for (int i = 0; i < 26; i++)
//         if (!char_exist[i])
//           cout << (char)('a'+i);
//       cout << endl;
//     }
//   }
//   return 0;
// }

//Version 2 of Answer - OOP
// #include <bits/stdc++.h>
// using namespace std;

// class pangram {
// private:
//   vector<bool> char_exist;

// public:
//   pangram(string line) {
//     char_exist.assign(26, false);
//     for (int i = 0; i < line.length(); ++i) { // check each char
//       char ch = tolower(line[i]); // convert to lowercase
//       if (!isalpha(ch)) continue; // not ['a'..'z'], skip
//       char_exist[ch-'a'] = true;
//     }
//   }

//   bool is_pangram() {
//     bool ans = true;
//     for (int i = 0; i < 26; i++)
//       ans &= char_exist[i];
//     return ans;
//   }

//   bool is_exist(char ch) {
//     return char_exist[ch-'a'];
//   }
// };

// int main() {
//   ios::sync_with_stdio(false); cin.tie(NULL);
//   int N; cin >> N; cin.get(); // consume \n
//   while (N--) {
//     string line; getline(cin, line); // read entire line
//     pangram p(line);
//     if (p.is_pangram())
//       cout << "pangram" << endl;
//     else {
//       cout << "missing ";
//       for (int i = 0; i < 26; i++)
//         if (!p.is_exist((char)('a'+i)))
//           cout << (char)('a'+i);
//       cout << endl;
//     }
//   }
//   return 0;
// }

