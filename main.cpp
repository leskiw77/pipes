#include <vector>
#include <iostream>
#include <queue>
#include <fstream>
#include <climits>
#include <cstring>
#include <list>
#include "Element.h"
#include "Solution.h"



int main()
{
    int x = 10;
    int y = 8;
    std::list<Source> sources = {Source(0, 0)};
    std::list<House> houses = {House(0, 3)};
    std::list<Stone> stones = {Stone(1, 4)};
    std::list<Pipe > pipes = {Pipe::I, Pipe::I, Pipe::I};

    auto *s = new Solution(x, y, pipes, sources, houses, stones);
    s->calculate();

    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
//            std::cout<<s->map[i][j]->x<<","<<s->map[i][j]->y<<" ";
//            std::cout<< s->map[i][i]->elementType<<" ";
            std::cout<<*(s->map[i][j]);
        }
        std::cout<<"\n";
    }

    return 0;
}