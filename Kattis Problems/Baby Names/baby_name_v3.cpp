// Problem: https://nus.kattis.com/sessions/gsfm3j/problems/nus.babynames

// Each babyName string consists of only UPPERCASE alphabet characters of no more than 30 characters
// GenderSuitability of that name (integer 1 for male or integer 2 for female)
    // One BST for all male names
    // One BST for all female names
// Tell Kattis how many baby names start with a prefix that is inside a given query interval [start…end), where start<end, and both are strings
    // Insert all names in BST where all names are arranged in lexicographically order
    // Find the lower_bound(start) and rank of that vertex, X
    // Find the lower_bound(end) and rank of that vertex, Y
    // Number of baby names suitable = Y - X

#include <bits/stdc++.h>

using namespace std;

struct BSTVertex {
  // all these attributes remain public to slightly simplify the code although this may not be the best practice
  BSTVertex* parent;
  BSTVertex* left;
  BSTVertex* right;
  string key;
  int height; // will be used in AVLDemo.cpp
  int size; // will be used for rank()
};

class StringBST_WithRank{
  private:
    BSTVertex * root;

    int h(BSTVertex* T) { return T == NULL ? -1 : T->height; }
    int size(BSTVertex* T) {return T == NULL ? 0 : T->size; }

    BSTVertex* rotateLeft(BSTVertex* T) {
      BSTVertex* w = T->right;
      w->parent = T->parent;
      T->parent = w;
      T->right = w->left;
      if (w->left != NULL) w->left->parent = T;
      w->left = T;
      // Only T & w's height & size will be affected during rotation
      T->height = max(h(T->left), h(T->right)) + 1;
      w->height = max(h(w->left), h(w->right)) + 1;
      T->size = size(T->left) + size(T->right) + 1;
      w->size = size(w->left) + size(w->right) + 1;
      return w; // Returns w for calling method to set the inbalanced vertex which was T now became w
    }

    BSTVertex* rotateRight(BSTVertex* T) {
      BSTVertex* w = T->left;
      w->parent = T->parent;
      T->parent = w;
      T->left = w->right;
      if (w->right != NULL) w->right->parent = T;
      w->right = T;

      T->height = max(h(T->left), h(T->right)) + 1;
      w->height = max(h(w->left), h(w->right)) + 1;
      T->size = size(T->left) + size(T->right) + 1;
      w->size = size(w->left) + size(w->right) + 1;
      return w;
  }

  BSTVertex* insert(BSTVertex* T, string& v) {       // override insert in BST class
    if (T == NULL) {                             // insertion point is found
      T = new BSTVertex;
      T->key = v;
      T->parent = T->left = T->right = NULL; // Parent set to NULL thus return T itself for parent along insertion path to set its left/right ptr
      T->height = 0; // // New vertex (in its own subtree with no children) currently has height 0
      T->size = 1; // New vertex (in its own subtree with no children) currently has size 1
    }
    else if (T->key < v) {                       // search to the right
      T->right = insert(T->right, v);
      T->right->parent = T;
    }
    else {                                       // search to the left
      T->left = insert(T->left, v);
      T->left->parent = T;
    }

    // Check vertex's balance factor
    int balance = h(T->left) - h(T->right);
    if (balance == 2) { // left heavy
      // Check vertex's left child's balance factor to determine LL or LR rotation
      int balance2 = h(T->left->left) - h(T->left->right);
      if (balance2 == 1) // LL-Rotation 
        T = rotateRight(T);
      else { // balance2 = -1 -> LR-Rotation 
        T->left = rotateLeft(T->left);
        T = rotateRight(T);
      }
    }
    else if (balance == -2) { // right heavy
      int balance2 = h(T->right->left) - h(T->right->right);
      if (balance2 == -1) // RR-Rotation
        T = rotateLeft(T);
      else { // balance2 = 1 -> RL-Rotation
        T->right = rotateRight(T->right);
        T = rotateLeft(T);
      }
    }
    // All 4 rotations are achieved by the 2 fundamental rotateLeft() & rotateRight()!

    // Update the height of the vertex
    // All the vertices along the insertion path will have its height updated when insert() returns
    // Just inserted vertex has height 0. Because the + 1, the next layer has h=1, next layer has h=2 ...
    T->height = max(h(T->left), h(T->right)) + 1;
    // Update the size too
    T->size = size(T->left) + size(T->right) + 1;
    return T;                                    // return the updated AVL
  }

  BSTVertex* findMin(BSTVertex* T) {
    // Base Cases:
    if (T == NULL)       return NULL;         // BST is empty, no minimum
    else if (T->left == NULL) return T;     // this is the min
    // Recursive Step: (Notice the "return"s! Interaction between different layers of recursion!!!)
    else                      return findMin(T->left); // go to the left
  }

