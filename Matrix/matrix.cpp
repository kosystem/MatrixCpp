#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

#include "matrix.h"
using namespace std;

//---------------------------------
//     通常のコンストラクタ
//---------------------------------
Matrix::Matrix(int i, int j)
{
    //  i,j のチェック
    if( i<1 || j<1 ){
        cerr << "err Matrix::Matrix" <<endl;
        exit(1);
    }
    
    row = i;
    column = j;
    
    //  配列のメモリ領域を動的に確保
    p_top = new float*[row+1];
    *p_top = new float[row*column+1];
    // +1 ga daiji kore tukenaito bagu ga deta
    for(int k=1; k<=row; k++)
        *(p_top+k) = *p_top+((k-1)*column);
    
    //  値の初期化
    for(int k1=1; k1<=row; k1++){
        for(int k2=1; k2<=column; k2++){
            p_top[k1][k2] = 0;
        }
    }
}

//---------------------------------
//     コピーコンストラクタ
//---------------------------------
Matrix::Matrix(const Matrix &cp)
{
    row = cp.row;
    column = cp.column;
    
    //  配列のメモリ領域を動的に確保
    p_top = new float*[row+1];
    *p_top = new float[row*column+1];
    // +1 ga daiji kore tukenaito bagu ga deta
    for(int k=1; k<=row; k++)
        *(p_top+k) = *p_top+((k-1)*column);
    
    //  値のコピー
    for(int k1=1; k1<=row; k1++){
        for(int k2=1; k2<=column; k2++){
            p_top[k1][k2] = cp.p_top[k1][k2];
        }
    }
}

//----------------------
//   デストラクタ
//----------------------
Matrix::~Matrix()
{
    delete [] *p_top;
    delete [] p_top;
}

//------------------------------
//   行列の大きさを変える  値は０
//------------------------------
void Matrix::change_size(int i, int j)
{
    //  i,j のチェック
    if( i<1 || j<1 ){
        cerr << "err Matrix::change_size" <<endl;
        exit(1);
    }
    
    delete [] *p_top;
    delete [] p_top;
    
    row = i;
    column = j;
    
    //  配列のメモリ領域を動的に確保
    p_top = new float*[row+1];
    *p_top = new float[row*column+1];
    // +1 ga daiji kore tukenaito bagu ga deta
    for(int k=1; k<=row; k++)
        *(p_top+k) = *p_top+((k-1)*column);
    
    //  値の初期化
    for(int k1=1; k1<=row; k1++){
        for(int k2=1; k2<=column; k2++){
            p_top[k1][k2] = 0;
        }
    }
    
}

//------------------------------------
//     代入
//------------------------------------
Matrix Matrix::operator=(const Matrix &a)
{
    if( row != a.row || column != a.column ){
        change_size(a.row, a.column);
    }
    
    for(int i=1; i<=row; i++){
        for(int j=1; j<=column; j++){
            p_top[i][j] = a.p_top[i][j];
        }
    }
    return(*this);
}

//------------------------------------
//       行列の加算
//------------------------------------
Matrix Matrix::operator+(const Matrix &a)
{
    if( row != a.row || column != a.column ){
        cerr << "err Matrix::operator+" <<endl;
        cerr << "  not equal matrix size" <<endl;
        exit(0);
    }
    
    Matrix r(row, column);
    for(int i=1; i<=row; i++){
        for(int j=1; j<=column; j++){
            r.p_top[i][j] = p_top[i][j] + a.p_top[i][j];
        }
    }
    r.cleanup();
    return(r);
}

//------------------------------------
//       行列の減算
//------------------------------------
Matrix Matrix::operator-(const Matrix &a)
{
    if( row != a.row || column != a.column ){
        cerr << "err Matrix::operator-" <<endl;
        cerr << "  not equal matrix size" <<endl;
        exit(0);
    }
    
    Matrix r(row, column);
    for(int i=1; i<=row; i++){
        for(int j=1; j<=column; j++){
            r.p_top[i][j] = p_top[i][j] - a.p_top[i][j];
        }
    }
    r.cleanup();
    return(r);
}

