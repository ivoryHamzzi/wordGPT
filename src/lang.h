#ifndef LANG_H
#define LANG_H
#include <string>

using namespace std;

class LangDef {
public:
    LangDef(const string& w, const string& d):word(w),def(d){};
    LangDef(const string& w):word(w),def(""){};
    LangDef():word(""),def(""){};

    const string& getWord();
    void setWord(const string& w);

    const string& get_def();
    void set_def(const string& d);

    virtual void printWordDetail();

protected:
    string word;
    string def;    
};

class EngDef: public LangDef{
public:
    EngDef(const string& w, const string& d, const string& p) : pron(p), LangDef(w, d) {};

    const string& getPronunc();
    void setPronunc(const string& p);

    void printWordDetail();

private:
    string pron;
};

class JpnDef: public LangDef {
public:
    JpnDef(const string& w, const string& d, const string& p) : pron(p), LangDef(w, d) {};

    const string& getPronunc();
    void setPronunc(const string& p);

    void setKanxi(string k);
    const string& getKanxi();

    void printWordDetail();

private:
    string kanxi;
    string pron;
};

class ChnDef: public LangDef {
public:
    ChnDef(const string& w, const string& d, const string& k, string& en)
        : kanxi(k), eng_rep(en), LangDef(w, d) {};

    void setKanxi(string k);
    const string& getKanxi();

    void setEngRep(string e);
    const string& getEngRep();

    void printWordDetail();

private:
    string kanxi;
    string eng_rep;
};

class KorDef: public LangDef{
public:
    KorDef(const string& w, const string& d, const string& p, string& h)
        : pron(p), hanja_rep(h), LangDef(w, d) {};    

    const string& getPronunc();
    void setPronunc(const string& p);

    const string& getHanja();
    void setHanja(const string& h);

    void printWordDetail();

private:
    string pron;
    string hanja_rep;
};

#endif