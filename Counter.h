//
// Created by mahmood on 6/13/21.
//

#ifndef COUNTER_COUNTER_H
#define COUNTER_COUNTER_H
#include<bits/stdc++.h>
#include <vector>
#include <cstddef>
#include <iostream>
#include <ostream>
template<typename T>
class Counter {

public:
    Counter();
    ~Counter();

    // clearing the vector of the objects
    void clear();

    // add new obj with counter 1 to the vector or raising the counter by 1 if it is included
    void add(T obj);


    size_t operator[](T& obj) const;
    T& most_common() const;
    void add_from_stream(std::istream *istream);
    void print_to_stream(std::ostream& ostream) const;
    void print_most_common(std::ostream &ostream) const;
    bool is_empty();
private:
    // template vector of pairs: the first describe the object the second describe the freq
    std::vector<std::pair<T,size_t> > counter_vector;

    size_t find_index(T &obj) const;
    size_t find_max()const;
};

template<typename T>
Counter<T>::Counter() {

}

template<typename T>
Counter<T>::~Counter() {

}

template<typename T>
void Counter<T>::clear() {
    counter_vector.clear();
}

template<typename T>
void Counter<T>::add(T obj) {
    if (counter_vector.size() == 0){
        std::pair<T,size_t> newPair(obj,1);
        counter_vector.push_back(newPair);
        return;
    }
    size_t index = find_index(obj);
    if(counter_vector[index].first == obj)
        ++counter_vector[index].second;
    else{
        std::pair<T,size_t> newPair(obj,1);
        counter_vector.push_back(newPair);
    }
    std::sort(counter_vector.begin(), counter_vector.end());
}

template<typename T>
size_t Counter<T>::find_index(T &obj)const {
    size_t i = 0;
    for (; i < counter_vector.size(); i++)
        if(counter_vector[i].first == obj)
            break;
    return i;
}

template<typename T>
size_t Counter<T>::operator[](T &obj) const {
    size_t index = find_index(obj);
    if (counter_vector[index].first == obj)
        return counter_vector[index].second;
    return 0;
}

template<typename T>
T &Counter<T>::most_common() const {
    // the vector is sorted, so returning the first element hits the max
    size_t max_index = find_max();
    return counter_vector[max_index].first;
}

template<typename T>
void Counter<T>::add_from_stream( std::istream *istream) {
    T obj;
    while((*istream) >> obj)
        //istream >> obj;
        add(obj);


}

template<typename T>
void Counter<T>::print_to_stream(std::ostream& ostream) const {

    ostream << "{ " ;
    for (size_t i = 0; i < counter_vector.size();++i){
        ostream << counter_vector[i].first;
        ostream << ':';
        ostream << counter_vector[i].second;
        ostream << ' ';
    }
    ostream << " }";
}

template<typename T>
void Counter<T>::print_most_common( std::ostream &ostream) const {
    size_t index = find_max();
    ostream << counter_vector[index].first << ":" << counter_vector[index].second;
}

template<typename T>
size_t Counter<T>::find_max() const {
    if (counter_vector.size() == 0)
        throw std::runtime_error("Vector has no elements");
    size_t max = 0;
    size_t max_index = 0;
    size_t i = 0;
    for (;i< counter_vector.size();++i){
        if (counter_vector[i].second > max) {
            max = counter_vector[i].second;
            max_index = i;
        }
    }
    return max_index;
}

template<typename T>
bool Counter<T>::is_empty() {
    return counter_vector.empty();
}


#endif //COUNTER_COUNTER_H
