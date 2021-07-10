#include <iostream>
using namespace std;


class AU {
public:
    static int* concat(int s1[], int s2[], int size) {
        int* p = new int[size*2];
        if(!p) return NULL;

        for(int i=0;i<size;i++) p[i] = s1[i];
        for(int i=0;i<size;i++) p[i+size] = s2[i];
        return p;
    };
    static int* remove(int s1[], int s2[], int size, int&retSize) {
        int* p = new int[size*2];
        if(!p) return NULL;
        int k = 0;
        for (int i = 0; i < size; i++) {
            int j;
            for(j = 0; j< size; j++) {
                if(s1[i] == s2[j]){
                    break;
                };
            };
            if(j == size) {
                p[k] = s1[i];
                k++;
            };
        };
        retSize = k;
        if(k ==0) return NULL;
        int* q = new int[retSize];
        if(!q) {retSize = 0; return NULL;};
        for(int i=0; i<retSize; i++) q[i] = p[i];
        delete [] p;
        return q;
    };
};