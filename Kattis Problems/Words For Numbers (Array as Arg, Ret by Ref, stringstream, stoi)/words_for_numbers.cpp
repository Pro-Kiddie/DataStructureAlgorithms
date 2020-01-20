//Problem: https://nus.kattis.com/sessions/syek8x/problems/wordsfornumbers

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// string* get_Words(const string& num_token, string* a, string* tenth){
// //Return by reference will be string*, but need to create the returned value on heap and must delete
//     //cout << num_token.length();
//     int num = stoi(num_token);
//     if (num <= 20) return &a[num-1];
//     else{
//         char first, second; first=num_token[0]; second=num_token[1];
//         if(second == '0') return &tenth[(int)(first - '2')];
//         else{
//             string result;
//             result.append(tenth[(int)(first - '2')]);
//             result.append("-");
//             result.append(a[(int)(second - '1')]);
//             return new string(result);
//         }
//     } 
// }

string get_Words(const string& num_token, string* a, string* tenth){
//Return by value
    //cout << num_token.length();
    int num = stoi(num_token);
    if (num <= 20) return a[num];
    else{
        char first, second; first=num_token[0]; second=num_token[1];
        if(second == '0') return tenth[(int)(first - '2')];
        else{
            string result;
            result.append(tenth[(int)(first - '2')]);
            result.append("-");
            result.append(a[(int)(second - '0')]);
            return result;
        }
    } 
}

int main(){
    //freopen("sample.in","r",stdin);
    string a[] = {"zero","one","two","three","four","five","six","seven","eight","nine","ten",
                    "eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen", "twenty"};
    string tenth[] = {"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

    string line;
    while(getline(cin, line)){
        stringstream iss(line);
        string token;
        int first_token = 0;
        while(iss >> token){
            //check if the token contains alphabet
            bool digit_token = true;
            if(!isdigit(token[0])) digit_token = false;
            if (!digit_token) {
                cout << token << " ";
                first_token++;
                continue;
            }
            //handle the numeric tokens
            //check if last character is a punctuation
            //if(!isdigit(token[token.length()-1])) token = token.substr(0, token.length() == 2 ? 1 : 2);
            string result = get_Words(token, a, tenth);
            if (first_token == 0){
                result[0] = toupper(result[0]);
                first_token++;
            }
            cout << result << " ";
        }
        cout << endl;

    }

    return 0;
}