  BSTVertex* findMax(BSTVertex* T) {
    if (T == NULL)        return NULL;        // BST is empty, no maximum
    else if (T->right == NULL) return T;    // this is the max
    else                       return findMax(T->right); // go to the right
  }

  BSTVertex* search(BSTVertex* T, string& v) {
    if (T == NULL)   return T;              // not found
    else if (T->key == v) return T;              // found
    else if (T->key < v)  return search(T->right, v); // search to the right
    else                  return search(T->left, v); // search to the left
  }

  BSTVertex* successor(BSTVertex* T) {
    if (T->right != NULL)                        // we have right subtree
      return findMin(T->right);                  // this is the successor
    else {
      BSTVertex* par = T->parent;
      BSTVertex* cur = T;
      // if par(ent) is not root and cur(rent) is its right children
      while ((par != NULL) && (cur == par->right)) { // Will break when cur is not parent's right -> cur is parent's left! -> parent is the successor
        cur = par;                               // continue moving up
        par = cur->parent;
      }
      return par == NULL ? NULL : par;        // this is the successor of T which can be NULL meaning T is already the max
    }
  }

  BSTVertex* predecessor(BSTVertex* T) {
    if (T->left != NULL)                         // we have left subtree
      return findMax(T->left);                   // this is the predecessor
    else {
      BSTVertex* par = T->parent;
      BSTVertex* cur = T;
      // if par(ent) is not root and cur(rent) is its left children
      while ((par != NULL) && (cur == par->left)) { 
        cur = par;                               // continue moving up
        par = cur->parent;
      }
      return par == NULL ? NULL : par;        // this is the predecessor of T
    }
  } 

  BSTVertex* deleteNode(BSTVertex* root, string& key) {  
      
    // STEP 1: PERFORM STANDARD BST DELETE  
    if (root == NULL) return root;  
  
    // If the key to be deleted is smaller than the root's key, then it lies in left subtree  
    if ( key < root->key ) root->left = deleteNode(root->left, key);  
  
    // If the key to be deleted is greater than the root's key, then it lies in right subtree  
    else if( key > root->key ) root->right = deleteNode(root->right, key);  
  
    // If key is same as root's key, then This is the node to be deleted  
    else {  
        // node with only one child or no child  
        if( (root->left == NULL) || (root->right == NULL) ) {  
            BSTVertex *temp = root->left ? root->left : root->right;  
  
            // No child case  
            if (temp == NULL){  
                temp = root;  
                root = NULL;  
            } 
            // One child case 
            else *root = *temp; // Copy the contents of the non-empty child  
            free(temp);  
        }  
        else{  
            // node with two children: Get the inorder successor (smallest in the right subtree)  
            BSTVertex* temp = findMin(root->right);  
  
            // Copy the inorder successor's data to this node  
            root->key = temp->key;  
  
            // Delete the inorder successor  
            root->right = deleteNode(root->right, temp->key);  
        }  
    }  
  
    // If the tree had only one node then return  
    if (root == NULL) return root;  
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
    root->height = 1 + max(h(root->left),h(root->right));
    root->size = size(root->left) + size(root->right) + 1;  
  
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)  
    int balance = h(root->left) - h(root->right);  
  
    // Left Left Case  
    if (balance == 2 && (h(root->left->left) - h(root->left->right)) == 1)  
        return rotateRight(root);  
  
    // Left Right Case  
    if (balance == 2 && (h(root->left->left) - h(root->left->right)) == -1){  
        root->left = rotateLeft(root->left);  
        return rotateRight(root);  
    }  
  
    // Right Right Case  
    if (balance == -2 && (h(root->right->left) - h(root->right->right)) == -1)  
        return rotateLeft(root);  
  
