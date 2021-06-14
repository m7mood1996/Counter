//
// Created by mahmood on 6/13/21.
//

#include "Parser.h"
Parser::Parser() {

}

Parser::~Parser() {
    for (size_t i = 0; i < counters.size(); ++i){
        if (counters[i].second.second)
            delete ((Counter<int>*)(counters[i].second.first));
        else
            delete ((Counter<std::string>*)(counters[i].second.first));
    }

}

void Parser::run() {
    std::string input;
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string delimiter = " ";
    std::size_t i = 0;

    while(true){

        std::cout << "[input]\t";
        getline(std::cin,input);
        while ((pos = input.find(delimiter)) != std::string::npos) {
            tokens.push_back(input.substr(0, pos));
            input.erase(0, pos + delimiter.length());
            i++;
        }
        tokens.push_back(input);

        if (tokens.at(0) == "string_counter"){
            add_counter(tokens.at(1), false);
        }
        else if (tokens.at(0) == "int_counter"){
            add_counter(tokens.at(1), true);
        }
        else if (tokens.at(0) == "add_from_file"){
            add_from_file(tokens.at(1), tokens.at(2).c_str());
        }
        else if (tokens.at(0) == "add_from_string"){
            add_from_string(tokens);

        }
        else if (tokens.at(0) == "stats"){
            stats(tokens.at(1));

        }
        else if (tokens.at(0) == "most_common"){
            most_common(tokens.at(1));

        }
        else if (tokens.empty()){
            std::cerr << "Not supported command";
            exit(1);
        }
        else{
            std::cerr << "Unknown command " << tokens.at(0);
            exit(1);
        }

        std::cout << std::endl;
        input = "";
        tokens.clear();
    }

}

void Parser::add_counter(const std::string &counter_name, bool type) {
    if(counter_exist(counter_name)){
        std::cerr << "Counter name already exists";
        exit(-1);
    }
    if (type){ // int_counter
        Counter<int>* int_counter = new Counter<int>;
        std::pair<void*,bool > pair1(int_counter,type);
        std::pair<std::string,std::pair<void*,bool> > pair(counter_name, pair1);
        counters.push_back(pair);
    }
    else{
        Counter<std::string>* string_counter = new Counter<std::string>;
        std::pair<void*,bool > pair1(string_counter, type);
        std::pair<std::string,std::pair<void*,bool > > pair(counter_name, pair1);
        counters.push_back(pair);
    }

}

void Parser::add_from_file(const std::string &counter_name, const char *file_name) {
    size_t index = find_counter_by_name(counter_name);
    if(counters[index].first != counter_name){
        std::cerr << "No counter named " << counter_name;
        exit(1);
    }
    std::ifstream input_file(file_name);
    if(counters[index].second.second) { // int counter
        std::ifstream inFile(file_name);
        ((Counter<int> *) counters[index].second.first)->add_from_stream(&inFile);
        inFile.close();


    }
    else {
        std::ifstream inFile;
        inFile.open(file_name);

        ((Counter<std::string> *) counters[index].second.first)->add_from_stream(&input_file);
        inFile.close();

    }

}

void Parser::add_from_string(std::vector<std::string> &input_string_vector) {
    size_t index = find_counter_by_name(input_string_vector[1]);
    //std::stringstream ss;
    if(counters[index].first != input_string_vector[1]){
        std::cerr << "No counter named " << input_string_vector[1];
        exit(1);
    }
    if(counters[index].second.second) { // int
        Counter<int>* temp_counter = ((Counter<int>*)counters[index].second.first);
        for (size_t i = 2; i < input_string_vector.size(); i++) {
            try {
                //ss << input_string_vector[i];
                temp_counter->add(std::atoi(( input_string_vector[i].c_str())));
            }
            catch (const std::exception &e) {
                std::cerr << "Read failed" ;
                exit(-1);
            }
        }
    }
    else{
        Counter<std::string>* temp_counter = ((Counter<std::string>*)counters[index].second.first);
        for (size_t i = 2; i < input_string_vector.size(); i++) {
            try {
                //ss << input_string_vector[i];
                temp_counter->add(input_string_vector[i]);
            }
            catch (const std::exception &e) {
                std::cerr << "Read failed" ;
                exit(-1);
            }
        }

    }
}

void Parser::stats(const std::string &counter_name) {
    size_t index = find_counter_by_name(counter_name);
    if(counters[index].first !=counter_name){
        std::cerr << "No counter named " << counter_name;
        exit(1);
    }
    std::cout << counter_name << " =";
    if(counters[index].second.second) { // int

        ((Counter<int>*)counters[index].second.first)->print_to_stream(std::cout);
    }
    else{
        ((Counter<std::string>*)counters[index].second.first)->print_to_stream(std::cout);
    }

    }

bool Parser::counter_exist(const std::string &counter_name) const {
    if(counters.empty())
        return false;
    size_t i = find_counter_by_name(counter_name);
    if (counters[i].first == counter_name)
        return true;
    return false;
}

size_t Parser::find_counter_by_name(const std::string &counter_name) const {
    size_t i =0;
    for (; i < counters.size();++i){
        if (counters[i].first == counter_name)
            break;
    }
    return i;
}

void Parser::most_common(const std::string &counter_name) {
    size_t i = find_counter_by_name(counter_name);
    if (counters[i].first != counter_name){
        std::cerr << "No counter named " << counter_name;
        exit(1);
    }
    if(counters[i].second.second) { // int counter
        if (((Counter<int> *) (counters[i].second.first))->is_empty()) {
            std::cout << "Counter is empty" << std::endl;
            return;
        }
        ((Counter<int> *) (counters[i].second.first))->print_most_common(std::cout);
    }
    else {
        if (((Counter<std::string> *) (counters[i].second.first))->is_empty()) {
            std::cout << "Counter is empty" << std::endl;
            return;
        }
        ((Counter<std::string> *) (counters[i].second.first))->print_most_common(std::cout);
    }

}
