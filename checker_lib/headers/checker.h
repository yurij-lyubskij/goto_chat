#ifndef CHECHER_H
#define CHECHER_H

#include <iostream>
#include <string>
#include <regex>

class Checker {
public:
    Checker();

    ~Checker();

    static bool check_email(const std::string &str);

    static bool check_login(const std::string &str);

    static bool check_name(const std::string &str);

    static bool check_password(const std::string &str);

    static bool check_phone(const std::string &str);
};

#endif // CHECHER_H
