#pragma once

#include <cstdint> 

typedef uint32_t uint;

#define one_block_size_bytes 64          
#define one_block_size_uints 16           
#define block_expend_size_uints 80        

#define SHA1HASHLENGTHBYTES 20            
#define SHA1HASHLENGTHUINTS 5            
// Тип для указателя на блок из 16 слов
typedef uint* Block;
// Тип для расширенного блока из 80 слов
typedef uint ExpendBlock[block_expend_size_uints];

// Объявление глобальной переменной начальных значений хеша
extern uint H[5];

// Объявление функций
// Вращение влево 32-битного числа
uint cycle_shift_left(uint val, int bit_count);

// Основная функция вычисления SHA-1
uint* sha1(const char* message, uint msize_bytes);