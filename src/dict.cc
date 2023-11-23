#include "dict.h"
#include <fstream>


template<class T>
void Dict<T>::load_dict(){
    using namespace std;
    ifstream ins;
    ins.open(dict_file_path);
    
    int ops = -1;
    while(ins >> ops){
        switch (ops){
        case 1:
            string k;
            T e;
            cin>> k>> e;
            dict_from_kor.insert((k,e));
            break;
        case 2:
            string e;
            KorDef k;
            cin>> e>> k;
            dict_to_kor.insert((e,k));
            break;
        case 3:
            string e;
            T ec;
            cin>> e>> ec;
            dict_to_kor.insert((e,ec));
            break;
        }

    }
}

template<class T>
void Dict<T>::store_dict(){
    using namespace std;
    ofstream out;
    out.open(dict_file_path);
    auto iter = dict_from_kor.begin();
    while(iter != dict_from_kor.end()){
        out<<"1" << (*iter).first<<" "<<(*iter).second<<'\n';
        iter++;
    }
    iter = dict_to_kor.begin();
    while(iter != dict_to_kor.end()){
        out<<"2" << (*iter).first<<" "<<(*iter).second<<'\n';
        iter++;
    }
    iter = word_detail.begin();
    while(iter != word_detail.end()){
        out<<"3" << (*iter).first<<" "<<(*iter).second<<'\n';
        iter++;
    }
}

template<class T>
void Dict<T>::search_mode(int mode){
    String input_word;
    std::cout<<"type word to search: ";
    std::cin>>input_word;
    switch(mode){
    case 0://from korean
        T lang();
        auto iter = dict_from_kor.find(input_word);
        if(iter == dict_from_kor.end()) { // NOT-FOUND
            lang.load_from_gpt_from_kor(input_word);
            KorDef kor();
            kor.load_from_gpt_from_kor(input_word);

            dict_from_kor.insert(kor.get_word(), lang);
            dict_to_kor.insert(lang.get_word(), kor);
            word_detail.insert(lang.get_word(), lang);
        } else {
            lang = *iter;
        }
        lang.print_search();
        break;
    case 1://to korean
        KorDef lang();
        auto iter = dict_to_kor.find(input_word);
        if(iter == dict_to_kor.end()){
            lang.load_from_gpt_to_kor();
            KorDef kor();
            kor.load_from_gpt_to_kor();

            dict_from_kor.insert(kor.get_word(), lang);
            dict_to_kor.insert(lang.get_word(), kor);
            word_detail.insert(lang.get_word(), lang);
        }else{
            lang = *iter;
        }
        lang.print_search();
        break;
    }
} 

template<class T>
void Dict<T>::add_map(const KorDef& kor, const T& lang){
    auto iter = dict_from_kor.find(kor.get_word);
    if(iter != dict_from_kor.end())return;
    dict_from_kor.insert((kor.get_word(), lang));
    dict_to_kor.insert((lang.get_word(), kor));
    word_detail.insert((lang.get_word(), lang));
}

