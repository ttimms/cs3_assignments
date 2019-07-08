// Tyler Timms
// cs3 Lab 3
// 9/15/2018

#include "list.h"

#ifndef COLLECTION_H
#define COLLECTION_H

template<typename T>
class Collection{
public:

    Collection(): front_(nullptr) {}
    void addItem(const T&);
    void removeItem(const T&); // implement
    T lastItem() const {return front_->getData();}
    void printCollection();

    template<typename U>
    friend bool equal(const Collection<U>&, const Collection<U>&);

private:

    node<T> *front_;
};

template<typename T>
void Collection<T>::addItem(const T &item){
    node<T> *newNode = new node<T>;
    newNode->setData(item);
    newNode->setNext(front_);
    front_ = newNode;
}

template<typename T>
void Collection<T>::removeItem(const T &item){

    //handles deleting front items
    while(front_ != nullptr && front_->getData() == item){
        node<T> *tmp = front_;
        tmp = front_->getNext();
        delete front_;
        front_ = tmp;
    }

    node<T> *temp = front_;
    node<T> *temp2 = temp->getNext();

    // handles cases after the front. does not handle front item.
    while(temp2 != nullptr){ 
        if(temp2->getData() == item){
            temp->setNext(temp2->getNext());
            delete temp2;
            temp2 = temp->getNext();
        }
        else{
            temp = temp->getNext();
            temp2 = temp2->getNext();
        }
    }
}

template<typename T>
void Collection<T>::printCollection(){
    node<T> *temp = front_;
    while(temp != nullptr){
        std::cout << temp->getData() << " ";
        temp = temp->getNext();
    }
}

template<typename U>
bool equal(const Collection<U> &x, const Collection<U> &y){
    node<U> *tempX = x.front_;
    node<U> *tempY = y.front_;

    while(tempX != nullptr && tempY != nullptr){
        if(tempX->getData() == tempY->getData()){
            tempX = tempX->getNext();
            tempY = tempY->getNext();
        }
        else
            return false;
    } 
    if(tempX == nullptr && tempY == nullptr)
        return true;
    else 
        return false;

}

#endif // COLLECTION_H
