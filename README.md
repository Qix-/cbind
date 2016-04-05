# cbind

Make _real_ C function pointers that inject a state argument into the call.

```c
#include <stdio.h>

#include "cbind.h"

typedef struct {
	const char *foo;
} MyString;

void setStringTo(MyString *self, const char *newString) {
	self->foo = newString;
}

int main(void) {
	MyString myString;
	myString.foo = "hello";

	printf("%s\n", myString.foo); // "hello"

	void (*setMyStringTo)(const char *) = cbind(&myString, &setStringTo);

	setMyStringTo("foobar!");

	printf("%s\n", myString.foo); // "foobar!"

	return 0;
}

```

## Building

You'll need `yasm` installed and on your path. Most package managers have it :+1:

Then you'll have to set some janky parameters :D

First, determine your architecture:

- `i386`
- `x86_64`

Then, determine your platform:

- `macosx`
- `win32`
- `linux`

Then, determine the output format you want:

```console
$ yasm -f help
```

Then put it all together with `make`:

```console
$ make CBIND_PLATFORM=macosx CBIND_ARCH=x86_64 CBIND_FORMAT=macho64
```

I don't care if you trust me, you shouldn't. _Test this_ before you use it. If the tests succeed, then everything is okay.

Not saying this isn't okay for production, but this isn't okay for production.

```console
$ make test
```

## License
Licensed under CC0 by Josh Junon.
