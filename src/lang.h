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
    virtual void load_from_gpt(string str);
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

    void load_from_gpt_from_kor(string str);
    void load_from_gpt_to_kor(string str);
    void printWordDetail();
    static const string& get_prompt_from_kor(){
        return prompt_from_kor;
    }
    static const string& get_prompt_to_kor(){
        return prompt_from_kor;
    }
private:
    string pron;
    static const string prompt_from_kor;//kor ->
    static const string prompt_to_kor;
};

class JpnDef: public LangDef {
public:
    JpnDef(const string& w, const string& d, const string& p) : pron(p), LangDef(w, d) {};

    const string& getPronunc();
    void setPronunc(const string& p);

    void setKanxi(string k);
    const string& getKanxi();

    void load_from_gpt(string str);
    void printWordDetail();
    static const string& get_prompt_from_kor(){
        return prompt_from_kor;
    }
    static const string& get_prompt_to_kor(){
        return prompt_from_kor;
    }
private:
    string kanxi;
    string pron;
    static const string prompt_from_kor;//kor ->
    static const string prompt_to_kor;
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

    static const string& get_prompt_from_kor(){
        return prompt_from_kor;
    }
    static const string& get_prompt_to_kor(){
        return prompt_from_kor;
    }

private:
    string kanxi;
    string eng_rep;
    static const string prompt_from_kor;//kor ->
    static const string prompt_to_kor;
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