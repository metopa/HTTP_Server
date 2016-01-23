//
// Created by metopa on 28.4.15.
//

#ifndef HTTP_SERVER_GLOBALS2_H
#define HTTP_SERVER_GLOBALS2_H

#include <map>
#include <vector>
#include <string>


using namespace std;

extern const char * MSG_CRIT_ERR;
extern const char * DEFAULT_INIFILE;
extern const char * DEFAULT_LOGFILE;
extern const char * http_endl;

typedef map<string, map<string, vector<string>>> ini_struct_t;

#endif //HTTP_SERVER_GLOBALS2_H
