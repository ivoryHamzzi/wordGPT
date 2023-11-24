#include "quiz.h"

#include <string>

using namespace std;

void Quiz<EngDef>::question(Dict<EngDef>& dict, bool if_from)
{
        //Get from openai the question (English)
        //Give an response from 4 multiple choices (Korean)
        string gpt_in = "Give me a question with a single English word in\
        4 choices(1, 2, 3 and 4.) of Korean. The probability for\
        all of the choices to be an answer must be same.\
        You will reply to my answer with \"Yes\" or \"No\".\
        Set difficulty of question for TOEIC 900.";

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
        KorDef korean(prob, string(), string(), string());
        EngDef eng(ans, "", "");
        dict.addMap(p.word_id, korean, eng);
        
}

void Quiz<ChnDef>::question(Dict<ChnDef>& dict, bool if_from)
{
        //Get from openai the question (Chinese)
        //Give an response with 4 multiple choices (Korean)
        //then get the answer.
}

void Quiz<JpnDef>::question(Dict<JpnDef>& dict, bool if_from)
{
        //Get from openai the question (Japanese)
        //Give an response with 4 multiple choices (Korean)
        //then get the answer.
}