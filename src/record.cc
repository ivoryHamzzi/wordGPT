#include "record.h"
#include <algorithm>
#include <fstream>


Rec_probs::Rec_probs(const vector<Prob>&probs,Language lang):l(lang)
{
    time_t t = time(NULL);
    setDay(localtime(&t)->tm_mday);
    setMonth(localtime(&t)->tm_mon + 1);
    problems = vector<Prob>(probs.begin(), probs.end());
    score = 0;
    for(auto& p: probs)
        score += p.if_right ? 1 : 0;
    sz = problems.size();
}

/* Load history from the given file */
void QuizHistory::load_rec(const string& s){
    ifstream ins;
    ins.open(s);
    if(ins.fail())
        return;
    Rec_probs k;
    while(ins>>k){
        //if(ins.eof())break;
        records.push_back(k);
        scores.insert(k.getScore());
        score_sum+=k.getScore();
        sz++;
        if(ins.eof())
            break;
    }

}

void QuizHistory::store_rec(const string& s){
    ofstream outs;
    outs.open(s);
    if(outs.fail())
        return;
    for(Rec_probs& x : records){
        outs<<x;
    }
}

Prob Rec_probs::operator[] (int n) const
{
    if(n < 0 || n >= sz) 
        exit(1);

    return problems[n];
}

istream& operator >> (istream& ins, Rec_probs& rec)
{
    string sz, dm, dd, sc, lg;
    if(ins.eof())return ins;
    getline(ins, sz, '#');
    if(ins.eof())return ins;
    getline(ins, dm, '#');
    if(ins.eof())return ins;
    getline(ins, dd, '#');
    if(ins.eof())return ins;
    getline(ins, sc, '#');
    if(ins.eof())return ins;
    getline(ins, lg, '#');
    if(ins.eof())return ins;
    rec.sz = stoi(sz);
    rec.date.month = stoi(dm);
    rec.date.day = stoi(dd);
    rec.score = stoi(sc);
    rec.problems.reserve(rec.sz);
    int l_int = stoi(lg);
    if(l_int == 0)rec.l=ENGLISH;
    if(l_int == 1)rec.l=JAPANESE;
    if(l_int == 2)rec.l=CHINESE;
    Prob tmp;
    for(int i=0; i<rec.sz; i++){
        getline(ins, tmp.prob, '#');
        getline(ins, tmp.ans, '#');
        string b;
        getline(ins, b, '#');
        if(b.compare("t")==0) tmp.if_right = true;
        else tmp.if_right = false;
        string id_str;
        getline(ins, id_str, '#');
        tmp.word_id = stoi(id_str);
        rec.problems.push_back(tmp);
    }
    return ins;
}
ostream& operator << (ostream& outs, Rec_probs& rec)
{
    outs<<rec.sz<<'#'<<rec.date.month<<'#'<<rec.date.day<<'#'<<rec.score<<'#';
    if(rec.l == ENGLISH)outs<<0<<'#';
    if(rec.l == JAPANESE)outs<<1<<'#';
    if(rec.l == CHINESE)outs<<2<<'#';
    Prob tmp;
    for(int i=0; i<rec.sz; i++){
        tmp = rec.problems[i];
        outs<<tmp.prob<<'#'<<tmp.ans<<'#';
        if(tmp.if_right)outs<<'t'<<'#';
        else outs<<'f'<<'#';
        outs<<tmp.word_id<<'#';
    }
    return outs;
}

void QuizHistory::insertRec(const Rec_probs& pbs)
{
    records.push_back(pbs);
    sz++;
    score_sum += pbs.getScore();
    scores.insert(pbs.getScore());
}

void QuizHistory::printRec(int n = 1)
{
    auto cur = records.begin();
    for(int i=0; i<n; i++){
        const Rec_probs& cur_rec = *cur;
        cout << "Record#: " << i + 1 << '\n';
        cout << cur_rec.getMonth() << '/' << cur_rec.getDay() << ":\n";
        for(int i = 0; i < cur_rec.getSize(); i++) {
            cout << '\t' << i + 1 << ". " << endl;
            cout << '\t' << "Prob: " << cur_rec[i].prob << endl;
            cout << '\t' << "Ans: " << cur_rec[i].ans << endl;
            cout << '\t' << (cur_rec[i].if_right ? "Right!" : "Wrong...") << endl;
        }
        cout << cur_rec.getScore() << '\n';
        cout << endl;
        cur++;
    }
}

Language QuizHistory::getLanguage(int recN){
    auto cur = records.begin();
    for(int i=0; i<recN; i++)
        cur++;
    Rec_probs curRec = *cur;
    Language l = curRec.l;
    return l;
}
