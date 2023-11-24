#ifndef DICT_H
#define DICT_H
#include <iostream>
#include <string>
#include <map>
#include <queue>
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

    int retId(){return unused_id.first();}
    void load_dict();
    void store_dict();
    void searchDict(int id);
    void deleteDict(int id);
    void add_map(const int id, const KorDef& kor, const T& lang);
private:
    map<int, pair<T, KorDef> > wordMap;
    queue<int> unused_id;

    string dict_file_path;
};


#endif