#include "Crc32/crc32.h"

static constexpr uint32_t CRC32_POLY = 0xEDB88320;

// Предвычисленная таблица (256 значений)
static std::array<uint32_t, 256> generate_crc32_table()
{
    std::array<uint32_t, 256> table = {};
    for (uint32_t i = 0; i < 256; ++i)
    {
        uint32_t crc = i;
        for (int j = 0; j < 8; ++j)
            crc = (crc >> 1) ^ (CRC32_POLY & -(crc & 1));
        table[i] = crc;
    }
    return table;
}

uint32_t calculateCRC32(const QByteArray& data)
{
    static const std::array<uint32_t, 256> table = generate_crc32_table();

    uint32_t crc = 0xFFFFFFFF;

    for (uint8_t byte : data)
        crc = (crc >> 8) ^ table[(crc ^ byte) & 0xFF];

    return crc ^ 0xFFFFFFFF;  // Инверсия в конце
}
