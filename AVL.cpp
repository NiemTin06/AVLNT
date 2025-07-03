#include <bits/stdc++.h>

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    int height;
};

Node* makeNode(int x){
    Node* p = new Node;
    p->data = x;
    p->left = NULL;
    p->right = NULL;
    p->height = 1;
    return p;
}

int maxheight(Node* l, Node* r){
    int pl = (l == NULL)? 0 : l->height;
    int pr = (r == NULL)? 0 : r->height;
    return (pl > pr) ? pl : pr;
}

int baln(Node* root){
    int pl = (root->left == NULL)? 0 : root->left->height;
    int pr = (root->right == NULL)? 0 : root->right->height;
    return pr - pl;
}
void updateHeight(Node* &p) {
    if (p == nullptr) return;
    p->height = maxheight(p->left, p->right) + 1;
}

int is_balance(Node* p){
    int hl = 0;
    int hr = 0;
    if (p->left != NULL){
        hl = p->left->height;
    }
    if (p->right != NULL){
        hr = p->right->height;
    }
    int idx = hr - hl;
    if (idx > 1) return 1;
    if (idx < -1) return -1;
    return 0;
}

void rotaterightright(Node* &root){
    Node* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    root = tmp;

    Node *ph = root->right;
    updateHeight(ph);
    updateHeight(root);
}
void rotaterleftleft(Node* &root){
    Node* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    root = tmp;

    Node *ph = root->left;
    updateHeight(ph);
    updateHeight(root);
}

void rotaterleftright(Node* &root){
    rotaterleftleft(root->left);
    rotaterightright(root);
}

void rotaterrightleft(Node* &root){
    rotaterightright(root->right);
    rotaterleftleft(root);
}

void balancetree(Node *&root){
    if (root == NULL) return ;
    balancetree(root->left);
    balancetree(root->right);
    int bal = is_balance(root);
    if (bal == -1){
        Node*p1 = root->left;
        int idx = baln(p1);
        if (idx <= 0) {
            rotaterightright(root);
        }
        else {
            rotaterleftright(root);
        }
    }
    else if (bal == 1){
        Node*p1 = root->right;
        int idx = baln(p1);
        if (idx >= 0) {
            rotaterleftleft(root);
        }
        else {
            rotaterrightleft(root);
        }
    }
}
int main(){
    return 0;
}