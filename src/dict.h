#ifndef DICT_H
#define DICT_H
#include <iostream>
#include <string>
#include <unordered_map>
enum Language {
    KOREAN,
    ENGLISH,
    JAPANESE,
    CHINESE,
};

template<class T>
class Dict {
public:
    Dict();
    ~Dict();

    void search_mode(int mode){
        string input;
        std::cout<<"type word to search: ";
        std::cin>>input;
        switch(mode){
            case 0://from korean


        }
    } 
private:
    unordered_map<string, T> dict_from_kor;
    unordered_map<string, KOREAN> dict_to_kor;
    unordered_map<string, T> word_detail;
};


#endif