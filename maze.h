//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <string>

using namespace std;

class Maze {
public:
    Maze(); //default constructor

    int startRow(); //standard variable access functions
    int startCol();
    int targetRow();
    int targetCol();

    bool wall(int r, int c); //check cells for various options
    bool button(int r, int c);
    bool target(int r, int c);
    bool door(int r, int c);

    void press(int r, int c); //press the button (assumes cell is a button)

private:
    int num_colors;
    int height, width;
    int start_r, start_c;
    int target_r, target_c;
    char openDoor;
    char mazeMap[20000][20000];
};