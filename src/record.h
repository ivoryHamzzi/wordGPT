#ifndef REC_H
#define REC_H
#include <list>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <set>
#include "dict.h"

using namespace std;

struct Prob{
    string prob;
    string ans;
    bool if_right;

    template<class T>
    void showDetail(const Dict<T>& dict);
    template<class T>
    void deleteProb(Dict<T>& dict);
};

class Rec_probs{
public:
    Rec_probs():sz(0), date({0, 0}), score(0), problems(0) {}
    Rec_probs(const vector<Prob>& probs, Language lang);
    int getScore() const {return score;}
    int getSize() const {return sz;}
    int getMonth() const {return date.month;}
    int getDay() const {return date.day;}
    //int getScore() const {return score;}

    void setMonth(const int& m) {date.month = (m >= 1 && m <= 12) ? m : 0;}
    void setDay(const int& d) {date.day = (d >= 1 && d <= 31) ? d : 0;}
    void setScore(const int& s) {score = s;}

    template<class T>
    void deleteProbs(Dict<T> &dict);
    template<class T>
    void showDetail(Dict<T> &dict, int probN);

    Prob operator[] (int n) const;
    friend istream& operator >> (istream& ins, Rec_probs& rec);
    friend ostream& operator << (ostream& outs, Rec_probs& rec);
    Language l;
protected:
    int sz;
    struct {
        int month;
        int day;
    } date;
    int score;
    vector<Prob> problems;

};

class QuizHistory{
public:
    QuizHistory():score_sum(0),sz(0) {
        records = list<Rec_probs>(0);
        scores.clear();
    }
    void insertRec(const Rec_probs& pbs);
    void printRec(int n);

    Language getLanguage(int recN);
    template <class T>
    void delete_rec(int recN, Dict<T> &dict);
    template <class T>
    void show_detail(int recN, int index, Dict<T> &dict);


    void load_rec(const string& s);
    void store_rec(const string& s);
    long getScore() const {return score_sum;}
    int getSize() const {return sz;}
    int getMaxScore() const
    {
        if(scores.empty())
            return 0;
        return *scores.rbegin();
    }

private:
    list<Rec_probs> records;
    long score_sum;
    multiset<int> scores;
    int sz;
};


template <class T>
void Prob::showDetail(const Dict<T>& dict)
{
    dict.printDict(prob);
}

template<class T>
void Prob::deleteProb(Dict<T>& dict)
{
    dict.deleteDict(prob);
}

template<class T>
void Rec_probs::deleteProbs(Dict<T> &dict){
    for(int i=0; i<sz; i++)
        problems[i].deleteProb(dict);
}
template<class T>
void Rec_probs::showDetail(Dict<T> &dict, int index){
    problems[index - 1].showDetail(dict);
}

template<class T>
void QuizHistory::delete_rec(int recN, Dict<T> &dict)
{
    recN--;
    auto cur = records.begin();
    for(int i=0; i<recN; i++)
        cur++;
    Rec_probs& curRec = *cur;
    int score2 = curRec.getScore();
    scores.erase(score2);
    sz --;
    score_sum -= score2;

    curRec.deleteProbs(dict);
    records.erase(cur);

}

template<class T>
void QuizHistory::show_detail(int rec_num, int index, Dict<T> &dict){
    auto cur = records.begin();
    for(int i=1; i<rec_num; i++)
        cur++;
    Rec_probs& cur_rec = *cur;
    cur_rec.showDetail(dict, index);
}

#endif