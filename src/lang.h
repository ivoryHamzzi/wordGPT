#ifndef LANG_H
#define LANG_H
#include <string>
#include "nlohmann/json.hpp"
#include "openai.hpp"
#include <fstream>
using namespace std;

class LangDef {
public:
    LangDef(const string& w, const string& d):word(w),def(d){}
    LangDef(const string& w):word(w),def(""){}
    LangDef():word(""),def(""){}

    const string& getWord();
    void setWord(const string& w);

    const string& get_def();
    
    void set_def(const string& d);
    
    virtual void printWordDetail() const;
    
protected:
    string word;
    string def; 
};

class EngDef: public LangDef{
public:
    EngDef(const string& w, const string& d, const string& p) : LangDef(w, d), pron(p) {}
    EngDef() : LangDef(), pron() {}

    const string& getPronunc();
    void setPronunc(const string& p);

    friend ostream& operator << (ostream& outs, const EngDef& l);
    friend istream& operator >> (istream& ins, EngDef& l);
    void printWordDetail() const;
private:
    string pron;
};

class JpnDef: public LangDef {
public:
    JpnDef(const string& w, const string& d, const string& p, const string& k) : LangDef(w, d), kanxi(k), pron(p) {}
    JpnDef() : LangDef(), kanxi(), pron() {}

    const string& getPronunc();
    void setPronunc(const string& p);

    void setKanxi(string k);
    const string& getKanxi();

    friend ostream& operator << (ostream& outs, const JpnDef& l);
    friend istream& operator >> (istream& ins, JpnDef& l);
    void printWordDetail() const;
private:
    string kanxi;
    string pron;
};

class ChnDef: public LangDef {
public:
    ChnDef(const string& w, const string& d, const string& k, string& en)
        : LangDef(w, d), kanxi(k), eng_rep(en) {}
    ChnDef() : LangDef(), kanxi(), eng_rep() {}

    void setKanxi(string k);
    const string& getKanxi();

    void setEngRep(string e);
    const string& getEngRep();

    void printWordDetail() const;

    friend ostream& operator << (ostream& outs, const ChnDef& l);
    friend istream& operator >> (istream& ins, ChnDef& l);

private:
    string kanxi;
    string eng_rep;
};

class KorDef: public LangDef{
public:
    KorDef(const string& w, const string& d, const string& p, string& h)
        : LangDef(w, d), pron(p), hanja_rep(h) {}  
    KorDef() : LangDef(), pron(), hanja_rep() {}

    const string& getPronunc();
    void setPronunc(const string& p);

    const string& getHanja();
    void setHanja(const string& h);

    friend ostream& operator << (ostream& outs, const KorDef& l);
    friend istream& operator >> (istream& ins, KorDef& l);
    void printWordDetail() const;

private:
    string pron;
    string hanja_rep;
};

#endif