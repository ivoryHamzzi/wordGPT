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

    void insert_rec(const vector<Prob>& new_rec) {rec.insertRec(new_rec);}
    QuizHistory& getRec(){return rec;}
private:
    QuizHistory rec;
    string rec_file;
};

#endif