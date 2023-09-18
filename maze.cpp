//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include "maze.h"
#include <iostream>


using namespace std;

Maze::Maze(bool styleIn){
    style = styleIn;
    cin >> num_colors >> height >> width;
    mazeMap = vector<vector<char> >(height, vector<char>(width, '.'));
    discoverMap = vector<vector<vector<bool> > >(height, vector<vector<bool>>(width, vector<bool>(num_colors + 1, false)));
    for (size_t q = 0; q < num_colors; q++) {
        cout << "color " << q << " :" << endl;
        for (size_t r = 0; r < height; r++) {
            for (size_t c = 0; c < width; c++) {
                cout << discoverMap[r][c][q];
            } cout << endl;
        } cout << endl;
    } 
        cout << "color " << num_colors << " (trap) :" << endl;
        for (size_t r = 0; r < height; r++) {
            for (size_t c = 0; c < width; c++) {
                cout << discoverMap[r][c][num_colors];
            } cout << endl;
        } cout << endl;
    if (num_colors > 26) {
        cerr << "Error: Invalid numColor";
        assert(false);
    } if (width < 1) {
        cerr << "Error: Invalid width";
    } if (height < 1) {
        cerr << "Error: Invalid height";
    }
    openDoor = '^';
    bool startInit = false;
    bool targetInit = false;
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
    } path.push_front({'0', target_r, target_c});
    cout << endl << endl;
}

bool Maze::wall(state x) const {return (mazeMap[x.row][x.col] == '#' || door(x));}
bool Maze::button(state x) const {
    return ((mazeMap[x.row][x.col] >= 97 && mazeMap[x.row][x.col] <= 122) || mazeMap[x.row][x.col] == '^');
}
bool Maze::door(state x) const {
    if (mazeMap[x.row][x.col] >= 65 && mazeMap[x.row][x.col] <= 90) {
        return (mazeMap[x.row][x.col] != x.color - 32);
    } else return false;
}

size_t Maze::startRow() {return start_r;}
size_t Maze::startCol() {return start_c;}

player::player(state startIn, vector<vector<vector<bool> > > &discoverMap, Maze &y, bool root) {
    style = y.style;
    current_state.row = startIn.row;
    current_state.col = startIn.col;
    current_state.color = startIn.color;
    if (root) {
        cout << "discovering start position" << endl;
        discover(current_state, discoverMap, y);
    } else {
        cout << "known start position" << endl;
    }
}

size_t Maze::solve(state start, bool root) {
    cout << "solve on " << "(" << start.color << ", ("
                    << start.row << ", " << start.col << "))" 
                    << endl;
    player observer = player({start.color, start.row, start.col}, discoverMap, *this, root);
    while(!observer.empty()) {
        cout << "starting new solve instance" << endl;
        if (observer.current_state.row == target_r && observer.current_state.col == target_c) {
            cout << "target found" << endl;
            return 0;
        } 
        bool isButton = button(start);
        observer.investigate(isButton, discoverMap, *this);
        cout << "investigate finished on " << "(" << start.color << ", ("
                    << start.row << ", " << start.col << "))" << endl;
        if (solve(observer.current_state, false) == 0) {
            path.push_front(observer.current_state);
            cout << "updating path" << endl;
            return 0;
        } else {
            cout << "branch failed from " << "(" << start.color << ", ("
                    << start.row << ", " << start.col << "))" << endl;
            return 1;
        } 
    } return 2;
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
    cout << "starting discover instance on " << "(" << x.color << ", ("
                    << x.row << ", " << x.col << "))" 
                    << endl;
    if (x.row >= y.width || x.col >= y.height || x.color - 0 >= int(y.num_colors + 97)) {
        cout << "shouldn't be here" << endl;
        return;
    } else if (!y.checkDiscover(x) && !y.wall(x)) { 
        cout << "checking..." << endl;
        if(!style) {
            search_container.push_back(x);
            cout << "pushed back " << "(" << search_container.back().color << ", (" << 
                    search_container.back().row << ", " << search_container.back().col << "))" << endl; 
        } else if (style) {
            search_container.push_front(x);
            cout << "pushed front " << "(" << search_container.front().color << ", (" << 
                    search_container.front().row << ", " << search_container.front().col << "))" << endl; 
        } if (x.color == '^') {
            discoverMap[x.row][x.col][y.num_colors] = true;
        } else discoverMap[x.row][x.col][size_t(x.color - 97)] = true;
    } else {
        cout << "how did I get here" << endl;
    }
}

bool Maze::checkDiscover(state x){
    if (x.row >= width || x.col >= height || x.color - 0 >= int(num_colors + 97)) {
        return true;
    } else {
        if (x.color == '^') {
            return discoverMap[x.row][x.col][num_colors];
        } else return discoverMap[x.row][x.col][size_t(x.color - 97)];
    }
}

bool player::checkButton(state x, Maze &y){
    if (!y.checkDiscover(x)) {
        return true;
    } else return false;
}

void player::investigate(bool button, vector<vector<vector<bool> > > &discoverMap, Maze &y) {
    cout << "starting investigate instance" << endl;
    if (button && checkButton(current_state, y)) {
        cout << "investigating button" << endl;
        discover({current_state.color, current_state.row, current_state.col}, discoverMap, y);
    } else {
        cout << "investigating surroundings" << endl;
        if (current_state.row > 0)
            discover({current_state.color, current_state.row - 1, current_state.col}, discoverMap, y); //north
        if (current_state.col < y.width)
            discover({current_state.color, current_state.row, current_state.col + 1}, discoverMap, y); //east
        if (current_state.row < y.height)
            discover({current_state.color, current_state.row + 1, current_state.col}, discoverMap, y); //south
        if (current_state.col > 0)
            discover({current_state.color, current_state.row, current_state.col - 1}, discoverMap, y); //west
    }
    search_container.pop_front();
    current_state = search_container.front();
}

bool player::empty() {
    return search_container.empty();
}