//Problem: https://nus.kattis.com/sessions/syek8x/problems/measurement

#include <iostream>
#include <array>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    //freopen("sample2.in", "r", stdin);

    array<int,8> factors = {1,1000,12,3,22,10,8,3};
    array<string,8> units = {"thou","inch","foot","yard","chain","furlong","mile","league"};
    array<string,8> units_sf = {"th","in","ft","yd","ch","fur","mi","lea"};

    int value;
    cin >> value;
    string u1, rubbish, u2;
    cin >> u1 >> rubbish >> u2;

    //find index of u1
    auto itr = find(units.begin(), units.end(), u1);
    int index;
    if (itr == end(units)){
        itr = find(units_sf.begin(), units_sf.end(), u1);
        index = distance(units_sf.begin(), itr);
    }else{
        index = distance(units.begin(), itr);
    }

    long double thou = value;
    //Multiply all the factors up to the corresponding factor of u1 to convert to thou unit
    for(int i=0; i <= index; ++i) thou *= factors[i];
    //cout << thou << endl;

    //find index of u2
    itr = find(units.begin(), units.end(), u2);
    if (itr == end(units)){
        itr = find(units_sf.begin(), units_sf.end(), u2);
        index = distance(units_sf.begin(), itr);
    }else{
        index = distance(units.begin(), itr);
    }

    //Divide all the factors up to the corresponding factor of u2 to convert thou unit to u2
    for(int i=0; i <= index; ++i) thou /= factors[i];

    cout << fixed; //To make cout.precision() function to count precision starting after decimal place
    cout.precision(13);
    cout << thou << endl;

    return 0;
}