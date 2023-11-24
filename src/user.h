#ifndef USER_H
#define USER_H
#include <vector>
#include <string>
#include <iostream>
#include "record.h"
using namespace std;
class User{
public:
    User(string s):rec_file(s){rec.load_rec(s);}
    User():rec_file(""){}

    void insert_rec(const vector<Prob>& new_rec, Language lang) {rec.insertRec(new_rec, lang);}
    QuizHistory& getRec(){return rec;}
    QuizHistory rec;
private:
    string rec_file;
};

#endif