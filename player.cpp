//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <player.h>
#include <deque>

using namespace std;

player::player(int r, int c, int width_in, int height_in, int num_colors_in, bool style_in) {
    current_state.row = r;
    current_state.col = c;
    current_state.color = '^';
    width = width_in;
    height = height_in;
    num_colors = num_colors_in;
    style = style_in;
    discover(current_state);
}

void player::discover(state x) {
    if (x.row >= width || x.col >= height || x.color >= (num_colors + 97)) {
        return;
    } else if (!checkDiscover(x)) {
        if(!style) {
            search_container.push_back(x);
        } else if (style) {
            search_container.push_front(x);
        } discoverMap[x.row][x.col][x.color - 97] = true;
    } 
}

bool player::checkDiscover(state x){
    return discoverMap[x.row][x.col][x.color - 97];
}

bool player::checkButton(state x){
    if (!checkDiscover(x)) {
        return true;
    } else return false;
}

void player::investigate(bool button, char color) {
    if (button && checkButton(current_state)) {
        discover({color, current_state.row, current_state.col});
    } else {
        discover({current_state.color, current_state.row - 1, current_state.col}); //north
        discover({current_state.color, current_state.row, current_state.col + 1}); //east
        discover({current_state.color, current_state.row + 1, current_state.col}); //south
        discover({current_state.color, current_state.row, current_state.col - 1}); //west
    }
    search_container.pop_front();
    current_state = search_container.front();
}
