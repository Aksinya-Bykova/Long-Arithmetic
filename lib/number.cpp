#include "number.h"

int2023_t from_unsigned_int(int32_t i) {
    int2023_t temp;
    temp.data[0] = i & int2023_t::kMaxValue;
    temp.data[1] = (i >> int2023_t::kByteMove) & int2023_t::kMaxValue;
    temp.data[2] = (i >> (2 * int2023_t::kByteMove)) & int2023_t::kMaxValue;
    temp.data[3] = i >> (3 * int2023_t::kByteMove);

    return temp;
}

int2023_t modulo(const int2023_t& i) {
    int2023_t POW_2022;
    POW_2022.data[int2023_t::kArrSize - 1] = (int2023_t::kBase / 2);

    int2023_t temp = from_unsigned_int(0);
    uint8_t sum = 0;

    for (int iter = 0; iter < int2023_t::kArrSize; ++iter) {
        temp.data[iter] = POW_2022.data[iter] - i.data[iter] - sum + int2023_t::kBase;
        sum = (int2023_t::kMaxValue - POW_2022.data[iter] + i.data[iter] + sum) / int2023_t::kBase;
    }

    return temp;
}

int2023_t get_minus(const int2023_t& i) {
    int2023_t POW_2022;
    POW_2022.data[int2023_t::kArrSize - 1] = (int2023_t::kBase / 2);

    return modulo(i) + POW_2022;
}

int2023_t get_plus(const int2023_t& i) {
    int2023_t POW_2022;
    POW_2022.data[int2023_t::kArrSize - 1] = (int2023_t::kBase / 2);

    int2023_t temp = from_unsigned_int(0);
    uint8_t sum = 0;

    for (int iter = 0; iter < int2023_t::kArrSize; ++iter) {
        temp.data[iter] = i.data[iter] - POW_2022.data[iter] - sum + int2023_t::kBase;
        sum = (int2023_t::kMaxValue - i.data[iter] + POW_2022.data[iter] + sum) / int2023_t::kBase;
    }

    return modulo(temp);
}

bool is_negative(const int2023_t& i) {
    return i.data[int2023_t::kArrSize - 1] >= (int2023_t::kBase / 2);
}

int2023_t from_int(int32_t i) {
    if (i >= 0) {
        return from_unsigned_int(i);
    }

    return get_minus(from_unsigned_int((-1) * i));
}

int2023_t from_string(const char* buff) {
    size_t len = 0;
    int start = 0;

    if (buff[0] == '-') {
        start = 1;
    }

    for (int i = start; i < int2023_t::kArrSize; ++i) {
        if (std::isdigit(buff[i])) {
            ++len;
        } else {
            break;
        }
    }

    int2023_t temp = from_unsigned_int(0);
    int2023_t constant = from_unsigned_int(1);

    for (int i = len - 1 + start; i >= start; --i) {
        temp = temp + constant * static_cast<int>(buff[i] - '0');
        constant = constant * 10;
    }

    if (start == 0) {
        return temp;
    } else {
        return get_minus(temp);
    }
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t temp = from_unsigned_int(0);
    uint8_t sum = 0;

    for (int i = 0; i < int2023_t::kArrSize; ++i) {
        temp.data[i] = lhs.data[i] + rhs.data[i] + sum;
        sum = (lhs.data[i] + rhs.data[i] + sum) / int2023_t::kBase;
    }

    return temp;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
    return lhs + get_minus(rhs);
}

int2023_t operator*(const int2023_t& lhs, const uint32_t& rhs) {
    int2023_t temp = from_unsigned_int(0);
    uint64_t sum = 0;

    for (int i = 0; i < int2023_t::kArrSize; ++i) {
        temp.data[i] = lhs.data[i] * rhs + sum;
        sum = (lhs.data[i] * rhs + sum) / int2023_t::kBase;
    }

    return temp;
}

int2023_t modulo_multiply(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t temp = from_unsigned_int(0);
    uint64_t sum = 0;
    
    for (int i = 0; i < int2023_t::kArrSize; ++i) {
        sum = sum / int2023_t::kBase;
        temp.data[i] += sum;

        for (int j = 0; j <= i; ++j) {
            temp.data[i] += lhs.data[j] * rhs.data[i - j];
            sum += lhs.data[j] * rhs.data[i - j];
        }
    }

    return temp;
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
    if (is_negative(lhs) && is_negative(rhs)) {
        return modulo_multiply(get_plus(lhs), get_plus(rhs));
    }

    if (is_negative(lhs) && !is_negative(rhs)) {
        return get_minus(modulo_multiply(get_plus(lhs), rhs));
    }

    if (!is_negative(lhs) && is_negative(rhs)) {
        return get_minus(modulo_multiply(lhs, get_plus(rhs)));
    }

    return modulo_multiply(lhs, rhs);
}

uint8_t search_digit(const int2023_t& quot, const int2023_t& rhs) {
    uint16_t left = 0;
    uint16_t right = int2023_t::kBase;

    while (right - left > 1) {
        uint16_t mid = (right + left) / 2;
        if (!(quot < rhs * mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    return left;
}

int2023_t modulo_divide(const int2023_t& lhs, const int2023_t& rhs) {
    if (lhs < rhs || rhs == from_unsigned_int(0)) {
        return from_unsigned_int(0);
    }

    int2023_t result;
    int2023_t quot = from_unsigned_int(0);

    for (int i = int2023_t::kArrSize - 1; i >= 0; --i) {
        quot = quot * int2023_t::kBase + from_unsigned_int(lhs.data[i]);

        if (quot < rhs) {
            result.data[i] = 0;
        } else {
            uint8_t digit = search_digit(quot, rhs);

            result.data[i] = digit;
            quot = quot - rhs * digit;
        }
    }

    return result;
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
    if (is_negative(lhs) && is_negative(rhs)) {
        return modulo_divide(get_plus(lhs), get_plus(rhs));
    }

    if (is_negative(lhs) && !is_negative(rhs)) {
        return get_minus(modulo_divide(get_plus(lhs), rhs));
    }

    if (!is_negative(lhs) && is_negative(rhs)) {
        return get_minus(modulo_divide(lhs, get_plus(rhs)));
    }

    return modulo_divide(lhs, rhs);
}

bool operator<(const int2023_t& lhs, const int2023_t& rhs) {
    for (int i = int2023_t::kArrSize - 1; i >= 0; --i) {
        if (lhs.data[i] != rhs.data[i]) {
            return lhs.data[i] < rhs.data[i];
        }
    }

    return false;
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
    for (int i = 0; i < int2023_t::kArrSize; ++i) {
        if (lhs.data[i] != rhs.data[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
    int2023_t temp;

    if (is_negative(value)) {
        stream << '-';
        temp = get_plus(value);
    } else {
        temp = value;
    }

    uint8_t dec_v[int2023_t::kMaxDecSize];
    uint32_t len = 0;

    for (int i = 0; i < int2023_t::kMaxDecSize; ++i) {
        dec_v[i] = (temp - (temp / from_int(10)) * 10).data[0];
        temp = temp / from_unsigned_int(10);
        ++len;
        if (temp == from_unsigned_int(0)) {
            break;
        }
    }

    for (int i = len - 1; i >= 0; --i) {
        stream << static_cast<int>(dec_v[i]);
    }

    return stream;
}
