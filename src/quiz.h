#ifndef QUIZ_H
#define QUIZ_H


#include "user.h"
#include "openai.hpp"
#include "json.hpp"

using namespace std;

template<class T>
class Quiz {
public:
    Quiz();
    /*
        Get question from GPT,
        get Answer from User,
        Check if the answer is right from GPT
        record it to records
    */
    void question(Dict<T>& dict);
    /* 
        return the record vector to user class;
        they will save it into Rec_probs.
    */
    vector<Prob> getRecords() const {return record;}
    int getScore(){return score;}
    string get_rand_word();
    bool get_if_match(string q, string a);
    string get_right_ans(string q);
    openai::Json get_foreign_def(string q);
    openai::Json get_Korean_def(string q);

protected:
    vector<Prob> record;
    int score;
    openai::Json rand_word_prompt;
    openai::Json if_match_prompt;
    openai::Json actual_translate_prompt;
    openai::Json foreign_def_prompt;
    openai::Json korean_def_prompt;
};


template <class T>
string Quiz<T>::get_rand_word()
{
    T a;
    rand_word_prompt["messages"][1]["content"]=a.get_rand_word_prompt();
    
    auto completion = openai::chat().create(rand_word_prompt);
    return completion["choices"][0]["message"]["content"].template get<string>();
}

template<class T>
bool Quiz<T>::get_if_match(string q, string a)
{
        cout<< q + " / " + a<<'\n';
        string s = q + " / " + a;
        if_match_prompt["messages"][1]["content"] = s;
        auto completion = openai::chat().create(if_match_prompt);
        
        return (completion["choices"][0]["message"]["content"].get<string>()) == "Y";
}

template<class T>
string Quiz<T>::get_right_ans(string q)
{
    string s = "What is ";
    s += q;
    s += " in Korean?";
        actual_translate_prompt["messages"][1]["content"] = s;

        auto completion = openai::chat().create(actual_translate_prompt);
        return completion["choices"][0]["message"]["content"].get<string>();
}

template <class T>
openai::Json Quiz<T>::get_foreign_def(string q)
{
    T a;-
        foreign_def_prompt["messages"][0]["content"] = a.get_foreign_def_prompt();
        foreign_def_prompt["messages"][1]["content"] = q;
        auto completion = openai::chat().create(foreign_def_prompt);
        return openai::Json::parse(completion["choices"][0]["message"]["content"].get<string>());
}
/*
//template<>
openai::Json Quiz<EngDef>::get_foreign_def(string q)
{
        foreign_def_prompt["message"][0]["content"] = 	R"(Give details of the word given by user in the following Json format:
                { 
                      "word": "word given by user", 
                      "definition": "definition of the word", 
                      "pronounciation": "pronounciation of word in english"
                      
                  })";
        foreign_def_prompt["message"][1]["content"] = q;
        auto completion = openai::chat().create(rand_word_prompt);
        return openai::Json::parse(completion["choices"][0]["message"]["content"].get<string>());
}

//template<>
openai::Json Quiz<JpnDef>::get_foreign_def(string q)
{
        foreign_def_prompt["message"][0]["content"] = 	R"(Give details of the word given by user in the following Json format:
                { 
                        "word" : "word that will be provided by user",
                        "definition":"definition of the word in Japanese",
                        "pronounciation": "pronounciation of the word",
                        "kanxi":"Kanxi represetation of the given Japanese word"
                      
                })";
        foreign_def_prompt["message"][1]["content"] = q;
        auto completion = openai::chat().create(rand_word_prompt);
        return openai::Json::parse(completion["choices"][0]["message"]["content"].get<string>());
}

//template<>
openai::Json Quiz<ChnDef>::get_foreign_def(string q)
{
        foreign_def_prompt["message"][0]["content"] = 	R"(Give details of the word given by user in the following Json format:
                { 
                        "word" : "word that will be provided by user",
                        "definition" : "definition of the word in chinese",
                        "pronounciation":"pronounciation of the word",
                        "kanxi":"Kanxi represetation of the given Chinese word"
                })";
        foreign_def_prompt["message"][1]["content"] = q;
        auto completion = openai::chat().create(rand_word_prompt);
        return openai::Json::parse(completion["choices"][0]["message"]["content"].get<string>());
}
*/
template<class T>
openai::Json Quiz<T>::get_Korean_def(string q)
{
        korean_def_prompt["messages"][0]["content"] = 	R"(Give details of the word given by user in the following Json format:
                { 
                      "word": "korean word given by user",
                      "definition":"definition of the given word in korean",
                      "pronounciation": "pronounciation of the word in korean",
                      "hanja" : "chinese character representation of the given korean word. if not exists, set it to null."
                })";
        korean_def_prompt["messages"][1]["content"] = q;
        auto completion = openai::chat().create(korean_def_prompt);
        return openai::Json::parse(completion["choices"][0]["message"]["content"].get<string>());
}

