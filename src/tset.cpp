// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(-1)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(-1)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(-1)
{
	MaxPower = bf.GetLength();
	BitField = bf;
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem > MaxPower) throw 0;
	if (BitField.GetBit(Elem))
		return 1;
	return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem > MaxPower) throw 0;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem > MaxPower) throw 0;
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (s != *this)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if ((MaxPower != s.MaxPower) && (BitField != s.BitField))
		return 0;
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if ((MaxPower == s.MaxPower) && (BitField == s.BitField))
		return 0;
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	unsigned max = MaxPower;
	if (MaxPower < s.MaxPower)
	{
		max = s.MaxPower;
	}
	TSet tmp(max);
	tmp.BitField = BitField | s.BitField;
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < 0 || Elem >= MaxPower) throw 0;
	TSet tmp(MaxPower);
	for (int i = 0; i < tmp.MaxPower; i++)
		if (BitField.GetBit(i))
			tmp.BitField.SetBit(i);
	tmp.BitField.SetBit(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem < 0 || Elem >= MaxPower) throw 0;
	TSet tmp(MaxPower);
	for (int i = 0; i < tmp.MaxPower; i++)
		if (BitField.GetBit(i))
			tmp.BitField.SetBit(i);
	if (BitField.GetBit(Elem))
		tmp.BitField.ClrBit(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	unsigned max = 1, min = 1;
	if (MaxPower > s.MaxPower)
	{
		max = MaxPower;
		min = s.MaxPower;
	}
	else
	{
		min = MaxPower;
		max = s.MaxPower;
	}
	TSet tmp(max);
	for (int i = 0; i < min; i++)
		if (BitField.GetBit(i) && s.BitField.GetBit(i))
			tmp.BitField.SetBit(i);
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(*this);
	tmp.BitField = ~tmp.BitField;
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	return ostr;
}
