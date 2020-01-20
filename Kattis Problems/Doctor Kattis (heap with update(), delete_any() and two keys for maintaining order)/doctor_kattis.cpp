//Matric number:  
//Full name:  
//Lab group number:  
//Lab group TA:  

// https://stackoverflow.com/questions/9209323/easiest-way-of-using-min-priority-queue-with-key-update-in-c
// https://stackoverflow.com/questions/46996 4/how-to-update-elements-within-a-heap-priority-queue
// https://stackoverflow.com/questions/17009056/how-to-implement-ologn-decrease-key-operation-for-min-heap-based-priority-queu

#include <bits/stdc++.h>

using namespace std;

struct Cat {
    string name;
    int infectionLevel;
    int orderEnqueued;
};

class ClinicPriorityQueue {
   private:
    vector<Cat> pQueue;
    unordered_map<string, int> index;
    const unsigned int MAX_CATS = 200000;
    int heap_size;
    int order;

    int parent(int i) { return i >> 1; }       // i>>1 is the same as i/2
    int left(int i) { return i << 1; }         // i<<1 is the same as i*2
    int right(int i) { return (i << 1) + 1; }  // (i<<1)+1 is the same as i*2+1

    void Swap(Cat& a, Cat& b, int iA, int iB) { // Swap structs
        // Swap index of two nodes recorded in map too
        index[a.name] = iB;
        index[b.name] = iA;
        
        Cat tmp = a;

        a.name = b.name;
        a.infectionLevel = b.infectionLevel;
        a.orderEnqueued = b.orderEnqueued;

        b = tmp;
    }

    void shift_up(int i) {                                                  // O(log n)
        if (i == 1) return;                                                 // at root, do nothing
        if (pQueue[i].infectionLevel > pQueue[parent(i)].infectionLevel) {  // violate property with parent
            Swap(pQueue[i], pQueue[parent(i)], i, parent(i));               // swap upwards
            shift_up(parent(i));                                            // recurse, at most O(log n) steps back to the root
        } 
        else if (pQueue[i].infectionLevel == pQueue[parent(i)].infectionLevel) {
            if (pQueue[i].orderEnqueued < pQueue[parent(i)].orderEnqueued) {
                Swap(pQueue[i], pQueue[parent(i)], i, parent(i));  // swap upwards
                shift_up(parent(i));
            }
        }
    }

    void shift_down(int i) {        // O(log n)
        if (i > heap_size) return;  // beyond last element, do nothing
        int swap_id = i;
        if (left(i) <= heap_size && pQueue[i].infectionLevel < pQueue[left(i)].infectionLevel) {  // compare with left child, if exists
            swap_id = left(i);
        }
        else if (left(i) <= heap_size && pQueue[i].infectionLevel == pQueue[left(i)].infectionLevel) {  // compare with left child, if exists
            swap_id = pQueue[i].orderEnqueued > pQueue[left(i)].orderEnqueued ? left(i) : i;
        }
        if (right(i) <= heap_size && pQueue[swap_id].infectionLevel < pQueue[right(i)].infectionLevel) {  // compare with right child, if exists
            swap_id = right(i);
        }
        else if (right(i) <= heap_size && pQueue[swap_id].infectionLevel == pQueue[right(i)].infectionLevel) {  // compare with right child, if exists
            swap_id = pQueue[swap_id].orderEnqueued > pQueue[right(i)].orderEnqueued ? right(i) : swap_id;

        }
        if (swap_id != i) {                    // need to swap with the larger of the two children
            Swap(pQueue[i], pQueue[swap_id], i, swap_id);  // swap downwards with the larger of the two children
            shift_down(swap_id);               // recurse, at most O(log n) steps to one of the bottom-most leaf
        }
    }


public:
    
    ClinicPriorityQueue(){
        pQueue.clear();
        pQueue.reserve(MAX_CATS);
        pQueue.resize(1); // Initialize index 0 as empty
        heap_size = 0;
        order = 1;
    }

    void ArriveAtClinic(const string& catName, int _infectionLevel) { // O(log n)
        if (heap_size+1 >= (int)pQueue.size()) { // O(1)
            pQueue.resize(pQueue.size() + 1); // enlarge the vector by one if needed, to avoid potential RTE below, O(1)
        }
        pQueue[++heap_size] = {catName, _infectionLevel, order++}; 
        index[catName] = heap_size; // Store the index of the newly added node
        shift_up(heap_size); // shift upwards, O(log n) at worst -> When shifting up the index map is updated too
    }

    void UpdateInfectionLevel(const string& catName, int changeInfection){
        int i = index[catName];
        pQueue[i].infectionLevel += changeInfection; //update infection commands are given in such a way that the overall infection level of any cat will not exceed 100.
        if(changeInfection > 0) shift_up(i); // Can only shift up since priority can only increases
        else if (changeInfection < 0) shift_down(i);
        // If priority can decrease, then change will be negative -> shift down
    }

    void Treated(const string& catName) { // O(log n)
        int i = index[catName];
        Swap(pQueue[i], pQueue[heap_size], i, heap_size); // swap with the last existing leaf, O(1)
        index.erase(catName); // erase after swap. If not during swapping the index is assessed again and will create the deleted catName
        heap_size--;
        if(i == 1) shift_down(i);
        else{
            if(pQueue[i].infectionLevel > pQueue[parent(i)].infectionLevel || (pQueue[i].infectionLevel == pQueue[parent(i)].infectionLevel && pQueue[i].orderEnqueued < pQueue[parent(i)].orderEnqueued)){
                shift_up(i);
            }
            else shift_down(i); // fix heap property downwards, O(log n) at worst
        }
        // shift_up(i);
        // shift_down(i);
    }

    void Query() { // O(1)
       if (heap_size == 0) cout << "The clinic is empty" << endl;
       else cout << pQueue[1].name << endl; // this is the root
    }

    void debug(){
        for(int i = 1; i <= heap_size; i++) cout << "(" << pQueue[i].name << "," << pQueue[i].infectionLevel << ") ";
        cout << endl;
        for(auto i : index) cout << i.first << " - Index:" << i.second << endl;
    }

};

int main() {
    // freopen("1.in", "r", stdin);
    int N; cin >> N;
    ClinicPriorityQueue clinic;
    while(N--){
        int cmd; cin >> cmd;
        string catName;
        int infection;
        switch(cmd){
            case 0:
                cin >> catName;
                cin >> infection;
                clinic.ArriveAtClinic(catName, infection);
                break;
            case 1:
                cin >> catName;
                cin >> infection;
                clinic.UpdateInfectionLevel(catName, infection);
                break;
            case 2:
                cin >> catName;
                clinic.Treated(catName);
                break;
            case 3:
                clinic.Query();
        }
    }
    // clinic.Query();
    // clinic.ArriveAtClinic("LUNA", 31);
    // clinic.ArriveAtClinic("NALA", 55);
    // clinic.ArriveAtClinic("BELLA", 42);
    // clinic.Query();
    // clinic.ArriveAtClinic("KITTY", 77);  
    // clinic.Query();
    // clinic.UpdateInfectionLevel("LUNA", 24);
    // clinic.Treated("KITTY");
    // clinic.Query();
    // clinic.Treated("BELLA");
    // clinic.Query();
    // clinic.Treated("LUNA");
    // clinic.Query();
    // clinic.Treated("NALA");
    // clinic.Query();
    // clinic.debug();
    return 0;
}