//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <maze.h>
#include <iostream>

using namespace std;

Maze::Maze(){
    cin >> num_colors >> height >> width;
    start_r = start_c = target_r = target_c = -1;
    mazeMap.reserve(height);
    for (int q = 0; q < height; q++) {
        mazeMap[q].reserve(width);
    }
    if (num_colors < 0 || num_colors > 26) {
        cerr << "Error: Invalid numColor";
        assert(false);
    } if (width <= 1) {
        cerr << "Error: Invalid width";
    } if (height <= 1) {
        cerr << "Error: Invalid height";
    }
    openDoor = 0;
    for (int r = 0; r < height; r++) {
        for (int c = 0; r < width; c++) {
            cin >> mazeMap[r][c];
            if (mazeMap[r][c] == '@') {
                if (start_r != -1 || start_c != -1) {
                    cerr << "Error: Puzzle must have only one start and one target";
                    assert(false);
                }
                start_r = r;
                start_c = c;
            } else if (mazeMap[r][c] == '?') {
                if (target_r != -1 || target_c != -1) {
                    cerr << "Error: Puzzle must have only one start and one target";
                    assert(false);
                }
                target_r = r;
                target_c = c;
            } else if (mazeMap[r][c] <= 'a' && mazeMap [r][c] >= 'z') {
                if (mazeMap[r][c] > (96 + num_colors)) {
                    cerr << "Error: Invalid button in map";
                    assert(false);
                }
            } else if (mazeMap[r][c] <= 'A' && mazeMap [r][c] >= 'A') {
                if (mazeMap[r][c] > (96 + num_colors)) {
                    cerr << "Error: Invalid door in map";
                    assert(false);
                }
            } else if (mazeMap[r][c] == '.' || mazeMap [r][c] >= '#' || mazeMap[r][c] == '^');
            else {
                cerr << "Error: Invalid character in map";
                assert(false);
            }
        }
    } if (start_r == -1 || start_c == -1 || target_r == -1 || target_c == -1) {
        cerr << "Error: Puzzle must have exactly one start and one target";
        assert(false);
    }
}

int Maze::startRow() const {return start_r;};
int Maze::startCol() const {return start_c;};
int Maze::targetRow() const {return target_r;};
int Maze::targetCol() const {return target_c;};

bool Maze::wall(int r, int c) const {return (mazeMap[r][c] == '#' || !door(r,c));};
bool Maze::button(int r, int c) const {return ((mazeMap[r][c] >= 97 && mazeMap[r][c] <= 122) || mazeMap[r][c] == '^');};
bool Maze::target(int r, int c) const {return (r == target_r && c == target_c);};
bool Maze::door(int r, int c) const {
    if (mazeMap[r][c] >= 65 && mazeMap[r][c] <= 90) {
        return (mazeMap[r][c] == openDoor);
    } else return false;
}

void Maze::press(int r, int c) {
    if (mazeMap[r][c] == '^') {
            openDoor = 0;
        } else openDoor = mazeMap[r][c] - 32;
}

struct Maze::state {
    char color;
    int row;
    int col;
};

Maze::player::player(int r, int c) {
    current_state.row = r;
    current_state.col = c;
    current_state.color = '^';
    discover(current_state);
}

void Maze::solve() {
    player observer = player(start_r, start_c);
    while(!checkDiscover({observer.current_state.color, target_r, target_c})) {
        investigate(button(observer.current_state.))
    }
}

void Maze::player::discover(state x) {
    if (x.row >= width || x.col >= height || x.color >= (num_colors + 97)) {
        return;
    } else if (!checkDiscover(x) && !wall(x.row, x.col)) {
        if(!style) {
            search_container.push_back(x);
        } else if (style) {
            search_container.push_front(x);
        } discoverMap[x.row][x.col][x.color - 97] = true;
    } 
}

bool Maze::player::checkDiscover(state x){
    return discoverMap[x.row][x.col][x.color - 97];
}

bool Maze::player::checkButton(state x){
    if (!checkDiscover(x)) {
        return true;
    } else return false;
}

void Maze::player::investigate(bool button, char color) {
    if (button && checkButton(current_state)) {
        discover({color, current_state.row, current_state.col});
    } else {
        discover({current_state.color, current_state.row - 1, current_state.col}); //north
        discover({current_state.color, current_state.row, current_state.col + 1}); //east
        discover({current_state.color, current_state.row + 1, current_state.col}); //south
        discover({current_state.color, current_state.row, current_state.col - 1}); //west
    }
    search_container.pop_front();
    current_state = search_container.front();
}
