#pragma once

#include <stdbool.h>
#include <string.h>
#include "../kp9/table.h"

/**
 * @brief Бинарный поиск
 * @warning ОБРАТИ ВНИМАНИЕ: тут два массива, обычно используется только один
 * @param keys массив ключей
 * @param datas массив значений
 * @return
 */
void Binary_Search(const Key *keys, const Data *datas);