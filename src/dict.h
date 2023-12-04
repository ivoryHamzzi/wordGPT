#ifndef DICT_H
#define DICT_H
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <fstream>
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
    Dict(string s):dict_file_path(s) {loadDict();}
    Dict():dict_file_path(""){}
    ~Dict() {storeDict();}

    void loadDict();
    void storeDict();
    void printDict(const string& word) const;
    void deleteDict(const string& word);
    void addMap(const string& word, const KorDef& kor, const T& lang);
    friend class Rec_probs;
    friend struct Prob;
    auto find(const string& s) {return wordMap.find(s);}
    auto exist(const string& s) {return find(s) != wordMap.end();};
private:
    map<string, pair<T, KorDef> > wordMap;
    string dict_file_path;
};


template<class T>
void Dict<T>::loadDict(){
    using namespace std;
    ifstream ins;
    ins.open(dict_file_path);
    if(ins.fail())
        return;
    string word;
    while(getline(ins, word, '#') && (!ins.eof())){
        T f;
        KorDef k;
        ins>>f>>k;
        wordMap.insert({word, {f, k}});
    }
}

template<class T>
void Dict<T>::storeDict(){
    using namespace std;
    ofstream out;
    out.open(dict_file_path);
    auto iter = wordMap.begin();
    while(iter != wordMap.end()){
        out<<(*iter).first<<'#'<<(*iter).second.first<<(*iter).second.second;
        iter++;
    }
}

template<class T>
void Dict<T>::printDict(const string& word)const{
    auto iter = wordMap.find(word);
    if(iter == wordMap.end()) {
        cout << word << ": Definition Not found!" << endl;
        return;
    }
    cout << "##### Foreign Definition #####" << endl;
    (*iter).second.first.printWordDetail();
    cout << "##### Korean Definition #####" << endl;
    (*iter).second.second.printWordDetail();
    cout << endl;
}

template<class T>
void Dict<T>::deleteDict(const string& word){
    auto iter = wordMap.find(word);
    if(iter != wordMap.end())
        wordMap.erase(iter);
}

template<class T>
void Dict<T>::addMap(const string& word, const KorDef& kor, const T& lang){
    if(wordMap.find(word) == wordMap.end())
        wordMap[word] = make_pair(lang, kor);
}

#endif