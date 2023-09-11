//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <string>

using namespace std;

class Maze {
public:
    Maze();

    int startRow();
    int startCol();
    int targetRow();
    int targetCol();

private:
    int num_colors;
    int height, width;
    int start_r, start_c;
    int target_r, target_c;
    char mazeMap[1200][1200];
};