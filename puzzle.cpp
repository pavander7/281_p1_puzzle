//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <getopt.h>
#include <iostream>
#include <string>
#include "header.h"

using namespace std;

int main(int argc, char* argv[]) {
    //used for getOptLong()
    ios_base::sync_with_stdio(false);

    static struct option long_options[] = {
    {"help",    no_argument,        NULL,  'h'},
    {"queue",   no_argument,        NULL,  'q'},
    {"stack",   no_argument,        NULL,  's'},
    {"output",  required_argument,  0,  'o'},
    {0,         0,                  NULL,  0, }
    };
    int option_index = 0;

    //used to track data type, 2 signifies unknown
    size_t dataType = 2;
    size_t outputType = 0;

    //input parsing
    int c = getopt_long(argc, argv, "hqso:", long_options, &option_index);
    while (c != -1) {
        if (c == 'h') {
            cout << "help menu" << endl; //UPDATE
        } else if (c == 'q') {
            if (dataType == 2) dataType = 0;
            else {
                cerr << "Error: Can not have both stack and queue";
                return 1;
            }
        } else if (c == 's') {
            if (dataType == 2) dataType = 1;
            else {
                cerr << "Error: Can not have both stack and queue";
                return 1;
            }
        } else if (c == 'o') {
            string temp = optarg;
            if (temp == "map") {
                outputType = 0;
            } else if (temp == "list") {
                outputType = 1;
            } else {
                cerr << "Error: Invalid output mode";
                return 1;
            }
        } else {
            cerr << "Error: Unknown option";
            return 1;
        }
        c = getopt_long(argc, argv, "hqso:", long_options, &option_index);
    }

    //create map and player
    bool error = false;
    Maze map = Maze(dataType == 1, error);
    if (error) {
        return 1;
    }
    node* q = map.solve({'^', map.startRow(),map.startCol()});
    if (q == nullptr) {
        cout << "No solution." << endl << "Discovered:" << endl;
        map.mazeOut();
    } else {
        //cout << "solve successful, output:" << endl;
        if (outputType == 1) {
            map.listOut(*q);
        } else {
            cout << "not yet implemented";
        }
    } return 0;
}