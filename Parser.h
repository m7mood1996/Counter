//
// Created by mahmood on 6/13/21.
//

#ifndef COUNTER_PARSER_H
#define COUNTER_PARSER_H

#include "Counter.h"
class Parser {
public:
    // constructor and destructor
    Parser();
    ~Parser();
    // function for making the program run (getting input from the user and gives output)
    void run();
    // add new counter to the victor type is representing int/string counter
    void add_counter(const std::string& string_counter, bool type);
    // adding objects to specific counter objects from a given file
    void add_from_file(const std::string& counter_name, const char* file_name );
    // adding objects to specific counter objects from string
    void add_from_string(std::vector<std::string>& input_string_vector );
    // print the counter
    void stats(const std::string& counter_name);
    // print the most common object from a given counter name
    void most_common(const std::string& counter_name);


private:
    // template vector of counter name and a counter object and the type
    std::vector<std::pair<std::string ,std::pair<void*,bool> > > counters;
    // returns if the given counter name is exist in the counters vector
    bool counter_exist(const std::string& counter_name) const;
    // returns the index of the counter name in the counter vector
    size_t find_counter_by_name(const std::string& counter_name) const;

};


#endif //COUNTER_PARSER_H
