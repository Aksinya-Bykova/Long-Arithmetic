#pragma once

#include <cinttypes>
#include <iostream>

struct int2023_t {
    static const uint8_t kByteMove = 8;
    static const uint8_t kMaxValue = 0xff;
    static const uint16_t kBase = 256;
    static const uint8_t kArrSize = 253;
    static const uint16_t kMaxDecSize = 609;

    uint8_t data[kArrSize] = {0};
};

static_assert(sizeof(int2023_t) <= 253, "Size of int2023_t must be no higher than 253 bytes");

int2023_t from_unsigned_int(int32_t i);

int2023_t get_minus(const int2023_t& i);

int2023_t get_plus(const int2023_t& i);

bool is_negative(const int2023_t& i);

int2023_t from_int(int32_t i);

int2023_t from_string(const char* buff);

int2023_t operator+(const int2023_t& lhs, const int32_t& rhs);

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator*(const int2023_t& lhs, const uint32_t& rhs);

int2023_t modulo_multiply(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs);

uint8_t search_digit(const int2023_t& quot, const int2023_t& rhs);

int2023_t modulo_divide(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs);

bool operator<(const int2023_t& lhs, const int2023_t& rhs);

bool operator==(const int2023_t& lhs, const int2023_t& rhs);

bool operator!=(const int2023_t& lhs, const int2023_t& rhs);

std::ostream& operator<<(std::ostream& stream, const int2023_t& value);
