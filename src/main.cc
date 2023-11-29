#include "quiz.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    Dict<EngDef> dict_eng("./dict_store_eng.txt");

    Dict<JpnDef> dict_jpn("./dict_store_jpn.txt");
    Dict<ChnDef> dict_chn("./dict_store_chn.txt");
    //user_init();
    User users("./user_store_eng.txt"); // Multiple users to be implemented

    openai::start(); // Will use the api key provided by `OPENAI_API_KEY` environment variable

    bool if_run = true;
    while(if_run) {
        int mode;
        int lang_int = -1;
        int action;
        int rec_num, rec_prob;
        cout << "Press 1: search Record, 2: quiz mode, else: quit" << endl;
        cin >> mode;
        while(lang_int > 3 || lang_int < 1) {
            cout << "1: English, 2: Japanese, 3: Chinese" << endl;
            cin >> lang_int;
        }
        int sz=-1, pos=-1;
        QuizHistory& history = users.rec;
        switch(mode) {
        case 1: // RECORD mode
            if(history.getSize()==0){
                cout<< "No record\n";
                break;
            }
            cout<<"Average score: "<<static_cast<float>(history.getScore())/history.getSize()<<'\n';
            cout<<"Highest score: "<<history.getMaxScore()<<'\n';
            cout<<"Threre are total "<<history.getSize()<<
                " records.\nSelect starting position and size to print.\n";
            while(sz <= 0 || pos<0 || pos>history.getSize()){
                cout<<"number of record to print: ";
                cin>>sz;
                cout<<"from recent(starting from 0): ";
                cin>>pos;
            }
            history.printRec(sz);
            action=-1;
            while(action <0 || action >2){
                cout<<"\nSelect Action\n\t1: Delete record\n\t2: Show Detail\nuser: "; 
                cin>>action;
            }
            
            switch(action){
            case 1:
                cout<<"Select record number to delete: ";
                cin>>rec_num;
                if(rec_num >= history.getSize()){
                    cout<<"Bad input. Type record num 0 ~ "<<history.getSize()<<'\n';
                    break;
                }
                switch(history.getLanguage(rec_num)) {
                case ENGLISH:
                    history.delete_rec(rec_num, dict_eng);
                    break;
                case JAPANESE:
                    history.delete_rec(rec_num, dict_jpn);
                    break;
                case CHINESE:
                    history.delete_rec(rec_num, dict_chn);
                    break;
                default:
                    break;
                }
                break;
            case 2:
                cout<<"Select record number to show detail: ";
                cin>>rec_num;
                cout<<"Select question number to show detail: ";
                cin>>rec_prob;
                if(rec_num >= history.getSize()){
                    cout<<"Bad input. Type record num 0 ~ "<<history.getSize()<<'\n';
                    break;
                }
                switch(history.getLanguage(rec_num)) {
                case ENGLISH:
                    history.show_detail(rec_num, rec_prob, dict_eng);
                    break;
                case JAPANESE:
                    history.show_detail(rec_num, rec_prob, dict_jpn);
                    break;
                case CHINESE:
                    history.show_detail(rec_num, rec_prob, dict_chn);
                    break;
                default:
                    break;
                }
                break;
            }
            break;

        case 2: // QUIZ mode
            switch(lang_int) {
            case ENGLISH: {
                Quiz<EngDef> quiz;
                quiz.question(dict_eng);
                users.insert_rec(Rec_probs(quiz.getRecords(), ENGLISH));
            }
            break;
            case JAPANESE: {
                Quiz<JpnDef> quiz;
                quiz.question(dict_jpn);
                users.insert_rec(Rec_probs(quiz.getRecords(), JAPANESE));
            }
            break;
            case CHINESE: {
                Quiz<ChnDef> quiz;
                quiz.question(dict_chn);
                users.insert_rec(Rec_probs(quiz.getRecords(), CHINESE));
            }
            break;
            }
            break;
        default:
            if_run = false;
        }
        if(!if_run)
            break;
    }
    // Move these to Deconstructor
    dict_eng.storeDict();
    dict_jpn.storeDict();
    dict_chn.storeDict();
    users.store_rec();
}