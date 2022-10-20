#include "../DataStructures/Matrix.h"
#include "../DataStructures/Vector.h"
#include "../Ilumination/Color.h"
#include <stdio.h>

int main(){
    //Matrix<Color,1,2> c = Matrix<Color,1,2>();
    //Matrix<int,1,2> m = Matrix<int,1,2>();
    //m.setVal(1,1,2);
    //m.setVal(0,0,1);
    //m.setVal(0,1,2);
    //m.setVal(1,0,1);
    ////std::cout << m;
    //Vector v = Vector(1,2,3);
    //Matrix<int,3,1> vm = Matrix<int,3,1>(v);
    std::cout<<"dajisd\n";
    Vector v = Vector(1,1,1);
    std::cout<<v.getElementAt(2) <<'\n';
    Matrix<double,3,1> x = Matrix<double,3,1>(Vector(1,1,1));
    std::cout << x;
    std::cout << '\n';
    
    /*
    x.setVal(0,0,1);
    x.setVal(0,1,1);
    x.setVal(0,2,1);
   */
    Matrix<double,1,3> xt = x.transpose();

    std::cout << xt;
    std::cout << '\n';
    //Matrix<int,1,3> vmt = vm.transpose();
    Matrix<double,3,3> id = Matrix<double,3,3>::identity();
    Matrix<double,3,3> r = x*xt;
    
    std::cout << r;
    std::cout << '\n';
    double scalar = 2;
    Matrix<double,3,3> r2 = r*scalar;
    std::cout << (r2);
    std::cout << '\n';
    Matrix<double,3,3> s = r2-id;
    std::cout<<s;
    //std::cout << m;
    //std::cout << '\n';
    //std::cout << c ;
}
