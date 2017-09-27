#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include "listRecordDict.h"
#include "recordDict.h"
#include "RBtreeNode.h"
#include "RBRecordDict.h"
using namespace std;

RBRecordDict::RBRecordDict(){
    root = NULL;
}

RBRecordDict::~RBRecordDict(){
    destroy_tree(root);
}

RBtreeNode* RBRecordDict::grandparent(RBtreeNode *n){
    if (n!=NULL && n->parent != NULL)
        return n->parent->parent;
    else
        return NULL;
}

RBtreeNode* RBRecordDict::uncle(RBtreeNode *n){
    RBtreeNode *g = grandparent(n);
    if (g == NULL)
        return NULL;
    else if (g->left == n->parent)
        return g->right;
    else
        return g->left;
}

RBtreeNode* RBRecordDict::sibling(RBtreeNode *n){
    if (n->parent == NULL)
        return NULL;
    else if (n->parent->left == n)
        return n->parent->right;
    else
        return n->parent->left;
}

RBcolor RBRecordDict::Color(RBtreeNode *n){
    if (n==NULL){
        return Black;
    }
    else
        return n->color;
}

void RBRecordDict::destroy_tree(RBtreeNode *leaf){
    if (leaf!=NULL){
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void RBRecordDict::insert(record *in){
    if (root == NULL){
        root = new RBtreeNode(in);
        root->color = Black;
    }
    else
        insert_h(root, in);
}

void RBRecordDict::insert_h(RBtreeNode *n, record *in){
    if (n->data->operator>(*in)){ //Case 1
        if (n->left==NULL){
            n->left = new RBtreeNode(in, n);
            insert_fixup(n->left);
        }
        else
            insert_h(n->left, in);
    }

    else { //Case 2
        if (n->right==NULL){
            n->right = new RBtreeNode(in, n);
            insert_fixup(n->right);

        }
        else
            insert_h(n->right, in);
    }
}

void RBRecordDict::insert_fixup(RBtreeNode *n){
    if (n==root){ //Case 1
        n->color = Black;
        return;
    }

    else if (n->parent->color==Black)
        return;

    RBtreeNode *p = n->parent;
    RBtreeNode *g = grandparent(n);
    RBtreeNode *u = uncle(n);

    if(Color(u) == Black){ //Case 2
        if(p==g->left && p->right==n){
            rotate_left(p);
            swap(p,n);
        }
        else if(p==g->right && p->left==n){
            rotate_right(p);
            swap(p,n);
        }
        p->color = Black;
        g->color= Red;

        if (p->left == n){
            rotate_right(g);
        }
        else
            rotate_left(g);
        return;
    }

    else if(Color(u)==Red){
        p->color=Black;
        u->color=Black;
        g->color=Red;
        insert_fixup(g);
    }
}


void RBRecordDict::rotate_right(RBtreeNode *x){
    RBtreeNode *y;
    y=x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent=x;
    y->parent = x->parent;
    if(x->parent==NULL)
        root=y;
    else{
        if (x==x->parent->right){
            x->parent->right=y;
        }
        else{
            x->parent->left=y;
        }
    }
    y->right=x;
    x->parent=y;
}

void RBRecordDict::rotate_left(RBtreeNode *x){
    RBtreeNode *y;
    y=x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent=x;
    y->parent = x->parent;
    if(x->parent==NULL)
        root=y;
    else{
        if (x==x->parent->left){
            x->parent->left=y;
        }
        else{
            x->parent->right=y;
        }
    }

    y->left=x;
    x->parent=y;
}

RBtreeNode* RBRecordDict::search(string key){
    return search_help(key, root);
}

RBtreeNode* RBRecordDict::search_help(string key, RBtreeNode *leaf){
    if (leaf == NULL)
        return NULL;
    else if (leaf->data->operator==(key)){
        return leaf;
    }
    else if (leaf->data->operator>(key)){
        return search_help(key, leaf->left);

    }
    else
        return search_help(key, leaf->right);
}

void RBRecordDict::inOrderTraversal(){
    inOrder_help(root);
}

void RBRecordDict::preOrderTraversal(){
    preOrder_help(root);
}

void RBRecordDict::postOrderTraversal(){
    postOrder_help(root);
}

void RBRecordDict::inOrder_help(RBtreeNode *leaf){
    if (leaf == NULL)
        return;
    else{
        inOrder_help(leaf->left);
        myfile << leaf->data->fileString();
        myfile << endl;
        inOrder_help(leaf->right);
    }
}

RBtreeNode *RBRecordDict::successor (RBtreeNode *c){
    RBtreeNode *z;
    z = c->right;
    while (z->left!= NULL)
        z = z-> left;
    return z;
}

void RBRecordDict::remove(string r){
    RBtreeNode *datanode, *indanger;
    datanode = search(r);
    if (datanode == NULL)
        return;
    if (datanode->left == NULL || datanode->right==NULL)
        indanger=datanode;
    else{
        indanger = successor(datanode);
        datanode->data = indanger->data;
    }
    if(indanger->left!=NULL){
        indanger->data = indanger->left->data;
        delete indanger->left;
        indanger->left=NULL;
        return;
    }
    if(indanger->right!=NULL){
        indanger->data = indanger->right->data;
        delete indanger->right;
        indanger->right=NULL;
        return;
    }
    if (indanger->color == Black)
        remove_fixup(indanger);
    if (indanger->parent==NULL)
        root=NULL;
    else if(indanger->parent->left ==indanger)
        indanger->parent->left==NULL;
    else
        indanger->parent->right=NULL;
    delete indanger;

}

void RBRecordDict::remove_fixup(RBtreeNode *n){
    if(n->parent == NULL) //Case 1
        return;

    RBtreeNode *s=sibling(n);

    if (s->color == Red){ //Case 2
        n->parent->color=Red;
        s->color=Black;
        if (n == n->parent->left)
            rotate_left(n->parent);
        else
            rotate_right(n->parent);
        s = sibling(n);
    }

    if(n->parent->color == Red && s->color == Black && Color(s->left)==Black && Color(s->right)==Black){ //Case 3
        n->parent->color=Black;
        s->color=Red;
        return;
    }

    if (s==n->parent->right && Color(s->left)==Red && Color(s->right)==Black){ //Case 4 left
        s->color=Red;
        s->left->color=Black;
        rotate_right(s);
        s=sibling(n);
    }

    else if (s==n->parent->left && Color(s->left)==Black && Color(s->right)==Red){ //Case 4 right
        s->color=Red;
        s->right->color=Black;
        rotate_left(s);

        s=sibling(n);
    }

    if (n==n->parent->left && Color(s->right) == Red){ //Case 5 left
        s->color = n->parent->color;
        n->parent->color = Black;
        s->right->color=Black;
        rotate_left(n->parent);

        return;
    }

    else if (n==n->parent->right && Color(s->left) == Red){ //Case 5 right
        s->color = n->parent->color;
        n->parent->color = Black;
        s->left->color=Black;
        rotate_right(n->parent);

        return;
    }

    else{ //Case 6
        s->color = Red;
        remove_fixup(n->parent);
    }
}
void RBRecordDict::preOrder_help(RBtreeNode *leaf){
    if (leaf == NULL)
        return;

    else{
        myfile << leaf->data->fileString();
        myfile<<endl;
        preOrder_help(leaf->left);
        preOrder_help(leaf->right);
    }
}

void RBRecordDict::postOrder_help(RBtreeNode *leaf){
    if (leaf == NULL)
        return;
    else{
        postOrder_help(leaf->left);
        postOrder_help(leaf->right);
        myfile << leaf->data->fileString();
        myfile << endl;
    }
}

void RBRecordDict::toFile(string filename){
    myfile.open(filename.c_str());
    cout << "Would you like to use preorder(1), inorder(2), or postorder(3) traversal?" << endl;
    int order;
    cin >> order; //choose what order you'd like to display data in file
    cout << endl;
    if (order ==1)
        preOrderTraversal();
    if (order ==2)
        inOrderTraversal();
    if (order ==3)
        postOrderTraversal();
    myfile.close();
}



