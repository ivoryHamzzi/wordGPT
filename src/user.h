#ifndef USER_H
#define USER_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class User{
public:
    User(string s):rec_file(s), rec_size(0){}
    User():rec_file(""),rec_size(0){}

    void load_rec();
    void insert_rec(const Record& new_rec);
private:
    vector<Record> rec;
    int rec_size;
    string rec_file;
};
class Record{
public:
    Record():score(0){}
    Record(int sc):score(sc){}
    void insert_quiz(const string& s1, const string& s2, bool ans){
        quiz.push_back(make_pair(s1, s2));
        is_ans.push_back(ans);
    }
    void print_rec();
private:
    int score;
    vector<pair<const string, const string> > quiz;
    vector<bool> is_ans;
};

void Record::print_rec(){
    cout<<"Score: "<<score<<endl;
    for(int i=0; i<10; i++){
        cout<<i+1<<") q: "<<quiz[i].first<<", a: "<<quiz[i].second<<", ";
        if(is_ans[i])
            cout<<"O"<<endl;
        else 
            cout<<"X"<<endl;
    }
}
#endif