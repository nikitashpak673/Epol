#pragma once
#include<iostream>
class Complex
{
private:
   double re, im;


public:

   Complex() {};

   Complex (double r, double i);


   Complex (Complex &c);

   ~Complex() {}


   Complex &operator = (Complex &c){
       this->re = c.re;
       this->im = c.im;

       return (*this);
   }

   friend Complex operator + (const Complex &first,const Complex&second);

   friend Complex operator - (const Complex &first,const Complex&second);

   friend Complex operator * (const Complex &first,const Complex&second)
   {
      double re=first.re* second.re -first.im * second.im;
      double im=first.re * second.im + first.im* second.re;
      Complex temp(re,im);
      return temp;
   }
   friend Complex operator / (const Complex &first,const Complex &second)
     {
       Complex temp;

       double r = second.re * second.re + second.im * second.im;
       temp.re = (first.re * second.re + first.im* second.im) / r;
       temp.im = (first.im * second.re - first.re * second.im) / r;

       return temp;
     }
   friend bool operator ==(const Complex &first,const Complex&second){return (first.re==second.re)and(first.im==second.im);}
   friend bool operator!=(const Complex &first,const Complex&second){return !(first==second);}
   friend std::ostream& operator<< (std::ostream &out, const Complex&complex);
   friend std::istream& operator>> (std::istream &in, Complex&point);


};

