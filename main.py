import math
from enum import Enum

file = open("testfile.txt", "w")


class Direction(Enum):
    UP = 1
    RIGHT = 2
    DOWN = 3
    LEFT = 4


class Pipe(Enum):
    I = 1
    L = 2
    T = 3
    X = 4


class Element:
    def __init__(self, x, y, possibilities: [Direction]):
        self.possibilities = possibilities
        self.x = x
        self.y = y

    def __str__(self):
        return "X: {} Y: {}".format(self.x, self.y)

    def __repr__(self):
        return "X: {} Y: {}".format(self.x, self.y)


class Source(Element):
    def __init__(self, x, y):
        super().__init__(x, y, [Direction.DOWN, Direction.RIGHT, Direction.UP, Direction.LEFT])


class House(Element):
    def __init__(self, x, y):
        super().__init__(x, y, [Direction.DOWN, Direction.RIGHT, Direction.UP, Direction.LEFT])


class Stone(Element):
    def __init__(self, x, y):
        super().__init__(x, y, [])


class PipeElement(Element):
    def __init__(self, x, y, possibilities: [Direction]):
        super().__init__(x, y, possibilities)


# class PossibleConnection:
#     def __init__(self, element, direction):
#         self.direction = direction
#         self.element = element


class PipeAdjustment(Enum):
    I1 = 1
    I2 = 2
    L1 = 3
    L2 = 4
    L3 = 5
    L4 = 6
    T1 = 7
    T2 = 8
    T3 = 9
    T4 = 10
    X = 11


class PipeLocation:
    def __init__(self, x, y, pipe_adjustment):
        self.x = x
        self.y = y
        self.pipe_adjustment = pipe_adjustment

    def __str__(self):
        return "X: {} Y: {} Elem: {}".format(self.x, self.y, self.pipe_adjustment)

    def __repr__(self):
        return "X: {} Y: {} Elem: {}".format(self.x, self.y, self.pipe_adjustment.name)


