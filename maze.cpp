//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <maze.h>
#include <iostream>

using namespace std;

class Maze {
public:
    Maze() {
        cin >> num_colors >> height >> width;
        start_r = start_c = target_r = target_c = -1;
        if (num_colors < 0 || num_colors > 26) {
            cerr << "Error: Invalid numColor";
            assert(false);
        } if (width <= 1) {
            cerr << "Error: Invalid width";
        } if (height <= 1) {
            cerr << "Error: Invalid height";
        }
        openDoor = 0;
        for (int r = 0; r < height; r++) {
            for (int c = 0; r < width; c++) {
                cin >> mazeMap[r][c];
                if (mazeMap[r][c] == '@') {
                    if (start_r != -1 || start_c != -1) {
                        cerr << "Error: Puzzle must have only one start and one target";
                        assert(false);
                    }
                    start_r = r;
                    start_c = c;
                } else if (mazeMap[r][c] == '?') {
                    if (target_r != -1 || target_c != -1) {
                        cerr << "Error: Puzzle must have only one start and one target";
                        assert(false);
                    }
                    target_r = r;
                    target_c = c;
                } else if (mazeMap[r][c] <= 'a' && mazeMap [r][c] >= 'z') {
                    if (mazeMap[r][c] > (96 + num_colors)) {
                        cerr << "Error: Invalid button in map";
                        assert(false);
                    }
                } else if (mazeMap[r][c] <= 'A' && mazeMap [r][c] >= 'A') {
                    if (mazeMap[r][c] > (96 + num_colors)) {
                        cerr << "Error: Invalid door in map";
                        assert(false);
                    }
                } else if (mazeMap[r][c] == '.' || mazeMap [r][c] >= '#' || mazeMap[r][c] == '^');
                else {
                    cerr << "Error: Invalid character in map";
                    assert(false);
                }
            }
        } if (start_r == -1 || start_c == -1 || target_r == -1 || target_c == -1) {
            cerr << "Error: Puzzle must have exactly one start and one target";
            assert(false);
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