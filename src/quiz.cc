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


void Quiz<EngDef>::question(Dict<EngDef>& dict, bool from_korean)
{
        //Get from openai the question (English)
        //Give an response from 4 multiple choices (Korean)
        string gpt_in;
        if(from_korean) {

        } else {

        }


        //then get the answer.
        string prob;
        string ans;
        bool isAns = true;

        Prob p;
        p.prob=prob;
        p.ans=ans;
        p.if_right=isAns;
        p.word_id=dict.retId();

        records.push_back(p);

        //load details from gpt anyway
        KorDef korean(prob, prob, prob, prob);
        EngDef eng(ans, "", "");
        dict.addMap(p.word_id, korean, eng);
        
}

void Quiz<ChnDef>::question(Dict<ChnDef>& dict, bool from_korean)
{
        //Get from openai the question (Chinese)
        //Give an response with 4 multiple choices (Korean)
        //then get the answer.
}

void Quiz<JpnDef>::question(Dict<JpnDef>& dict, bool from_korean)
{
        //Get from openai the question (Japanese)
        //Give an response with 4 multiple choices (Korean)
        //then get the answer.
}