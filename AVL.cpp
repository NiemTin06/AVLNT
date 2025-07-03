#include <bits/stdc++.h>

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    int height; // chieu cao cua node
};

typedef Node* Tree;

// Ham tao node moi
Tree makeNode(int x){
    Tree T = new Node;
    T->data = x;
    T->left = NULL;
    T->right = NULL;
    T->height = 1;
    return T;
}

void MakeNULL(Tree &T){
    T = NULL;
}

//AVL
int maxheight(Tree  T){
    int pl = (T->left == NULL)? 0 : T->left->height;
    int pr = (T->right == NULL)? 0 : T->right->height;
    return (pl > pr) ? pl : pr;
}

//tim chi so can bang cua cay
int baln(Tree T){
    int pl = 0; 
    int pr = 0;
    if (T->left == NULL) pl = 0;
    else pl = T->left->height;
    if (T->right == NULL) pr = 0;
    else pr = T->right->height;
    return pl - pr;
}

//ham cap nhat chieu cao sau khi quay
void updateheight(Tree &T){
    if (T == NULL) return;
    T->height = maxheight(T) + 1;
}

// Ham danh gia mot Node co bi mat can bang hay khong
int is_baln(Tree T){
    int tmp = baln(T);
    if (tmp > 1) return 1;
    else if (tmp < -1) return -1;
    return 0;
}

// Xu ly l - L
void rotateright(Tree &T){
    Tree tmp = T;
    T  = T->left;
    tmp->left = T->right;
    T->right = tmp;

    updateheight(tmp);
    updateheight(T);
}

// xu ly R - R
void rotateleft(Tree &T){
    Tree tmp = T;
    T  = T->right;
    tmp->right= T->left;
    T->left = tmp;

    updateheight(T);
    updateheight(tmp);
}

// xu ly  R - L
void rotateleftright(Tree &T){
    rotateleft(T->left);
    rotateright(T);
}

// xu ly  L - R
void rotaterightleft(Tree &T){
    rotateright(T->right);
    rotateleft(T);
}

//Kiem tra cay da can bang hay chua
void balancetree(Tree &T){
    if (T == NULL) return ;
    balancetree(T->left);
    balancetree(T->right);
    int bal = is_baln(T);
    if (bal == 1){
        Node*p1 = T->left;
        int idx = baln(p1);
        if (idx >= 0) {
            rotateright(T);
        }
        else {
            rotateleftright(T);
        }
    }
    else if (bal == -1){
        Node*p1 = T->right;
        int idx = baln(p1);
        if (idx <= 0) {
            rotateleft(T);
        }
        else {
            rotaterightleft(T);
        }
    }
    updateheight(T);
}

// End AVL

// tim kiem phan tu
bool check(Tree T, int x){
    if (T == NULL) return false;
    if (T->data == x) return true;
    else {
        if (T->data > x) return check(T->left, x) ;
        else  return check(T->right, x) ;
    }
}

// Chen phan tu 
void insertNode(Tree &T, int x){
    if (T == NULL) T = makeNode(x);
    else{
        if (T->data > x) insertNode(T->left, x);
        else if (T->data < x) insertNode(T->right, x);
    }
    updateheight(T);
    balancetree(T);
}


int minNode(Tree &T){
    if (T->left == NULL){
        int tmp = T->data;
        Tree tmpNode = T;
        T = T->right;
        delete tmpNode;
        return tmp;
    }
    else return minNode(T->left);
}

// Xoa phan tu 
void deleteNode(Tree &T, int x){
    if (T == NULL) return ;
    if (T->data > x) deleteNode(T->left, x);
   else if (T->data < x) deleteNode(T->right, x);
   else{ 
        if(T->left == NULL){
            Tree tmp = T;
            T = T->right;
            delete tmp;
        }
        else if(T->right == NULL){
            Tree tmp = T;
            T = T->left;
            delete tmp;
        }
        else {
            T->data = minNode(T->right);
        }
   }
   updateheight(T);
    balancetree(T);
}
int main(){
    return 0;
}
