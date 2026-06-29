#include "parser_rules.hpp"

#define FILE_HEADER "#Life 1.06"
#define UNI_NAME_HEADER "#N"
#define RULES_HEADER "#R"
#define DEFAULT_UNINAME "Life Universe"
#define DEFAULT_BIRTH_RULES "3"
#define DEFAULT_SURVIVE_RULES "23"


//--------------------------------------------------------------------------------------------------------------------
Parser::Parser() {

}
//--------------------------------------------------------------------------------------------------------------------

std::string Parser::readLine(){
    std::string line;
    if (rules.is_open()){
        std::getline(rules, line);
        fstr_num++;
    }
    return line;
}
//--------------------------------------------------------------------------------------------------------------------

void Parser::init(std::string& filename){
    
    rules = std::ifstream(filename);
    if (rules.is_open()){
        std::string header = this->readLine();
        //DEBUG
        std::cout << "INFO: Header line = " << header << std::endl;
        //DEBUG
        if (header != FILE_HEADER){
            std::cerr << "WARNING: header of file is " << header << "which is different from " << FILE_HEADER << std::endl; 
        }
    }
    else{
        std::cerr << "FATAL ERROR: Error of reading file with rules: " << filename << std::endl;
        return;
    }
}
//--------------------------------------------------------------------------------------------------------------------

void Parser::Read_birth_rules(){
    rules.seekg(0, std::ios_base::beg);

    std::string line;
    std::string::size_type sz;

    do{
        line = readLine(); 
        if (rules.eof()){
            std::cerr << "WARNING: Birth rules are not declared. They should be after \"#R B*\" in the start of any line of .life file.\nDefault birth rules set: B" << DEFAULT_BIRTH_RULES <<std::endl;
            birth_rules.insert(std::stoi(DEFAULT_BIRTH_RULES, &sz));
            return;
        }
    }while(line.substr(0, 2) != RULES_HEADER);
    //DEBUG
    #ifndef NDEBUG
    std::cout << "INFO: Rules line = " << line << std::endl; // Let's glance on the string with #R
    #endif
    //DEBUG

    size_t B_pos = line.find("B");
    size_t end_B_rules_pos = line.find('/');

    //DEBUG
    #ifndef NDEBUG
    std::cout << "INFO: B_pos = " << B_pos << std::endl;
    std::cout << "INFO: end_B_rules_pos = " << end_B_rules_pos << std::endl;
    #endif
    //DEBUG

    if (B_pos == std::string::npos || end_B_rules_pos == std::string::npos){
        std::cerr << "WARNING: Birth rules are not declared correct. They must be in line, started with #R and written after B and before / i.e. #R B1234/S23" << std::endl;
        std::cerr << "Setting default B: B" << DEFAULT_BIRTH_RULES << std::endl;
        birth_rules.insert(std::stoi(DEFAULT_BIRTH_RULES, &sz));
        return;
    }

    std::string B_rules_str = line.substr(B_pos + 1, end_B_rules_pos - (B_pos + 1));
    //DEBUG
    #ifndef NDEBUG
    std::cout << "INFO: B_rules_str = " << B_rules_str << std::endl;
    #endif
    //DEBUG

    for (char digit : B_rules_str){
        if (digit - '0' < 0 || digit - '0' > 9){
            std::cerr << "WARNING: Birth rules are not declared correct. After B must be ONLY digits [0..8] i.e. B876543" << std::endl;
            std::cerr << "Setting default B: B" << DEFAULT_BIRTH_RULES << std::endl;
            birth_rules.clear();
            birth_rules.insert(std::stoi(DEFAULT_BIRTH_RULES, &sz));
            return;
        }
        birth_rules.insert(digit - '0');
    }
}
//--------------------------------------------------------------------------------------------------------------------

