#include <stdio.h>

int main(){

	int i, j;
	int v[10];
	int sum = 0;
	int max = -1;
	int size;

	for(i = 0; i < 10; i++) {
		scanf("%d", &v[i]);
	}
	for(i = 0; i < 10; i++) {
		sum = 0;
		for(j = i; j < 10; j++) {
			size = i;
			sum += v[j];
			if(sum > max) {
				max = sum;
			}
		}
	}
	for(i = 0; i < size; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
	printf("%d\n", max);
    return 0;
}
