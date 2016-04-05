#include <stdio.h>
#include <errno.h>
#include "cbind.h"

typedef struct {
	int data;
} MyData;

int addFromMyData(MyData *data, int add) {
	return data->data + add;
}

int main(void) {
	MyData dat;
	dat.data = 15;

	int (*boundFn)(int) = cbind(&dat, &addFromMyData);
	if (!boundFn) {
		printf("cbind() failed: %d\n", errno);
		return 1;
	}

	printf("bound function at: %p\n", boundFn);
	
	int result = boundFn(6);
	printf("got %d as result from boundFn\n", result);

	if (result != 21) {
		return 1;
	}

	return 0;
}
