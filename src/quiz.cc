#include "quiz.h"

#include <string>

using namespace std;

template<class T>
Quiz<T>:: Quiz()
{
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


string Quiz<EngDef>::get_rand_word()
{
        rand_word_prompt["messages"][1]["content"]="Give me an English word in TOEIC difficulty level.";
        auto completion = openai::chat().create(rand_word_prompt);
        return completion["choices"][0]["message"]["content"].get<string>();
}

string Quiz<JpnDef>::get_rand_word()
{
        rand_word_prompt["messages"][1]["content"]="Give me an Japanese word in JLPT difficulty level.";
        auto completion = openai::chat().create(rand_word_prompt);
        return completion["choices"][0]["message"]["content"].get<string>();
}

string Quiz<ChnDef>::get_rand_word()
{
        rand_word_prompt["messages"][1]["content"]="Give me an Chinese word in HSK difficulty level.";
        auto completion = openai::chat().create(rand_word_prompt);
        return completion["choices"][0]["message"]["content"].get<string>();
}

template<class T>
bool Quiz<T>::get_if_match(string q, string a)
{
        if_match_prompt["message"][1]["content"] = q + " / " + a;
        auto completion = openai::chat().create(rand_word_prompt);
        return (completion["choices"][0]["message"]["content"].get<string>()) == "Y";
}

template<class T>
string Quiz<T>::get_right_ans(string q)
{
        actual_translate_prompt["message"][1]["content"] = q;
        auto completion = openai::chat().create(rand_word_prompt);
        return completion["choices"][0]["message"]["content"].get<string>();
}

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

openai::Json Quiz<ChnDef>::get_foreign_def(string q)
{
        foreign_def_prompt["message"][0]["content"] = 	R"(Give details of the word given by user in the following Json format:
                { 
                        "word" : "word that will be provided by user",
                        "definition" : "definition of the word in chinese",
                        "pronounciation":"pronounciation of the word",
                        "kanxi":"Kanxi represetation of the Chinese word"
                })";
        foreign_def_prompt["message"][1]["content"] = q;
        auto completion = openai::chat().create(rand_word_prompt);
        return openai::Json::parse(completion["choices"][0]["message"]["content"].get<string>());
}

template<class T>
openai::Json Quiz<T>::get_Korean_def(string q)
{
        korean_def_prompt["message"][0]["content"] = 	R"(Give details of the word given by user in the following Json format:
                { 
                      "word": "korean word given by user",
                      "definition":"definition of the given word in korean",
                      "pronounciation": "pronounciation of the word in korean",
                      "hanja" : "chinese character representation of the given korean word. if not exists, set it to null."
                })";
        korean_def_prompt["message"][1]["content"] = q;
        auto completion = openai::chat().create(rand_word_prompt);
        return openai::Json::parse(completion["choices"][0]["message"]["content"].get<string>());
}