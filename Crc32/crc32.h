#ifndef CRC32_H
#define CRC32_H

#include <QByteArray>
#include <array>
#include <cstdint>

// Предвычисленная таблица (256 значений)
static std::array<uint32_t, 256> generate_crc32_table();
uint32_t                         calculateCRC32(const QByteArray& data);

#endif  // CRC32_H
