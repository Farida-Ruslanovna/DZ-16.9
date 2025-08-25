#pragma once

#include "sha1.h"
#include <vector>
#include <algorithm>
#include <cstring>

#define LOGINLENGTH 10

// Класс для управления регистрацией и авторизацией
class Chat {
public:
    Chat();

    // Регистрация пользователя
    void reg(const char _login[LOGINLENGTH], const char _pass[], int pass_length);

    // Авторизация пользователя
    bool login(const char _login[LOGINLENGTH], const char _pass[], int pass_length);

private:
    struct AuthData {
        char login[LOGINLENGTH];
        uint* pass_sha1_hash;

        AuthData() : pass_sha1_hash(nullptr) {
            memset(login, 0, sizeof(login));
        }

        AuthData(const char _login[LOGINLENGTH], uint* sha1_hash) : pass_sha1_hash(nullptr) {
            strncpy(login, _login, LOGINLENGTH);
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
            memcpy(pass_sha1_hash, sha1_hash, SHA1HASHLENGTHBYTES);
        }

        ~AuthData() {
            delete[] pass_sha1_hash;
        }

        // Конструктор копии
        AuthData(const AuthData& other) : pass_sha1_hash(nullptr) {
            strncpy(login, other.login, LOGINLENGTH);
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
            memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);
        }

        // Оператор присваивания
        AuthData& operator=(const AuthData& other) {
            if (this != &other) {
                strncpy(login, other.login, LOGINLENGTH);
                delete[] pass_sha1_hash;
                pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
                memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);
            }
            return *this;
        }
    };

    std::vector<AuthData> data;
};