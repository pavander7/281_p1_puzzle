//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <getopt.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    
    cout << "flag 1" << endl;
    
    /*static struct option long_options[] = {
    {"help",    no_argument,        NULL,  'h'},
    {"queue",   no_argument,        NULL,  'q'},
    {"stack",   no_argument,        NULL,  's'},
    {"output",  required_argument,  NULL,  'o'},
    {0,         0,                  NULL,  0, }
    };*/

    //getopt_long(argc, argv, "hqso:", long_options, &option_index)

    //int option_index = 0;
    int dataType = 0;
    int outputType = 0;
    cout << "flag 1" << endl;
    int c = getopt(argc, argv, "hqso:");
    while (c != -1) {
        cout << "flag 2 " << c << endl;
        if (c == 'h') {
            cout << "help menu" << endl; //UPDATE
        } else if (c == 'q') {
            dataType = 0;
        } else if (c == 's') {
            dataType = 1;
        } else if (c == 'o') {
            string temp = optarg;
            if (temp == "map") {
                outputType = 0;
            } else if (temp == "list") {
                outputType = 1;
            } else return 1;
        } else return 1;
        c = getopt(argc, argv, "hqso:");
    }
    
}