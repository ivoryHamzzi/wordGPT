#include "quiz.h"

#include <string>

using namespace std;

template<class T>
Prob Quiz<T>::question(Dict<T>& dict, bool if_from, string uname = "admin")
{
    return Prob();
}

Prob QuizE2K::question(Dict<EngDef>& dict, string uname = "admin")
{
        //Get from openai the question (English)
        //Give an response from 4 multiple choices (Korean)

        string gpt_in = "Give me a question with a single English word in\
        4 choices(1, 2, 3 and 4.) of Korean. The probability for\
        all of the choices to be an answer must be same.\
        You will reply to my answer with "Yes" or "No".\
        Set difficulty of question for TOEIC 900.";

        //then get the answer.
}

Prob QuizK2E::question(Dict<EngDef>& dict, string uname = "admin")
{
        //Get from openai the question (Korean)
        //Give an response with 4 multiple choices (English)
        //then get the answer.
}

Prob QuizC2K::question(Dict<ChnDef>& dict, string uname = "admin")
{
        //Get from openai the question (Chinese)
        //Give an response with 4 multiple choices (Korean)
        //then get the answer.
}

Prob QuizK2C::question(Dict<ChnDef>& dict, string uname = "admin")
{
        //Get from openai the question (Korean)
        //Give an response with 4 multiple choices (Chinese)
        //then get the answer.
}

Prob QuizJ2K::question(Dict<JpnDef>& dict, string uname = "admin")
{
        //Get from openai the question (Japanese)
        //Give an response with 4 multiple choices (Korean)
        //then get the answer.
}
Prob QuizK2J::question(Dict<JpnDef>& dict, string uname = "admin")
{
        //Get from openai the question (Korean)
        //Give an response with 4 multiple choices (Japanese)
        //then get the answer.
}