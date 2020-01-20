
//Matric number:  
//Full name:  
//Lab group number:  
//Lab group TA:  

#include <bits/stdc++.h>

using namespace std;

struct PrefixRange {
    int totalCount;
    int boyCount;
    int girlCount;
    PrefixRange():totalCount(0), boyCount(0), girlCount(0){}
    PrefixRange(int total, int boy, int girl):totalCount(total), boyCount(boy), girlCount(girl){}
};

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    freopen("in.txt", "r", stdin);
    int cmd;
    map<string, int> babyNames;
    unordered_map<string,PrefixRange> records;
    while(cin >> cmd, cmd != 0){
        switch(cmd){
            case 1:{
                string name; cin >> name;
                int gender; cin >> gender;
                babyNames[name] = gender;
                for(auto itr2 = records.begin(); itr2 != records.end(); itr2++){
                    stringstream iss(itr2->first);
                    string start, end;
                    getline(iss,start,'_');
                    if (name < start) continue;
                    getline(iss, end);
                    if (name < end) {
                        itr2->second.totalCount++;
                        gender == 1 ? itr2->second.boyCount++ : itr2->second.girlCount++;
                    }
                }
                break;
            }
            case 2:{
                string name; cin >> name;
                auto itr1 = babyNames.find(name);
                for(auto itr2 = records.begin(); itr2 != records.end(); itr2++){
                    stringstream iss(itr2->first);
                    string start, end;
                    getline(iss,start,'_');
                    if (name < start) continue;
                    getline(iss, end);
                    if (name < end) {
                        int gender = itr1->second;
                        itr2->second.totalCount--;
                        gender == 1 ? itr2->second.boyCount-- : itr2->second.girlCount--;
                    }
                }
                babyNames.erase(itr1);
                break;
            }
            case 3:{
                string start, end;
                cin >> start >> end;
                int gender; cin >> gender;
                string prefixRange = start + string("_") + end;
                auto itr = records.find(prefixRange);
                if(itr == records.end()){
                    int totalCount = 0, boyCount = 0, girlCount = 0;
                    auto itr2 = babyNames.lower_bound(start);
                    while(itr2 != babyNames.end()){
                        if(itr2->first < end){
                            totalCount++;
                            if(itr2->second == 1) boyCount++;
                            else if(itr2->second == 2) girlCount++;
                        }
                        itr2++;
                    }
                    records[prefixRange] = PrefixRange(totalCount, boyCount, girlCount);
                    switch(gender){
                        case 0:
                            cout << totalCount << "\n";
                            break;
                        case 1:
                            cout << boyCount << "\n";
                            break;
                        case 2:
                            cout << girlCount << "\n";
                            break;
                    }
                }
                else{
                    switch(gender){
                        case 0:
                            cout << itr->second.totalCount << "\n";
                            break;
                        case 1:
                            cout << itr->second.boyCount << "\n";
                            break;
                        case 2:
                            cout << itr->second.girlCount << "\n";
                            break;
                    }
                }
            }
        }
    }
	return 0;
}