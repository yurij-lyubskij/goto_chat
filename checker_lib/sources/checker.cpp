#include "checker.h"


Checker::Checker() {
    std::cout << "Hello";
}

Checker::~Checker() {

}

bool Checker::check_name(const std::string &name) {
    bool f1 = true;
    for (const auto &it: name) {
        if ((it >= 'A' && it <= 'z')) {
            continue;
        } else {
            f1 = false;
            break;
        }
    }
    bool f2 = true;
    std::string abc = "йцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";
    for (const auto &it: name) {
        if (std::find(abc.begin(), abc.end(), it) == abc.end()) {
            f2 = false;
            break;
        }
    }
    return (f1 || f2);
}

bool Checker::check_password(const std::string &pass) {
    for (const auto &it: pass) {
        if (it == ' ') {
            return false;
        }
    }
    return true;
}


bool Checker::check_email(const std::string &email) {
    auto mail = email;
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(mail, pattern);
}

bool Checker::check_login(const std::string &login) {
    for (const auto &it: login) {
        if ((it >= '0' && it <= '9') || (it >= 'A' && it <= 'z') || (it == '_')) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}
