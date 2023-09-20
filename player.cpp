//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include "header.h"

using namespace std;

player::player(state startIn, Maze &y) {
    style = y.style;
    //cout << "discovering start position" << endl;
    discover(startIn, nullptr, y);
    //cout << endl;
}

bool player::discover(state x, node* origin, Maze &y) {
    //cout << "starting discover instance on " << "(" << x.color << ", ("
    //                << x.row << ", " << x.col << "))" << endl;
    if (!y.checkDiscover(x) && !y.wall(x)) { 
        node temp = {x, origin};
        if(!style) {
            search_container.push_back(temp);
        } else if (style) {
            search_container.push_front(temp);
        } y.discoverMap[x.row][x.col].push_back(x.color);
        return true;
    } else {
        return false;
    }
}

void player::investigate(bool button, Maze &y) {
    //cout << "starting investigate instance" << endl;
    bool find = false;
    state place = front().datum;
    y.backtrace.push_back(front());
    node* mommy = &(y.backtrace.back());
    search_container.pop_front();
    if (button) {
        //cout << "investigating button" << endl;
        find =  discover({y.mazeMap[place.row][place.col], 
                place.row, place.col}, mommy, y);
    } else {
        //cout << "investigating surroundings" << endl;
        if (place.row > 0)
            if (discover({place.color, place.row - 1, place.col}, mommy, y)) find = true; //north
        if (place.col < y.width - 1)
            if (discover({place.color, place.row, place.col + 1}, mommy, y)) find = true; //east
        if (place.row < y.height - 1)
            if (discover({place.color, place.row + 1, place.col}, mommy, y)) find = true; //south
        if (place.col > 0)
            if (discover({place.color, place.row, place.col - 1}, mommy, y)) find = true; //west
    } if (!find) y.backtrace.pop_back(); //cout << endl;
}

bool player::empty() const {
    return search_container.empty();
}

node player::front() const {
    return search_container.front();
}