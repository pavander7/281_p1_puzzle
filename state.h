//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <string>
#include <vector>

using namespace std;

struct state {
    char color;
    size_t row;
    size_t col;
};

struct node {
    state datum;
    node* prev;
    vector<node*> next;
    void evacuate();
};