#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H

#include <iostream>
using namespace std;

class CustomMatrix {
public:
    bool mat[5][5] = {0};
    CustomMatrix() {}

    CustomMatrix(bool m[5][5]) {
        const int m_size = sizeof(m) / sizeof(m[0]);
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < sizeof(m[0]); j++) {
                mat[i][j] = m[i][j];
            }
        }
    }

    void fillMatrix(bool m[5][5]) {
        const int m_size = sizeof(m) / sizeof(m[0]);
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < sizeof(m[0]); j++) {
                mat[i][j] = m[i][j];
            }
        }
    }

    bool isNonEmpty() const {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (mat[i][j]) return true;
            }
        }
        return false;
    }
};

#endif // CUSTOMMATRIX_H
