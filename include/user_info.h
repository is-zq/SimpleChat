#ifndef _USER_INFO_
#define _USER_INFO_
#include <string>

class UserInfo
{
private:
    string ID;
    string password;
    string name;

public:
    UserInfo(string ID,string password,string name);
    string GetID();
    string GetName();
    bool ModifyPassword(string password);
    bool ModifyName(string name);
};

#endif
