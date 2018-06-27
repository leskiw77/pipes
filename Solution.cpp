//
// Created by jarema on 27.06.18.
//

#include <iostream>
#include "Solution.h"

Solution::Solution(int x, int y, const std::list<Pipe> &pipes, const std::list<Source> &source,
                   const std::list<House> &houses, const std::list<Stone> &stones) : x(x), y(y), pipes(pipes),
                                                                                     source(source), houses(houses), stones(stones) {
    map = new Element**[x];
    for(int i = 0; i < x; ++i){
        map[i] = new Element*[y];

        for(int j = 0; j < y; ++j){
            map[i][j] = new Element(i,j,{});
        }
    }


    for (auto & i : source) {
        map[i.x][i.y] = new Source(i.x, i.y);
    }

    for (auto & i : houses) {
        map[i.x][i.y] = new House(i.x, i.y);
    }

    for (auto & i : stones) {
        map[i.x][i.y] = new Stone(i.x, i.y);
    }
}

void Solution::calculate() {
    if(checkEndCondition()){
//        throw throw std::overflow_error("too big");
        return;
    }

}

bool Solution::checkEndCondition() {
    bool flag = true;

    for (auto const& i : source) {
        if(typeid(i) != typeid(Source)){
            flag = false;
            break;
        }
    }

    if (!flag){
        return false;
    }

    return checkIfHousesAreConnected();
}

bool Solution::checkIfHousesAreConnected() {
    for (auto const& i : source) {
        if (i.possibilities.size() == 4){
            return false;
        }
    }
    return true;
}


