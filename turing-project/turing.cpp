#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <getopt.h>
#include <set>
#include "tm.h"
using namespace std;

string filename;
string input_str;
enum mode {NORMAL, VERBOSE};

#ifdef DEBUG
  #define Log(format, ...) \
    fprintf(stderr, "\033[1;31m%s:%d: " format "\033[0m", __func__, __LINE__, ##__VA_ARGS__)
#else
  #define Log(format, ...) ((void)0)
#endif

/**
 * Simple multi tape turing machine
 */

class Turing {
private:
    int n_tape;
    set<string> Q;
    set<string> S;
    set<string> G;
    string q0;
    string B;
    set<string> F;

    void build_tm(const string &filename) {
        /**
         * Read the tm file, parse the file and build corresponding tm
         */ 
        ifstream in(filename);
        string s;

        while(getline(in, s)) {
            // delete the comment and empty string
            int comment_pos = s.find(";");
            if(comment_pos != -1) 
                s.erase(comment_pos);
            if(s == "")
                continue;

            if(s[0] == '#') {
                char line_type = s[1];

                int parenthesis_pos = s.find("{");
                if(parenthesis_pos != -1)
                    s[parenthesis_pos] = ' ';
                parenthesis_pos = s.find("}");
                if(parenthesis_pos != -1)
                    s[parenthesis_pos] = ' ';

                int start_pos = s.find(" = ");
                s = s.substr(start_pos+3);
                
                replace_all(s, ",", " ");
                
                insert_state_tm(line_type, s);
            } else {
                ;
            }
            
        }
    }

    void insert_state_tm(const char type, const string &state_str) {
        istringstream istr(state_str);
        string tmp_str;
        set<string> *pt = NULL;

        switch(type) {
            case 'Q':
                pt = &Q; break;
            case 'S':
                pt = &S; break;
            case 'G':
                pt = &G; break;
            case 'q':
                istr >> q0; break;
            case 'B':
                istr >> B; break;
            case 'F':
                pt = &F; break;
            case 'N':
                istr >> n_tape; break;
            default:
                exit(-1);
        }
        
        if(pt != NULL)
            while(istr >> tmp_str)
                pt->insert(tmp_str);
    }

    void replace_all(string &s, const string &old_value, const string &new_value) {
        int pos;
        while((pos = s.find(old_value)) != -1)
            s = s.replace(pos, old_value.size(), new_value);
    }

    void print_set(const set<string> &s) const {
        set<string>::iterator i;
        for(i = s.begin(); i != s.end(); i++) 
            cout << *i << " ";
        cout << endl;
    }

public:
    Turing(const string &filename) {
        Log("Parse file %s\n", filename.c_str());
        Log("\n");
        int n_tape = -1;
        build_tm(filename);        
    }

    void step() {
        ;
    }

    void info() const {
        cout << "------------ TM -------------" << endl;
        cout << "N tape: " << n_tape << endl;

        cout << "Input set Q: ";
        print_set(Q);

        cout << "Input set S: ";
        print_set(S);

        cout << "Tape set G: ";
        print_set(G);

        cout << "Start state q0: " << q0 << endl;
        cout << "Block B: " << B << endl;

        cout << "Final state set F: ";
        print_set(F);
        cout << "-----------------------------" << endl;
    }

    ~Turing() {
        ;
    }
};

int parse_args(int argc, char *argv[]) {
    static struct option long_options[] = {
        {"verbose", no_argument, NULL, 'v'}, 
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
    };
    int opt, option_idx = 0;
    while((opt = getopt_long(argc, argv, "vh", long_options, &option_idx)) != -1) {
        switch(opt) {
            case 'v':
                break;
            case 'p':
                break;
            default:
                fprintf(stderr, "Usage");
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
        printf("Filename %s\n", filename.c_str());
        printf("Input string: %s\n", input_str.c_str());
    }
}

int main(int argc, char *argv[]) {
    parse_args(argc, argv);

    Turing tm(filename);
    tm.info();

    return 0;
}