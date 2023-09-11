//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <maze.h>
#include <iostream>

using namespace std;

class Maze {
public:
    Maze() {
        cin >> num_colors >> height >> width;
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

private:
    int num_colors;
    int height, width;
    int start_r, start_c;
    int target_r, target_c;
    char mazeMap[1200][1200];
};