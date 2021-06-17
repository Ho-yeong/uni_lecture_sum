#ifndef RANDOM
#define RANDOM

#include<cstdlib>
#include<ctime>

class Random {

public:
    Random();
    int next();
    int nextInRange(int start, int end);
};

Random:: Random() {
    srand((unsigned)time(0));
};

int Random:: next() {
    return rand();
};

int Random:: nextInRange(int start, int end) {
    int range = (end - start) + 1;
    return start + (rand() % range);
}


#endif