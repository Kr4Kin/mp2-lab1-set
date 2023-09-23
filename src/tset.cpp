// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Множество - реализация через битовые поля

#include <iostream>
#include "tbitfield.h"
#include "tset.h"

TSet::TSet(size_t mp) : bitField(1) {
    maxPower = mp;
    bitField = TBitField(mp);
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField) {
    maxPower = s.maxPower;
    bitField = s.bitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf) {
    maxPower = bf.getLength();
    bitField = bf;
}

TSet::operator TBitField()
{
    return bitField;
}

size_t TSet::getMaxPower() const // получить макс. к-во эл-тов
{
    return maxPower;
}

bool TSet::isMember(const uint elem) const // элемент множества?
{
    return bitField.getBit(elem);
}

void TSet::insElem(const uint elem) // включение элемента множества
{
    bitField.setBit(elem);
}

void TSet::delElem(const uint elem) // исключение элемента множества
{
    bitField.clrBit(elem);
}

// теоретико-множественные операции
TSet& TSet::operator=(const TSet &s) // присваивание
{
    maxPower = s.maxPower;
    bitField = s.bitField;
    return *this;
}

bool TSet::operator==(const TSet &s) const // сравнение
{
    if (maxPower == s.maxPower && bitField == s.bitField) return true;
    return false;
}

bool TSet::operator!=(const TSet &s) const // сравнение
{
    if (maxPower != s.maxPower || bitField != s.bitField) return true;
    return false;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    if (maxPower > s.maxPower) {
        TSet a(maxPower);
        a.bitField = bitField | s.bitField;
        return a;
    }
    else {
        TSet a(s.maxPower);
        a.bitField = bitField | s.bitField;
        return a;
    }
}

TSet TSet::operator+(const uint elem) // объединение с элементом
{
    TSet a(maxPower);
    a.bitField.setBit(elem);
    return a;
}

TSet TSet::operator-(const uint elem) // разность с элементом
{
    TSet a(maxPower);
    a.bitField.clrBit(elem);
    return a;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    if (maxPower > s.maxPower) {
        TSet a(maxPower);
        a.bitField = bitField & s.bitField;
        return a;
    }
    else {
        TSet a(s.maxPower);
        a.bitField = bitField & s.bitField;
        return a;
    }
    return TSet(1);
}

TSet TSet::operator~() // дополнение
{
    TSet a(maxPower);
    a.bitField = ~bitField;
    return a;
}

// перегрузка ввода/вывода
std::istream &operator>>(std::istream &istr, TSet &s) // ввод
{
    return istr;
}

std::ostream& operator<<(std::ostream &ostr, const TSet &s) // вывод
{
    ostr << s.bitField;
    return ostr;
}
