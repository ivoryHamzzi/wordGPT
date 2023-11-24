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
    /*
        Get question from GPT,
        get Answer from User,
        Check if the answer is right from GPT
        record it to records
    */
    void question(Dict<T>& dict, bool if_from, User& user);
    /* 
        return the record vector to user class;
        they will save it into Rec_probs.
    */
    const vector<Prob>& getRecords() const {return records;}

protected:
    vector<Prob> records;
    const static vector<string> init_prompt = 
    "Give me a question with a single English word\
                        in 4 choices of Korean.";
};

#endif
