//
// Created by jarema on 27.06.18.
//

#ifndef COMPILER_TEST_SOLUTION_H
#define COMPILER_TEST_SOLUTION_H


#include <list>
#include <array>
#include "Pipe.h"
#include "Element.h"

class Solution {
public:
    int x;
    int y;
    std::list<Pipe> pipes;
    std::list<Source> source;
    std::list<House> houses;
    std::list<Stone> stones;

    Element *** map;

    Solution(int x, int y, const std::list<Pipe> &pipes, const std::list<Source> &source,
             const std::list<House> &houses, const std::list<Stone> &stones);

public:
    void calculate();

private:
    bool checkEndCondition();
    bool checkIfHousesAreConnected();


};


#endif //COMPILER_TEST_SOLUTION_H
