//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <deque>

using namespace std;

struct state {
    int row;
    int col;
    char color;
};

class player
{
public:
    player(int r, int c, int width_in, int height_in, int num_colors_in, bool style_in);
    void discover(state x);
    bool checkDiscover(state x);
    bool checkButton(state x);
    void investigate(state x);
private:
    state current_state;
    deque search_container;
    bool discoverMap[1200][1220][26];
    int width, height, num_colors;
    bool style;
};

