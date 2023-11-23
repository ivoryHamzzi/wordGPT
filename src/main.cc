#include "user.h"
#include "dict.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    Dict<Eng> dict_eng;
    Dict<Jpn> dict_jpn;
    Dict<Chn> dict_chn;

    Users users;

    bool if_run = true;
    while(if_run) {
        int mode;
        int lang_int = -1;
        int mode_2 = -1;
        cout << "Press 1: dict mode, 2: quiz mode, else: quit" << endl;
        cin >> mode;
        switch(mode) {
        case 1: // DICT mode
            while(lang_int > 3 || lang_int < 1) {
                cout << "1: English, 2: Japanese, 3: Chinese" << endl;
                cin >> lang_int;
            }
            while(mode_2 < 0 || mode_2 > 1) {
                cout << "From Korean(0), or to Korean(1)?" << endl;
                cin >> mode_2;
            }
            switch(static_cast<Language>(lang_int)) {
            case ENGLISH:
                dict_eng.search_mode(mode_2);
                break;
            case JAPANESE:
                dict_jpn.search_mode(mode_2);
                break;
            case CHINESE:
                dict_chn.search_mode(mode_2);
                break;
            }
            break;
        case 2: // QUIZ mode
            while(lang_int > 3 || lang_int < 1) {
                cout << "1: English, 2: Japanese, 3: Chinese" << endl;
                cin >> lang_int;
            }
            break;
        default:
            if_run = false;
        }
        if(!if_run)
            break;

    }
}