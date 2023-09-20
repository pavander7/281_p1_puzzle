//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include "header.h"

using namespace std;

Maze::Maze(bool styleIn, bool &error){
    cin >> num_colors >> height >> width;
    if (num_colors > 26) {
        cerr << "Error: Invalid numColor";
        exit(1);
        return;
    } 
    if (width < 1) {
        cerr << "Error: Invalid width";
        exit(1);
        return;
    } if (height < 1) {
        cerr << "Error: Invalid height";
        exit(1);
        return;
    }
    mazeMap = vector<vector<char> >(height, vector<char>(width, '.'));
    discoverMap = vector<vector<vector<char> > >(height, vector<vector<char>>(width));
    style = styleIn;
    /*for (size_t q = 0; q < num_colors; q++) {
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
    } */
    bool startInit = false;
    bool targetInit = false;
    int maxDoor = 64 + int(num_colors);
    int maxButton = 96 + int(num_colors);
    string line;
    getline(cin, line);
    size_t r = 0;
    while (r < height) {
        line = "";
        //cout << endl << r << endl;
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
            //cout << "comment detected: " << line;
        } else {
            //cout << ": ";
            for (size_t c = 0; c < width; c++) {
                mazeMap[r][c] = line[c];
                //cout << line[c];
                if (mazeMap[r][c] == '@') {
                    if (startInit) {
                        cerr << "Error: Puzzle must have only one start and one target";
                        error = true;
                        return;
                    }
                    start_r = r;
                    start_c = c;
                    startInit = true;
                } else if (mazeMap[r][c] == '?') {
                    if (targetInit) {
                        cerr << "Error: Puzzle must have only one start and one target";
                        error = true;
                        return;
                    } else {
                        target_r = r;
                        target_c = c;
                        targetInit = true;
                    }
                } else if (mazeMap[r][c] >= 'a' && mazeMap [r][c] <= 'z') {
                    if ((mazeMap[r][c] - 0) > (maxButton)) {
                        cerr << "Error: Invalid button in map";
                        error = true;
                        return;
                    }
                } else if (mazeMap[r][c] <= 'Z' && mazeMap [r][c] >= 'A') {
                    if ((mazeMap[r][c] - 0) > (maxDoor)) {
                        cerr << "Error: Invalid door in map";
                        error = true;
                        return;
                    }
                } else if (mazeMap[r][c] == '.' || mazeMap [r][c] == '#' || mazeMap[r][c] == '^');
                else {
                    cerr << "Error: Invalid character in map";
                    //cout << "broken: " << mazeMap[r][c] << endl;
                    error = true;
                    return;
                }
            } r++; 
        }
    } if (!startInit || !targetInit) {
        cerr << "Error: Puzzle must have exactly one start and one target";
        error = true;
        return;
    }
    //cout << endl << endl;
}

bool Maze::wall(state x) const {return (mazeMap[x.row][x.col] == '#' || door(x));}
bool Maze::button(state x) const {
    bool result = ((mazeMap[x.row][x.col] >= 97 && mazeMap[x.row][x.col] <= 122) || mazeMap[x.row][x.col] == '^');
    //cout << x.color << " " << mazeMap[x.row][x.col] << endl;
    if (x.color == mazeMap[x.row][x.col]) return false;
    else return result;
}
bool Maze::door(state x) const {
    if (mazeMap[x.row][x.col] >= 65 && mazeMap[x.row][x.col] <= 90) {
        return (mazeMap[x.row][x.col] != x.color - 32);
    } else return false;
}

size_t Maze::startRow() {return start_r;}
size_t Maze::startCol() {return start_c;}

void Maze::mazeOut() {
    for (size_t r = 0; r < height; r++) {
        for (size_t c = 0; c < width; c++) {
            if (discoverMap[r][c].size() > 0) cout << mazeMap[r][c];
            else cout << '#';
        } cout << "\n";
    }
}

bool Maze::solve(state start) {
    /* cout << "solve on " << "(" << start.color << ", ("
                    << start.row << ", " << start.col << "))" 
                    << endl; */
    player observer = player(start, discoverMap, *this);
    while(!observer.empty()) {
        state spyglass = observer.front().datum;
        /* cout << "solve on " << "(" << spyglass.color << ", ("
                    << spyglass.row << ", " << spyglass.col << "))" 
                    << endl; */
        if (spyglass.row == target_r && spyglass.col == target_c) {
            //cout << "target found" << endl;
            backtrace.push_back(observer.front());
            return true;
        } 
        observer.investigate(button(spyglass), discoverMap, *this);
        //cout << "investigate finished on " << "(" << spyglass.color << ", ("
        //            << spyglass.row << ", " << spyglass.col << "))" << endl;
    } return false;
}

