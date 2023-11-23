#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

struct Prob{
    string prob;
    string ans;
    bool if_right;
};

class Rec_probs{
public:
    Rec_probs():sz(0), score(0){}
    Rec_probs(vector<Prob>probs);
    int getScore() const {return score;}
    int getSize() const {return sz;}
    int getMonth() const {return date.month;}
    int getDay() const {return date.day;}
    int getScore() const {return score;}

    int setMonth(const int& m) {date.month = (m >= 1 && m <= 12) ? m : 0;}
    int setDay(const int& d) {date.day = (d >= 1 && d <= 31) ? d : 0;}
    int setScore(const int& s) {score = s;}

    Prob operator[] (int n) const;
    friend istream& operator >> (istream& ins, Rec_probs& rec);
    friend ostream& operator << (ostream& outs, Rec_probs& rec);
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
    QuizHistory():score(0),sz(0), highest_score(0) {records = vector<Rec_probs>(0);}
    void insertRec(const vector<Prob>& pbs);
    void printRec(int n, int from);

    void load_rec(string s);
    long getScore() const {return score;}
    int getSize() const {return sz;}
    int getMaxScore() const {return highest_score;}

private:
    vector<Rec_probs> records;
    long score;
    int sz;
    int highest_score;
};
