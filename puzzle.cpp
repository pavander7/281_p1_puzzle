//IDENTIFIER  = A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <getopt.h>
#include <iostream>
#include <string>
#include <map.h>

using namespace std;

int main(int argc, char* argv[]) {
    
    //cout << "flag 1" << endl;
    
    static struct option long_options[] = {
    {"help",    no_argument,        NULL,  'h'},
    {"queue",   no_argument,        NULL,  'q'},
    {"stack",   no_argument,        NULL,  's'},
    {"output",  required_argument,  0,  'o'},
    {0,         0,                  NULL,  0, }
    };

    

    int option_index = 0;
    int dataType = 0;
    int outputType = 0;
    //cout << "flag 1" << endl;
    int c = getopt_long(argc, argv, "hqso:", long_options, &option_index);
    while (c != -1) {
        //cout << "flag 2 " << c << endl;
        if (c == 'h') {
            //cout << "help menu" << endl; //UPDATE
        } else if (c == 'q') {
            dataType = 0;
        } else if (c == 's') {
            dataType = 1;
        } else if (c == 'o') {
            string temp = optarg;
            //cout << "slay 1" << endl;
            if (temp == "map") {
                outputType = 0;
                //cout << "slay 2.1: " << optind << endl;
            } else if (temp == "list") {
                outputType = 1;
                //cout << "slay 2.2: " << optind << endl;
            } else return 1;
        } else return 1;
        c = getopt_long(argc, argv, "hqso:", long_options, &option_index);
    }
    
}