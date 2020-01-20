#include <bits/stdc++.h>

using namespace std;

int main(){
//	freopen("1.in","r",stdin);
	int n; cin >> n;
	int k; cin >> k;
	stack<int> prePos;
	int index = 0;
	prePos.push(0);
	while(k--){
		string cmd;
		cin >> cmd;
		int num;
		if(cmd == "undo") {
			cin >> num;
			while(num--){
				prePos.pop();
			}
			index = prePos.top();
		}
		else{
			num = stoi(cmd);
			//if(num % n == 0 ) continue; //Wrong because never update stack which is an opeartion
			if(num > 0){
				index = (index + (num % n)) % n;
				prePos.push(index);
			}else if (num < 0){
				index = (index + (num % n + n)) % n;
				prePos.push(index);
			} 
		}
	}
	cout << index;
	return 0;
}