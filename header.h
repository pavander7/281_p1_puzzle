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
    Maze(bool styleIn); //default constructor

    size_t startRow();
    size_t startCol();

    bool wall(state x) const; //check cells for various options
    bool button(state x) const;
    bool door(state x) const;

    node* solve(state start, bool root);
    void listOut(node begin);
    void mapOut();

    bool checkDiscover(state x);
    vector<vector<vector<bool> > > discoverMap;

private:
    friend class player;
    size_t num_colors;
    size_t height, width;
    size_t start_r, start_c;
    size_t target_r, target_c;
    vector<vector<char> > mazeMap;
    bool style;
};

class player {
    public:
        player(state startIn, vector<vector<vector<bool> > > &discoverMap, Maze &y, bool root);
        bool discover(state x, node* origin, vector<vector<vector<bool> > > &discoverMap, Maze &y);
        node* frontPoint();
        node front();
        bool checkButton(state x, Maze &y);
        bool investigate(bool button, vector<vector<vector<bool> > > &discoverMap, Maze &y);
        bool empty();
        state current_state;
    private:
        deque<node*> search_container;
        node begin;
        bool style;
};