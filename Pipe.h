#ifndef COMPILER_TEST_PIPE_H
#define COMPILER_TEST_PIPE_H

enum class Pipe{
    I,
    L,
    T,
    X
};

enum class PipeAdjustment{
    I1,
    I2,
    L1,
    L2,
    L3,
    L4,
    T1,
    T2,
    T3,
    T4,
    X,
};

enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class PipeLocation{
public:
    int x;
    int y;
    PipeAdjustment pipeAdjustment;

    PipeLocation(int x, int y, PipeAdjustment pipeAdjustment) : x(x), y(y), pipeAdjustment(pipeAdjustment) {}
};

class PairDouble{
public:
    double x;
    double y;

    PairDouble(double x, double y) : x(x), y(y) {}
};

class PairInt{
public:
    int x;
    int y;

    PairInt(int x, int y) : x(x), y(y) {}
};

#endif //COMPILER_TEST_PIPE_H
