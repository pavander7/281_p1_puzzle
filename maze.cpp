//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <maze.h>
#include <iostream>

using namespace std;

class Maze {
public:
    Maze() {
        cin >> num_colors >> height >> width;
        openDoor = 0;
        for (int r = 0; r < height; r++) {
            for (int c = 0; r < width; c++) {
                cin >> mazeMap[r][c];
                if (mazeMap[r][c] == '@') {
                    start_r = r;
                    start_c = c;
                } else if (mazeMap[r][c] == '?') {
                    target_r = r;
                    target_c = c;
                }
            }
        }
    }

    int startRow() {
        return start_r;
    }
    int startCol() {
        return start_c;
    }
    int targetRow(){
        return target_r;
    }
    int targetCol() {
        return target_c;
    }

    bool wall(int r, int c) {
        return (mazeMap[r][c] == '#' || !door(r,c));
    }
    bool button(int r, int c) {
        return ((mazeMap[r][c] >= 97 && mazeMap[r][c] <= 122) || mazeMap[r][c] == '^');
    }
    bool target(int r, int c) {
        return (r == target_r && c == target_c);
    }
    bool door(int r, int c) {
        if (mazeMap[r][c] >= 65 && mazeMap[r][c] <= 90) {
            return (mazeMap[r][c] == openDoor);
        } else return false;
    }

    void press(int r, int c) {
        if (mazeMap[r][c] == '^') {
            openDoor = 0;
        } else openDoor = mazeMap[r][c] - 32;
    }

private:
    int num_colors;
    int height, width;
    int start_r, start_c;
    int target_r, target_c;
    char openDoor;
    char mazeMap[1200][1200];
};