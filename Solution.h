//
// Created by jarema on 27.06.18.
//

#ifndef COMPILER_TEST_SOLUTION_H
#define COMPILER_TEST_SOLUTION_H

#include <algorithm>
#include <list>
#include <array>
#include "Pipe.h"
#include "Element.h"

class Solution {
public:
    int x;
    int y;
    std::list<Pipe> pipes;
    std::list<Element> sources;
    std::list<Element> houses;
    std::list<Element> stones;

    Element *** map;

    Solution(int x, int y, const std::list<Pipe > &pipes, const std::list<Element> &source,
             const std::list<Element> &houses, const std::list<Element> &stones);

public:
    void calculate();
    void printMap();

private:
    bool checkEndCondition();
    bool checkIfHousesAreConnected();
    void makeMove(Element &element);

    void moveProposalForI(Element &element, std::list<Element> list);

    PairDouble distanceCooficient(Element start, std::list<Element> destination);

    Direction *directionPriority(Element start, std::list<Element> destination);

    PairInt moveFromPositionInDirection(int x, int y, Direction direction);

    Direction oppositeDirection(Direction direction);

    bool checkIfNotDestroyElement(Element start, Direction move);

    bool checkIfNextInsideMap(Element start, Direction move, std::list<Direction> nextMoves);

    bool checkIfInsideMap(Element start, Direction move);

    bool checkIfCanBeConnected(Element start, Direction move, std::list<Direction> nextMoves);

    bool check_add_pipe_conditions(Element start, Direction move, std::list<Direction> nextMoves);

    void redoPossibilitiesOrRemoveSource(Element start, std::list<Direction> nextDirections);

    void redoPossibilitiesOrRemoveSource(Element start, std::list<Direction> nextDirections, Element addedSource);

    Element removePossibilitiesOrRemoveSource(Element start, std::list<Direction> nextDirections, Element addedSource);
};


#endif //COMPILER_TEST_SOLUTION_H
