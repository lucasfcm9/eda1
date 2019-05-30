#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mdc(int a, int b)
{
    if(a < 0)
        a = -a;
    if(b < 0)
        b = -b;
    if(a % b == 0)
        return b;
    else
        return mdc(b, a%b);
}

int main()
{
    int n;
    scanf("%d", &n);
    char ch = '/';
    char op;
    int soma = 0, subt = 0, mult = 0, div = 0;
    int N1, D1, N2, D2;

    int i;
    do {
        scanf("%d%*c%c%*c%d%*c%c%*c%d%*c%c%*c%d", &N1, &ch, &D1, &op, &N2, &ch, &D2);

        int num, den;

        if(op == '+')
        {
            num = (N1*D2+N2*D1);
            den = (D1*D2);
        }
        else if(op == '-')
        {
            num = (N1*D2-N2*D1);
            den = (D1*D2);
        }
        else if(op == '*')
        {
            num = (N1*N2);
            den = (D1*D2);
        }
        else
        {
            num = (N1*D2);
            den = (N2*D1);
        }
        div = mdc(num, den);

        printf("%d/%d = %d/%d\n", num, den, num/div, den/div);
        n--;        
    } while(n > 0);
    return 0;
}
