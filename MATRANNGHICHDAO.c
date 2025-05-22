#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

// Hàm tính định thức ma trận 3x3
double determinant(double mat[SIZE][SIZE]) {
    double det = 0;
    det = mat[0][0]*(mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1])
        - mat[0][1]*(mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0])
        + mat[0][2]*(mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0]);
    return det;
}

// Hàm tính ma trận con (minor) loại bỏ dòng p và cột q
void getMinor(double src[SIZE][SIZE], double dest[SIZE-1][SIZE-1], int p, int q) {
    int i = 0, j = 0;
    for (int row = 0; row < SIZE; row++) {
        if (row == p) continue;
        j = 0;
        for (int col = 0; col < SIZE; col++) {
            if (col == q) continue;
            dest[i][j] = src[row][col];
            j++;
        }
        i++;
    }
}

// Hàm tính định thức ma trận 2x2 (phục vụ minor)
double determinant2(double mat[SIZE-1][SIZE-1]) {
    return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
}

// Hàm tính ma trận phụ hợp (cofactor matrix)
void adjoint(double mat[SIZE][SIZE], double adj[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            double minor[SIZE-1][SIZE-1];
            getMinor(mat, minor, i, j);
            double detMinor = determinant2(minor);
            // Cofactor C_ij = (-1)^{i+j} * det(minor)
            adj[j][i] = ((i+j)%2 == 0 ? 1 : -1) * detMinor; // Chuyển vị luôn
        }
    }
}

// Hàm tính ma trận nghịch đảo
int inverse(double mat[SIZE][SIZE], double inv[SIZE][SIZE]) {
    double det = determinant(mat);
    if (det == 0) {
        return 0; // Không khả nghịch
    }

    double adj[SIZE][SIZE];
    adjoint(mat, adj);

    // Tính nghịch đảo = adj / det
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inv[i][j] = adj[i][j] / det;
        }
    }
    return 1; // Thành công
}

// Hàm in ma trận
void printMatrix(double mat[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%8.4f ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    double matrix[SIZE][SIZE];

    printf("Nhap ma tran vuong 3x3:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("a[%d][%d] = ", i+1, j+1);
            scanf("%lf", &matrix[i][j]);
        }
    }

    double inv[SIZE][SIZE];
    if (inverse(matrix, inv)) {
        printf("Ma tran nghich dao:\n");
        printMatrix(inv);
    } else {
        printf("Ma tran khong co nghich dao (det = 0)\n");
    }

    return 0;
}