#include "dict.h"

template<class T>
void Dict<T>::search_mode(int mode){
    String input_word;
    std::cout<<"type word to search: ";
    std::cin>>input_word;
    switch(mode){
    case 0://from korean
        T lang;
        auto iter = dict_from_kor.find(input_word);
        if(iter == dict_from_kor.end()){
            T* langPtr = new T();
            langPtr.load_from_gpt();
            KorDef* korPtr = new KorDef();
            korPtr.load_from_gpt();

            dict_from_kor.insert(((*korPtr).get_word(), *langPtr));
            dict_to_kor.insert(((*langPtr).get_word(), *korPtr));
            word_detail.insert(((*langPtr).get_word(), *langPtr));
            lang = *langPtr;
        }else{
            lang = *iter;
        }
        lang.print_search();
        break;
    case 1://to korean
        KorDef lang;
        auto iter = dict_to_kor.find(input_word);
        if(iter == dict_to_kor.end()){
            T* langPtr = new T();
            langPtr.load_from_gpt();
            KorDef* korPtr = new KorDef();
            korPtr.load_from_gpt();

            dict_from_kor.insert(((*korPtr).get_word(), *langPtr));
            dict_to_kor.insert(((*langPtr).get_word(), *korPtr));
            word_detail.insert(((*langPtr).get_word(), *langPtr));
            lang = *korPtr;
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

