#include <stdio.h>
#include <dlfcn.h>

int main( void )
{
	typedef int (Fuc)(int, int);

	void *handle = dlopen("libmath.so", RTLD_LAZY);
	if ( handle == NULL )
		printf("%s\n", dlerror());

	Fuc *fun = (Fuc*)dlsym(handle, "add");
	if ( fun == NULL )
		printf("%s\n", dlerror());

	printf("%d\n", fun(1,3));
	
	dlclose(handle);
}

