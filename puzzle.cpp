//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <getopt.h>
#include <iostream>

using namespace std;

static struct option long_options[] = {
    {"help",    no_argument,        NULL,  'h'},
    {"queue",   no_argument,        NULL,  'q'},
    {"stack",   no_argument,        NULL,  's'},
    {"output",  required_argument,  NULL,  'o'},
    {0,         0,                  NULL,  0, }
};

int main(int argc, char* argv[]) {
    int option_index = 0;
    int dataType = 0;
    int outputType = 0;
    for (int c; c != -1; c = getopt_long(argc, argv, "hqso:", long_options, &option_index)) {
        if (c == 'h') {
            cout << "help menu"; //UPDATE
        } else if (c == 'q') {
            dataType = 0;
        } else if (c == 's') {
            dataType = 1;
        } else if (c == 'o') {
            if (optarg == "map") {
                outputType = 0;
            } else if (optarg == "list") {
                outputType = 1;
            } else return 1;
        } else return 1;
    }
}