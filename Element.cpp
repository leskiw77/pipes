//
// Created by jarema on 26.06.18.
//

#include "Element.h"


Element::Element(int x, int y, const std::list<Direction> &possibilities, ElementType elementType) : x(x), y(y),
                                                                                                     possibilities(
                                                                                                             possibilities),
                                                                                                     elementType(
                                                                                                             elementType) {}

Element *Element::createEmptyElement(int x, int y) {
    return new Element(x, y, {}, ElementType::None);
}

Element *Element::createSourceElement(int x, int y) {
    return new Element(x, y, {Direction::LEFT, Direction::DOWN, Direction::RIGHT, Direction::UP}, ElementType::Source);
}

Element *Element::createStoneElement(int x, int y) {
    return new Element(x, y, {}, ElementType::Stone);
}

Element *Element::createHouseElement(int x, int y) {
    return new Element(x, y, {Direction::LEFT, Direction::DOWN, Direction::RIGHT, Direction::UP}, ElementType::House);
}

Element *Element::createPipeElement(int x, int y, std::list<Direction> &possibilities) {
    return new Element(x, y, possibilities, ElementType::Pipe);
}

std::ostream &operator<<(std::ostream &os, const Element &element) {

    switch(element.elementType) {
        case ElementType::None :
            os << ' ';
            break;
        case ElementType::Source:
            os << 'O';
            break;
        case ElementType::Stone:
            os << 'S';
            break;
        case ElementType::House:
            os << 'X';
            break;
        case ElementType::Pipe:
            os << '-';
            break;
    }
    return os;
}

bool Element::isNone() {
    return this->elementType == ElementType::None;
}

bool Element::isSource()const {
    return this->elementType == ElementType::Source;
}

bool Element::isStone() {
    return this->elementType == ElementType::Stone;
}

bool Element::isHouse() {
    return this->elementType == ElementType::House;
}

bool Element::isPipe()const {
    return this->elementType == ElementType::Pipe;
}

bool Element::operator==(const Element &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           elementType == rhs.elementType;
}

bool Element::operator!=(const Element &rhs) const {
    return !(rhs == *this);
}
