#define _CRT_SECURE_NO_WARNINGS
#include "chat.h"
#include <cstring>

Chat::Chat() {
    
}

// Регистрация
void Chat::reg(const char _login[LOGINLENGTH], const char _pass[], int pass_length) {
    // Проверка наличия логина
    auto it = std::find_if(data.begin(), data.end(), [&](const AuthData& d) {
        return strncmp(d.login, _login, LOGINLENGTH) == 0;
        });
    if (it != data.end()) {
        // Пользователь уже существует
        return;
    }

    // Вычисляем SHA-1 пароля
    uint* hash = sha1(_pass, pass_length);
    // Создаем нового пользователя
    data.emplace_back(_login, hash);
    delete[] hash; // освобождаем временный хеш
}

// Вход
bool Chat::login(const char _login[LOGINLENGTH], const char _pass[], int pass_length) {
    for (auto& user : data) {
        if (strncmp(user.login, _login, LOGINLENGTH) == 0) {
            // Вычисляем SHA-1 введенного пароля
            uint* hash = sha1(_pass, pass_length);
            // Сравниваем с сохраненным
            bool match = true;
            for (int i = 0; i < SHA1HASHLENGTHUINTS; i++) {
                if (hash[i] != user.pass_sha1_hash[i]) {
                    match = false;
                    break;
                }
            }
            delete[] hash;
            return match;
        }
    }
    return false;
}