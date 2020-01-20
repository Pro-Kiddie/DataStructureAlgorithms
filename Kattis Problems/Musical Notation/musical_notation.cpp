//Problem: https://nus.kattis.com/sessions/syek8x/problems/musicalnotation

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void addColumn(vector<string>& output){
    output[0].push_back(' '); //G
    output[1].push_back('-'); //F
    output[2].push_back(' '); //E
    output[3].push_back('-'); //D
    output[4].push_back(' '); //C
    output[5].push_back('-'); //B
    output[6].push_back(' '); //A
    output[7].push_back('-'); //g
    output[8].push_back(' '); //f
    output[9].push_back('-'); //e
    output[10].push_back(' '); //d
    output[11].push_back(' '); //c
    output[12].push_back(' '); //b
    output[13].push_back('-'); //a
}

void addNote(vector<string>& output, const char& note){
    switch(note){
        case 'G':
            output[0][output[0].length()-1] = '*';
            break;
        case 'F':
            output[1][output[1].length()-1] = '*';
            break;
        case 'E':
            output[2][output[2].length()-1] = '*';
            break;
        case 'D':
            output[3][output[3].length()-1] = '*';
            break;
        case 'C':
            output[4][output[4].length()-1] = '*';
            break;
        case 'B':
            output[5][output[5].length()-1] = '*';
            break;
        case 'A':
            output[6][output[6].length()-1] = '*';
            break;
        case 'g':
            output[7][output[7].length()-1] = '*';
            break;
        case 'f':
            output[8][output[8].length()-1] = '*';
            break;
        case 'e':
            output[9][output[9].length()-1] = '*';
            break;
        case 'd':
            output[10][output[10].length()-1] = '*';
            break;
        case 'c':
            output[11][output[11].length()-1] = '*';
            break;
        case 'b':
            output[12][output[12].length()-1] = '*';
            break;
        case 'a':
            output[13][output[13].length()-1] = '*';
            break;
        default:
            cout << "Invalid Note: " << note << endl;
    }
}

int main(){
    vector<string> output = {"G: ",
                            "F: ",
                            "E: ",
                            "D: ",
                            "C: ",
                            "B: ",
                            "A: ",
                            "g: ",
                            "f: ",
                            "e: ",
                            "d: ",
                            "c: ",
                            "b: ",
                            "a: "};
    //freopen("sample02.in", "r", stdin);
    int n;
    cin >> n;
    while(n--){
        string note;
        cin >> note;
        addColumn(output);
        addNote(output, note[0]);
        if(note.length() > 1){
            for(int i=0; i < (int)(note[1]-'0')-1; ++i){
                addColumn(output);
                addNote(output, note[0]);
            }
        }

        //Between each pair of note, there should be a separating column, except for last note
        //last note, n already decremented to 0
        if (n != 0) addColumn(output);
    }

    for(string& line: output){
        cout << line << endl;
    }
    
    return 0;
}
