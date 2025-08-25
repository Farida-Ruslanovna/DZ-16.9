#define _CRT_SECURE_NO_WARNINGS
#include "sha1.h"
#include <cstring> 

// Инициализация начальных значений хеша
uint H[5] = {
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
};

uint cycle_shift_left(uint val, int bit_count) {
    return (val << bit_count | val >> (32 - bit_count));
}

uint bring_to_human_view(uint val) {
    return  ((val & 0x000000FF) << 24) |
        ((val & 0x0000FF00) << 8) |
        ((val & 0x00FF0000) >> 8) |
        ((val & 0xFF000000) >> 24);
}
uint* sha1(const char* message, uint msize_bytes) {
    // Инициализация переменных
    uint A = H[0], B = H[1], C = H[2], D = H[3], E = H[4];

    // Расчет общего количества блоков
    uint totalBlockCount = msize_bytes / one_block_size_bytes;

    // Количество дополнительных байт для дополнения сообщения
    uint needAdditionalBytes = one_block_size_bytes - (msize_bytes - totalBlockCount * one_block_size_bytes);

    if (needAdditionalBytes < 8) {
        totalBlockCount += 2; // Еще два блока
        needAdditionalBytes += one_block_size_bytes;
    }
    else {
        totalBlockCount += 1; // Еще один блок
    }

    uint extendedMessageSize = msize_bytes + needAdditionalBytes;

    // Создаем буфер для дополненного сообщения
    unsigned char* newMessage = new unsigned char[extendedMessageSize];
    memcpy(newMessage, message, msize_bytes); // копируем исходное сообщение

    // Добавляем бит '1'
    newMessage[msize_bytes] = 0x80;
    // Остальные байты - нули
    memset(newMessage + msize_bytes + 1, 0, needAdditionalBytes - 1);

    // Записываем длину исходного сообщения в битах в конец блока
    uint* ptr_to_size = (uint*)(newMessage + extendedMessageSize - 4);
    *ptr_to_size = bring_to_human_view(msize_bytes * 8);

    // Расширение блока до 80 слов
    ExpendBlock exp_block;

    for (int i = 0; i < totalBlockCount; i++) {
        unsigned char* cur_p = newMessage + one_block_size_bytes * i;
        // Читаем блок как массив из 16 слов
        Block block = (Block)cur_p;

        // Конвертируем байты в слова, меняя порядок байтов
        for (int j = 0; j < one_block_size_uints; j++) {
            exp_block[j] = bring_to_human_view(
                (block[j * 4] << 24) |
                (block[j * 4 + 1] << 16) |
                (block[j * 4 + 2] << 8) |
                (block[j * 4 + 3])
            );
        }

        // Расширение блока до 80 слов
        for (int j = one_block_size_uints; j < block_expend_size_uints; j++) {
            exp_block[j] = cycle_shift_left(
                exp_block[j - 3] ^ exp_block[j - 8] ^ exp_block[j - 14] ^ exp_block[j - 16], 1);
        }

        // Инициализация переменных для текущего блока
        uint a = H[0], b = H[1], c = H[2], d = H[3], e = H[4];

        // Основной цикл обработки блока
        for (int j = 0; j < block_expend_size_uints; j++) {
            uint f, k;
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            }
            else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            }
            else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            }
            else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint temp = cycle_shift_left(a, 5) + f + e + k + exp_block[j];
            e = d;
            d = c;
            c = cycle_shift_left(b, 30);
            b = a;
            a = temp;
        }

        // Обновляем значения хеша
        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
    }

    // Итоговый хеш
    uint* digest = new uint[5];
    digest[0] = H[0];
    digest[1] = H[1];
    digest[2] = H[2];
    digest[3] = H[3];
    digest[4] = H[4];

    delete[] newMessage;
    return digest;
}