#ifndef DICT_H
#define DICT_H
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
#include "lang.h"

enum Language {
    KOREAN,
    ENGLISH,
    JAPANESE,
    CHINESE,
};

template<class T>
class Dict {
public:
    Dict(string s):dict_file(s){}
    Dict():dict_file(""){}

    void search_mode(int mode);
    void add_map(const KorDef& kor, const T& lang);
private:
    unordered_map<String, T> dict_from_kor;
    unordered_map<String, KOREAN> dict_to_kor;
    unordered_map<String, T> word_detail;
    string dict_file;
};


#endif