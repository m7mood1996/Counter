//
// Created by mahmood on 6/13/21.
//

#ifndef COUNTER_PARSER_H
#define COUNTER_PARSER_H

#include "Counter.h"
class Parser {
public:
    Parser();
    ~Parser();
    void run();
    // add new counter to the victor type is representing int/string counter
    void add_counter(const std::string& string_counter, bool type);
    void add_from_file(const std::string& counter_name, const char* file_name );
    void add_from_string(std::vector<std::string>& input_string_vector );
    void stats(const std::string& counter_name);
    void most_common(const std::string& counter_name);


private:
    std::vector<std::pair<std::string ,std::pair<void*,bool> > > counters;
    bool counter_exist(const std::string& counter_name) const;
    size_t find_counter_by_name(const std::string& counter_name) const;

};


#endif //COUNTER_PARSER_H
