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

    Element * s1 = Element::createSourceElement(0,0);
    std::list<Element> sources = {*s1};

    Element * h1 = Element::createHouseElement(0, 3);
    std::list<Element> houses = {*h1};

    std::list<Element> stones = {};

    std::list<Pipe> pipes = {Pipe::I, Pipe::I, Pipe::I};

    auto *s = new Solution(x, y, pipes, sources, houses, stones);
    s->calculate();
s->printMap();


    return 0;
}