void Maze::listOut() {
    /* cout << "(^, (" << 
        start_r << ", " << start_c << "))" << endl; */
    deque<state> path;
    node* current = &(backtrace.back());
    while (current != nullptr) {
        //cout << "proccessing " << "(" << (*current).datum.color << ", ("
        //            << (*current).datum.row << ", " << (*current).datum.col << "))" << endl;
        path.push_front((*current).datum);
        //current->evacuate();
        node* temp = current->prev;
        //delete current;
        current = temp;
    } backtrace.clear();
    discoverMap.clear();
    mazeMap.clear();
    for (size_t u = 0; u < path.size(); u++) {
        cout << "(" << path[u].color << ", (" << 
            path[u].row << ", " << path[u].col << "))\n";
    }
}

void Maze::mapOut() {
    deque<state> path;
    node* current = &(backtrace.back());
    while (current != nullptr) {
        //cout << "proccessing " << "(" << (*current).datum.color << ", ("
        //            << (*current).datum.row << ", " << (*current).datum.col << "))" << endl;
        path.push_front((*current).datum);
        //current->evacuate();
        node* temp = current->prev;
        //delete current;
        current = temp;
    } backtrace.clear();
    discoverMap.clear();
    vector<vector<vector<char> > >outMap(num_colors+1, vector<vector<char>>(height, vector<char>(width, '.')));
    for (size_t w = 0; w < num_colors; w++) {
        for (size_t r = 0; r < height; r++) {
            for (size_t c = 0; c < width; c++) {
                if (size_t(mazeMap[r][c]) == w + 97 || size_t(mazeMap[r][c]) == w + 65 || mazeMap[r][c] == '@') {
                    outMap[w][r][c] = '.';
                } else outMap[w][r][c] = mazeMap[r][c];
            }
        }
    }
    for (size_t r = 0; r < height; r++) {
        for (size_t c = 0; c < width; c++) {
            if (mazeMap[r][c] == '^') outMap[num_colors][r][c] = '.';
            else outMap[num_colors][r][c] = mazeMap[r][c];
        }
    }
    mapReplace(outMap, num_colors, '^', '.');
    char currentColor = '^';
    for (size_t u = 1; u < path.size() - 1; u++) {
        if(path[u].color != path[u+1].color) {
            if (currentColor != '^') outMap[size_t(currentColor - 97)][path[u].row][path[u].col] = '%';
            else outMap[num_colors][path[u].row][path[u].col] = '%';
            currentColor = path[u+1].color;
            if (currentColor != '^') outMap[size_t(path[u+1].color - 97)][path[u].row][path[u].col] = '@';
            else outMap[num_colors][path[u].row][path[u].col] = '@';
            u++;
        } else {
            if (currentColor != '^') outMap[size_t(currentColor - 97)][path[u].row][path[u].col] = '+';
            else outMap[num_colors][path[u].row][path[u].col] = '+';
        }
    } 
    mapPrint(outMap);
}

//Prints map to cout
void Maze::mapPrint(const vector<vector<vector<char> > > &map) {
    cout << "// color ^\n";
    for (size_t r = 0; r < height; r++) {
        for (size_t c = 0; c < width; c++) {
            cout << map[num_colors][r][c];
        }
        cout << "\n";
    }
    for (size_t w = 0; w < num_colors; w++) {
        cout << "// color " << char(w + 97) << "\n";
        for (size_t r = 0; r < height; r++) {
            for (size_t c = 0; c < width; c++) {
                cout << map[w][r][c];
            }
            cout << "\n";
        }
    }
}

//Replaces all instances in Maze map of char x with char y
void Maze::mapReplace(vector<vector<vector<char> > > &map, size_t level, char x, char y) {
    for (size_t r = 0; r < height; r++) {
        for (size_t c = 0; c < width; c++) {
            if (map[level][r][c] == x) map[level][r][c] = y;
        }
    }
}

bool Maze::checkDiscover(state x) const{
    if (x.row > height || x.col > width || x.color - 0 >= int(num_colors + 97)) {
        //cout << "check out of bounds" << endl;
        return true;
    } else {
        bool check = false;
        for (size_t w = 0; w < discoverMap[x.row][x.col].size(); w++) {
            if (discoverMap[x.row][x.col][w] == x.color) {
                check = true;
            }
        }
        return check;
    }
}

/* void node::evacuate() {
    //cout << "evacuating " << "(" << datum.color << ", ("
    //                << datum.row << ", " << datum.col << ")) [" << next.size() << "]" << endl;
    for(size_t u = 0; u < next.size(); u++) {
        next[u]->evacuate();
        delete next[u];
    }
} */