class Solution:
    solution = []

    def __init__(self, x, y, sources: [Source], houses: [House], stones: [Stone], pipes):
        self.x = x
        self.y = y
        self.pipes = pipes
        self.map = [[Element(i, j, []) for j in range(y)] for i in range(x)]

        self.sources: [Source] = sources
        self.houses = houses

        for s in stones:
            self.map[s.x][s.y] = s

        for s in houses:
            self.map[s.x][s.y] = s

        for s in sources:
            self.map[s.x][s.y] = s

    def solution_to_string(self):
        l = reversed(self.solution)
        s = ["({},{},{})".format(e.x, e.y, e.pipe_adjustment.name) for e in l]
        return ",".join(s)

    def calculate(self):
        print(self.sources, len(self.pipes))
        file.write('{}\n'.format(self.solution_to_string()))

        if self.solution_to_string() == "(2,2,I2),(3,2,I2),(4,2,I2),(5,2,T3),(6,2,I2),(7,2,L3),(7,3,I1),(5,3,I1),(5,4,I1),(5,5,L4),(4,5,I2)":
            print("dupa")

        if self.check_end_condition():
            print(self.solution)
            raise Exception

        if len(self.pipes) > 0:
            sources_copy = self.sources.copy()

            for cp in sources_copy:
                flag = True
                if type(cp) == PipeElement and len(cp.possibilities) > 1:
                    flag = False
                else:
                    self.sources.remove(cp)

                self.make_move(cp)

                if flag:
                    self.sources.insert(0, cp)
        else:
            print("brak pipe")

    def print_map(self):
        print("____________________________")
        for x in self.map:
            for y in x:
                if type(y) == House:
                    print('X', end='')
                elif type(y) == Source:
                    print('O', end='')
                elif type(y) == PipeElement:
                    print('-', end='')
                elif type(y) == Stone:
                    print('S', end='')
                else:
                    print(' ', end='')
            print()
        print("____________________________")

    def make_move(self, cp):
        if self.pipes[0] == Pipe.I:
            self.move_proposal_for_i(cp, self.houses)

        elif self.pipes[0] == Pipe.L:
            self.move_proposal_for_l(cp, self.houses)

        elif self.pipes[0] == Pipe.T:
            self.move_proposal_for_t(cp, self.houses)

        elif self.pipes[0] == Pipe.X:
            self.move_proposal_for_x(cp, self.houses)

    def distance_cooficient(self, start: Element, destinations: [Element]):
        x = sum([d.x - start.x / math.sqrt((d.x - start.x) ** 2 + (d.y - start.y) ** 2) for d in destinations])
        y = sum([d.y - start.y / math.sqrt((d.x - start.x) ** 2 + (d.y - start.y) ** 2) for d in destinations])
        return x, y

    def direction_priority(self, start: Element, destinations: [Element]):
        x, y = self.distance_cooficient(start, destinations)

        priority_array = [None] * 4
        if abs(x) > abs(y):
            if x > 0:
                priority_array[0] = Direction.RIGHT
                priority_array[3] = Direction.LEFT
            else:
                priority_array[0] = Direction.LEFT
                priority_array[3] = Direction.RIGHT

            if y > 0:
                priority_array[1] = Direction.DOWN
                priority_array[2] = Direction.UP
            else:
                priority_array[1] = Direction.UP
                priority_array[2] = Direction.DOWN
        else:
            if y > 0:
                priority_array[0] = Direction.DOWN
                priority_array[3] = Direction.UP
            else:
                priority_array[0] = Direction.UP
                priority_array[3] = Direction.DOWN

            if x > 0:
                priority_array[1] = Direction.RIGHT
                priority_array[2] = Direction.LEFT
            else:
                priority_array[1] = Direction.LEFT
                priority_array[2] = Direction.RIGHT
        return priority_array

    def check_end_condition(self):
        flag = True
        for s in self.sources:
            if type(s) != Source:
                flag = False
                break

        if not flag:
            return False
        return self.check_if_houses_are_connected()

    def check_if_houses_are_connected(self):
        for house in self.houses:
            if len(house.possibilities) == 4:
                return False
        return True

    def check_house_connected(self, house):
        x, y = house.x, house.y
        if x - 1 >= 0 and Direction.RIGHT in self.map[x - 1][y].possibilities:
            return True

        if x + 1 < self.x and Direction.LEFT in self.map[x + 1][y].possibilities:
            return True

        if y - 1 >= 0 and Direction.DOWN in self.map[x][y - 1].possibilities:
            return True

        if y + 1 < self.y and Direction.UP in self.map[x][y + 1].possibilities:
            return True

        return False

    def move_proposal_for_i(self, start: Element, destinations: [Element]):
        priorities = self.direction_priority(start, destinations)
        for p in priorities:
            for s in start.possibilities:
                if s == p:
                    if p == Direction.UP:
                        self.put_i_pipe_top(start)
                    elif p == Direction.RIGHT:
                        self.put_i_pipe_right(start)
                    elif p == Direction.LEFT:
                        self.put_i_pipe_left(start)
                    elif p == Direction.DOWN:
                        self.put_i_pipe_down(start)

    def put_i_pipe_right(self, start):
        self.put_pipe_element(start, Direction.RIGHT, [Direction.RIGHT], PipeAdjustment.I2)

    def put_i_pipe_left(self, start):
        self.put_pipe_element(start, Direction.LEFT, [Direction.LEFT], PipeAdjustment.I2)

    def put_i_pipe_top(self, start):
        self.put_pipe_element(start, Direction.UP, [Direction.UP], PipeAdjustment.I1)

    def put_i_pipe_down(self, start):
        self.put_pipe_element(start, Direction.DOWN, [Direction.DOWN], PipeAdjustment.I1)

    def move_proposal_for_l(self, start, destinations):
        priorities = self.direction_priority(start, destinations)

        for i in range(len(priorities)):
            for j in range(len(start.possibilities)):
                if priorities[i] == start.possibilities[j]:
                    if i == 0:
                        self.choose_l_pipe_for(start, priorities[0], priorities[1])
                        self.choose_l_pipe_for(start, priorities[0], priorities[2])
                    elif i == 1:
                        self.choose_l_pipe_for(start, priorities[1], priorities[0])
                        self.choose_l_pipe_for(start, priorities[1], priorities[3])
                    elif i == 2:
                        self.choose_l_pipe_for(start, priorities[2], priorities[0])
                        self.choose_l_pipe_for(start, priorities[2], priorities[3])
                    elif i == 3:
                        self.choose_l_pipe_for(start, priorities[3], priorities[1])
                        self.choose_l_pipe_for(start, priorities[3], priorities[2])

    def choose_l_pipe_for(self, start, dir1: Direction, dir2: Direction):
        if dir1 == Direction.UP:
            if dir2 == Direction.RIGHT:
                self.put_l_element_up_right(start)
            elif dir2 == Direction.LEFT:
                self.put_l_element_up_left(start)

        elif dir1 == Direction.RIGHT:
            if dir2 == Direction.UP:
                self.put_l_element_right_up(start)
            elif dir2 == Direction.DOWN:
                self.put_l_element_right_down(start)

        elif dir1 == Direction.DOWN:
            if dir2 == Direction.RIGHT:
                self.put_l_element_down_right(start)
            elif dir2 == Direction.LEFT:
                self.put_l_element_down_left(start)

        elif dir1 == Direction.LEFT:
            if dir2 == Direction.UP:
                self.put_l_element_left_up(start)
            elif dir2 == Direction.DOWN:
                self.put_l_element_left_down(start)

    def put_l_element_up_right(self, start):
        self.put_pipe_element(start, Direction.UP, [Direction.RIGHT], PipeAdjustment.L2)

    def put_l_element_up_left(self, start):
        self.put_pipe_element(start, Direction.UP, [Direction.LEFT], PipeAdjustment.L3)

    def put_l_element_right_up(self, start):
        self.put_pipe_element(start, Direction.RIGHT, [Direction.UP], PipeAdjustment.L4)

    def put_l_element_right_down(self, start):
        self.put_pipe_element(start, Direction.RIGHT, [Direction.DOWN], PipeAdjustment.L3)

    def put_l_element_down_right(self, start):
        self.put_pipe_element(start, Direction.DOWN, [Direction.RIGHT], PipeAdjustment.L1)

    def put_l_element_down_left(self, start):
        self.put_pipe_element(start, Direction.DOWN, [Direction.LEFT], PipeAdjustment.L4)

    def put_l_element_left_up(self, start):
        self.put_pipe_element(start, Direction.LEFT, [Direction.UP], PipeAdjustment.L1)

    def put_l_element_left_down(self, start):
        self.put_pipe_element(start, Direction.LEFT, [Direction.DOWN], PipeAdjustment.L2)

    def move_proposal_for_t(self, start, destinations):
        priorities = self.direction_priority(start, destinations)
        possibilities_copy = start.possibilities.copy()
        for i in range(len(priorities)):
            for j in range(len(possibilities_copy)):
                if priorities[i] == possibilities_copy[j]:
                    if priorities[i] == Direction.UP:
                        self.put_t_up(start)
                    if priorities[i] == Direction.DOWN:
                        self.put_t_down(start)
                    if priorities[i] == Direction.LEFT:
                        self.put_t_left(start)
                    if priorities[i] == Direction.RIGHT:
                        self.put_t_right(start)

    def put_t_up(self, start):
        self.put_pipe_element(start, Direction.UP, [Direction.RIGHT, Direction.LEFT], PipeAdjustment.T3)
        self.put_pipe_element(start, Direction.UP, [Direction.RIGHT, Direction.UP], PipeAdjustment.T2)
        self.put_pipe_element(start, Direction.UP, [Direction.LEFT, Direction.UP], PipeAdjustment.T4)

    def put_t_down(self, start):
        self.put_pipe_element(start, Direction.DOWN, [Direction.RIGHT, Direction.LEFT], PipeAdjustment.T1)
        self.put_pipe_element(start, Direction.DOWN, [Direction.LEFT, Direction.DOWN], PipeAdjustment.T4)
        self.put_pipe_element(start, Direction.DOWN, [Direction.DOWN, Direction.RIGHT], PipeAdjustment.T2)

    def put_t_left(self, start):
        self.put_pipe_element(start, Direction.LEFT, [Direction.UP, Direction.DOWN], PipeAdjustment.T2)
        self.put_pipe_element(start, Direction.LEFT, [Direction.LEFT, Direction.DOWN], PipeAdjustment.T3)
        self.put_pipe_element(start, Direction.LEFT, [Direction.UP, Direction.LEFT], PipeAdjustment.T1)

    def put_t_right(self, start):
        self.put_pipe_element(start, Direction.RIGHT, [Direction.UP, Direction.DOWN], PipeAdjustment.T4)
        self.put_pipe_element(start, Direction.RIGHT, [Direction.RIGHT, Direction.DOWN], PipeAdjustment.T3)
        self.put_pipe_element(start, Direction.RIGHT, [Direction.UP, Direction.RIGHT], PipeAdjustment.T1)

    def move_proposal_for_x(self, start, destinations):
        priorities = self.direction_priority(start, destinations)
        for i in range(len(priorities)):
            for j in range(len(start.possibilities)):
                if priorities[i] == start.possibilities[j]:
                    if priorities[i] == Direction.UP:
                        self.put_x_up(start)
                    if priorities[i] == Direction.DOWN:
                        self.put_x_down(start)
                    if priorities[i] == Direction.LEFT:
                        self.put_x_left(start)
                    if priorities[i] == Direction.RIGHT:
                        self.put_x_right(start)

    def put_x_up(self, start):
        self.put_pipe_element(start, Direction.UP, [Direction.RIGHT, Direction.UP, Direction.LEFT], PipeAdjustment.X)

    def put_x_down(self, start):
        self.put_pipe_element(start, Direction.DOWN, [Direction.UP, Direction.LEFT, Direction.DOWN], PipeAdjustment.X)

    def put_x_left(self, start):
        self.put_pipe_element(start, Direction.LEFT, [Direction.UP, Direction.LEFT, Direction.DOWN], PipeAdjustment.X)

    def put_x_right(self, start):
        self.put_pipe_element(start, Direction.RIGHT, [Direction.RIGHT, Direction.UP, Direction.DOWN], PipeAdjustment.X)

    def put_pipe_element(self, start, move: Direction, next_moves: [Direction], pipe_adjustment):
        if not self.check_add_pipe_conditions(start, move, next_moves):
            return

        pipe = self.pipes.pop(0)
        start.possibilities.remove(move)
        next_x, next_y = self.move_from_position_in_direction(start.x, start.y, move)

        f = PipeLocation(next_x, next_y, pipe_adjustment)
        added_pipe = PipeElement(next_x, next_y, next_moves)

        current_elem = self.map[next_x][next_y]
        self.map[next_x][next_y] = added_pipe
        self.solution.insert(0, f)

        new_source = self.remove_possibilities_or_add_source(added_pipe, next_moves)

        self.print_map()
        self.calculate()

        self.redo_possibilities_or_remove_source(added_pipe, next_moves, new_source)
        self.map[next_x][next_y] = current_elem
        self.pipes.insert(0, pipe)
        start.possibilities.append(move)
        self.solution.remove(f)

    def remove_possibilities_or_add_source(self, start: Element, next_directions: [Direction]):
        flag = True

        for m in next_directions:
            m_x, m_y = self.move_from_position_in_direction(start.x, start.y, m)

            if type(self.map[m_x][m_y]) == PipeElement:
                self.map[m_x][m_y].possibilities.remove(self.opposite_direction(m))
                start.possibilities.remove(m)
                flag = False

            if type(self.map[m_x][m_y]) == House:
                self.map[m_x][m_y].possibilities = []
                flag = False

        if flag:
            new_source = PipeElement(start.x, start.y, next_directions)
            self.sources.insert(0, new_source)
            return new_source
        else:
            return None

    def redo_possibilities_or_remove_source(self, start: Element, next_directions: [Direction], added_source):
        if added_source is not None:
            self.sources.remove(added_source)
            return

        for m in next_directions:
            m_x, m_y = self.move_from_position_in_direction(start.x, start.y, m)

            if type(self.map[m_x][m_y]) == PipeElement:
                self.map[m_x][m_y].possibilities.append(self.opposite_direction(m))
                start.possibilities.append(m)

            if type(self.map[m_x][m_y]) == House:
                self.map[m_x][m_y].possibilities = [Direction.DOWN, Direction.RIGHT, Direction.UP, Direction.LEFT]

    def check_add_pipe_conditions(self, start, move: Direction, next_moves: [Direction]):
        if not self.check_if_move_inside_map(start, move):
            return False

        if not self.check_if_next_inside_map(start, move, next_moves):
            return False

        if not self.check_if_not_destroy_element(start, move):
            return False

        if not self.check_if_can_be_connected(start, move, next_moves):
            return False

        return True

    def check_if_can_be_connected(self, start, move, next_moves: [Direction]):
        x, y = self.move_from_position_in_direction(start.x, start.y, move)

        for m in next_moves:
            m_x, m_y = self.move_from_position_in_direction(x, y, m)
            if type(self.map[m_x][m_y]) in [Stone]:
                return False

            if type(self.map[m_x][m_y]) == PipeElement\
                    and self.opposite_direction(m) not in self.map[m_x][m_y].possibilities:
                return False

            if type(self.map[m_x][m_y]) == House and self.opposite_direction(m) not in self.map[m_x][m_y].possibilities:
                return False

        return True

    def check_if_move_inside_map(self, start, move: Direction):
        x, y = self.move_from_position_in_direction(start.x, start.y, move)
        if x < 0 or x >= self.x:
            return False

        if y < 0 or y >= self.y:
            return False
        return True

    def check_if_next_inside_map(self, start, move: Direction, next_moves: [Direction]):
        x, y = self.move_from_position_in_direction(start.x, start.y, move)

        for m in next_moves:
            m_x, m_y = self.move_from_position_in_direction(x, y, m)
            if m_x < 0 or m_x >= self.x:
                return False

            if m_y < 0 or m_y >= self.y:
                return False
        return True

    def check_if_not_destroy_element(self, start, move: Direction):
        x, y = self.move_from_position_in_direction(start.x, start.y, move)
        if type(self.map[x][y]) in [Stone, House, PipeElement]:
            return False
        return True

    def move_from_position_in_direction(self, x, y, direction):
        if direction == Direction.UP:
            return x, y - 1
        if direction == Direction.DOWN:
            return x, y + 1
        if direction == Direction.LEFT:
            return x - 1, y
        if direction == Direction.RIGHT:
            return x + 1, y

    def opposite_direction(self, direction):
        if direction == Direction.UP:
            return Direction.DOWN
        if direction == Direction.DOWN:
            return Direction.UP
        if direction == Direction.LEFT:
            return Direction.RIGHT
        if direction == Direction.RIGHT:
            return Direction.LEFT


x = 10
y = 8

# sources = [Source(0, 0), Source(1, 1)]
# houses = [House(4, 1), House(0, 4)]
# stones = [Stone(0, 3)]
# pipes = [Pipe.I, Pipe.I, Pipe.I, Pipe.I, Pipe.I, Pipe.I]

sources = [Source(1, 2)]
houses = [House(3, 5), House(7, 4)]
stones = []
pipes = [Pipe.I, Pipe.I, Pipe.I, Pipe.T, Pipe.I, Pipe.L, Pipe.I, Pipe.I, Pipe.I, Pipe.L, Pipe.I]

Solution(x, y, sources, houses, stones, pipes).calculate()

file.close()