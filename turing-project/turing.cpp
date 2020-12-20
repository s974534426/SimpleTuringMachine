#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <getopt.h>
#include "tm.h"
using namespace std;

string filename;
string input_str;

mode parse_args(int argc, char *argv[]) {
    static struct option long_options[] = {
        {"verbose", no_argument, NULL, 'v'}, 
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
    };

    int opt, option_idx = 0;
    mode m = NORMAL;
    while((opt = getopt_long(argc, argv, "vh", long_options, &option_idx)) != -1) {
        switch(opt) {
            case 'v':
                m = VERBOSE;
                break;
            case 'h':
                break;
            default:
                exit(-1);
        }
    }

    if(argc >= 3) {
        filename = argv[argc-2];
        input_str = argv[argc-1];
        if(filename.size()-3 < 0 || filename.substr(filename.size()-3) != ".tm") {
            // print error message
            exit(-1);
        }
    }

    return m;
}

void help_info() {
    printf("usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n");
}

int main(int argc, char *argv[]) {
    mode m = parse_args(argc, argv);

    Turing tm(filename);
    tm.simulate(input_str, m);
    tm.get_cur_state();
    // tm.info();

    return 0;
}
