#include "record.h"
#include <algorithm>
#include <fstream>


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
void QuizHistory::load_rec(const string& s){
    ifstream ins;
    ins.open(s);
    if(ins.fail())
        return;
    Rec_probs k;
    while(ins>>k){
        records.push_back(k);
        if(k.getScore()>highest_score)scores.insert(k.getScore());
        score_sum+=k.getScore();
        sz++;
    }

}

void QuizHistory::store_rec(const string& s){
    ofstream outs;
    outs.open(s);
    if(outs.fail())
        return;
    for(Rec_probs x : records){
        outs<<x;
    }
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
    return ins;
}
ostream& operator << (ostream& outs, Rec_probs& rec)
{
    outs<<rec.sz<<' '<<rec.date.month<<' '<<rec.date.day<<' '<<rec.score<<' ';
    Prob tmp;
    for(int i=0; i<rec.sz; i++){
        outs<<tmp.prob<<' '<<tmp.ans<<' '<<tmp.if_right<<'\n';
        rec.problems.push_back(tmp);
    }
    return outs;
}

void QuizHistory::insertRec(const Rec_probs& pbs)
{
    records.push_back(pbs);
    if(pbs.getScore() > highest_score)highest_score = pbs.getScore();
    sz++;
    score_sum += pbs.getScore();
    scores.insert(pbs.getScore());
}

void QuizHistory::printRec(int n = 1)
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
