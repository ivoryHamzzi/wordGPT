#include "record.h"
#include <algorithm>
#include <fstream>

template <class T>
void Prob::showDetail(const Dict<T>& dict)
{
    dict.printDict(word_id);
}

template<class T>
void Prob::deleteProb(const Dict<T>& dict)
{
    auto iter = dict.wordMap.find(word_id);
    dict.wordMap.erase(iter);
    dict.unused_id.push(word_id);
}

Rec_probs::Rec_probs(const vector<Prob>&probs,Language lang):l(lang)
{
    time_t t = time(NULL);
    setDay(localtime(&t)->tm_mday);
    setMonth(localtime(&t)->tm_mon + 1);
    problems = vector<Prob>(probs.begin(), probs.end());
    for(auto& p: probs)
        score += p.if_right ? 1 : 0;
    sz = problems.size();
}

Prob Rec_probs::operator[] (int n) const
{
    if(n < 0 || n >= sz) 
        exit(1);

    return problems[n];
}
/*
int sz;
struct {
    int month;
    int day;
} date;
int score;
vector<Prob> problems;
*/
istream& operator >> (istream& ins, Rec_probs& rec)
{
    ins>>rec.sz>>rec.date.month>>rec.date.day>>rec.score;
    rec.problems.reserve(rec.sz);
    Prob tmp;
    for(int i=0; i<rec.sz; i++){
        ins>>tmp.prob>>tmp.ans>>tmp.if_right;
        rec.problems.push_back(tmp);
    }
}
ostream& operator << (ostream& outs, Rec_probs& rec)
{
    outs<<rec.sz<<' '<<rec.date.month<<' '<<rec.date.day<<' '<<rec.score<<' ';
    Prob tmp;
    for(int i=0; i<rec.sz; i++){
        outs<<tmp.prob<<' '<<tmp.ans<<' '<<tmp.if_right<<'\n';
        rec.problems.push_back(tmp);
    }
}

template<class T>
void Rec_probs::deleteProbs(Dict<T> &dict){
    for(int i=0; i<sz; i++)
        problems[i].deleteProb(dict);
}
template<class T>
void Rec_probs::showDetail(Dict<T> &dict, int index){
    problems[index].showDetail(dict);
}

void QuizHistory::load_rec(const string& s){
    ifstream ins;
    ins.open(s);
    Rec_probs k;
    while(ins>>k){
        records.push_back(k);
        if(k.getScore()>highest_score)scores.insert(k.getScore());
        score_sum+=k.getScore();
        sz++;
    }

}
void QuizHistory::insertRec(const vector<Prob>& pbs, Language lang)
{
    Rec_probs newRec = Rec_probs(pbs, lang);
    records.push_back(newRec);
    if(newRec.getScore() > highest_score)highest_score = newRec.getScore();
    sz++;
    score_sum += newRec.getScore();
    scores.insert(newRec.getScore());
}

template<class T>
void QuizHistory::delete_rec(int recN, Dict<T> &dict)
{
    auto cur = records.begin();
    for(int i=0; i<recN; i++)
        cur++;
    Rec_probs curRec = *cur;
    curRec.deleteProbs(dict);
}
void QuizHistory::printRec(int n = 1, int from = 0)
{
    auto cur = records.begin();
    for(int i=0; i<n; i++){
        const Rec_probs& cur_rec = *cur;
        cout << cur_rec.getMonth() << '/' << cur_rec.getDay() << ":\n";
        for(int i = 0; i < cur_rec.getSize(); i++) {
            cout << i + 1 << ". " << endl;
            cout << "Prob: " << cur_rec[i].prob << endl;
            cout << "Ans: " << cur_rec[i].ans << endl;
            cout << (cur_rec[i].if_right ? "Right!" : "Wrong...") << endl;
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

template<class T>
void QuizHistory::show_detail(int recN, int index, Dict<T> &dict){
    auto cur = records.begin();
    for(int i=0; i<recN; i++)
        cur++;
    Rec_probs curRec = *cur;
    curRec.showDetail(dict, index);
}
