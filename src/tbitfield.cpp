// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#include <limits>
#include <iostream>
#include "tbitfield.h"

TBitField::TBitField(size_t len)
{
    bitLen = len;
    if (len % (sizeof(uint) * 8) != 0)
        memLen = len / (sizeof(uint) * 8) + 1;
    else
        memLen = len / (sizeof(uint) * 8);
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

size_t TBitField::getIndex(const size_t n) const  // индекс в pМем для бита n
{
    if (n < bitLen) {
        size_t ind = n % (sizeof(uint) * 8);
        return ind;
    }
    else {
        throw "1";
    }
}

uint TBitField::getMask(const size_t n) const // битовая маска для бита n
{
    uint mask = (uint)1 << n;
    return mask;
}

// доступ к битам битового поля
uint TBitField::getLength() const // получить длину (к-во битов)
{
    return (uint)bitLen;
}

size_t TBitField::getNumBytes() const // получить количество байт выделенной памяти
{
    return memLen * sizeof(uint);
}

void TBitField::setBit(const size_t n) // установить бит
{
    pMem[n / (sizeof(uint) * 8)] = pMem[n / (sizeof(uint) * 8)] | getMask(getIndex(n));
}

void TBitField::clrBit(const size_t n) // очистить бит
{
    pMem[n / (sizeof(uint) * 8)] = pMem[n / (sizeof(uint) * 8)] & ~getMask(getIndex(n));
}

bool TBitField::getBit(const size_t n) const // получить значение бита
{
    uint a = pMem[n / (sizeof(uint) * 8)];
    uint b = getMask(getIndex(n));
    if (a & b)
        return true;
    return false;
}

// битовые операции
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    delete[] pMem;
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (bitLen != bf.bitLen) return false;
    for (int i = 0; i < memLen; i++) {
        if (pMem[i] != bf.pMem[i]) return false;
    }
    return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (bitLen != bf.bitLen) return true;
    for (int i = 0; i < memLen; i++) {
        if (pMem[i] != bf.pMem[i]) return true;
    }
    return false;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    if (bitLen < bf.bitLen) {
        TBitField a(bf.bitLen);
        for (int i = 0; i < memLen; i++) {
            a.pMem[i] = pMem[i] | bf.pMem[i];
        }
        return a;
    }
    else {
        TBitField a(bitLen);
        for (int i = 0; i < bf.memLen; i++) {
            a.pMem[i] = pMem[i] | bf.pMem[i];
        }
        return a;
    }
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    if (bitLen < bf.bitLen) {
        TBitField a(bf.bitLen);
        for (int i = 0; i < memLen; i++) {
            a.pMem[i] = pMem[i] & bf.pMem[i];
        }
        return a;
    }
    else {
        TBitField a(bitLen);
        for (int i = 0; i < bf.memLen; i++) {
            a.pMem[i] = pMem[i] & bf.pMem[i];
        }
        return a;
    }

}

TBitField TBitField::operator~() // отрицание
{
    TBitField a(bitLen);
    for (int i = 0; i < memLen-1; i++) {
        a.pMem[i] = ~pMem[i];
    }
    uint z = 0;
    for (int i = 0; i < bitLen % (sizeof(uint) * 8); i++) {
        z += (uint)1 << i;
    }
    a.pMem[memLen - 1] = pMem[memLen - 1] ^ z;
    return a;
}

TBitField::~TBitField()
{
    delete[] pMem;
}

// ввод/вывод
std::istream &operator>>(std::istream &istr, TBitField &bf) // ввод
{
    char ss[255];
    istr.getline(ss, 255);
    return istr;
}

std::ostream &operator<<(std::ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = bf.bitLen - 1; i >= 0; i--) {
        if (bf.pMem[i / (sizeof(uint)*8)] & bf.getMask(bf.getIndex(i)))
            ostr << '1';
        else
            ostr << '0';
    }
    return ostr;
}