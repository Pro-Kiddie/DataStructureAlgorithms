//Problem: https://github.com/mpfeifer1/Kattis/blob/master/display.cpp

#include <iostream>
#include <array>
#include <string>

using namespace std;

void addChar(array<string,7>& display, const char& c){
    switch(c){
    case '0':
        display[0].append("+---+");
        display[1].append("|   |");
        display[2].append("|   |");
        display[3].append("+   +");
        display[4].append("|   |");
        display[5].append("|   |");
        display[6].append("+---+");
        break;
    case '1':
        display[0].append("    +");
        display[1].append("    |");
        display[2].append("    |");
        display[3].append("    +");
        display[4].append("    |");
        display[5].append("    |");
        display[6].append("    +");
        break;
    case '2':
        display[0].append("+---+");
        display[1].append("    |");
        display[2].append("    |");
        display[3].append("+---+");
        display[4].append("|    ");
        display[5].append("|    ");
        display[6].append("+---+");
        break;
    case '3':
        display[0].append("+---+");
        display[1].append("    |");
        display[2].append("    |");
        display[3].append("+---+");
        display[4].append("    |");
        display[5].append("    |");
        display[6].append("+---+");
        break;
    case '4':
        display[0].append("+   +");
        display[1].append("|   |");
        display[2].append("|   |");
        display[3].append("+---+");
        display[4].append("    |");
        display[5].append("    |");
        display[6].append("    +");
        break;
    case '5':
        display[0].append("+---+");
        display[1].append("|    ");
        display[2].append("|    ");
        display[3].append("+---+");
        display[4].append("    |");
        display[5].append("    |");
        display[6].append("+---+");
        break;
    case '6':
        display[0].append("+---+");
        display[1].append("|    ");
        display[2].append("|    ");
        display[3].append("+---+");
        display[4].append("|   |");
        display[5].append("|   |");
        display[6].append("+---+");
        break;
    case '7':
        display[0].append("+---+");
        display[1].append("    |");
        display[2].append("    |");
        display[3].append("    +");
        display[4].append("    |");
        display[5].append("    |");
        display[6].append("    +");
        break;
    case '8':
        display[0].append("+---+");
        display[1].append("|   |");
        display[2].append("|   |");
        display[3].append("+---+");
        display[4].append("|   |");
        display[5].append("|   |");
        display[6].append("+---+");
        break;
    case '9':
        display[0].append("+---+");
        display[1].append("|   |");
        display[2].append("|   |");
        display[3].append("+---+");
        display[4].append("    |");
        display[5].append("    |");
        display[6].append("+---+");
        break;
    case ':':
        display[0].append(" ");
        display[1].append(" ");
        display[2].append("o");
        display[3].append(" ");
        display[4].append("o");
        display[5].append(" ");
        display[6].append(" ");
    }
}

void addSpace(array<string,7>& display){
    for(string& s : display){
        s.append("  ");
    }
}

int main(){
    //freopen("sample.in","r",stdin);
    string line;
    while(getline(cin,line)){
        if(line.compare("end") == 0) {
            cout << line << endl;
            break;
        }
        array<string,7> display;
        int index = 0;
        for (char& c : line){
            addChar(display, c);
            if(index < 4){
                addSpace(display);
                index++;
            }
        }
        for(string& s : display) cout << s << endl;
        cout << endl << endl;
    }

    return 0;
}