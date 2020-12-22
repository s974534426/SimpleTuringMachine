#ifndef __TM_H__
#define __TM_H__

#include <stdio.h>
#include <iostream>
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

enum tm_mode_t {NORMAL, VERBOSE, HELP};

/**
 * @struct key
 * 
 * The input of transition function 
 */
struct key {
    string state;
    string tape_state;
    key(string s = "", string t = "") {
        state = s, tape_state = t;
    }
    bool operator < (const key &k) const {
        if(state != k.state) {
            return state < k.state;
        } else {
            return tape_state < k.tape_state;
        }
    }
};

/**
 * @struct value
 * 
 * The output of transition function 
 */
struct value {
    string new_tape_state;
    string direction;
    string next_state;
};

/**
 * @class Turing
 * 
 * Simple multi tape deterministic turing machine
 */
class Turing {
private:
    // variables to build the turing machine
    tm_mode_t mode;         // NORMAL, VERBOSE
    int n_tape;             // Number of tapes
    set<string> Q;          // State set
    set<string> S;          // Input symbol set
    set<string> G;          // Tape symbol set
    string q0;              // Start state
    string B;               // block state
    set<string> F;          // final state set
    map<key, value> delta;  // transition set: f((state, tape_state)) = (new_tape_state, dir, next_state) 

    // current state
    string input_string;
    struct tape_t {
        int head;
        pair<int, int> range;  // [range.first, range.second)
        map<int, char> tape;
        tape_t() {
            head = 0;
            range.first = 0, range.second = 1;
            tape[0] = '_';
        }
    };
    vector<tape_t> tapes;
    string cur_state;
    int cur_step;

    void build_tm(const string &filename);
    void insert_state_tm(const char type, const string &state_str);
    int is_delta_illegal(const key &k, const value &v, string &error_message) const;
    void print_delta_illegal_info(const key &k, const value &v, string &error_message) const;
    void insert_delta(const string &delta_str);
    void replace_all(string &s, const string &old_value, const string &new_value) const;
    void print_set(const set<string> &s) const;
    void print_input_illegal_info(const int illegal_idx) const;
    char get_tape_state(const int idx) {
        return tapes[idx].tape[tapes[idx].head];
    }

public:
    Turing(const string &filename, const tm_mode_t m);
    void init();
    int step(); // one step ahead
    void simulate(const string &input_str);
    void info() const;
    void print_cur_state();
    int is_input_illegal(const string &input_str) const;
};

#endif 
