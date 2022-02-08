#include<iostream>
#include"complexnumber.h"
Complex::Complex(double r,double i)
    {
       re = r;
       im = i;
    }
Complex::Complex(Complex &c){
    this->im=c.im;
    this->re=c.re;
}
Complex operator + (const Complex &first,const Complex&second)
{
   Complex temp;

   temp.re = first.re+second.re;
   temp.im = first.im+second.im;

   return temp;
}
Complex operator - (const Complex &first,const Complex&second)
{
   Complex temp;

   temp.re = first.re-second.re;
   temp.im = first.im-second.im;

   return temp;
}
std::ostream& operator<< (std::ostream &out, const Complex &complex)
{
    if(complex.im>0){
        char buffer='+';
        out << "Complex number="<<complex.re<<buffer<<complex.im<<"i"<<std::endl;
    }
    else{
    out << "Complex number="<<complex.re<<complex.im<<"i"<<std::endl;
    }
    return out;
}
std::istream& operator>> (std::istream &in,Complex&point)
{

    in >> point.re;
    in >> point.im;

    return in;
}
