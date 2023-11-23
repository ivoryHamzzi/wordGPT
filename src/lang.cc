#include "lang.h"
#include "../include/openai/openai.hpp"
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

void LangDef::printWordDetail()
{
    using std::cout;
    using std::endl;

    cout << "Word: " << word << '\n';
    cout << "Definition: " << def << endl;
}

const string& EngDef::getPronunc()
{
    return pron;
}

void EngDef::setPronunc(const string& p)
{
    pron = p;
}

void EngDef::printWordDetail()
{
    using std::cout;
    using std::endl;

    cout << "Word: " << word << '[' << pron << ']' << '\n';
    cout << "Definition: " << def << endl;
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

void JpnDef::printWordDetail()
{
    using std::cout;
    using std::endl;

    cout << "Word: " << word << '[' << pron << ']' << '\n';
    cout << "Kanxi: " << kanxi << '\n';
    cout << "Definition: " << def << endl;
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

void ChnDef::printWordDetail()
{
    cout << "Word: " << word << '[' << eng_rep << ']' << '\n';
    cout << "Kanxi: " << kanxi << '\n';
    cout << "Definition: " << def << endl;
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

void KorDef::printWordDetail()
{
    cout << "Word: " << word << '[' << pron << ']' << '\n';
    cout << "Hanja: " << hanja_rep << '\n';
    cout << "Definition: " << def << endl;
}

const KorDef& EngDef::load_from_gpt_from_kor(string str){
    openai::start();
    string s = "return word, definition, pronounciation of "+str+
                " in both korean and english in Json format\n "+
                    "like\n"+
                    "{\"word\" : \"\", \n"+
                    "\"definition\" : \"\", \n"+
                    "\"pronounciation\" : \"\", \n"+
                    "\"k_word\" : \"\", \n"+
                    "\"k_definition\" : \"\", \n"+
                    "\"k_pronounciation\" : \"\", \n"+
                    "\"Hanja\" : \"\", \n"+
                    "}";
    auto completion = openai::completion().create({
        {"model", "gpt-3.5-turbo-1106"},
        {"response_format", "{ \"type\": \"json_object\"}"},
        {"prompt", s},
        {"max_tokens", 500},
        { "temperature", 0}
    });

    this->word = completion["data"][0]["word"];
    this->def = completion["data"][0]["definition"];
    this->pron = completion["data"][0]["pronounciation"];
    string kw = completion["data"][0]["k_word"];
    string kd = completion["data"][0]["k_definition"];
    string kp = completion["data"][0]["k_pronounciation"];
    string kh = completion["data"][0]["Hanja"];
    KorDef k(kw, kd, kp, kh);
    return k;
}

const KorDef& EngDef::load_from_gpt_to_kor(string str){
    openai::start();
}

const KorDef& ChnDef::load_from_gpt_from_kor(string str){
    openai::start();
    
}

const KorDef& ChnDef::load_from_gpt_to_kor(string str){
    openai::start();
}

const KorDef& JpnDef::load_from_gpt_from_kor(string str){
    openai::start();
}

const KorDef& JpnDef::load_from_gpt_to_kor(string str){
    openai::start();
}

istream& operator >> (istream& ins, EngDef& l){
    ins >> l.word >>l.def >>l.pron;
    return ins;
}
istream& operator >> (istream& ins, ChnDef& l){
    ins>>l.word>>l.def>>l.eng_rep>>l.kanxi;
    return ins;
}
istream& operator >> (istream& ins, JpnDef& l){
    ins>>l.word>>l.def>>l.pron>>l.kanxi;
    return ins;
}
istream& operator >> (istream& ins, KorDef& l){
    ins>>l.word>>l.def>>l.pron>>l.hanja_rep;
    return ins;
}

ostream& operator << (ostream& outs, const EngDef& l){
    outs<<l.word<<' '<<l.def<<' '<<l.pron<<'\n';
    return outs;
}
ostream& operator << (ostream& outs, const ChnDef& l){
    outs<<l.word<<' '<<l.def<<' '<<l.eng_rep<<' '<<l.kanxi<<'\n';
    return outs;
}
ostream& operator << (ostream& outs, const JpnDef& l){
    outs<<l.word<<' '<<l.def<<' '<<l.pron<<' '<<l.kanxi<<'\n';
    return outs;
}
ostream& operator << (ostream& outs, const KorDef& l){
    outs<<l.word<<' '<<l.def<<' '<<l.pron<<' '<<l.hanja_rep<<'\n';
    return outs;
}
