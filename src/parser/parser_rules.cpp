#include "parser_rules.hpp"

Parser::Parser() {
    
}

std::string Parser::readLine(){
    std::string line;
    if (rules.is_open()){
        std::getline(rules, line);
    }
    return line;
}

void Parser::init(std::string& filename){
    
    rules = std::ifstream(filename);
    if (rules.is_open()){
        std::string header = this->readLine();
        //DEBUG
        std::cout << header << std::endl;
        //DEBUG
    }
    else{
        std::cerr << "Error of reading file with rules: " << filename << std::endl;
        return;
    }
}

void Parser::Get_birth_rules(){

}

void Parser::Get_survive_rules(){

}

void Parser::Get_universe_name(){

}

void Parser::Get_universe_start_state(){

}