template<class T>
Quiz<T>:: Quiz()
{
    cout<<"Quiz init\n";
    rand_word_prompt["model"]="gpt-3.5-turbo";
    rand_word_prompt["messages"][0]["role"]="system";
    rand_word_prompt["messages"][0]["content"]="Answer only in a single word. Do not make the same response you made before.";
    rand_word_prompt["messages"][1]["role"]="user";
    //openai_json["messages"][1]["content"] = ans;
    rand_word_prompt["temperature"] = 1.0;        

    if_match_prompt["model"]="gpt-3.5-turbo";
    if_match_prompt["messages"][0]["role"]="system";
    if_match_prompt["messages"][0]["content"]=R"(You will get two words, divided by '/', by user. 
                      Type 'Y' only if the first word can be translated into second word. 
                      Else, type 'N' only.)";
    if_match_prompt["messages"][1]["role"]="user";
    //openai_json["messages"][1]["content"] = ans;
    if_match_prompt["temperature"] = 0.0;       

    actual_translate_prompt["model"]="gpt-3.5-turbo";
    actual_translate_prompt["messages"][0]["role"]="system";
    actual_translate_prompt["messages"][0]["content"]="Response only with the korean word.";
    actual_translate_prompt["messages"][1]["role"]="user";
    //actual_translate_prompt["messages"][1]["content"] =
    actual_translate_prompt["temperature"] = 0.0;       
 
    foreign_def_prompt["model"]="gpt-3.5-turbo";
    foreign_def_prompt["messages"][0]["role"]="system";
    /*
    foreign_def_prompt["messages"][0]["content"]= R"(Give details of the word given by user in the following Json format:
                { 
                      "word": "word given by user", 
                      "definition": "definition of the word", 
                      "pronounciation": "pronounciation of word in english"
                      
                  })";
                  */
    foreign_def_prompt["messages"][1]["role"]="user";
    //openai_json["messages"][1]["content"] = ans;
    foreign_def_prompt["temperature"] = 0.0;       

    korean_def_prompt["model"]="gpt-3.5-turbo";
    korean_def_prompt["messages"][0]["role"]="system";
    korean_def_prompt["messages"][0]["content"]=R"(Give details of the word given by user in the following Json format:
                { 
                    
                      "word": "Korean word given by user",
                      "definition":"definition of the word in korean",
                      "pronounciation": "pronounciation of the word in korean",
                      "hanja" : "chinese character representation of the given korean word. if not exists, set it to null."
                    
                  })";
    korean_def_prompt["messages"][1]["role"]="user";
    //openai_json["messages"][1]["content"] = ans;
    korean_def_prompt["temperature"] = 0.0;
}

template <class T>
void Quiz<T>::question(Dict<T>& dict)
{
        score = 0;
        record.clear();
        for(int i=0; i<3; i++){
            cout<<"Question\n";
            string q = get_rand_word();
            cout << "Question: " << q << endl;
            cout << "Type answer\n";
            string ans;
            if(i==0)cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(cin, ans);
            bool is_ans = get_if_match(q, ans);
            if(!is_ans) {
                    cout<<"Wrong answer... :(\n";
                    ans = get_right_ans(q);
                    cout<<"The answer is "<<ans<<endl;
            }
            else{
                cout<<"Correct!\n";
                score++;
            } 
            openai::Json eng_detail = get_foreign_def(q);
            /*string word = eng_detail["word"].get<string>();
            string def = eng_detail["definition"].get<string>();
            string pro = eng_detail["pronounciation"].get<string>();*/
            T e;
            e.set_details(eng_detail);
            openai::Json kor_detail = get_Korean_def(ans);
            string kor_word = "null";
            string kor_def= "null";
            string kor_pro = "null";
            string kor_h = "null";
            if(kor_detail["word"].is_null() == false)
                kor_word = kor_detail["word"].get<string>();
            if(kor_detail["definition"].is_null() == false)
                kor_def = kor_detail["definition"].get<string>();
            if(kor_detail["pronounciation"].is_null() == false)
                kor_pro = kor_detail["pronounciation"].get<string>();
            if(kor_detail["hanja"].is_null() == false)
                kor_h = kor_detail["hanja"].get<string>();
            KorDef k(kor_word, kor_def, kor_pro, kor_h);

            Prob problem;
            problem.prob = q;
            problem.ans = ans;
            problem.if_right = is_ans;
            problem.word_id = dict.retId();
            record.push_back(problem);
            dict.addMap(problem.word_id, k, e);
        }
}
#endif
