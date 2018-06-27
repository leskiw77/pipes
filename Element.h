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

    static Element * createEmptyElement(int x, int y);

    static Element * createSourceElement(int x, int y);

    static Element * createStoneElement(int x, int y);

    static Element * createHouseElement(int x, int y);

    static Element * createPipeElement(int x, int y, std::list<Direction> &possibilities);

    bool isNone();

    bool isSource()const;

    bool isStone();

    bool isHouse();

    bool isPipe()const;

    bool operator==(const Element &rhs) const;

    bool operator!=(const Element &rhs) const;
};

#endif //COMPILER_TEST_ELEMENT_H
