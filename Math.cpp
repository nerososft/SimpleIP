//
// Created by neroyang on 2017/10/15.
//

#include "Math.h"
namespace OpenIP {
    void Math::quickSort(float *s, int l, int r) {
        if (l < r) {
            int i = l, j = r;
            float x = s[l];
            while (i < j) {
                while (i < j && s[j] >= x) // 从右向左找第一个小于x的数
                    j--;
                if (i < j)
                    s[i++] = s[j];
                while (i < j && s[i] < x) // 从左向右找第一个大于等于x的数
                    i++;
                if (i < j)
                    s[j--] = s[i];
            }
            s[i] = x;
            quickSort(s, l, i - 1); // 递归调用
            quickSort(s, i + 1, r);
        }
    }

    void Math::quickSortDouble(double s[], int l, int r){
        if (l < r) {
            int i = l, j = r;
            double x = s[l];
            while (i < j) {
                while (i < j && s[j] >= x) // 从右向左找第一个小于x的数
                    j--;
                if (i < j)
                    s[i++] = s[j];
                while (i < j && s[i] < x) // 从左向右找第一个大于等于x的数
                    i++;
                if (i < j)
                    s[j--] = s[i];
            }
            s[i] = x;
            quickSortDouble(s, l, i - 1); // 递归调用
            quickSortDouble(s, i + 1, r);
        }
    }

    Math::Math() {}
}
