#include <iostream>
#include <cmath>
#include "Solution.h"

Solution::Solution(int x, int y, const std::list<Pipe > &pipes, const std::list<Element> &source,
                   const std::list<Element> &houses, const std::list<Element> &stones) : x(x), y(y), pipes(pipes),
                                                                                     sources(source), houses(houses), stones(stones) {
    map = new Element**[x];
    for(int i = 0; i < x; ++i){
        map[i] = new Element*[y];

        for(int j = 0; j < y; ++j){
            map[i][j] = Element::createEmptyElement(i, j);
        }
    }

    for (auto & i : source) {
        map[i.x][i.y] = Element::createSourceElement(i.x, i.y);
    }

    for (auto & i : houses) {
        map[i.x][i.y] = Element::createHouseElement(i.x, i.y);
    }

    for (auto & i : stones) {
        map[i.x][i.y] = Element::createStoneElement(i.x, i.y);
    }
}

void Solution::calculate() {
    if(checkEndCondition()){
//        throw throw std::overflow_error("too big");
        return;
    }

    if(!this->pipes.empty()){
        std::list<Element> sourcesCopy = this->sources;

        for(auto cp : sourcesCopy){
            bool flag = true;

//            not deleting source if pipe have many exits
            if(cp.isPipe()){
                flag = false;
            } else {
                this->sources.remove(cp);
            }

            makeMove(cp);

            if (flag){
                this->sources.push_back(cp);
            }
        }

    }

}

bool Solution::checkEndCondition() {
    bool flag = true;

    for (auto i : sources) {
        if(!i.isSource()){
            flag = false;
        }
    }

    if (!flag){
        return false;
    }

    return checkIfHousesAreConnected();
}

bool Solution::checkIfHousesAreConnected() {
    for (auto const& i : sources) {
        if (i.possibilities.size() == 4){
            return false;
        }
    }
    return true;
}

void Solution::printMap() {
    std::cout<<"________________________\n";
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            std::cout<<*(this->map[i][j]);
        }
        std::cout<<"\n";
    }
    std::cout<<"________________________\n";
}

void Solution::makeMove(Element &element) {
    Pipe p = this->pipes.front();

    switch (p){
        case Pipe::I:
            moveProposalForI(element, this->houses);
            break;
        case Pipe::L:break;
        case Pipe::T:break;
        case Pipe::X:break;
    }
}

PairDouble Solution::distanceCooficient(Element start, std::list<Element> destination){
    double x = 0;
    double y = 0;

    for(auto & d : destination){
        double distanceToStart = std::sqrt((d.x - start.x) * (d.x - start.x) + (d.y - start.y) * (d.y - start.y));
        x += d.x - start.x / distanceToStart;
        y += d.y - start.y / distanceToStart;
    }

    return {x,y};
}

Direction* Solution::directionPriority(Element start, std::list<Element> destination){

    PairDouble p = distanceCooficient(start, destination);
    double x = p.x;
    double y = p.y;

    auto * priority_array = new Direction[4];;

    if(std::abs(x) > std::abs(y)) {
        if (x > 0) {
            priority_array[0] = Direction::RIGHT;
            priority_array[3] = Direction::LEFT;
        } else {
            priority_array[0] = Direction::LEFT;
            priority_array[3] = Direction::RIGHT;
        }
        if (y > 0) {
            priority_array[1] = Direction::DOWN;
            priority_array[2] = Direction::UP;
        }
        else {
            priority_array[1] = Direction::UP;
            priority_array[2] = Direction::DOWN;
        }
    } else {
        if (y > 0) {
            priority_array[0] = Direction::DOWN;
            priority_array[3] = Direction::UP;
        }
        else {
            priority_array[0] = Direction::UP;
            priority_array[3] = Direction::DOWN;
        }
        if (x > 0) {
            priority_array[1] = Direction::RIGHT;
            priority_array[2] = Direction::LEFT;
        }
        else {
            priority_array[1] = Direction::LEFT;
            priority_array[2] = Direction::RIGHT;
        }
    }
    return priority_array;
}

template <typename T>
bool contains(std::list<T> & listOfElements, const T & element)
{
    auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
    return it != listOfElements.end();
}

void Solution::moveProposalForI(Element &element, std::list<Element> list) {
}