    // Right Left Case  
    if (balance == -2 && (h(root->right->left) - h(root->right->right)) == 1) {  
        root->right = rotateRight(root->right);  
        return rotateLeft(root);  
    }  
    return root;  
} 

  BSTVertex* remove(BSTVertex* T, string& v) {
    if (T == NULL)  return T;                    // cannot find the item

    if (T->key == v) {                           // the node to be deleted
      if (T->left == NULL && T->right == NULL){   // this is a leaf
        // delete T;
        T = NULL;                                // simply erase this node
      }
      else if (T->left == NULL && T->right != NULL) { // only one child at right
        BSTVertex* temp = T;
        T->right->parent = T->parent;
        T = T->right;                            // bypass T
        // delete temp;
        temp = NULL;
      }
      else if (T->left != NULL && T->right == NULL) { // only one child at left
        BSTVertex* temp = T;
        T->left->parent = T->parent;
        T = T->left;                             // bypass T
        // delete temp;
        temp = NULL;
      }
      else {                                     // find successor
        BSTVertex* successorV = successor(T);  // successor() will never return NULL since T has two children
        T->key = successorV->key;               // replace with successorV 
        T->right = remove(T->right, successorV->key); // delete the old successorV
      }
    }
    else if (T->key < v)                         // search to the right
      T->right = remove(T->right, v);
    else                                         // search to the left
      T->left = remove(T->left, v);

    if (T != NULL) {  // Similar as insertion code except this line -> T is NULL when T is leaf node which just got deleted 
      // Leaf node no need to balance, but vertices along the deletion path needs to be checked and rebalanced
      int balance = h(T->left) - h(T->right);
      if (balance == 2) { // left heavy
        int balance2 = h(T->left->left) - h(T->left->right);
        if (balance2 == 1) {
          T = rotateRight(T);
        }
        else { // -1
          T->left = rotateLeft(T->left);
          T = rotateRight(T);
        }
      }
      else if (balance == -2) { // right heavy
        int balance2 = h(T->right->left) - h(T->right->right);
        if (balance2 == -1)
          T = rotateLeft(T);
        else { // 1
          T->right = rotateRight(T->right);
          T = rotateLeft(T);
        }
      }

      T->height = max(h(T->left), h(T->right)) + 1;
      T->size = size(T->left) + size(T->right) + 1;
    }
    return T;                                    // return the updated BST
  }

  BSTVertex* lower_bound(string& v){
    // Iterative Implementation
    BSTVertex* lb = NULL;
    BSTVertex* vertex = root;
    while(vertex != NULL){
      if(vertex->key >= v){
        lb = vertex; // If lower_bound is 1st ele, lb will be set to ptr to 1st ele
        vertex = vertex->left;
      }
      else{
        vertex = vertex->right; // If no vertex is >= v, will traverse to most right and lb will not be set
      }
    }
    return lb;
  }

  int rank(BSTVertex* T, BSTVertex* v){
    if(T->key == v->key) return size(T->left) + 1;
    else if(T->key > v->key) return rank(T->left, v);
    else return size(T->left) + 1 + rank(T->right, v); // v must be present
  }  

  void inorder(BSTVertex* T) {
    if (T == NULL) return; // 1
    inorder(T->left);      // 2                      // recursively go to the left
    cout << T-> key << " "; // 3                      // visit this BST node
    inorder(T->right);     // 4                      // recursively go to the right
  }

public:
  StringBST_WithRank(){
    root = NULL;
  }

  void insert(string v) {
    BSTVertex* temp = search(root, v);
    if(temp == NULL) root = insert(root, v); 
  }

  void remove(string v) {
    root = deleteNode(root, v); 
  }

  int query(string v){
    BSTVertex* lb = lower_bound(v);
    if(lb == NULL){ // If no lower_bound is found as all elements are smaller than v
      lb = findMax(root);
      if (lb == NULL) return 0; // findMax() returns NULL -> BST is empty
      else return rank(root, lb) + 1; // The largest element is used as "end" which should be counted as valid name
    }
    else{
      return rank(root, lb);
    }
  }

  void inorder() { 
    inorder(root);
    printf("\n");
  }
    
};


// StringBST_WithRank t; // change the data structure name
// int MAXITR = 100;

// int main() {
//  srand(time(NULL));
//  for (int i = 0; i < MAXITR; i++) {
//   int cmd = rand() % 2;
//   int val = rand() % 10;
//   if (cmd == 0) {
//    cout << "inserting " << val << endl;
//    t.insert(val);
//   }
//   else {
//    cout << "erasing " << val << endl;
//    t.erase(val);
//   }
//   t.inorder();
//  }
// }


int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("in.txt", "r", stdin);
    int cmd;
    StringBST_WithRank male;
    StringBST_WithRank female;
    while(cin >> cmd, cmd != 0){
        switch(cmd){
            case 1:{
                string name; cin >> name;
                int gender; cin >> gender;
                gender == 1 ? male.insert(name) : female.insert(name);
                break;
            }
            case 2:{
                string name; cin >> name;
                male.remove(name);
                female.remove(name);
                break;
            }
            case 3:{
                string start, end;
                cin >> start >> end;
                int gender; cin >> gender;
                int count;
                switch(gender){
                  case 0:
                      count = (male.query(end) - male.query(start)) + (female.query(end) - female.query(start));
                      break;
                  case 1:
                      count = male.query(end) - male.query(start);
                      break;
                  case 2:
                      count = female.query(end) - female.query(start);
                }
                cout << count << "\n";
            }   
        }
    }
  // cout << "Fine";
	return 0;
}
