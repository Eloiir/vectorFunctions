/**
*   A simple example of usage
**/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "sortedVectorInsert.h"

using namespace std;

class _Test{
    public:
    int id;
    int value;
    _Test(int _id, int _value){
        value = _value;
        id = _id;
    }
};

int main(){
    srand(time(NULL));
    // - SORTED INSERT SHOWCASE -
    vector<int> v;

    cout << "sortedInsert() showcase: " << endl;
    for(int i = 0; i < 50; i++){
        sortedInsert(v, rand()%20, false);
    }

    for(unsigned int i = 0; i < v.size(); i++){
        cout << v[i] << ' ';
    }
    cout << endl;
    // - --- -

    // - SORTED INSERT OBJECT SHOWCASE -
    vector<_Test> v2;

    cout << "sortedObjectInsert() showcase: " << endl;
    for(unsigned int i = 0; i < 50; i++){
        _Test temp(i, rand()%20);
        int* ptr = (i) ? &v2[0].value : nullptr;
        sortedObjectInsert<_Test, int>(v2, temp, ptr);
        //  Or just:
        //  sortedObjectInsert(v2, temp, ptr);
    }
    for(unsigned int i = 0; i < v2.size(); i++){
        cout << v2[i].value << ' ';
    }
    cout << endl;
    // - --- -

    return 0;
}
