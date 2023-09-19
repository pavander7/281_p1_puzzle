//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include "state.h"
#include "maze.h"

using namespace std;

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