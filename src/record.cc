#include "record.h"
#include <algorithm>
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


void QuizHistory::insertRec(const vector<Prob>& pbs)
{
    records.push_back(Rec_probs(pbs));
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
        cout << endl;
    }
}