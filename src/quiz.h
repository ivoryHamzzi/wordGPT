#ifndef QUIZ_H
#define QUIZ_H

#include "lang.h"
#include "user.h"
#include "dict.h"
#include <openai.hpp>
#include <vector>

using namespace std;

template<class T>
class Quiz {
public:
    virtual Prob question(Dict<T>& dict, string uname = "admin");
    const vector<Prob>& get_records() const {return records;}
    T a;
    string q = a.get_question();

    
private:
    vector<Prob> records;
    const static vector<string> init_prompt = set_init_prompt();
    static vector<string> set_init_prompt = {
        vector<string> ret(0);
        ret.push_back(
            "Give me an simple word without any sentence.
            Then I'll give you an Korean answer.
            And then you'll give me an response with the json format:
            {
            "Question": "Giraffe",
            "User's answer": "기린",
            "Actual answer": "기린"
            "If-correct": "Yes"
            }
        );
    }
}

template<class T>
class Quiz_word_to_word: Quiz<T> {
    Prob question(Dict<T>& dict, string uname = "admin");
}

#endif
