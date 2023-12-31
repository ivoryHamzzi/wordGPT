#include "lang.h"
#include "openai.hpp"
#include <iostream>

const string& LangDef::getWord()
{
    return word;
}

void LangDef::setWord(const string& w)
{
    word = w;
}

const string& LangDef::get_def()
{
    return def;
}

void LangDef::set_def(const string& d)
{
    def = d;
}

void LangDef::printWordDetail() const
{
    using std::cout;
    using std::endl;

    cout << "  Word: " << word << '\n';
    cout << "  Definition: " << def << endl;
}

const string& EngDef::getPronunc()
{
    return pron;
}

void EngDef::setPronunc(const string& p)
{
    pron = p;
}

void EngDef::printWordDetail() const
{
    using std::cout;
    using std::endl;

    cout << "  Word: " << word << '[' << pron << ']' << '\n';
    cout << "  Definition: " << def << endl;
}

const string& JpnDef::getPronunc()
{
    return pron;
}

void JpnDef::setPronunc(const string& p)
{
    pron = p;
}

void JpnDef::setKanxi(string k)
{
    kanxi = k;
}

const string& JpnDef::getKanxi()
{
    return kanxi;
}

void JpnDef::printWordDetail() const
{
    using std::cout;
    using std::endl;

    cout << "  Word: " << word << '[' << pron << ']' << '\n';
    cout << "  Kanxi: " << kanxi << '\n';
    cout << "  Definition: " << def << endl;
}

void ChnDef::setKanxi(string k)
{
    kanxi = k;
}

const string& ChnDef::getKanxi()
{
    return kanxi;
}

void ChnDef::setEngRep(string e)
{
    eng_rep = e;
}

const string& ChnDef::getEngRep()
{
    return eng_rep;
}

void ChnDef::printWordDetail() const
{
    cout << "  Word: " << word << '[' << eng_rep << ']' << '\n';
    cout << "  Kanxi: " << kanxi << '\n';
    cout << "  Definition: " << def << endl;
}

const string& KorDef::getPronunc()
{
    return pron;
}

void KorDef::setPronunc(const string& p)
{
    pron = p;
}

const string& KorDef::getHanja()
{
    return hanja_rep;
}

void KorDef::setHanja(const string& h)
{
    hanja_rep = h;
}

void KorDef::printWordDetail() const
{
    cout << "  Word: " << word << '[' << pron << ']' << '\n';
    cout << "  Hanja: " << hanja_rep << '\n';
    cout << "  Definition: " << def << endl;
}

istream& operator >> (istream& ins, EngDef& l)
{
    getline(ins, l.word, '#');
    getline(ins, l.def, '#');
    getline(ins, l.pron, '#');
    return ins;
}
istream& operator >> (istream& ins, ChnDef& l)
{
    getline(ins, l.word, '#');
    getline(ins, l.def, '#');
    getline(ins, l.eng_rep, '#');
    getline(ins, l.kanxi, '#');
    return ins;
}
istream& operator >> (istream& ins, JpnDef& l)
{
    getline(ins, l.word, '#');
    getline(ins, l.def, '#');
    getline(ins, l.pron, '#');
    getline(ins, l.kanxi, '#');
    return ins;
}
istream& operator >> (istream& ins, KorDef& l)
{
    getline(ins, l.word, '#');
    getline(ins, l.def, '#');
    getline(ins, l.pron, '#');
    getline(ins, l.hanja_rep, '#');
    return ins;
}

ostream& operator << (ostream& outs, const EngDef& l)
{
    outs<<l.word<<'#'<<l.def<<'#'<<l.pron<<'#';
    return outs;
}
ostream& operator << (ostream& outs, const ChnDef& l)
{
    outs<<l.word<<'#'<<l.def<<'#'<<l.eng_rep<<'#'<<l.kanxi<<'#';
    return outs;
}
ostream& operator << (ostream& outs, const JpnDef& l)
{
    outs<<l.word<<'#'<<l.def<<'#'<<l.pron<<'#'<<l.kanxi<<'#';
    return outs;
}
ostream& operator << (ostream& outs, const KorDef& l)
{
    outs<<l.word<<'#'<<l.def<<'#'<<l.pron<<'#'<<l.hanja_rep<<'#';
    return outs;
}

string LangDef::get_rand_word_prompt()
{
    return string();
}
string LangDef::get_foreign_def_prompt()
{
    return string();
}

string EngDef::get_rand_word_prompt()
{
    string s ="Give me an English word in TOEIC difficulty level.";
    return s;
}

string EngDef::get_foreign_def_prompt()
{
    string s =	R"(Give details of the word given by user in the following Json format:
                { 
                      "word": "word given by user", 
                      "definition": "definition of the given word", 
                      "IPA": " IPA representation of the given word"
                })";
    return s;
}

string JpnDef::get_rand_word_prompt()
{
    string s ="Give me an Japanese word in JLPT difficulty level. Answer in a word represented only with Hiragana or Katakana";
    return s;
}

string JpnDef::get_foreign_def_prompt()
{
    string s =R"(Give details of the word given by user in the following Json format:
                { 
                        "word": "word that will be provided by user",
                        "definition": "definition of the word in Japanese",
                        "IPA": "IPA representation of the given word",
                        "kanxi": "Kanxi represetation of the given Japanese word"
                      
                })";
    return s;
}
string ChnDef::get_rand_word_prompt()
{
    string s ="Give me an Chinese word in HSK difficulty level. Answer only with the chinese character.";
    return s;
}
string ChnDef::get_foreign_def_prompt()
{
    string s =R"(Give details of the word given by user in the following Json format:
                { 
                        "word": "word that will be provided by user",
                        "definition": "definition of the word in chinese",
                        "IPA": "IPA representation of the word",
                        "kanxi": "Kanxi represetation of the given Chinese word"
                })";
    return s;
}

void EngDef::set_details(openai::Json eng_detail)
{
    word = "null";
    def = "null";
    pron = "null";
    if(eng_detail["word"].is_null() == false) 
        word = eng_detail["word"].get<string>();
    if(eng_detail["definition"].is_null() == false)
        def = eng_detail["definition"].get<string>();
    if(eng_detail["IPA"].is_null() == false)
        pron = eng_detail["IPA"].get<string>();
}

void JpnDef::set_details(openai::Json jpn_detail)
{
    word = "null";
    def = "null";
    pron = "null";
    kanxi = "null";
    if(jpn_detail["word"].is_null() == false)
        word = jpn_detail["word"].get<string>();
    if(jpn_detail["definition"].is_null() == false)
        def = jpn_detail["definition"].get<string>();
    if(jpn_detail["IPA"].is_null() == false)
        pron = jpn_detail["IPA"].get<string>();
    if(jpn_detail["kanxi"].is_null() == false)
        kanxi = jpn_detail["kanxi"].get<string>();      
}

void ChnDef::set_details(openai::Json chn_detail)
{
    word = "null";
    def = "null";
    eng_rep = "null";
    kanxi = "null";
    if(chn_detail["word"].is_null() == false)
        word = chn_detail["word"].get<string>();
    if(chn_detail["definition"].is_null() == false)
        def = chn_detail["definition"].get<string>();
    if(chn_detail["IPA"].is_null() == false)
        eng_rep = chn_detail["IPA"].get<string>();
    if(chn_detail["kanxi"].is_null() == false)
        kanxi = chn_detail["kanxi"].get<string>();      
}
