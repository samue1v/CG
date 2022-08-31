#ifndef DataStructHeader
#define DataStructHeader

const long unsigned int INF = 10e18;

template <typename T> struct Pair{
    T left;
    T right;
};

struct Color{
    short int red;
    short int green;
    short int blue;
};

struct Coordinate
{
    int x;
    int y;
    int z;

};



class Matrix{
    public:
        Matrix(int lines, int columns);
        bool setVal(int x, int y,int val);
        int getVal(int x, int y);

    private:
        int nLines;
        int nColumns;
        int ** matrix;

};

Matrix::Matrix(int lines, int columns){
    this->nLines = lines;
    this->nColumns = columns;
    int ** m[lines];
    this->matrix = *m;
    for(int i =0;i<lines;i++){
        int c[columns];
        int *l = c;
        this->matrix[i] = l;
    }
}

int Matrix::getVal(int x, int y){
    return (this->matrix)[x][y];
}

bool Matrix::setVal(int x, int y, int val){
    if(val>=0){(this->matrix)[x][y] = val;return true;}
    return false;  
}

#endif

