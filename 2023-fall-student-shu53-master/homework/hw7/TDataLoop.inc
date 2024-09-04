//Default constructor: empty data loop
template <typename DataType>
TDataLoop<DataType>::TDataLoop() : start(nullptr), count(0) { }

//Non-default constructor
template <typename DataType>
TDataLoop<DataType>::TDataLoop(const DataType& num) : count(1) {
    start = new _Node({num, nullptr, nullptr});
    start->next = start;
    start->prev = start;
}

//Copy constructor
template <typename DataType>
TDataLoop<DataType>::TDataLoop(const TDataLoop<DataType>& rhs) : TDataLoop() {
    *this = rhs;
}

template <typename DataType>
TDataLoop<DataType>& TDataLoop<DataType>::operator=(const TDataLoop<DataType>& rhs) {
    if (this != &rhs) {
        //delete existing nodes
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

template <typename DataType>
void TDataLoop<DataType>::clearDataLoop() {
    _Node* current = start;
    for (size_t i = 0; i < count; ++i) {
        _Node* next = current->next;
        delete current;
        current = next;
    }
    start = nullptr;
    count = 0;
}

//helper func to remove all existing element in the data loop
template <typename DataType>
TDataLoop<DataType>::~TDataLoop() {
    clearDataLoop();
}

template <typename DataType>
bool TDataLoop<DataType>::operator==(const TDataLoop<DataType>& rhs) const {
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

template <typename DataType>
TDataLoop<DataType>& TDataLoop<DataType>::operator+=(const DataType& num) {
    if (count == 0) {
        start = new _Node({num, nullptr, nullptr});
        start->next = start;
        start->prev = start;
        count++;
    } else {
        _Node* newNode = new _Node({num, nullptr, nullptr});
        newNode->next = start;
        start->prev->next = newNode;
        newNode->prev = start->prev;
        start->prev = newNode;
        ++count;
    }

    return *this;
}

template <typename DataType>
TDataLoop<DataType> TDataLoop<DataType>::operator+(const TDataLoop<DataType>& rhs) const {
    TDataLoop<DataType> result = *this;
    _Node* rhsCurrent = rhs.start;

    for (size_t i = 0; i < rhs.count; ++i) {
        result += rhsCurrent->data;
        rhsCurrent = rhsCurrent->next;
    }

    return result;
}

template <typename DataType>
TDataLoop<DataType>& TDataLoop<DataType>::operator^(int offset) {
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

template <typename DataType>
TDataLoop<DataType>& TDataLoop<DataType>::splice(TDataLoop<DataType>& rhs, size_t pos) {
    if (pos > count) {
        pos %= count;
    }

    if (rhs.count > 0) {
        if (count == 0) {
            *this = rhs; 
        } else {
            _Node* rhsStart = rhs.start;
            _Node* current = start;

            for (size_t i = 0; i < pos; ++i) {
                current = current->next;
            }

            //update pointers for rhs list
            rhsStart->prev->next = current;
            rhsStart->next->prev = current->prev;

            //update pointers for current list
            current->prev->next = rhsStart;
            current->prev = rhsStart->prev;

            //update start pointer if needed
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

template <typename DataType>
std::ostream& operator<<(std::ostream& os, const TDataLoop<DataType>& dl) {
    if (dl.count == 0) {
        os << ">no values<";
    } else {
        os << "-> ";
        typename TDataLoop<DataType>::_Node* cur = dl.start;
        for (size_t i = 0; i < dl.count - 1; ++i) {
            os << cur->data << " <--> ";
            cur = cur->next;
        }

        os << cur->data << " <-";
    }
    return os;
}

