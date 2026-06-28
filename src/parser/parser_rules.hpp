#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <utility>


class Parser {
private:
    std::ifstream rules;
    std::set<int> birth_rules;
    std::set<int> survive_rules;
    std::string uniName;
    std::vector<std::pair<int, int>> start_state;
    uint32_t fstr_num = 0;

    std::string readLine();

public:
    Parser();

    void init(std::string& filename);
    void Read_birth_rules();
    void Read_survive_rules();
    void Read_universe_name();
    void Read_universe_start_state();
    void Read_all_rules();

    void Print_all_rules();

};