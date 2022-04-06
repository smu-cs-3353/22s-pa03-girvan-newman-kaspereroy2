//
// Created by Jeremy on 4/6/2022.
//

#ifndef GIRVAN_NEWMAN_KASPEREROY_LINKEDLIST_H
#define GIRVAN_NEWMAN_KASPEREROY_LINKEDLIST_H
#include <iostream>
template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    Node* tail;
    int size;
public:
    LinkedList();
    ~LinkedList();
    void push_back(T);
    void pop();
    void print();
    T at(int);
};

template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
    Node *temp = head;
    while (temp != nullptr) {
        head = head->next;
        delete temp;
        temp = head;
    }
}

template <class T>
void LinkedList<T>::push_back(T data) {
    Node *temp = new Node;
    temp->data = data;
    temp->next = nullptr;
    if (head == nullptr) {
        head = temp;
        tail = head;
    } else {
        tail->next = temp;
        tail = tail->next;
    }
    size++;
}

template <class T>
void LinkedList<T>::print() {
    Node *temp = head;
    while (temp != nullptr) {
        std::cout << " -> " << temp->data;
        temp = temp->next;
    }
    std::cout << std::endl;
}

template<typename T>
void LinkedList<T>::pop() {
    if(head != nullptr){
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
    else{
        std::cout << "Empty List" << std::endl;
        exit(11);
    }
}

template<typename T>
T LinkedList<T>::at(int position) {
    if(position >= size){
        std::cout << "Out Of Range" << std::endl;
        exit(11);
    }
    Node* curr = head;
    for(int i=0; i<position; i++){
        curr = curr->next;
    }
    return curr->data;
}


#endif //GIRVAN_NEWMAN_KASPEREROY_LINKEDLIST_H
