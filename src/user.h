#ifndef USER_H
#define USER_H
#include <vector>
#include <string>
#include <iostream>
#include "record.h"
using namespace std;
class User{
public:
    User(string s):rec_file(s), rec_size(0){}
    User():rec_file(""),rec_size(0){}

    void load_rec();
    void insert_rec(const vector<Prob>& new_rec) {rec.insertRec(new_rec);}
private:
    QuizHistory rec;
    string rec_file;
};

#endif