Element Solution::removePossibilitiesOrRemoveSource(Element start, std::list<Direction> nextDirections, Element addedSource){

    bool flag = true;

    for(auto &m : nextDirections){
        PairInt mp = moveFromPositionInDirection(start.x, start.y, m);

        Element e = *(this->map[mp.x][mp.y]);
        if(e.isPipe()){
            e.possibilities.remove(oppositeDirection(m));
            start.possibilities.remove(m);
            flag = false;
        } else if(e.isHouse()){
            e.possibilities = {};
            start.possibilities.remove(m);
            flag = false;
        }
    }

    if(flag){
        Element* newSource = Element::createPipeElement(start.x, start.y, nextDirections);
        this->sources.push_front(*newSource);
        return *newSource;
    } else{
        return nullptr;
    }
}

void Solution::redoPossibilitiesOrRemoveSource(Element start, std::list<Direction> nextDirections, Element addedSource){
    if (addedSource != nullptr){
        this->sources.remove(addedSource);
    }

    for(auto &m : nextDirections){
        PairInt mp = moveFromPositionInDirection(start.x, start.y, m);

        Element e = *(this->map[mp.x][mp.y]);
        if(e.isPipe()){
            e.possibilities.push_back(oppositeDirection(m));
            start.possibilities.push_back(m);
        } else if(e.isHouse()){
            e.possibilities = {Direction::LEFT, Direction::DOWN, Direction::RIGHT, Direction::UP};
            start.possibilities.push_back(m);
        }
    }
}

bool Solution::check_add_pipe_conditions(Element start, Direction move, std::list<Direction> nextMoves){
    if(!this->checkIfInsideMap(start, move)){
        return false;
    }
    if(!this->checkIfNextInsideMap(start, move, nextMoves)){
        return false;
    }
    if(!this->checkIfNotDestroyElement(start, move)){
        return false;
    }
    if(!this->checkIfCanBeConnected(start, move, nextMoves)){
        return false;
    }
    return true;
}

bool Solution::checkIfCanBeConnected(Element start, Direction move, std::list<Direction> nextMoves){
    PairInt p = moveFromPositionInDirection(start.x, start.y, move);

    for(auto &m : nextMoves){
        PairInt mp = moveFromPositionInDirection(p.x, p.y, m);

        if(this->map[mp.x][mp.y]->isStone()){
            return false;
        }

        if(this->map[mp.x][mp.y]->isPipe() and
           !contains(this->map[mp.x][mp.y]->possibilities, oppositeDirection(move))){
            return false;
        }

        if(this->map[mp.x][mp.y]->isHouse() and
           !contains(this->map[mp.x][mp.y]->possibilities, oppositeDirection(move))){
            return false;
        }
    }
    return true;
}

bool Solution::checkIfInsideMap(Element start, Direction move){
    PairInt p = moveFromPositionInDirection(start.x, start.y, move);

    if(p.x<0 or p.x>= this->x){
        return false;
    }

    if(p.y<0 or p.y>= this->y){
        return false;
    }
    return true;
}

bool Solution::checkIfNextInsideMap(Element start, Direction move, std::list<Direction> nextMoves){
    PairInt p = moveFromPositionInDirection(start.x, start.y, move);

    for(auto &m : nextMoves){
        PairInt mp = moveFromPositionInDirection(p.x, p.y, m);
        if(mp.x<0 or mp.x>= this->x){
            return false;
        }

        if(mp.y<0 or mp.y>= this->y){
            return false;
        }
    }
    return true;
}

bool Solution::checkIfNotDestroyElement(Element start, Direction move){
    PairInt p = moveFromPositionInDirection(start.x, start.y, move);
    Element e = *(this->map[p.x][p.y]);

    return !(e.isStone() or e.isHouse() or e.isPipe());
}

PairInt Solution::moveFromPositionInDirection(int x, int y, Direction direction) {
    switch (direction){
        case Direction::UP:
            return {x, y-1};
        case Direction::RIGHT:
            return {x+1, y};
        case Direction::DOWN:
            return {x, y+1};
        case Direction::LEFT:
            return {x-1, y};
    }
}

Direction Solution::oppositeDirection(Direction direction){
    switch (direction){
        case Direction::UP:
            return Direction::DOWN;
        case Direction::RIGHT:
            return Direction::LEFT;
        case Direction::DOWN:
            return Direction::UP;
        case Direction::LEFT:
            return Direction::RIGHT;
    }
}
