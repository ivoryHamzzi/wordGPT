#include "user.h"
#include "dict.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    Dict<EngDef> dict_eng("./dict_store_eng.txt");
    Dict<ChnDef> dict_jpn("./dict_store_jpn.txt");
    Dict<ChnDef> dict_chn("./dict_store_jpn.txt");
    //user_init();
    User users;

    bool if_run = true;
    while(if_run) {
        int mode;
        int lang_int = -1;
        int mode_2 = -1;
        cout << "Press 1: search Record, 2: quiz mode, else: quit" << endl;
        cin >> mode;
        while(lang_int > 3 || lang_int < 1) {
            cout << "1: English, 2: Japanese, 3: Chinese" << endl;
            cin >> lang_int;
        }
        QuizHistory history;
        switch(mode) {
        case 1: // RECORD mode
            int sz=-1, pos=-1;
            history = users.getRec();
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
            history.printRec(sz, pos);
            int action=-1;
            while(action <0 || action >2){
                cout<<"\nSelect Action\n\t1: Delete record\n\t2: Show Detail\nuser: "; 
                cin>>action;
            }
            if(action)
            switch(action){
                case 1:
                    cout<<"Select record number to delete: ";
                    cin>>action;
                    //history.delete(action);
                    break;
                case 2:
                    cout<<"Select record number to show detail: ";
                    int rec_num, rec_prob;
                    cin>>rec_num>>rec_prob;
                    //history.show_detail(rec_num, rec_prob);
                    break;
            }

        case 2: // QUIZ mode
            while(mode_2 < 0 || mode_2 > 1) {
                cout << "From Korean(0), or to Korean(1)?" << endl;
                cin >> mode_2;
            }
            break;
        default:
            if_run = false;
        }
        if(!if_run)
            break;

    }
    dict_eng.storeDict();
    dict_jpn.storeDict();
    dict_chn.storeDict();
}