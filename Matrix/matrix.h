#include <iostream>

using namespace std;

class Matrix{
    
    int row;  //行
    int column;  //列
    
    float** p_top; //配列の最初を指すポインタ
    
public:
    Matrix(int i=1, int j=1);//コンストラクタ
    Matrix(const Matrix &cp);//コピーコンストラクタ
    
    ~Matrix();//デストラクタ
    
    int row_size(){ return(row); }
    int column_size(){ return(column); }
    
    void change_size(int i, int j);//行列のサイズを変更する
    
    //演算子のオーバーロード
    float* &operator[](int i){ return(p_top[i]); }
    Matrix operator=(const Matrix &a);
    Matrix operator+(const Matrix &a);
    Matrix operator-(const Matrix &a);
    Matrix operator*(const Matrix &a);
    
    friend Matrix operator*(const Matrix &a, float b);
    friend Matrix operator*(float b, const Matrix &a);
    
    //行列の変換など
    void unit_matrix();//単位行列にする
    Matrix transposed();//転置行列をかえす
    float determinant();
    Matrix inverse();//逆行列を求める
    void cleanup();
    
};