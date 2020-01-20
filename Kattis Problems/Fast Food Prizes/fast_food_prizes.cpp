//Problem: https://nus.kattis.com/problems/fastfood 

//Predefined-Rules: 
//1. No two prizes will require the same type of stickers -> Do not need to consider if a sticker can be used to claim two type of prizes and must take the prize with higher value 
//2. There may be some stickers cannot be used to claim a cash prize
   
//THE NO OF TIMES I CAN CLAIM A PRIZE = THE DIFFERENT TYPES OF STICKER REQUIRED FOR THAT STICKER, WHICH TYPE I HAVE THE LOWEST NO

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
typedef long long ll; //64bits Integer

int main(){
    freopen("01.in", "r", stdin);
    //Read in the noOfCases -> This is the number of outer loop is going to run 
    ll noOfCases;
    cin >> noOfCases;
    while(noOfCases--){
        //For each case, read in the noOfPrizes and noOfStickerTypes
        ll noOfPrizes, noOfStickerTypes;
        cin >> noOfPrizes >> noOfStickerTypes;
        vector<vector<ll>> prizes(noOfPrizes); //Store the different prizes in this case in a 2D array
        vector<ll> values(noOfPrizes); //Store the different values of each prize in an array; values[0] = value for 1st type of prize
        //Run a loop noOfPrizes times 
        for(ll i=0; i < noOfPrizes; i++ ){
            //Read in the noStickerTypeRequired for each prize
            ll noStickerTypeRequired;
            cin >> noStickerTypeRequired;
            prizes[i].resize(noStickerTypeRequired); //Resized the dynamic array to size required and initialized with default value
            //Run in a loop noStickerTypeRequired times
            for(ll& j : prizes[i]){
                //Read in the StickerTypes
                cin >> j;
                //Must decreat each j by 1 to have 0-based index as the type of stickers required in each prize is 1-based index
                j--;
            }
            //Read in the Value of the prize
            cin >> values[i];
        }
        // for(vector<ll>& i: prizes){
        //     for(ll& j : i){
        //         cout << j << ",";
        //     }
        //     cout << endl;
        // }

        vector<ll> stickers(noOfStickerTypes);
        //Run a loop noOfStickerTypes times
        for(ll i=0; i < noOfStickerTypes; ++i){
            //Read in the no of stickers I have for different type of stickers
            //index 0 of array is type 1, value is the no of stickers I have for that type
            //0-based index
            cin >> stickers[i];
        }
        // for(ll& i: stickers){
        //     cout << i << ",";
        // }
        // cout << endl;

        ll total=0;
        //Run a loop of noOfPrizes times -> find out the No of times i can claim this prize with the amt of stickers I have
        for(ll i=0; i < noOfPrizes; i++){
            //For each StickerType required in a prize, use it as the index to access the different type of stickers I have
            ll lowest = stickers[prizes[i][0]];
            //Find out the StickerType I have the lowest no
            for(ll j : prizes[i]){
                lowest = stickers[j] < lowest ? stickers[j] : lowest;
            } 
            //Value I can claim for each prize = lowest no * Value
            ll value = lowest * values[i];
            //Add the Value to total amt
            total += value;
        }
        cout << total << endl;
   }
    return 0;
}

    
    
