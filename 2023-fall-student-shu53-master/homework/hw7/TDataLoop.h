#ifndef TDATALOOP_H
#define TDATALOOP_H

#include <iostream>

template <typename DataType>
class TDataLoop {
public:
    TDataLoop();
    TDataLoop(const DataType& value);
    TDataLoop(const TDataLoop& rhs);
    TDataLoop& operator=(const TDataLoop& rhs);
    ~TDataLoop();

    bool operator==(const TDataLoop& rhs) const;
    TDataLoop& operator+=(const DataType& value);
    TDataLoop operator+(const TDataLoop& rhs) const;
    TDataLoop& operator^(int offset);
    TDataLoop& splice(TDataLoop& rhs, size_t pos);
    int length() const { return count; }
    template<typename A>
    friend std::ostream& operator<<(std::ostream& os, const TDataLoop<A>& dl);

private:
    friend struct TDataLoopTest;
    struct _Node {
        DataType data;
        _Node* next;
        _Node* prev;
    };

    _Node* start;
    size_t count;

    void clearDataLoop();

};

#include "TDataLoop.inc"

#endif // TDATALOOP_H
