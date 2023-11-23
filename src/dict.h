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
    Dict(string s):dict_file_path(s){
        load_dict();
    }
    Dict():dict_file(""){}

    void load_dict();
    void store_dict();
    void search_mode(int mode);
    void add_map(const KorDef& kor, const T& lang);
private:
    unordered_map<string, T> dict_from_kor;
    unordered_map<string, KorDef> dict_to_kor;
    unordered_map<string, T> word_detail;
    string dict_file_path;
};


#endif