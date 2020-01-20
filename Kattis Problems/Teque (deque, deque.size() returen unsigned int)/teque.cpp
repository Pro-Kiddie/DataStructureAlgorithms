//Problem: https://nus.kattis.com/problems/teque

#include <iostream>
#include <deque>
#include <string>

typedef unsigned int ui;

using namespace std;

class teque{
private:
    deque<ui> firstHalf;  
    deque<ui> secondHalf;
    void rebalance(){
        // else if (secondHalf.size() - firstHalf.size() > 1){ 
        // deque.size() returns an UNSIGED INT!!!
        // If difference is negative value, which is stored in unsigned int will be a huge positive number!
        // Always CHECK THE DOCUMENTATION!!

        if(firstHalf.size() == secondHalf.size()) return;
        else if(firstHalf.size() > secondHalf.size() + 1){
            secondHalf.push_front(firstHalf.back());
            firstHalf.pop_back();
        }
        else if (secondHalf.size() > firstHalf.size()){ //secondHalf.size() will alway be equal or smaller than firstHalf 
            // In this way, the secondHalf.front() will always be median
            // Look below how Median is calculated
            firstHalf.push_back(secondHalf.front());
            secondHalf.pop_front();
        }
        //debug();
    }
    void debug(){
        for(auto ui : firstHalf) cout << ui << " ";
        cout << endl;
        for(auto ui : secondHalf) cout << ui << " ";
        cout << endl;
    }
public:
    teque() {};
    void push_back(ui ele){
        secondHalf.push_back(ele);
        rebalance();
    }
    void push_front(ui ele){
        firstHalf.push_front(ele);
        rebalance();
    }
    void push_middle(ui ele){
        secondHalf.push_front(ele);
        rebalance();
    }
    ui get (ui index) const {
        if(index < firstHalf.size()) return firstHalf[index];
        else //if(index >= firstHalf.size()) 
            return secondHalf[index-firstHalf.size()];
    }
    ui getMedianIndex() const {
        //Always draw how the MedianIndex changes as the Total Size changes to understand the pattern
        //Median will always be the front of secondHalf
        if (firstHalf.size() + secondHalf.size() == 1) return 0;
        else return (firstHalf.size() + secondHalf.size()+1)/2;
    }
};

int main(){
    // freopen("1.in","r", stdin);
    int N; cin >> N; cin.get();
    teque result = teque();
    while(N--){
        string command; cin >> command;
        ui num; cin >> num;
        if(command == "push_back"){
            result.push_back(num);
        }
        else if (command == "push_front"){
            result.push_front(num);
        }
        else if (command == "push_middle"){
            result.push_middle(num);
        }
        else if (command == "get"){
            ui ele = result.get(num);
            cout << ele << endl;
        }
    }
    return 0;
}