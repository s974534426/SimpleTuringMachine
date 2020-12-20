#ifndef __TM_H__
#define __TM_H__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <set>
#include <map>
#include <vector>
using namespace std;

#ifdef DEBUG
  #define Log(format, ...) \
    fprintf(stderr, "\033[1;31m%s:%d: " format "\033[0m", __func__, __LINE__, ##__VA_ARGS__)
#else
  #define Log(format, ...) ((void)0)
#endif

enum mode {NORMAL, VERBOSE};

struct key {
    string state;
    string tape_state;
    bool operator < (const key &k) const {
        if(state != k.state) {
            return state < k.state;
        } else {
            return tape_state < k.tape_state;
        }
    }
};

struct value {
    string new_tape_state;
    string direction;
    string next_state;
};

/**
 * @class Turing
 * 
 * Simple multi tape turing machine
 */
class Turing {
private:
    string input_string;

    int n_tape;
    set<string> Q;
    set<string> S;
    set<string> G;
    string q0;
    string B;
    set<string> F;
    map<key, value> delta;
    vector<int> head;
    vector<vector<char>> tapes;

    void build_tm(const string &filename);
    void insert_state_tm(const char type, const string &state_str);
    void insert_delta(const string &delta_str);
    void replace_all(string &s, const string &old_value, const string &new_value) const;
    void print_set(const set<string> &s) const;
    void print_input_illegal_info(const int illegal_idx, const mode m) const;

public:
    Turing(const string &filename);
    void simulate(const string &input_str, const mode m);
    void info() const;
    void get_cur_state() const;
    int is_input_illegal(const string &input_str) const;
};

#endif 
