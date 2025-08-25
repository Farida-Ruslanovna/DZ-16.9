// DZ 16.9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstring>
#include "chat.h"

int main() {

    setlocale(LC_ALL, "Russian");
    Chat chat;

    const char login1[LOGINLENGTH] = "user1";
    const char pass1[] = "password1";

    const char login2[LOGINLENGTH] = "user2";
    const char pass2[] = "password2";

    // Регистрация
    chat.reg(login1, pass1, strlen(pass1));
    chat.reg(login2, pass2, strlen(pass2));

    // Вход успешный
    if (chat.login(login1, pass1, strlen(pass1))) {
        std::cout << "User1 успешно вошел\n";
    }
    else {
        std::cout << "User1 не смог войти\n";
    }

    // Вход с неправильным паролем
    if (chat.login(login2, "wrongpass", strlen("wrongpass"))) {
        std::cout << "User2 успешно вошел\n";
    }
    else {
        std::cout << "User2 не смог войти\n";
    }

    return 0;
}