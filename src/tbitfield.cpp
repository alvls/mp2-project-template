// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include <iomanip>
#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw "length < 0";
	else
	{
		BitLen = len;
		MemLen = (BitLen - 1) / (sizeof(TELEM) * 8) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	BitLen = 0;
	MemLen = 0;
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (BitLen <= n))
	{
		throw "Error! Incorrect bit";
	}
	else
	{
		return n / (sizeof(TELEM) * 8);
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (BitLen <= n))
	{
		throw "Error! Incorrect bit";
	}
	else
	{
		return 1 << n % (sizeof(TELEM) * 8);
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (BitLen <= n))
	{
		throw "Error! Incorrect bit";
	}
	else
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (BitLen <= n))
	{
		throw "Error! Incorrect bit";
	}
	else
	{
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (BitLen <= n))
	{
		throw "Error! Incorrect bit";
	}
	else
	{
		return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0) ? 1 : 0;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = NULL;
		pMem = new TELEM[MemLen];
	}

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 0;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if ((MemLen == bf.MemLen) && (BitLen == bf.BitLen))
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 1;
		}
		return 0;
	}
	else
	{
		return 1;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int tmpBitLen = (BitLen > bf.BitLen) ? (BitLen) : (bf.BitLen);
	TBitField tmp(tmpBitLen);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}

	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] |= bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int tmpBitLen = (BitLen > bf.BitLen) ? (BitLen) : (bf.BitLen);
	TBitField tmp(tmpBitLen);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}

	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] &= bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField TMP(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) == 0)
		{
			TMP.SetBit(i);
		}
		else
		{
			TMP.ClrBit(i);
		}
	}
	return TMP;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int inBit;
	int inLen;
	istr >> inLen;
	bf = TBitField(inLen);
	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> inBit;
		if (inBit)
		{
			bf.SetBit(i);
		}
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	int outLen = bf.GetLength();
	ostr << outLen << endl;
	for (int i = 0; i < outLen; i++)
	{
		ostr << bf.GetBit(i);
    }
	return ostr;
}
