#include "DataLoop.h"
#include <iostream>

//Default constructor: empty data loop
DataLoop::DataLoop() : start(nullptr), count(0) {}

//Non-default constructor
DataLoop::DataLoop(const int& num) : count(1) {
    start = new _Node({num, nullptr, nullptr});
    start->next = start;
    start->prev = start;
}

//Copy constructor
DataLoop::DataLoop(const DataLoop& rhs) : DataLoop() {
    *this = rhs;
}

//operator=
DataLoop& DataLoop::operator=(const DataLoop& rhs) {
    if (this != &rhs) {
        //Delete existing nodes
        clearDataLoop();

        int rhsCount = rhs.count;
        if (rhsCount > 0) {
            _Node* rhsCur = rhs.start;
            for (int i = 0; i < rhsCount; ++i) {
                *this += rhsCur->data;
                rhsCur = rhsCur->next;
            }
        }
    }

    return *this;
}

//helper func to remove all existing element in the data loop
void DataLoop::clearDataLoop() {
    _Node* current = start;
    for (size_t i = 0; i < count; ++i) {
        _Node* next = current->next;
        delete current;
        current = next;
    }
    //reset instance variables
    start = nullptr;
    count = 0;
}

//Destructor
DataLoop::~DataLoop() {
    clearDataLoop();
}

//operator==
//compares two dataloops and returns true if they contain the same integers, node by node; 
//otherwise, returns false.
bool DataLoop::operator==(const DataLoop& rhs) const {
    if (count != rhs.count) {
        return false;
    }
    if (count == 0) {
        return true;
    }

    _Node* currentThis = start;
    _Node* currentOther = rhs.start;

    for (size_t i = 0; i < count; ++i) {
        if (currentThis->data != currentOther->data) {
            return false;
        }
        currentThis = currentThis->next;
        currentOther = currentOther->next;
    }

    return true;
}

//operator+=
DataLoop& DataLoop::operator+=(const int& num) {
    if(count == 0){
        start = new _Node({num,nullptr,nullptr});
        start->next = start;
        start->prev = start;
        count++;
    }else{
        _Node* newNode = new _Node({num, nullptr,nullptr});
        newNode->next = start;
        start->prev->next = newNode;
        newNode->prev = start->prev;
        start->prev = newNode;
        ++count;
    }
    
    return *this;
}



//operator+
DataLoop DataLoop::operator+(const DataLoop& rhs) const {
    DataLoop result = *this; //Copy constructor called
    _Node* rhsCurrent = rhs.start;

    for (size_t i = 0; i < rhs.count; ++i) {
        result += rhsCurrent->data;
        rhsCurrent = rhsCurrent->next;
    }

    return result;
}

//operator^
DataLoop& DataLoop::operator^(int offset) {
    if (count <= 1 || offset == 0) {
        return *this;
    }
    if (offset > 0) {
        //move forward
        for (int i = 0; i < offset; ++i) {
            start = start->next;
        }
    } else if (offset < 0) {
        //move backward
        for (int i = 0; i < -offset; ++i) {
            start = start->prev;
        }
    }

    return *this;
}

//splice
DataLoop& DataLoop::splice(DataLoop& rhs, size_t pos) {
    if (pos > count) {
        pos %= count;
    }

    if (rhs.count > 0) {
        if (count == 0) {
            *this = rhs; //just copy the other DataLoop
        } else {
            _Node* rhsStart = rhs.start;
            _Node* current = start;

            for (size_t i = 0; i < pos; ++i) {
                current = current->next;
            }

            //Update pointers for rhs list
            rhsStart->prev->next = current;
            rhsStart->next->prev = current->prev;

            //Update pointers for current list
            current->prev->next = rhsStart;
            current->prev = rhsStart->prev;

            //Update start pointer if needed
            if (pos == 0) {
                start = rhsStart;
            }

            count += rhs.count;
            rhs.count = 0;
            rhs.start = nullptr;
        }
    }

    return *this;
}


//operator<<
std::ostream& operator<<(std::ostream& os, const DataLoop& dl) {
    if (dl.count == 0) {
        os << ">no values<";
    } else {
        os << "-> ";
        DataLoop::_Node* cur = dl.start;
        for (size_t i = 0; i < dl.count-1; ++i) {
            os << cur->data << " <--> ";
            cur = cur->next;
        }
    
        os << cur->data << " <-";
    }
    return os;
}





