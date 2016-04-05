all: bin/test-more bin/test-basic bin/libcbind.a

.PHONY: test
test:
	@bin/test-basic && \
	bin/test-more

bin/test-more: test/more.c | bin/libcbind.a
	$(CC) -o $@ $< -I include -L bin -g3 -O0 -lcbind

bin/test-basic: test/basic.c | bin/libcbind.a
	$(CC) -o $@ $< -I include -L bin -g3 -O0 -lcbind

bin/libcbind.a: bin/cbind.o bin/cbind_asm.o
	$(AR) crs $@ $^

bin/cbind.o: src/cbind.c
	$(CC) -Wall -Wextra -Werror -g3 -O0 -c -o $@ $<

bin/cbind_asm.o: src/plat/$(CBIND_PLATFORM)/$(CBIND_ARCH)/cbind.asm
	yasm -f $(CBIND_FORMAT) -o $@ $<
