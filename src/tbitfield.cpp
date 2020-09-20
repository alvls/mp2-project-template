// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#include <memory.h>

TBitField::TBitField(int len)
{
    if (len < 0) throw "Unable to create BitField with negative length";
    MemLen = (len-1) / (8 * sizeof(TELEM)) + 1;
    pMem = new TELEM[MemLen];
    memset(pMem, 0, MemLen * sizeof(TELEM));
    BitLen = len;
}

TBitField::TBitField(const TBitField &bf): BitLen(bf.BitLen), MemLen(bf.MemLen) // конструктор копирования
{
    memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / (8 * sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n > this->BitLen - 1)) throw "Invalid index";
    pMem[GetMemIndex(n)] |= 1 << (n % (8 * sizeof(TELEM)));
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n > this->BitLen - 1)) throw "Invalid index";
    pMem[GetMemIndex(n)] &= ~(1 << (n % (8 * sizeof(TELEM))));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n > this->BitLen - 1)) throw "Invalid index";
    return (pMem[GetMemIndex(n)] >> (n %  (8 * sizeof(TELEM)))) & 1u;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
    return *this;    
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (this->BitLen != bf.BitLen) return 0;
  for (int i = 0; i < this->MemLen; i++)
  {
      if (this->pMem[i] != bf.pMem[i]) return 0;
  }
  return 1;
}
int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !((*this) == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField result(this->BitLen);
    for (int i = 0; i < result.MemLen; i++)
    {
        result.pMem[i] = this->pMem[i] | bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField result(this->BitLen);
    for (int i = 0; i < result.MemLen; i++)
    {
        result.pMem[i] = this->pMem[i] & bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(BitLen);
    for (int i = 0; i < BitLen; i++)
    {
        if (!GetBit(i)) result.SetBit(i); 
    }
    return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string s;
    istr >> s;
    for (int i=0; i < bf.BitLen; i++)
    {
        if (s[i] == '1') bf.SetBit(s.length() - i - 1);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
