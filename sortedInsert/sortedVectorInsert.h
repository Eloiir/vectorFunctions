/**
*   Author: Eloiir
*
*   Two functions to insert an element into a sorted vector. (If you insert all variables this way, it will also be a sorted vector.)
*
*   sortedInsert():
*   input:
*   vector,
*   variable of the same type as vector,
*   a boolean variable, where true means ascending order and false descending. True as default.
*   output: none
*
*   sortedObjectInsert():
*   input:
*   vector of objects,
*   object of the same type as vector,
*   address of value you want to sort by, on index 0 (Example: &vectorName[0].valueToSortBy). If the vector has no elements yet, pass nullptr or leave default(also nullptr).
*   a boolean variable, where true means ascending order and false descending. True as default.
*   output: none
*
**/
#ifndef sortedVectorInsert_h
#define sortedVectorInsert_h

#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

using namespace std;


template <typename T>
void sortedInsert(std::vector<T>& vec, const T& __x, bool sortOrder = true);

template <typename Obj, typename T>
void sortedObjectInsert(std::vector<Obj>& vec, const Obj& __x, T* ptrFirstVal = NULL, bool sortOrder = true);


template <typename T>
void sortedInsert(std::vector<T>& vec, const T& __x, bool sortOrder)
{
    if(vec.empty()){
        return vec.push_back(__x);
    }

    // - INVALID INPUT -
    for(int i = 0; i < (int(vec.size()) - 1); i++){  // check if vector is sorted
        if((sortOrder && (vec.at(i) > vec.at(i + 1))) || (!sortOrder && (vec.at(i) < vec.at(i + 1)))){
            throw invalid_argument(string("sortedInsert(): Vector not sorted. "));
        }
    }
    // - --- -

    // - SPECIAL CASES -
    if((sortOrder && (__x < *vec.begin())) || (!sortOrder && (__x > *vec.begin()))){   // input element smaller than smallest element in vector
        vec.insert(vec.begin(), __x); return;
    }
    if((sortOrder && (__x > *(vec.end() - 1))) || (!sortOrder && (__x < *(vec.end() - 1)))){   // input element bigger than biggest element in vector
        vec.push_back(__x); return;
    }
    // - --- -

    // - BINARY SEARCH AND INSERT -
    unsigned int low = 0;
    unsigned int high = (vec.size() - 1);

    bool found = false;
    while(!found){
        int mid = ((low + high) / 2);

        if((sortOrder && (vec.at(mid) <= __x && vec.at(mid + 1) >= __x)) || (!sortOrder && (vec.at(mid) >= __x && vec.at(mid + 1) <= __x))){
            found = true;
            vec.insert((vec.begin() + mid + 1), __x);
        }
        else if((sortOrder && (vec.at(mid) > __x)) || (!sortOrder && (vec.at(mid) < __x))){
            high = mid;
        }
        else if((sortOrder && (vec.at(mid) < __x)) || (!sortOrder && (vec.at(mid) > __x))){
            low = mid;
        }
    }
    // - -- -
}

int pointerDistance(void* ptr1, void* ptr2){
    for(int i = 0; i < 1000; i++){
        ptr1 = (char*)ptr1 + 1;
        if(ptr1 == ptr2){
            return i + 1;
        }
    }
    throw invalid_argument(string("pointerDistance() (in sortedVectorInsert.h) got bad arguments. "));
}

template <typename Obj, typename T>
void sortedObjectInsert(std::vector<Obj>& vec, const Obj& __x, T* ptrFirstVal, bool sortOrder){
    if(vec.empty()){
        return vec.push_back(__x);
    }
    if(ptrFirstVal == NULL){
        throw invalid_argument(string("sortedObjectInsert(): No pointer to object value. "));
    }
    //cout << '1' << endl;
    // - DISTANCE BETWEEN START OF OBJECT AND WANTED VALUE IN MEMORY -
    const unsigned int distance = pointerDistance(&vec[0], ptrFirstVal);
    // - --- -

    //cout << '2' << endl;
    // - EXTRACT VECTOR OF VALUES(FROM VECTOR OF OBJECTS), AND VALUE OF INSERTED OBJECT -
    T __xValue = *((char*)&__x + distance);
    vector<T> valueVector;
    for(unsigned int i = 0; i < vec.size(); i++){
        void* ptr = &vec[i];
        ptr = (char*)ptr + distance;
        valueVector.push_back(*((T*)ptr));
    }
    // - --- -

    //cout << '3' << endl;
    // - INVALID INPUT -
    for(int i = 0; i < (int(valueVector.size()) - 1); i++){  // check if vector is sorted
        if((sortOrder && (valueVector.at(i) > valueVector.at(i + 1))) || (!sortOrder && (valueVector.at(i) < valueVector.at(i + 1)))){
            throw invalid_argument(string("sortedObjectInsert(): Vector not sorted. "));
        }
    }
    // - --- -

    //cout << '4' << endl;
    // - SPECIAL CASES -
    if((sortOrder && (__xValue < *valueVector.begin())) || (!sortOrder && (__xValue > *valueVector.begin()))){   // input element smaller than smallest element in vector
        vec.insert(vec.begin(), __x); return;
    }
    if((sortOrder && (__xValue > *(valueVector.end() - 1))) || (!sortOrder && (__xValue < *(valueVector.end() - 1)))){   // input element bigger than biggest element in vector
        vec.push_back(__x); return;
    }
    // - --- -

    //cout << '5' << endl;
    // - BINARY SEARCH AND INSERT -
    unsigned int low = 0;
    unsigned int high = (valueVector.size() - 1);

    bool found = false;
    while(!found){
        int mid = ((low + high) / 2);

        if((sortOrder && (valueVector.at(mid) <= __xValue && valueVector.at(mid + 1) >= __xValue)) || (!sortOrder && (valueVector.at(mid) >= __xValue && valueVector.at(mid + 1) <= __xValue))){
            found = true;
            vec.insert((vec.begin() + mid + 1), __x);
        }
        else if((sortOrder && (valueVector.at(mid) > __xValue)) || (!sortOrder && (valueVector.at(mid) < __xValue))){
            high = mid;
        }
        else if((sortOrder && (valueVector.at(mid) < __xValue)) || (!sortOrder && (valueVector.at(mid) > __xValue))){
            low = mid;
        }
    }
    // - -- -
}

#endif // sortedVectorInsert_h
