#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <getopt.h>
#include "tm.h"
using namespace std;

string filename;
string input_str;

void print_help_info() {
    fprintf(stderr, "usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n");
}

tm_mode_t parse_args(int argc, char *argv[]) {
    static struct option long_options[] = {
        {"verbose", no_argument, NULL, 'v'}, 
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
    };

    int opt, option_idx = 0;
    tm_mode_t m = NORMAL;
    while((opt = getopt_long(argc, argv, "vh", long_options, &option_idx)) != -1) {
        switch(opt) {
            case 'v':
                m = VERBOSE;
                break;
            case 'h':
                m = HELP;
                break;
            default:
                exit(-1);
        }
    }

    if(argc < 2 || argc > 5) {
        print_help_info();
        exit(-1);
    }

    if(argc >= 3) {
        filename = argv[argc-2];
        input_str = argv[argc-1];
        if((int)(filename.size()-3) < 0 || filename.substr(filename.size()-3) != ".tm") {
            print_help_info();
            exit(-1);
        }
    }

    return m;
}

int main(int argc, char *argv[]) {
    tm_mode_t m = parse_args(argc, argv);

    if(m == HELP) {
        print_help_info();
    } else {
        Turing tm(filename, m);
        tm.simulate(input_str);
    }

    return 0;
}
