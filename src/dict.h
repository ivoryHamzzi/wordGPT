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

    int retId(){return unused_id.front();}
    void loadDict();
    void storeDict();
    void printDict(int id) const;
    void deleteDict(int id);
    void addMap(const int id, const KorDef& kor, const T& lang);
    friend class Rec_probs;
    friend struct Prob;
    auto find(int id) {return wordMap.find(id);}
private:
    map<int, pair<T, KorDef> > wordMap;
    queue<int> unused_id;

    string dict_file_path;
};


template<class T>
void Dict<T>::loadDict(){
    using namespace std;
    ifstream ins;
    ins.open(dict_file_path);
    if(ins.fail()){
        for(int i = 0; i < 10000; i++) 
            unused_id.push(i);
        return;
    }
    int cnt = 0;
    int curId = -1;
    while(ins>>curId){
        if(curId != cnt){
            for(int i = cnt; i<curId; i++)
                unused_id.push(i);
        }
        cnt = curId + 1;
        T f;
        KorDef k;
        cin>>f>>k;
        wordMap.insert({curId, {f, k}});
    }
    for(int i = cnt; i < 10000; i++) 
        unused_id.push(i);
}

template<class T>
void Dict<T>::storeDict(){
    using namespace std;
    ofstream out;
    out.open(dict_file_path);
    auto iter = wordMap.begin();
    while(iter != wordMap.end()){
        out<<(*iter).first<<'\n'<<(*iter).second.first<<(*iter).second.second;
        iter++;
    }
}

template<class T>
void Dict<T>::printDict(int id)const{
    auto iter = wordMap.find(id);
    (*iter).second.first.printWordDetail();
    (*iter).second.second.printWordDetail();
}

template<class T>
void Dict<T>::deleteDict(int id){
    auto iter = wordMap.find(id);
    wordMap.erase(iter);
}
template<class T>
void Dict<T>::addMap(const int id, const KorDef& kor, const T& lang){
    unused_id.pop();
    wordMap[id] = make_pair(lang, kor);
}

#endif