void Parser::Read_survive_rules(){
    rules.seekg(0, std::ios_base::beg);

    std::string line;
    std::string::size_type sz;

    do{
        line = readLine(); 
        if (rules.eof()){
            std::cerr << "WARNING: Survive rule are not declared. It should be after \"#R S*\" in the start of any line of .life file.\nDefault survive rules set: S" << DEFAULT_SURVIVE_RULES <<std::endl;
            survive_rules.insert(std::stoi(DEFAULT_SURVIVE_RULES, &sz));
            return;
        }
    }while(line.substr(0, 2) != RULES_HEADER);
    //DEBUG
    #ifndef NDEBUG
    std::cout << "INFO: Rules line = " << line << std::endl; // Let's glance on the string with #R
    #endif
    //DEBUG

    size_t S_pos = line.find("S");
    size_t end_S_rules_pos = line.find('\0');

    //DEBUG
    #ifndef NDEBUG
    std::cout << "INFO: S_pos = " << S_pos << std::endl;
    std::cout << "INFO: end_S_rules_pos = " << end_S_rules_pos << std::endl;
    #endif
    //DEBUG

    if (S_pos == std::string::npos || end_S_rules_pos == std::string::npos){
        std::cerr << "WARNING: Survive rules are not declared correct. They must be in line, started with #R and written after S and before endl i.e. #R B1234/S23" << std::endl;
        std::cerr << "Setting default S: S" << DEFAULT_SURVIVE_RULES << std::endl;
        for (char digit : DEFAULT_SURVIVE_RULES){
            if (digit - '0' < 0 || digit - '0' > 9)
                break;
            std::cout << "INFO: Digit of default survive rules = " << digit - '0' << std::endl;;   
            survive_rules.insert(digit - '0');
        }
        
        return;
    }

    std::string S_rules_str = line.substr(S_pos + 1, end_S_rules_pos - (S_pos + 1));
    //DEBUG
    #ifndef NDEBUG
    std::cout << "INFO: S_rules_str = " << S_rules_str << std::endl;
    #endif
    //DEBUG

    for (char digit : S_rules_str){
        if (digit - '0' < 0 || digit - '0' > 9){
            std::cerr << "WARNING: Survive rules not declared correct. After S must be ONLY digits [0..8] i.e. B876543" << std::endl;
            std::cerr << "Setting default S: S" << DEFAULT_SURVIVE_RULES << std::endl;
            survive_rules.clear();
            survive_rules.insert(std::stoi(DEFAULT_SURVIVE_RULES, &sz));
            return;
        }
        survive_rules.insert(digit - '0');
    }

}
//--------------------------------------------------------------------------------------------------------------------

void Parser::Read_universe_name(){
    rules.seekg(0, std::ios_base::beg);
    do{
        uniName = readLine();
        if (rules.eof()){
            std::cerr << "WARNING: Name of universe not declared. It should be after \"#N\" in the start of any line of .life file.\nDefault name of universe set: " << DEFAULT_UNINAME <<std::endl;
            uniName = DEFAULT_UNINAME;
            return;
        }
    }while(uniName.substr(0, 2) != UNI_NAME_HEADER);
    size_t N_pos = uniName.find("N");
    uniName = uniName.substr(N_pos + 2);
}
//--------------------------------------------------------------------------------------------------------------------

void Parser::Read_universe_start_state(){
    rules.seekg(0, std::ios_base::beg);
    std::string line;

    do{
        line = readLine(); 
        if (rules.eof() && start_state.empty()){
            std::cerr << "WARNING: Your start state is empty. Please add some lines with positions of living cells in file .life i.e. 5 7" << std::endl;
            return;
        }

        std::string first_symb_line = line.substr(0, 1);
        std::string delims = " ;,:";

        if (!first_symb_line.empty() && (first_symb_line.find_first_not_of("0123456789") == first_symb_line.npos)){
            
            // Handle the error of input
            if ((line.find_first_not_of("0123456789" + delims) != line.npos)){
                std::cerr << "WARNING: In the string number " << fstr_num << " is unparsable data. This line will be skipped.\nHere is the content of line: " << line << std::endl;
                std::cerr << "Line with cell coordinates must contain two numbers - x, y coordinates - and separated with any # of delimiters: \"" << delims << "\"" << std::endl;
                continue;
            }
            // Handle the error of input
            
            
            std::string before_delim = line.substr(0, line.find_first_of(delims));
            std::string after_delim = line.substr(line.find_last_of(delims) + 1);

            int x_pos = std::stoi(before_delim);
            int y_pos = std::stoi(after_delim);

            start_state.emplace_back(x_pos, y_pos);

        }

    }while(!line.substr(0, 1).empty());
}
//--------------------------------------------------------------------------------------------------------------------

void Parser::Print_all_rules(){
    std::cout << "Name of Universe: " << uniName << std::endl;

    std::cout << "Birth rules: ";
    for (int digit : birth_rules){
        std::cout << digit;
    }
    std::cout << std::endl;

    std::cout << "Survive rules: ";
    for (int digit : survive_rules){
        std::cout << digit;
    }
    std::cout << std::endl;

    std::cout << "Start cells: " << std::endl;
    for (std::pair<int, int> coord : start_state){
        std::cout << "(" << coord.first << ", " << coord.second << ")" << std::endl;
    }

}
//--------------------------------------------------------------------------------------------------------------------

void Parser::Read_all_rules(){
    Read_universe_name();
    Read_birth_rules();
    Read_survive_rules();
    Read_universe_start_state();
    Print_all_rules();

}