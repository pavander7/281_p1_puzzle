//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <string>
#include <vector>
#include <deque>
#include <cassert>

using namespace std;

struct state {
        char color;
        size_t row;
        size_t col;
};

class Maze {
public:
    Maze(bool styleIn); //default constructor

    size_t startRow();
    size_t startCol();

    bool wall(state x) const; //check cells for various options
    bool button(state x) const;
    bool door(state x) const;

    size_t solve(state start, bool root);
    void listOut();
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
    deque<state> path;
    bool style;
};

class player {
        public:
            player(state startIn, vector<vector<vector<bool> > > &discoverMap, Maze &y, bool root);
            void discover(state x, vector<vector<vector<bool> > > &discoverMap, Maze &y);
            
            bool checkButton(state x, Maze &y);
            void investigate(bool button, vector<vector<vector<bool> > > &discoverMap, Maze &y);
            bool empty();
            state current_state;
        private:
            deque<state> search_container;
            bool style;
    };