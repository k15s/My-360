// [ADDED: ksum, 11/1/2014]

#ifndef CUSTOMTUPLE_H
#define CUSTOMTUPLE_H

class CustomTuple {
public:
    int row;
    int col;
    int distance_from_goal;

    CustomTuple(int r, int c, int d);
};

#endif
