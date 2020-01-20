//Problem: https://nus.kattis.com/sessions/syek8x/problems/luhnchecksum

#include <iostream>
#include <string>
using namespace std;

int main(){
    //freopen("sample.in", "r", stdin);
    int cases;
    cin >> cases;
    cin.ignore(); //Skip the \n
    while(cases--){
        string s;
        getline(cin, s);
        int sum = 0;
        for(int i=s.length()-1, j=1; i >= 0; --i, ++j){
            //cout << (int)(s[i] - '0') << endl;
            if(j % 2 == 0) {
                int d = (int)(s[i] - '0') * 2;
                if (d > 9){
                    string ds = to_string(d);
                    d = (int)(ds[0] - '0') + (int)(ds[1] - '0');
                    sum += d;
                }else{
                    sum += d;
                }
            }
            else{
                sum += (int)(s[i] - '0');
            }
        }
        cout << (sum % 10 == 0 ? "PASS" : "FAIL") << endl;
    }

    return 0;
}