#include "dict.h"
#include <fstream>

template<class T>
void Dict<T>::loadDict(){
    using namespace std;
    ifstream ins;
    ins.open(dict_file_path);
    if(ins.fail())
        return;
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
        out<<(*iter).first<<" "<<(*iter).second.first<<' '<<(*iter).second.second<<'\n';
        iter++;
    }
}

template<class T>
void Dict<T>::printDict(int id){
    auto iter = wordMap.find(id);
    (*iter).second.first.printWordDetail();
    (*iter).second.se.printWordDetail();
}

template<class T>
void Dict<T>::deleteDict(int id){
    auto iter = wordMap.find(id);
    wordMap.erase(iter);
}
template<class T>
void Dict<T>::addMap(const int id, const KorDef& kor, const T& lang){
    unused_id.pop();
    wordMap.insert((id, (lang, kor)));
}


/*
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
*/
