// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw invalid_argument("Negative length is not allowed.");
	BitLen = len;
	MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}


TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.GetLength();
	MemLen = (BitLen + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}
TBitField::~TBitField()
{
	if (pMem != NULL) {
		delete[] pMem;
		pMem = NULL;
		MemLen = NULL;
	}
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0 && n < BitLen)
		return n >> 5;
	else
		throw - 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM tmp = 1 << n;
	return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0)
		throw invalid_argument("Can't set negative bit");
	if (n >= BitLen)
		throw invalid_argument("Can't set bit larger than the maximum bit field size");
	pMem[GetMemIndex(n)] |= GetMemMask(n % 32);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0)
		throw invalid_argument("Can't clear negative bit");
	if (n >= BitLen)
		throw invalid_argument("Can't clear bit larger than the maximum bit field size");
	pMem[GetMemIndex(n)] &= ~GetMemMask(n % 32);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0)
		throw invalid_argument("Can't get negative bit");
	if (n >= BitLen)
		throw invalid_argument("Can't get bit larger than the maximum bit field size");
	if ((pMem[GetMemIndex(n)] & GetMemMask(n % 32)) > 0)
		return 1;
	else
		return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this == &bf) return *this;

	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	if (bf.MemLen != MemLen)
	{
		MemLen = bf.MemLen;
		delete pMem;
		pMem = new TELEM[MemLen];
	}

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}

	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.GetLength())
		return 0;
	for (int i = 0; i < MemLen; ++i)
		if (pMem[i] != bf.pMem[i])
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.GetLength())
		return 1;
	for (int i = 0; i < MemLen; ++i)
		if (pMem[i] != bf.pMem[i])
			return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	if (BitLen >= bf.GetLength())
	{
		TBitField tmp(*this);
		for (int i = 0; i < bf.GetLength(); i++)
			tmp.pMem[i] |= bf.pMem[i];
		return tmp;
	}
	else
	{
		TBitField tmp(bf);
		for (int i = 0; i < BitLen; i++)
			tmp.pMem[i] |= pMem[i];
		return tmp;
	}
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; ++i)
		tmp.pMem[i] = pMem[i] & bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(*this);
	for (int i = 0; i < tmp.BitLen; i++)
	{
		if (tmp.GetBit(i))
			tmp.ClrBit(i);
		else
			tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	char* s;
	istr >> s;
	int len = sizeof(s) / sizeof(char) - 1;
	TBitField tmp(len);
	for (int i = 0; i < len; ++i)
	{
		if (s[i] == '1')
			tmp.SetBit(i);
		else
			tmp.ClrBit(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
		ostr << bf.GetBit(i);
	return ostr;
}
