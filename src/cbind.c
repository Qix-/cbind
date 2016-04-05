#include <stdlib.h>
#include <string.h>

#if defined(__APPLE__) || defined(__linux__) || defined(__unix__)
#	include <unistd.h>
#	include <sys/mman.h>
#endif

extern void cbind_functor(void);
extern void cbind_boundary(void);

extern char _cbind_functor_state_offset;
extern char _cbind_functor_jmp_offset;

extern char _cbind_mov_size;

extern void *cbind(void *thisptr, void *memberfn) {
	size_t functor_size = (size_t)&cbind_boundary - (size_t)&cbind_functor;
	char *buf = malloc(functor_size);

	if (!buf) {
		return 0;
	}

	memcpy(buf, &cbind_functor, functor_size);
	memcpy(&buf[((size_t)&_cbind_functor_state_offset - (size_t)&cbind_functor) + _cbind_mov_size], &thisptr, sizeof(void*));
	memcpy(&buf[((size_t)&_cbind_functor_jmp_offset - (size_t)&cbind_functor) + _cbind_mov_size], &memberfn, sizeof(void*));

#if defined(__APPLE__) || defined(__linux__) || defined(__unix__)
	size_t pageSize = sysconf(_SC_PAGESIZE);
	void *pageStart = (void*)((size_t)buf & ~(pageSize -1));

	if (mprotect(pageStart, pageSize, PROT_EXEC | PROT_WRITE | PROT_READ)) {
		free(buf);
		return 0;
	}
#endif

	return buf;
}
