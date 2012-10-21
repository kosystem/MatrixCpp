//
//  main.cpp
//  Matrix
//
//

#include <iostream>
#include "matrix.h"
#include <iomanip>

int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::cout << "In Matrix\n";

    Matrix mat(3,3);
    mat.unit_matrix();
//    mat[1][1] = 1;
//    mat[1][2] = 2;
//    mat[2][1] = 3;
//    mat[2][2] = 4;

    mat[1][1] = 1.0;
    mat[1][2] = 2.0;
    mat[1][3] = 1.0;
    mat[2][1] = 2.0;
    mat[2][2] = 1.0;
    mat[2][3] = 0.0;
    mat[3][1] = 1.0;
    mat[3][2] = 1.0;
    mat[3][3] = 2.0;
    
    for(int i=1; i <= mat.row_size(); i++){
        for(int j=1; j <= mat.column_size(); j++){
            printf(" %f",mat[i][j]);
        }
        printf("\n");
    }
    
    std::cout << "\nInverse Matrix\n";
    
    Matrix inv_mat(mat.inverse());
    for(int i=1; i <= inv_mat.row_size(); i++){
        for(int j=1; j <= inv_mat.column_size(); j++){
            printf(" %f",inv_mat[i][j]);
        }
        printf("\n");
    }
    
    std::cout << "\nIn Matrix\n";

    mat = mat * inv_mat;
    
    for(int i=1; i <= mat.row_size(); i++){
        for(int j=1; j <= mat.column_size(); j++){
            cout << setw(15) << mat[i][j];
        }
        printf("\n");
    }
    return 0;
}

