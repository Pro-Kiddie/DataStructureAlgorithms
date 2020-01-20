//Problem: https://nus.kattis.com/problems/filip

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//Using string method
int main(){
    //freopen("filip.dummy.3.in","r",stdin);
    ios::sync_with_stdio(false); cin.tie(NULL);
    string a, b;
    cin >> a >> b;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int c = stoi(a);
    int d = stoi(b);
    int out = c > d ? c : d;
    cout << out;

    return 0;
}

//O(1) as maximum 3 digits, merely a few division and assigning
int flip(int num){ //num is 3 digit numer ABC
    int a = num/100;
    int b = (num/10)%10;
    int c = num%10;
    return c*100+b*10+a;
}

//Using numeric method
int main() {
  ios::sync_with_stdio(false); cin.tie(NULL);
  int A, B; cin >> A >> B;
  int rA = flip(A), rB = flip(B); // "two or more call to the same piece of code, use a (function)" - paraphrase of famous CS quote from Edsger W Dijkstra
  cout << (rA < rB ? rA : rB) << endl;
  return 0;
}