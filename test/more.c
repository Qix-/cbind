#include <stdio.h>
#include "cbind.h"

typedef struct {
	int i;
} MyData;

void addOne(MyData *data) {
	++(data->i);
}

void addTwo(MyData *data) {
	data->i += 2;
}

void add(MyData *data, int added) {
	data->i += added;
}

int get(MyData *data) {
	return data->i;
}

typedef struct {
	void (*addOne)(void);
	void (*addTwo)(void);
	void (*add)(int added);
	int (*get)(void);
} BoundFunctions;

int main(void) {
	for (int i = 0; i < 5; i++) {
		printf("i: %d\n", i);

		MyData data;
		data.i = i;

		BoundFunctions fn;
		fn.addOne = cbind(&data, &addOne);
		fn.addTwo = cbind(&data, &addTwo);
		fn.add = cbind(&data, &add);
		fn.get = cbind(&data, &get);

		fn.addOne();
		printf("\t+1: %d\n", data.i);
		if (data.i != (i + 1)) {
			return 1;
		}

		fn.addTwo();
		printf("\t+2: %d\n", data.i);
		if (data.i != (i + 1 + 2)) {
			return 1;
		}

		fn.add(i + 5);
		printf("\t+i+5: %d\n", data.i);
		if (data.i != (i + 1 + 2 + i + 5)) {
			return 1;
		}

		int got = fn.get();
		printf("\tget: %d\n", got);
		if (got != data.i) {
			return 1;
		}
	}

	printf("SUCCESS!\n");

	return 0;
}
