//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <string>
#include <vector>
#include <deque>

using namespace std;

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
    void solve();

private:
    int num_colors;
    int height, width;
    int start_r, start_c;
    int target_r, target_c;
    char openDoor;
    vector<vector<char> > mazeMap;
    struct state;
    class player {
        public:
            player();
            void discover(state x);
            bool checkDiscover(state x);
            bool checkButton(state x);
            void investigate(bool button);

        private:
            state current_state;
            deque<state> search_container;
            bool discoverMap[20000][20000][26];
            int width, height, num_colors;
            bool style;
            struct state;
    };
};