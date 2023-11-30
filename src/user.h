#ifndef USER_H
#define USER_H
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include "record.h"
using namespace std;
class User{
public:
    User(string s):rec_file(s){rec.load_rec(s);}
    User():rec_file(""){}
    ~User() {cout << "Store" << rec_file << '\n'; store_rec();}

    void insert_rec(const Rec_probs& r) {rec.insertRec(r);}
    void store_rec() {rec.store_rec(rec_file);}
    QuizHistory rec;
private:
    string rec_file;
};

#endif