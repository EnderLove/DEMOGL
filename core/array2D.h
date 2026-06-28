#ifndef ARRAY_2D_H
#define ARRAY_2D_H

#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>

template <typename T> class Array2D{
private:
    int cols_ = 0;
    int rows_ = 0;
    T* p_ = NULL;

public:  
    Array2D(){}
    ~Array2D(){ Destroy(); }

    Array2D(int Cols, int Rows){ InitArray2D(Cols, Rows); }

    void InitArray2D(int Cols, int Rows){
        cols_ = Cols;
        rows_ = Rows;
        if (p_) free(p_);
        p_ = (T*)malloc(cols_* rows_* sizeof(T));
    }

    void InitArray2D(int Cols, int Rows, T initVal){
        InitArray2D(Cols, Rows);
        for (int i = 0; i < Cols * Rows; i++) p_[i] = initVal;
    }

    void InitArray2D(int Cols, int Rows, void* data){
        cols_ = Cols;
        rows_ = Rows;
        if (p_) free(p_);
        p_ = (T*)data;
    }

    void Destroy(){ if (p_){ free(p_); p_ = NULL; } }
    
    T* GetAddr(int Col, int Row) const {
        size_t index = CalcIndex(Col, Row);
        return &p_[index];
    }

    T* GetBaseAddr() const { return p_; }

    int GetSize() const { return rows_ * cols_; }

    int GetSizeInBytes() const { return GetSize() * sizeof(T); }

    const T &Get(int Col, int Row) const { return *GetAddr(Col, Row); }

    void Set(int index, const T &val){
#ifndef NDEBUG
        if (index >= rows_ * cols_){
            printf("%s:%d - index %d is out of bounds (max size %d)\n", __FILE__, __LINE__, index, rows_ * cols_);
            exit(0);
        }
#endif
        p_[index] = val;
    }

    void GetMinMax(T &min, T& max){
        max = min = p_[0];
        for (int i = 1; i < rows_ * cols_; i++){
            if (p_[i] < min) min = p_[i];
            if (p_[i] > max) max = p_[i];
        }
    }

    void Normalize(T minRange, T maxRange){
        T min, max;

        GetMinMax(min, max);
        if (max <= min) return;

        T minMaxDelta = max - min;
        T minMaxRange = maxRange - minRange;

        for (int i = 0; i < rows_ * cols_; i++){
            p_[i] = ((p_[i] - min) / minMaxDelta) * minMaxRange + minRange;
        }
    }

    void PrintFloat(){
        for (int y = 0; y < rows_; y++){
            printf("%d: ", y);
            for (int x = 0; x < cols_; x++){
                float f = (float)p_[y * cols_ + x];
                printf("%.6f ", f);
            }
            printf("\n");
        }
    }

    int GetWidth()  const { return cols_; }
    int GetHeight() const { return rows_; }

private: 
    size_t CalcIndex(int Col, int Row) const {
#ifndef NDEBUG
        if (Col < 0) { printf("%s:%d - negative col %d\n", __FILE__, __LINE__, Col); }
        if (Row < 0) { printf("%s:%d - negative row %d\n", __FILE__, __LINE__, Row); }
        if (Col >= cols_) { printf("%s:%d - column overflow (%d vs %d)\n", __FILE__, __LINE__, Col, cols_); exit(0); }
        if (Row >= rows_) { printf("%s:%d - row overflow (%d vs %d)\n", __FILE__, __LINE__, Row, rows_); exit(0); }
#endif
        size_t index = Row * cols_ + Col;
        return index;
    }
};

#endif // ARRAY_2D_H!
