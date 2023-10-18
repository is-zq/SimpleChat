#ifndef _USER_INFO_
#define _USER_INFO_

class UserInfo
{
private:
    std::string ID;
    std::string password;
    std::string name;

public:
    UserInfo(std::string ID,std::string password,std::string name);
    std::string GetID();
    std::string GetName();
    bool ModifyPassword(std::string password);
    bool ModifyName(std::string name);
};

#endif
