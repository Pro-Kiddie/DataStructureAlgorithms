//Problem: https://nus.kattis.com/problems/chopin

#include <iostream>
#include <string>

using namespace std;

int main() {
    // freopen("sample.in","r",stdin);
    string note, tonality;
    int case_no = 0;
    while (cin >> note) {
        cin >> tonality;
        cout << "Case " << ++case_no << ": ";
        if (note.length() == 1) {
            cout << "UNIQUE" << endl;
        } else {
            //note.length() == 2 > Confirm has alternate names
            char key = note[0];
            char accidental = note[1];
            if (accidental == '#') {
                //Next note
                key = key == 'G' ? 'A' : (char)(key + 1);
                accidental = 'b';
            } else if (accidental == 'b') {
                //Previous note
                key = key == 'A' ? 'G' : (char)(key - 1);
                accidental = '#';
            }
            cout << key << accidental << " " << tonality << endl;
        }
    }

    return 0;
}