//------------------------------------
//       行列の積
//------------------------------------
Matrix Matrix::operator*(const Matrix &a)
{
    if( column != a.row ){
        cerr << "err Matrix::operator*" <<endl;
        cerr << "  not equal matrix size" <<endl;
        exit(0);
    }
    
    Matrix r(row, a.column);
    for(int i=1; i<=row; i++){
        for(int j=1; j<=a.column; j++){
            for(int k=1; k<=column; k++){
                r.p_top[i][j] += p_top[i][k] * a.p_top[k][j];
            }
        }
    }
    r.cleanup();
    return(r);
}

//--------------------------------------
//       行列の定数倍
//--------------------------------------
Matrix operator*(const Matrix &a, float b)
{
    Matrix r(a.row, a.column);
    for(int i=1; i<=a.row; i++){
        for(int j=1; j<=a.column; j++){
            r[i][j] = b * a.p_top[i][j];
        }
    }
    return(r);
}
Matrix operator*(float b, const Matrix &a)
{
    Matrix r(a.row, a.column);
    for(int i=1; i<=a.row; i++){
        for(int j=1; j<=a.column; j++){
            r[i][j] = b * a.p_top[i][j];
        }
    }
    return(r);
}

//----------------------------------------
//  単位行列にする
//----------------------------------------
void Matrix::unit_matrix()
{
    if(row != column){
        cerr <<"err in Matrix::unit_matrix()" <<endl;
        exit(0);
    }
    
    int n = row;
    float** a = p_top;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            a[i][j] = 0;
            if(i == j) a[i][j] = 1;
        }
    }
    
}

//----------------------------------------
//  転置行列をかえす
//----------------------------------------
Matrix Matrix::transposed()
{
    Matrix t(column, row);
    float** a = p_top;
    
    for(int i=1; i<=row; i++){
        for(int j=1; j<=column; j++){
            t[j][i] = a[i][j];
        }
    }
    return(t);
}

float Matrix::determinant()
{
    //作業用コピー
    Matrix a(*this);
    
    float det=1.0,buf;
    if (row != column) {
        cerr << "err in Matrix::determinant() >> row != column\n";
        exit(0);
    }
    int n=row;  //配列の次数
    int i,j,k;
    
    //三角行列を作成
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i<j){
                buf=a[j][i]/a[i][i];
                for(k=1;k<=n;k++){
                    a[j][k]-=a[i][k]*buf;
                }
            }
        }
    }
    //対角部分の積
    for(i=0;i<n;i++){
        det*=a[i][i];
    }
    if (isnan(det)) {
        cerr << "err in Matrix::determinant() >> non Determinant\n";
//        exit(0);
    }
    return det;
}

Matrix Matrix::inverse()
{
    //作業用コピー
    Matrix a(*this);
    //単位行列を作る
    Matrix inv_a(row, column);
    inv_a.unit_matrix();
    
    float buf;
    
    int n = row;
    
    float det = this->determinant();
    if (isnan(det)) {
        cerr << "err in Matrix::inverse() >> non Determinant\n";
//        exit(0);
    }

    //掃き出し法
    for(int i=1; i<=n; i++){
        buf=1/a[i][i];
        for(int j=1; j<=n;j++){
            a[i][j]*=buf;
            inv_a[i][j]*=buf;
        }
        for(int j=1; j<=n; j++){
            if(i!=j){
                buf=a[j][i];
                for(int k=1; k<=n; k++){
                    a[j][k]-=a[i][k]*buf;
                    inv_a[j][k]-=inv_a[i][k]*buf;
                }
            }
        }
    }
    inv_a.cleanup();
    return inv_a;
}

void Matrix::cleanup()
{
    numeric_limits<float> limits;
    
    int i,j;
    float max = 0.0;
    // 最大要素 max を見つける
    for(i = 1; i <= row; i++){
        for(j = 1; j <= column; j++){
            if(fabs(p_top[i][j]) > max ) max = fabs(p_top[i][j]);
            if( max > limits.epsilon() ){
                for(i = 1; i <= row; i++){
                    for(j = 1; j <= column; j++){
                        if( fabs(p_top[i][j]) / max < limits.epsilon() ){
                            p_top[i][j] = 0.0;
                        }
                    }
                }
            }
        }
    }
}

