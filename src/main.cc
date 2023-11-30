#include "quiz.h"

#include <iostream>
#include <filesystem>

using namespace std;

enum OperMode {
    SIGNIN = 0,
    QUIZ,
    HISTORY,
    SIGNOUT,
    DICT,
    QUIT,
};


pair<int, int> getOpCode(int user_id)
{
    pair<int, int> ret(QUIT, 0);
    if(user_id > -1) {
        cout << "Input the number..." << endl;
        cout << "1: For some quiz" << endl;
        cout << "2: For history serach" << endl;
        cout << "3: Sign out" << endl;
        cout << "4: Dictionary" << endl;
        cout << "Else: quit the Program" << endl;
        if(!(cin >> ret.first)) {
            ret.first = QUIT;
            return ret;
        }
        switch(ret.first) {
        case QUIZ:
            cout << "Input the number..." << endl;
            cout << "1: English, 2: Japanese, 3: Chinese" << endl;
            while(cin >> ret.second) {
                if(ret.second >= 1 && ret.second <= 3)
                    break;
                cin.ignore();
            }
            break;
        case HISTORY:
            cout<< "Select Action..." << endl;
            cout << "1: Show Quiz History" << endl;
            cout << "2: Info of a single word of a history" << endl;
            cout << "3: Delete record" << endl;
            while(cin >> ret.second) {
                if(ret.second >= 1 && ret.second <= 3)
                    break;
                cin.ignore();
            }
            break;
        case SIGNOUT:
            break;
        case DICT:
            cout << "1: English, 2: Japanese, 3: Chinese" << endl;
            while(cin >> ret.second) {
                if(ret.second >= 1 && ret.second <= 3)
                    break;
                cin.ignore();
            }            
            break;
        default:
            ret.first = QUIT;
            return ret;
        }
    } else {
        ret.first = SIGNIN;
        cout << "Sign in your ID(Integer), type 0 for dictionary, or else for quit:" << endl;
        if(!(cin >> ret.second)) {
            ret.first = QUIT;
            return ret;
        }
        if(ret.second == -1)
            ret.first = QUIT;
        else if(ret.second == 0) {
            ret.first = DICT;
            cout << "1: English, 2: Japanese, 3: Chinese" << endl;
            while(cin >> ret.second) {
                if(ret.second >= 1 && ret.second <= 3)
                    break;
                cin.ignore();
            }            
        }
    }
    return ret;
}

int main(int argc, char* argv[])
{
    filesystem::path p("./dict");
    if (!filesystem::is_directory( p ))
        filesystem::create_directories( p );
    p = filesystem::path("./usr");
    if (!filesystem::is_directory( p ))
        filesystem::create_directories( p );

    Dict<EngDef> dict_eng("./dict/dict_store_eng.txt");
    Dict<JpnDef> dict_jpn("./dict/dict_store_jpn.txt");
    Dict<ChnDef> dict_chn("./dict/dict_store_chn.txt");
    //user_init();

    openai::start(); // Will use the api key provided by `OPENAI_API_KEY` environment variable

    bool if_run = true;
    int user_id = -1;
    User* user_ptr = nullptr;
    while(if_run) {
        User& user = *user_ptr;
        pair<int, int> opcode = getOpCode(user_id);
        switch(opcode.first) {
        case QUIT:
            if_run = false;
        case QUIZ:
            switch(opcode.second) {
            case ENGLISH: {
                Quiz<EngDef> quiz;
                quiz.question(dict_eng);
                user.insert_rec(Rec_probs(quiz.getRecords(), ENGLISH));
                }
                break;
            case JAPANESE: {
                Quiz<JpnDef> quiz;
                quiz.question(dict_jpn);
                user.insert_rec(Rec_probs(quiz.getRecords(), JAPANESE));
                }
                break;
            case CHINESE: {
                Quiz<ChnDef> quiz;
                quiz.question(dict_chn);
                user.insert_rec(Rec_probs(quiz.getRecords(), CHINESE));
                }
                break; 
            }
            break;
        case HISTORY: {
            if(user.rec.getSize()==0){
                cout<< "No record\n";
                break;
            }
            cout<<"Average score: "<<static_cast<float>(user.rec.getScore())/user.rec.getSize()<<'\n';
            cout<<"Highest score: "<<user.rec.getMaxScore()<<'\n';
            cout<<"Threre are total "<<user.rec.getSize()<< " records." << endl;

            int sz = 0;
            int rec_num, prob_num;
            switch(opcode.second) {
            case 1:
                while(sz <= 0){
                    cout << "Number of recent records to print: ";
                    cin >> sz;
                }
                user.rec.printRec(sz);
                break;
            case 2:
                cout<<"Select record number to show detail(1 ~ " << user.rec.getSize() << "): ";
                cin>>rec_num;
                if(rec_num > user.rec.getSize() || rec_num <= 0){
                    cout<<"Bad input. Type record num 1 ~ "<<user.rec.getSize()<<'\n';
                    break;
                }
                cout<<"Select problem number to show detail(1 ~ " << PROB_NUM << "): ";
                cin >> prob_num;
                if(prob_num > PROB_NUM || prob_num <= 0){
                    cout << "Bad input. Type record num 1 ~ " << PROB_NUM << '\n';
                    break;
                }
                switch(user.rec.getLanguage(rec_num)) {
                case ENGLISH:
                    user.rec.show_detail(rec_num, prob_num, dict_eng);
                    break;
                case JAPANESE:
                    user.rec.show_detail(rec_num, prob_num, dict_jpn);
                    break;
                case CHINESE:
                    user.rec.show_detail(rec_num, prob_num, dict_chn);
                    break;
                default:
                    break;
                }
                break;                
            case 3:
                cout<<"Select record number to delete: ";
                cin>>rec_num;
                if(rec_num > user.rec.getSize() || rec_num <= 0){
                    cout<<"Bad input. Type record num 0 ~ "<<user.rec.getSize()<<'\n';
                    break;
                }
                switch(user.rec.getLanguage(rec_num)) {
                case ENGLISH:
                    user.rec.delete_rec(rec_num, dict_eng);
                    break;
                case JAPANESE:
                    user.rec.delete_rec(rec_num, dict_jpn);
                    break;
                case CHINESE:
                    user.rec.delete_rec(rec_num, dict_chn);
                    break;
                default:
                    break;
                }
                break;  
            }
            }
            break;
        case SIGNOUT:
            user_id = -1;
            delete(user_ptr);
            user_ptr = nullptr;
            break;
        case SIGNIN:
            user_id = opcode.second;
            user_ptr = new User("./usr/user_" + to_string(user_id) + ".txt");
            break;
        case DICT:
            cout << "Type your word: ";
            string word;
            cin >> word;
            switch(opcode.second) {
            case ENGLISH:
                dict_eng.printDict(word);
                break;
            case JAPANESE:
                dict_jpn.printDict(word);
                break;
            case CHINESE:
                dict_chn.printDict(word);
                break;
            }
        }
    }
    if(user_id != -1)
        delete(user_ptr);
}
