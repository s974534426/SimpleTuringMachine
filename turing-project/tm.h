#include <iostream>
#include <set>

#ifdef DEBUG
  #define Log(format, ...) \
    fprintf(stderr, "\033[1;31m%s:%d: " format "\033[0m", __func__, __LINE__, ##__VA_ARGS__)
#else
  #define Log(format, ...) ((void)0)
#endif

class Turing {
private:
    int n_tape;
    set<string> Q;
    set<string> S;
    set<string> G;
    string q0;
    string B;
    set<string> F;

    void build_tm(const string &filename);
    void insert_state_tm(const char type, const string &state_str);
    void replace_all(string &s, const string &old_value, const string &new_value);
    void print_set(const set<string> &s);

public:
    Turing(const string &filename)
    void step();
    void info() const;
    ~Turing();
};