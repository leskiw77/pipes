#ifndef COMPILER_TEST_ELEMENT_H
#define COMPILER_TEST_ELEMENT_H

#include <list>
#include <ostream>
#include "Pipe.h"

enum class ElementType{
    None,
    Source,
    Stone,
    House,
    Pipe
};

class Element {
public:
    int x;
    int y;
    std::list<Direction> possibilities;
    ElementType elementType;

    friend std::ostream &operator<<(std::ostream &os, const Element &element);

    Element(int x, int y, const std::list<Direction> &possibilities, ElementType elementType);

    Element(int x, int y, const std::list<Direction> &possibilities);


};

class Source : public Element{
public:
    Source(int x, int y);

    friend std::ostream &operator<<(std::ostream &os, const Source &source);
};

class Stone : public Element{
public:
    Stone(int x, int y);

    friend std::ostream &operator<<(std::ostream &os, const Stone &stone);
};

class House : public Element{
public:
    House(int x, int y);

    friend std::ostream &operator<<(std::ostream &os, const House &house);
};

class PipeElement : public Element{
public:
    PipeElement(int x, int y, const std::list<Direction> &possibilities);

    friend std::ostream &operator<<(std::ostream &os, const PipeElement &element);
};

class PipeLocation{
public:
    const int x;
    const int y;
    const PipeAdjustment pipeAdjustment;

    PipeLocation(int x, int y, PipeAdjustment pipeAdjustment);
};

#endif //COMPILER_TEST_ELEMENT_H
