//
// Created by jarema on 26.06.18.
//

#include "Element.h"


Element::Element(int x, int y, const std::list<Direction> &possibilities, ElementType elementType) : x(x), y(y),
                                                                                                     possibilities(
                                                                                                             possibilities),
                                                                                                     elementType(
                                                                                                             elementType) {}

Element::Element(int x, int y, const std::list<Direction> &possibilities) : x(x), y(y),
                                                                            possibilities(possibilities),
                                                                            elementType(ElementType::None) {}

std::ostream &operator<<(std::ostream &os, const Element &element) {
    os << " ";
    return os;
}

Source::Source(int x, int y) : Element(x, y, {Direction::LEFT, Direction::DOWN, Direction::RIGHT, Direction::UP},
                                       ElementType::Source) {}

Stone::Stone(int x, int y) : Element(x, y, {}, ElementType::Stone) {}

House::House(int x, int y) : Element(x, y, {Direction::LEFT, Direction::DOWN, Direction::RIGHT, Direction::UP},
                                     ElementType::House) {}

PipeElement::PipeElement(int x, int y, const std::list<Direction> &possibilities) : Element(x, y, possibilities,
                                                                                            ElementType::Pipe) {}

PipeLocation::PipeLocation(const int x, const int y, const PipeAdjustment pipeAdjustment) : x(x), y(y), pipeAdjustment(
        pipeAdjustment) {}

std::ostream &operator<<(std::ostream &os, const Source &source) {
    os << "O";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Stone &stone) {
    os << "S";
    return os;
}

std::ostream &operator<<(std::ostream &os, const House &house) {
    os << "X";
    return os;
}

std::ostream &operator<<(std::ostream &os, const PipeElement &element) {
    os << "-";
    return os;
}

