#include<stdio.h>
#include<stdlib.h>

class A{
public :
A(){}
};

class M{
public :
M(){}

void f(int i, int j)
{
    i=1;
    j=1;
    printf("I'm pere\n");
}
};

class F : public M{
public :
F(){}

void f(int i, A a)
{
    i=0;
    printf("I'm fils\n");
}
};

int main()
{
    F nn;
    //nn.M::f(1,3);
    M *m;
    //F *f = (F*)m;
    return 0;
}
