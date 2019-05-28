#include <stdio.h>
main()
{
float pi = 3.1415, *pf, **ppf;
pf = &pi;
ppf = &pf;
printf("\n%.4f", **ppf);
printf("\n%.4f", *pf);
}
