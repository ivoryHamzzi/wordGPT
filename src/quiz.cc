#include "quiz.h"

template<class T>
Prob Quiz<T>::question(Dict<T>& dict, bool if_from, string uname = "admin")
{
    return Prob();
}

Prob QuizE2K::question(Dict<EngDef>& dict, string uname = "admin")
{
        //Get from openai the question (English)
        //Give an response with 4 multiple choices (Korean)
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