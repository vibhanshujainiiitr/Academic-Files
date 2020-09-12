#include<stdio.h>

    typedef struct {
        float real;
        float imag;
    } Complex;
    Complex sum(Complex m, Complex n);
    Complex product(Complex m, Complex n);


int main()
{ Complex a,b,c,d;
  scanf("%f%f", &a.real, &a.imag);
  scanf("%f%f", &b.real, &b.imag);

  c = sum(a,b);
  d = product(a,b);

  printf("Sum of a and b is %f + i%f\n", c.real,c.imag);
  printf("Product of a and b is %f + i%f\n", d.real,d.imag);
}

 Complex sum (Complex m, Complex n){
    Complex p;
    p.real = m.real + n.real;
    p.imag = m.imag + n.imag;
    return p;
 }

 Complex product(Complex m, Complex n){
    Complex p;
    p.real = (m.real*n.real) - (m.imag*n.imag);
    p.imag = (m.real*n.imag) + (n.real*m.imag);
    return p;
 }
