#pragma once

class TRatio
{
public:
    TRatio(int n = 1, int d = 1);
    int GetNumerator();
    int GetDenominator();

private:
    int numerator_;
    int denominator_;
};
