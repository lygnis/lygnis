#include "Matrix3X3.h"

Matrix3X3::Matrix3X3()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            index[i][j] = 0;
        }
    }
}

Matrix3X3::Matrix3X3(int _seed)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            index[i][j] = rand() % _seed;
        }
    }
}

Matrix3X3::Matrix3X3(float _a00, float _a01, float _a02, float _a10, float _a11, float _a12, float _a20, float _a21, float _a22)
{
    index[0][0] = _a00; index[0][1] = _a01; index[0][2] = _a02;
    index[1][0] = _a10; index[1][1] = _a11; index[1][2] = _a12;
    index[2][0] = _a20; index[2][1] = _a21; index[2][2] = _a22;
}

bool Matrix3X3::operator==(const Matrix3X3& _mat)
{
    bool bln = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->index[i][j] != _mat.index[i][j])
                bln = false;
        }
    }
    if (bln == false)
        return false;
    else
        return true;
}

Matrix3X3 Matrix3X3::operator+(const Matrix3X3& _mat)
{
    Matrix3X3 temp;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            temp.index[i][j] = this->index[i][j] + _mat.index[i][j];
        }
    }
    return temp;
}

Matrix3X3 Matrix3X3::operator-(const Matrix3X3& _mat)
{
    Matrix3X3 temp;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            temp.index[i][j] = this->index[i][j] - _mat.index[i][j];
        }
    }
    return temp;
}

Matrix3X3 Matrix3X3::operator*(const float _scalar)
{
    Matrix3X3 temp;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            temp.index[i][j] = this->index[i][j] * _scalar;
        }
    }
    return temp;
}

Matrix3X3 Matrix3X3::MatOperator(const Matrix3X3 _matA, const Matrix3X3 _matB)
{
    Matrix3X3 temp;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                temp.index[i][j] += _matA.index[i][k] * _matB.index[k][j];
            }
        }
    }
    return temp;
}

Matrix3X3 Matrix3X3::TransPos(Matrix3X3 _mat)
{
    Matrix3X3 temp;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            temp.index[i][j] = _mat.index[j][i];
        }
    }
    return temp;
}
