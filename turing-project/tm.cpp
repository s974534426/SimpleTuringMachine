#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include "tm.h"
using namespace std;

void Turing::build_tm(const string &filename) {
    // Read the tm file, parse the file and build corresponding tm
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
            insert_delta(s);
        }
        
    }
}

void Turing::insert_state_tm(const char type, const string &state_str) {
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

void Turing::insert_delta(const string &delta_str) {
    istringstream istr(delta_str);
    key k;
    value v;
    istr >> k.state >> k.tape_state >> v.new_tape_state >> v.direction >> v.next_state;
    // cout << k.state << " " << k.tape_state << " " << v.new_tape_state << " " << v.direction << " " << v.next_state << endl;
    delta[k] = v;
}

void Turing::replace_all(string &s, const string &old_value, const string &new_value) const {
    int pos;
    while((pos = s.find(old_value)) != -1)
        s = s.replace(pos, old_value.size(), new_value);
}

void Turing::print_set(const set<string> &s) const {
    set<string>::iterator i;
    for(i = s.begin(); i != s.end(); i++) 
        cout << *i << " ";
    cout << endl;
}

Turing::Turing(const string &filename) {
    build_tm(filename);        
}

void Turing::simulate(const string &input_str, const mode m) {
    input_string = input_str;

    // check input string
    int is_illegal = is_input_illegal(input_str);
    if(is_illegal != -1) {
        print_input_illegal_info(is_illegal, m);
        exit(-1);
    }
    if(is_illegal == -1 && m == VERBOSE) {
        cout << "Input: " << input_string << endl;;
        cout << "==================== RUN ====================" << endl;
    }
    
    // init the tm tapes
    vector<char> tmp_tape;

    for(int i = 0; i < input_str.size(); i++) {
        head.push_back(0);
        tmp_tape.push_back(input_str[i]); // 这里的拷贝有问题吗
    }
    tapes.push_back(tmp_tape);

    tmp_tape.clear();
    for(int i = 1; i < n_tape; i++) {
        head.push_back(0);
        tapes.push_back(tmp_tape);
    }

    // simulate
}

void Turing::info() const {
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

void Turing::get_cur_state() const {
    for(int i = 0; i < tapes.size(); i++) {
        if(tapes[i].size() == 0) {
            cout << "_" << endl;
        } else {
            for(int j = 0; j < tapes[i].size(); j++) {
                cout << tapes[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << "---------------------------------------------" << endl;
}

int Turing::is_input_illegal(const string &input_str) const {
    int illegal_idx = -1;
    for(int i = 0; i < input_str.size(); i++) {
        string tmp(1, input_str[i]);
        if(S.find(tmp) == S.end()) {
            illegal_idx = i;
            break;
        }
    }
    return illegal_idx;
}

void Turing::print_input_illegal_info(const int illegal_idx, const mode m) const {
    if(m == NORMAL) {
        fprintf(stderr, "illegal input\n");
    } else if (m == VERBOSE) {
        fprintf(stderr, "Input: %s\n", input_string.c_str());
        fprintf(stderr, "==================== ERR ====================\n");
        fprintf(stderr, "error: '%c' was not declared in the set of input symbols\n", input_string[illegal_idx]);
        fprintf(stderr, "Input: %s\n", input_string.c_str());
        for(int i = 0; i < string("Input: ").size() + illegal_idx; i++)
            fprintf(stderr, " ");
        fprintf(stderr, "^\n");
        fprintf(stderr, "==================== END ====================\n");
    } else {
        assert(0);
    }
}
