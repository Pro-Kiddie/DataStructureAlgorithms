//Problem: https://nus.kattis.com/problems/gearchanging

// 50 / 11 = 4.54 -> back go 4.54 rounds -> lightest
// 50 / 12 = 4.16 -> back go 4.16 rounds -> heavier
// Percentage increase = (4.54 - 4.16)/4.16 * 100 = 9%
// From heaviest to lightest
// (bigger - smaller) / smaller > p

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n, m;
    double p;
    cin >> n >> m;
    cin >> p;
    p /= 100;
    vector<int> front(n);
    vector<int> back(m);
    vector<double> ratios; // double result in certain amout of precision -> which might be inaccurate when calculating percentage
    // can use vector<pair<int,int>>, where pair(front_teeth, back_teeth) -> use custom comparator on the pair ratio directly -> so no lost of precision
    // [] (pair<int,int> a, pair<int,int>b){
    //      //cannot divide here! same problem
            // we a.first * b.second < b.first * a.second to avoid division -> multiplication no loss of precision
            // first is nom, second denom
    //}
    
    for(int& t : front){
        cin >> t;
    }
    for(int& t : back){
        cin >> t;
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ratios.push_back(front[i]/(double)back[j]);
        }
    }
    
    sort(ratios.begin(), ratios.end());
    double pre_ratio = ratios[0];
    bool failed = false;
    for(int i = 1; i < ratios.size(); i++){
        if( (pre_ratio + pre_ratio*p) < ratios[i]) failed = true;
        pre_ratio = ratios[i];
    }
    
    if(failed) cout << "Time to change gears!";
    else cout << "Ride on!";
    
    return 0;


// Attempt 1:

    //for(int t : front) cout << t << " ";
    
    //sort(front.begin(), front.end()); //34, 50
    //sort(back.begin(), back.end(), greater<int>()); // 32, 28, ..
    // Wrong! -> Cannot sort first!
    // Because E.g the lightest ratio for 34 might be _lighter_ than the haviest ratio of 50 -> Not From Heaviest to Lightest Anymore
    
    //from heaviest to lightest
//  double pre_ratio = front[0]/(double)back[0];
//  bool failed = false;
//  for(int i = 0; i < front.size(); i++){
//      for(int j = 0; j < back.size(); j++){
//          double ratio = (front[i] / (double)back[j]);
//          double percentage = (ratio - pre_ratio)/pre_ratio * 100;
//          if(percentage > p) {
//              cout << "Time to change gears!";
//              failed = true;
//              break;
//          }
//          pre_ratio = ratio;
//      }
//      if(failed) break;
//  }
//  if (!failed) cout << "Ride on!";
    
    
    
    //for(int t : front) cout << t << " ";
        
}