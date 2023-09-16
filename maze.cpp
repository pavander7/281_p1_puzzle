//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include "maze.h"
#include <iostream>

using namespace std;

Maze::Maze(){
    cin >> num_colors >> height >> width;
    mazeMap = vector<vector<char> >(height, vector<char>(width, '.'));
    discoverMap = vector<vector<vector<bool> > >(height, vector<vector<bool>>(num_colors, vector<bool>(width, false)));
    if (num_colors < 0 || num_colors > 26) {
        cerr << "Error: Invalid numColor";
        assert(false);
    } if (width <= 1) {
        cerr << "Error: Invalid width";
    } if (height <= 1) {
        cerr << "Error: Invalid height";
    }
    openDoor = 0;
    bool startInit, targetInit = false;
    int maxDoor = 64 + int(num_colors);
    int maxButton = 96 + int(num_colors);
    string junk;
    getline(cin, junk);
    size_t r = 0;
    while (r < height) {
        cout << endl;
        string line;
        if (r == height - 1) {
            char temp;
            //cout << "begin final line: " << endl;
            for (size_t i = 0; i < width; i++) {
                cin >> temp;
                //cout << temp << endl;
                line.push_back(temp);
            } 
            //cout << "hi";
        } else {
            getline(cin,line);
        }
        if (line[0] == '/') {
            cout << "comment detected";
        } else {
            //cout << ": ";
            for (size_t c = 0; c < width; c++) {
                mazeMap[r][c] = line[c];
                cout << line[c];
                if (r == height - 1 && c == width -1) {
                    cout << endl << "the final character is: " << mazeMap[r][c] << endl;
                }
                if (mazeMap[r][c] == '@') {
                    if (startInit) {
                        cerr << "Error: Puzzle must have only one start and one target";
                        assert(false);
                    }
                    start_r = r;
                    start_c = c;
                    startInit = true;
                } else if (mazeMap[r][c] == '?') {
                    if (targetInit) {
                        cerr << "Error: Puzzle must have only one start and one target";
                        assert(false);
                    } else {
                        target_r = r;
                        target_c = c;
                        targetInit = true;
                    }
                } else if (mazeMap[r][c] >= 'a' && mazeMap [r][c] <= 'z') {
                    if ((mazeMap[r][c] - 0) > (maxButton)) {
                        cerr << "Error: Invalid button in map";
                        assert(false);
                    }
                } else if (mazeMap[r][c] <= 'Z' && mazeMap [r][c] >= 'A') {
                    if ((mazeMap[r][c] - 0) > (maxDoor)) {
                        cerr << "Error: Invalid door in map";
                        assert(false);
                    }
                } else if (mazeMap[r][c] == '.' || mazeMap [r][c] == '#' || mazeMap[r][c] == '^');
                else {
                    cerr << "Error: Invalid character in map";
                    cout << "broken: " << mazeMap[r][c] << endl;
                    assert(false);
                }
            } r++; 
        }
    } if (!startInit || !targetInit) {
        cerr << "Error: Puzzle must have exactly one start and one target";
        assert(false);
    }
}

bool Maze::wall(size_t r, size_t c) const {return (mazeMap[r][c] == '#' || !door(r,c));};
bool Maze::button(size_t r, size_t c) const {return ((mazeMap[r][c] >= 97 && mazeMap[r][c] <= 122) || mazeMap[r][c] == '^');};
bool Maze::target(size_t r, size_t c) const {return (r == target_r && c == target_c);};
bool Maze::door(size_t r, size_t c) const {
    if (mazeMap[r][c] >= 65 && mazeMap[r][c] <= 90) {
        return (mazeMap[r][c] == openDoor);
    } else return false;
}

size_t Maze::startRow() {return start_r;}
size_t Maze::startCol() {return start_c;}

player::player(size_t r, size_t c, vector<vector<vector<bool> > > &discoverMap, Maze &y) {
    current_state.row = r;
    current_state.col = c;
    current_state.color = '^';
    discover(current_state, discoverMap, y);
}

bool Maze::solve(state start) {
    player observer = player(start.row, start.col, discoverMap, *this);
    while(!observer.empty()) {
        if (observer.current_state.row == target_r && observer.current_state.col) {
            return true;
        } 
        observer.investigate(button(observer.current_state.row, observer.current_state.col), discoverMap, *this);
        if (solve(observer.current_state)) {
            path.push_front(observer.current_state);
        }
    } return false;
}

void Maze::listOut() {
    cout << "(" << path.front().color << ", (" << 
            path.front().row << ", " << path.front().col << "))";
    path.pop_front();
    while(!path.empty()) {
        cout << endl << "(" << path.front().color << ", (" << 
            path.front().row << ", " << path.front().col << "))";
        path.pop_front();
    }
}

void Maze::mapOut() {
    cout << "(" << path.front().color << ", (" << 
            path.front().row << ", " << path.front().col << "))";
    path.pop_front();
    while(!path.empty()) {
        cout << endl << "(" << path.front().color << ", (" << 
            path.front().row << ", " << path.front().col << "))";
        path.pop_front();
    }
}

void player::discover(state x, vector<vector<vector<bool> > > &discoverMap, Maze &y) {
    if (x.row >= y.width || x.col >= y.height || x.color - 0 >= int(y.num_colors + 97)) {
        return;
    } else if (!y.checkDiscover(x) && !y.wall(x.row, x.col)) {
        if(!style) {
            search_container.push_back(x);
        } else if (style) {
            search_container.push_front(x);
        } discoverMap[x.row][x.col][size_t(x.color - 97)] = true;
    } 
}

bool Maze::checkDiscover(state x){
    return discoverMap[x.row][x.col][size_t(x.color - 97)];
}

bool player::checkButton(state x, Maze &y){
    if (!y.checkDiscover(x)) {
        return true;
    } else return false;
}

void player::investigate(bool button, vector<vector<vector<bool> > > &discoverMap, Maze &y) {
    if (button && checkButton(current_state, y)) {
        discover({current_state.color, current_state.row, current_state.col}, discoverMap, y);
    } else {
        discover({current_state.color, current_state.row - 1, current_state.col}, discoverMap, y); //north
        discover({current_state.color, current_state.row, current_state.col + 1}, discoverMap, y); //east
        discover({current_state.color, current_state.row + 1, current_state.col}, discoverMap, y); //south
        discover({current_state.color, current_state.row, current_state.col - 1}, discoverMap, y); //west
    }
    search_container.pop_front();
    current_state = search_container.front();
}

bool player::empty() {
    return search_container.empty();
}