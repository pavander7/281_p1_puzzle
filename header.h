//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <string>
#include <vector>
#include <deque>
#include <cassert>
#include <iostream>
#include "state.h"

using namespace std;

class Maze {
public:
    Maze(bool styleIn, bool &error); //default constructor

    size_t startRow();
    size_t startCol();

    bool wall(state x) const; //check cells for various options
    bool button(state x) const;
    bool door(state x) const;

    bool solve(state start);

    void listOut();
    void mapOut();

    bool checkDiscover(state x) const;
    vector<vector<vector<char> > > discoverMap;

    void mazeOut();
    void mapPrint(const vector<vector<vector<char> > > &map);

private:
    friend class player;
    size_t num_colors;
    size_t height, width;
    size_t start_r, start_c;
    size_t target_r, target_c;
    vector<vector<char> > mazeMap;
    deque<node> backtrace;
    bool style;
};

class player {
    public:
        player(state startIn, Maze &y);
        bool discover(state x, node* origin, Maze &y);
        node front() const;
        void investigate(bool button, Maze &y);
        bool empty() const;
    private:
        deque<node> search_container;
        bool style;
};