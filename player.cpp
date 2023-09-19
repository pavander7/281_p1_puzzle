//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include "header.h"

using namespace std;

player::player(state startIn, vector<vector<vector<bool> > > &discoverMap, Maze &y, bool root) {
    style = y.style;
    current_state.row = startIn.row;
    current_state.col = startIn.col;
    current_state.color = startIn.color;
    begin = {startIn, nullptr, {}};
    if (root) {
        cout << "discovering start position" << endl;
        discover(current_state, nullptr, discoverMap, y);
    } else {
        cout << "known start position" << endl;
        node* temp = new node{current_state, nullptr, {}};
        search_container.push_back(temp);
    }
}

bool player::discover(state x, node* origin, vector<vector<vector<bool> > > &discoverMap, Maze &y) {
    cout << "starting discover instance on " << "(" << x.color << ", ("
                    << x.row << ", " << x.col << "))" 
                    << endl;
    if (x.row >= y.height || x.col >= y.width || x.color - 0 >= int(y.num_colors + 97)) {
        cout << "discarding: off map" << endl;
        return false;
    } else if (!y.checkDiscover(x) && !y.wall(x)) { 
        node* temp = new node{x, origin, {}};
        if (origin != nullptr) origin->next.push_back(temp);
        if(!style) {
            search_container.push_back(temp);
            cout << "discovered (back) " << "(" << (*search_container.back()).datum.color << ", (" << 
                    (*search_container.back()).datum.row << ", " << (*search_container.back()).datum.col << "))" << endl; 
        } else if (style) {
            search_container.push_front(temp);
            cout << "discovered (front) " << "(" << (*search_container.front()).datum.color << ", (" << 
                    (*search_container.front()).datum.row << ", " << (*search_container.front()).datum.col << "))" << endl; 
        } if (x.color == '^') {
            discoverMap[x.row][x.col][y.num_colors] = true;
        } else { 
            
            discoverMap[x.row][x.col][size_t(x.color - 97)] = true; 
        }
        return true;
    } else if (y.checkDiscover(x)) {
        cout << "discarding: already discovered" << endl;
        return false;
    } else {
        cout << "discarding: wall or closed door" << endl;
        return false;
    }
}

bool player::checkButton(state x, Maze &y){
    if (!y.checkDiscover(x)) {
        return true;
    } else return false;
}

bool player::investigate(bool button, vector<vector<vector<bool> > > &discoverMap, Maze &y) {
    cout << "starting investigate instance" << endl;
    bool find = false;
    if (button && checkButton(front().datum, y)) {
        cout << "investigating button" << endl;
        find =  discover({y.mazeMap[front().datum.row][front().datum.col], 
                front().datum.row, front().datum.col}, frontPoint(), discoverMap, y);
    } else {
        cout << "investigating surroundings" << endl;
        state place = front().datum;
        search_container.pop_front();
        if (place.row > 0)
            if (discover({place.color, place.row - 1, place.col}, frontPoint(), discoverMap, y)) find = true; //north
        if (place.col < y.width)
            if (discover({place.color, place.row, place.col + 1}, frontPoint(), discoverMap, y)) find = true; //east
        if (place.row < y.height)
            if (discover({place.color, place.row + 1, place.col}, frontPoint(), discoverMap, y)) find = true; //south
        if (place.col > 0)
            if (discover({place.color, place.row, place.col - 1}, frontPoint(), discoverMap, y)) find = true; //west
    }
    return find;
}

bool player::empty() {
    return search_container.empty();
}

node* player::frontPoint() {
    return search_container.front();
}

node player::front() {
    return (*search_container.front());
}