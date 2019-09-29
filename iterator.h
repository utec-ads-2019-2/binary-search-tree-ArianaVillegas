#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"

template <typename T>
struct Inode{
    Node<T>* node;
    bool right;
    bool left;
    Inode(Node<T>* node):node(node),right(0),left(0){};
};

template <typename T> 
class Iterator {
    private:
        Node<T> *current;
        vector<Inode<T>> positions;
        void move(){
            while(current) {
                positions.emplace_back(current);
                positions.back().left=1;
                current=current->left;
            }
            current=positions.back().node;
            //Pre-order
            /*
            while (positions.back().left && positions.back().right){
                positions.pop_back();
                if(!positions.size()) {current=nullptr;break;}
                else current = positions.back().node;
            }*/
        }
    public:
        Iterator(): current(nullptr){}

        Iterator(Node<T> *node): current(node) {}

        Iterator<T>& operator=(const Iterator<T> &other) {
            // Qué se iguala?
            return (*this);
        }

        bool operator!=(Iterator<T> other) {
            return current!=other.current;
        }

        Iterator<T>& operator++() {
            if(positions.size() && current) {
                if (!positions.back().left || current->left) {
                    positions.back().right = 1;
                    if (current->right) {
                        current = current->right;
                    } else {
                        if (!positions.size()) {
                            current = nullptr;
                            return (*this);
                        }
                        while (positions.back().left && positions.back().right) {
                            positions.pop_back();
                            if (!positions.size()) {
                                current = nullptr;
                                return (*this);
                            }
                        }
                        current = positions.back().node;
                        return (*this);
                    }
                }
                move();
            } else current= nullptr;
            return (*this);
            //Iterator pre-order
            /*
            positions.emplace_back(current);
            if(!current->left && !current->right) {positions.back().left=1;positions.back().right=1;move();}
            if(current->left && !positions.back().left) {
                if(!current->right) positions.back().right=1;
                positions.back().left=1;
                current=current->left;
            } else if(current->right && !positions.back().right) {
                positions.back().left = 1;
                positions.back().right = 1;
                current=current->right;
            }
            return (*this);
             */
        }

        Iterator<T>& operator--() {
            // TODO
        }

        T operator*() {
            // Caso null?
            return current->data;
        }
};

#endif
