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
    Quiz();
    /*
        Get question from GPT,
        get Answer from User,
        Check if the answer is right from GPT
        record it to records
    */
    void question(Dict<T>& dict, bool if_from);
    /* 
        return the record vector to user class;
        they will save it into Rec_probs.
    */
    const vector<Prob>& getRecords() const {return records;}

    string get_rand_word();
    bool get_if_match(string q, string a);
    string get_right_ans(string q);
    openai::Json get_foreign_def(string q);
    openai::Json get_Korean_def(string q);

protected:
    static openai::Json rand_word_prompt;
    static openai::Json if_match_prompt;
    static openai::Json actual_translate_prompt;
    static openai::Json foreign_def_prompt;
    static openai::Json korean_def_prompt;
};

#endif
