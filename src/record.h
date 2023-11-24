#include <list>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <set>
#include "dict.h"

using namespace std;

struct Prob{
    uint32_t mapID;
    string prob;
    string ans;
    bool if_right;
    int word_id;

    template<class T>
    void showDetail(const Dict<T>& dict);
    template<class T>
    void deleteProb(const Dict<T>& dict);
};

class Rec_probs{
public:
    Rec_probs():sz(0), score(0){}
    Rec_probs(vector<Prob>probs, Language lang);
    int getScore() const {return score;}
    int getSize() const {return sz;}
    int getMonth() const {return date.month;}
    int getDay() const {return date.day;}
    int getScore() const {return score;}

    int setMonth(const int& m) {date.month = (m >= 1 && m <= 12) ? m : 0;}
    int setDay(const int& d) {date.day = (d >= 1 && d <= 31) ? d : 0;}
    int setScore(const int& s) {score = s;}

    template<class T>
    void deleteProbs(Dict<T> &dict);
    template<class T>
    void showDetail(Dict<T> &dict, int probN);
    
    Prob operator[] (int n) const;
    friend istream& operator >> (istream& ins, Rec_probs& rec);
    friend ostream& operator << (ostream& outs, Rec_probs& rec);
protected:
    Language l;
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
    QuizHistory():score_sum(0),sz(0), highest_score(0) {records = list<Rec_probs>(0);}
    void insertRec(const vector<Prob>& pbs, Language lang);
    void printRec(int n, int from);

    template <class T>
    void deleteRec(int recN, Dict<T> &dict);

    void show_detail(int recN, int probN);

    void load_rec(const string& s);
    long getScore() const {return score_sum;}
    int getSize() const {return sz;}
    int getMaxScore() const {return *(scores.end()--);}

private:
    list<Rec_probs> records;
    long score_sum;
    multiset<int> scores;
    int sz;
    int highest_score;

};
