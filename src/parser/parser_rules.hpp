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

    std::string readLine();

public:
    Parser();

    void init(std::string& filename);
    void Get_birth_rules();
    void Get_survive_rules();
    void Get_universe_name();
    void Get_universe_start_state();

};