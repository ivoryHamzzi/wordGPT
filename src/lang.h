#ifndef LANG_H
#define LANG_H
#include <string>

using namespace std;

class LangDef {
public:
    LangDef(const string& w, const string& d):word(w),def(d){};
    LangDef(const string& w):word(w),def(""){};
    LangDef():word(""),def(""){};

    virtual const string& get_word();
    virtual void set_word(const string& w);

    const string& get_def();
    void set_def(const string& d);

protected:
    string word;
    string def;    
};

class EngDef:LangDef{
public:
    void set_word()
private:
    string pron;
};

class JpnDef:LangDef{
    string chn_dcl;
};

class ChnDef:LangDef{
public:
    const set_kanxi(string k);
private:
    string kanxi;
};

class KorDef:LangDef{
private:
    string locLang[5];
};

#endif