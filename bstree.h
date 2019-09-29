#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"

template <typename T> 
class BSTree {
    Node<T> *root;
    bool find(T data, Node<T>* node){
        if(!node) { return false;}
        if(data==node->data) return true;
        else if(data<node->data) return find(data,node->left);
        else return find(data,node->right);
    }
    bool insert(T data, Node<T>* &node){
        if(!node) {node=new Node<T>(data); return true;}
        if(data<=node->data) return insert(data,node->left);
        else return insert(data,node->right);
    }
    bool remove(T data, Node<T>* &node){
        if(!node) return false;
        if(data<node->data) remove(data,node->left);
        else if(data>node->data) remove(data,node->right);
        else {
            if(!node->left && !node->right) {delete node; node= nullptr; return true;}
            else if(!node->left) return changeL(node,node->right);
            return changeR(node,node->left);
        }
    }
    bool changeL(Node<T>* actual, Node<T>* &node){
        if(!node->left && !node->right){swap(actual->data,node->data); delete node; node= nullptr; return true;}
        if(!node->left){swap(node->data,actual->data);actual=node;return changeL(actual,node->right);}
        return changeL(actual,node->left);
    }
    bool changeR(Node<T>* actual, Node<T>* &node){
        if(!node->left && !node->right){swap(actual->data,node->data); delete node; node= nullptr; return true;}
        if(!node->right){swap(node->data,actual->data);actual=node;return changeR(actual,node->left);}
        return changeR(actual,node->right);
    }
    void deleteAll(Node<T>* node){
        if(node->left) deleteAll(node->left);
        if(node->right) deleteAll(node->right);
        delete node;
    }
    size_t size(Node<T>* node){
        if(!node) return 0;
        return 1+size(node->right)+size(node->left);
    }
    size_t height(Node<T>* node){
        if(!node) return 0;
        size_t left=height(node->left);
        size_t right=height(node->right);
        return 1+((right<left)?left:right);
    }
    void traversePreOrder(Node<T>* node){
        cout << node->data << ' ';
        if(node->left) traversePreOrder(node->left);
        if(node->right) traversePreOrder(node->right);
    }
    void traverseInOrder(Node<T>* node) {
        if(node->left) traverseInOrder(node->left);
        cout << node->data << ' ';
        if(node->right) traverseInOrder(node->right);
    }
    void traversePostOrder(Node<T>* node) {
        if(node->left) traversePostOrder(node->left);
        if(node->right) traversePostOrder(node->right);
        cout << node->data << ' ';
    }
    public:
        BSTree() : root(nullptr) {};

        bool find(T data) {
            return find(data,root);
        }

        bool insert(T data) {
            return insert(data,root);
        }

        bool remove(T data) {
            // return?
            remove(data,root);
        }

        size_t size() {
            return size(root);
        }

        size_t height() {
            return height(root)-1;
        }

        void traversePreOrder() {
            if(root) traversePreOrder(root);
        }

        void traverseInOrder() {
            if(root) traverseInOrder(root);
        }

        void traversePostOrder() {
            if(root) traversePostOrder(root);
        }

        Iterator<T> begin() {
            Iterator<T> itr(root);
            return ++itr;
        }

        Iterator<T> end() {
            Iterator<T> itr(nullptr);
            return itr;
        }

        ~BSTree() {
            if (root) deleteAll(root);
            root= nullptr;
        }
};

#endif
