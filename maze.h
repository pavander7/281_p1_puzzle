//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <string>
#include <vector>
#include <deque>

using namespace std;

struct state {
        char color;
        int row;
        int col;
};

class Maze {
public:
    Maze(); //default constructor

    int startRow() const; //standard variable access functions
    int startCol() const;
    int targetRow() const;
    int targetCol() const;
    int Width() const;
    int Height() const;
    int numColors() const;

    bool wall(int r, int c) const; //check cells for various options
    bool button(int r, int c) const;
    bool target(int r, int c) const;
    bool door(int r, int c) const;

    void press(int r, int c); //press the button (assumes cell is a button)
    bool solve(state start);
    void listOut();
    void mapOut();

    bool checkDiscover(state x);

private:
    int num_colors;
    int height, width;
    int start_r, start_c;
    int target_r, target_c;
    char openDoor;
    vector<vector<char> > mazeMap;
    vector<vector<vector<bool> > > discoverMap;
    deque<state> path;

    class player {
        public:
            player(int r, int c, vector<vector<vector<bool> > > &discoverMap, Maze &y);
            void discover(state x, vector<vector<vector<bool> > > &discoverMap, Maze &y);
            
            bool checkButton(state x, Maze &y);
            void investigate(bool button, vector<vector<vector<bool> > > &discoverMap, Maze &y);
            bool empty();
            state current_state;
            friend class map;
        private:
            deque<state> search_container;
            int width, height, num_colors;
            bool style;
    };
};