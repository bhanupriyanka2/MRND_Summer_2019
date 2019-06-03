#include <stdio.h>

long  nthpower(int a, int n){
	if (n == 1){
		return a;
	}
	if (n % 2 == 0){
		return nthpower(a, n / 2)*nthpower(a, n / 2);
	}
	return a*nthpower(a, n / 2)*nthpower(a, n / 2);
}

/*int main(){
	printf("%ld", nthpower(2,8));
	getchar();
}*/