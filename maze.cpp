//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include "maze.h"

using namespace std;

Maze::Maze(bool styleIn){
    style = styleIn;
    cin >> num_colors >> height >> width;
    mazeMap = vector<vector<char> >(height, vector<char>(width, '.'));
    discoverMap = vector<vector<vector<bool> > >(height, vector<vector<bool>>(width, vector<bool>(num_colors + 1, false)));
    for (size_t q = 0; q < num_colors; q++) {
        cout << "color " << q << ":" << endl;
        for (size_t r = 0; r < height; r++) {
            for (size_t c = 0; c < width; c++) {
                cout << discoverMap[r][c][q];
            } cout << endl;
        } cout << endl;
    } 
        cout << "color " << num_colors << " (trap):" << endl;
        for (size_t r = 0; r < height; r++) {
            for (size_t c = 0; c < width; c++) {
                cout << discoverMap[r][c][num_colors];
            } cout << endl;
        }
    if (num_colors > 26) {
        cerr << "Error: Invalid numColor";
        assert(false);
    } if (width < 1) {
        cerr << "Error: Invalid width";
    } if (height < 1) {
        cerr << "Error: Invalid height";
    }
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
    }
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

node* Maze::solve(state start, bool root) {
    cout << "solve on " << "(" << start.color << ", ("
                    << start.row << ", " << start.col << "))" 
                    << endl;
    player observer = player(start, discoverMap, *this, root);
    while(!observer.empty()) {
        cout << "starting new solve instance" << endl;
        if (observer.front().datum.row == target_r && observer.front().datum.col == target_c) {
            cout << "target found" << endl;
            return observer.frontPoint();
        } 
        if (!observer.investigate(button(start), discoverMap, *this)) {
            cout << "branch failed from " << "(" << start.color << ", ("
                    << start.row << ", " << start.col << "))" << endl;
            return nullptr;
        }
        cout << "investigate finished on " << "(" << start.color << ", ("
                    << start.row << ", " << start.col << "))" << endl;
    } return nullptr;
}

void Maze::listOut(node begin) {
    deque<state> path;
    node* current = new node{begin};
    while ((*current).prev != nullptr) {
        path.push_front((*current).datum);
        current->evacuate();
        delete &current;
    } while (!(path.empty())) {
        cout << endl << "(" << path.front().color << ", (" << 
            path.front().row << ", " << path.front().col << "))";
        path.pop_front();
    }
}

void Maze::mapOut() {
    //tbi
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
