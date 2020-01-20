//Problem: https://open.kattis.com/problems/traveltheskies

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("2.in", "r", stdin);
    int k, n, m; cin >> k >> n >> m; // k = airpot, n = days, m = flights
    
    // For each day, there will be an Adjacency List to store flights
    vector<vector<vector<pair<int, int>>>> dayFlights(n, vector<vector<pair<int, int>>>(k));
    
    // Populate the ALs on each day
    for(int i = 0; i < m; i++){
        int u, v, d, z; cin >> u >> v >> d >> z; // u = departure airport, v = arrival airport, d = day of flight, z = capacity
        dayFlights[--d][--u].push_back(make_pair(--v, z)); // -- because 0-based indexing
    }

    // For each day, the number of customers arrive at each airpot
    int arrival[n][k] = {0};

    // Populate the arrival
    for(int i = 0; i < n*k; i++){
        int a, b, c; cin >> a >> b >> c; // a = airpot, b = day, c = customers arrived
        arrival[--b][--a] = c;
    }

    // At start of day, current no of customer at each airpot
    vector<int> current(k, 0);

    // At end of the day, after flight, the no of customer flew ro each aiport which will be added to next day's current customer which can flew again
    vector<int> next(k, 0);

    // For each day, simulate the flights
    for(int i = 0; i < n; i++){ // i = day
        // Populate the customers at each airport at the start of day
        for(int j = 0; j < k; j++) {
            current[j] += arrival[i][j];        
        }

        // On this day, for each city, fly the flight
        for(int j = 0; j < k; j++){
            for(auto& flight : dayFlights[i][j]){
                // j = source airport, flight.first = destination airpot, flight.second = capacity
                current[j] -= flight.second; // Fly the customer from source airport -> Since flight should be filled
                if (current[j] < 0){ // Not enough people to fill the flight -> No point continuing
                    cout << "suboptimal";
                    return 0;
                }
                next[flight.first] += flight.second; // Flew sucessful and increase destination airport's customer
                // Must be += but not "=" because there might be other flight flying to same destination city! Cannot overwrite
            }
        }

        // Get ready the number of people at each airport on next day
        for(int j = 0; j < k; j++){
            current[j] += next[j]; // Must += but not = because there might customer at each airport who did not fly today
            next[j] = 0;    
        }
    }
    cout << "optimal";
    return 0;
}