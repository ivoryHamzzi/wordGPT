#include "record.h"
#include <algorithm>
#include <fstream>

Prob::showDetail(const Dict& dict)
{
    dict.printDict(word_id);
}

Rec_probs::Rec_probs(vector<Prob>probs)
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
void QuizHistory::insertRec(const vector<Prob>& pbs)
{
    Rec_probs newRec = Rec_probs(pbs);
    records.push_back(newRec);
    if(newRec.getScore() > highest_score)highest_score = newRec.getScore();
    sz++;
    score_sum += newRec.getScore();
    scores.insert(newRec.getScore());
}

void QuizHistory::printRec(int n = 1, int from = 0)
{
    auto cur = records.size() - 1 - from;
    for(; cur >= 0 && n > 0; n--, cur--) {
        const Rec_probs& cur_rec = records[cur];
        cout << cur_rec.getMonth() << '/' << cur_rec.getDay() << ":\n";
        for(int i = 0; i < cur_rec.getSize(); i++) {
            cout << i + 1 << ". " << endl;
            cout << "Prob: " << cur_rec[i].prob << endl;
            cout << "Ans: " << cur_rec[i].ans << endl;
            cout << (cur_rec[i].if_right ? "Right!" : "Wrong...") << endl;
        }
        cout << cur_rec.getScore() << '\n';
        cout << endl;
    }
}