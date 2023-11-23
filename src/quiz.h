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
    virtual Prob question(Dict<T>& dict, bool if_from, string uname = "admin");

    /* 
        return the record vector to user class;
        they will save it into Rec_probs.
    */
    const vector<Prob>& get_records() const {return records;}
    
private:
    vector<Prob> records;
    const static vector<string> init_prompt = 
    "Give me a question with a single English word\
                        in 4 choices of Korean.";
}

class Quiz_E2K: Quiz<EngDef> {
    Prob question(Dict<EngDef>& dict, string uname = "admin");
}

class Quiz_K2E: Quiz<EngDef> {
    Prob question(Dict<EngDef>& dict, string uname = "admin");
}

class Quiz_C2K: Quiz<ChnDef> {
    Prob question(Dict<ChnDef>& dict, string uname = "admin");
}

class Quiz_K2C: Quiz<ChnDef> {
    Prob question(Dict<ChnDef>& dict, string uname = "admin");
}

class Quiz_J2K: Quiz<JpnDef> {
    Prob question(Dict<JpnDef>& dict, string uname = "admin");
}

class Quiz_K2J: Quiz<JpnDef> {
    Prob question(Dict<JpnDef>& dict, bool if_from, string uname = "admin");
}

#endif
