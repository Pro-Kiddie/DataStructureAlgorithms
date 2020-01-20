// Problem: https://open.kattis.com/problems/dyslectionary

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Compare {
    bool operator()(const string& lhs, const string& rhs) const {
        string lhs_r = lhs;
        reverse(lhs_r.begin(), lhs_r.end());
        string rhs_r = rhs;
        reverse(rhs_r.begin(), rhs_r.end());
        return lhs_r < rhs_r;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // // "String_literals" in C++ declared are const char[] -> CANNOT BE COMAPRED USING "<" and ">" directly!!!! USING strcmp() if u want to compare C string. Refer to your C Notes!!!
    // C++ STL string object CAN BE COMPARED DIRECTLY!
    // cout << ("B" < "A") << endl; //returns true which is WRONG!!!
    // // VS
    // cout << (string("AAAA") < string("B")) << endl; //returns true which is CORRECT!!!
    // cout << (string("B") < string("A")) << endl;

    // freopen("sample.in", "r", stdin);
    string word;
    int max_len = 0;
    vector<string> dict;
    while (getline(cin, word)) {
        if (word != "") dict.push_back(word);
        if (word.size() > max_len) max_len = word.size();
        // cout << dict.back() << endl;
        if (word == "") {
            // cout << "<blank line>" << endl;
            sort(dict.begin(), dict.end(), Compare());
            // char format[20];
            // sprintf(format, "%%%ds\n", max_len);
            // // printf("%10s\n", format);
            for (auto& i : dict) {
                string temp;
                temp.resize(max_len - i.length(), ' ');
                temp += i;
                swap(i, temp);
            }
            // for(int i = 0; i < dict.size(); i++) printf(format, dict[i].c_str());
            for (int i = 0; i < dict.size(); i++) cout << dict[i] << endl;
            cout << endl;
            dict.clear();
            max_len = 0;
        }
    }
    sort(dict.begin(), dict.end(), Compare());
    // char format[20];
    // sprintf(format, "%%%ds\n", max_len);
    for (auto& i : dict) {
        string temp;
        temp.resize(max_len - i.length(), ' ');
        temp += i;
        swap(i, temp);
    }
    for (int i = 0; i < dict.size(); i++) {
        cout << dict[i] << endl;
    }
    return 0;
}