#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose);

void good_function()
{
	    printf("Ejecutando función buena...\n");
}

void bad_exit_code()
{
	printf("Función que retorna código de error\n");
	exit(42);
}

void segfault_function()
{
	printf("Función que hace segfault...\n");
	int *ptr = NULL;
	*ptr = 42;
}

void abort_function()
{
	printf("Función que hace abort...\n");
	abort();
}

void timeout_function()
{
	printf("Función que se cuelga...\n");
	while (1)
		;
}

/*void divide_by_zero()
{
	printf("Función que divide por cero...\n");
	int x = 5 / 0;
	(void)x;
}*/

int main()
{
	int result;
	printf("=== Test 1: Función buena ===\n");
	result = sandbox(good_function, 2, true);
	printf("Resultado: %d (esperado: 1)\n\n", result);
	printf("=== Test 2: Exit con código 42 ===\n");
	result = sandbox(bad_exit_code, 2, true);
	printf("Resultado: %d (esperado: 0)\n\n", result);
	printf("=== Test 3: Segmentation fault ===\n");
	result = sandbox(segfault_function, 2, true);
	printf("Resultado: %d (esperado: 0)\n\n", result);
	printf("=== Test 4: Abort ===\n");
	result = sandbox(abort_function, 2, true);
	printf("Resultado: %d (esperado: 0)\n\n", result);
	printf("=== Test 5: Timeout (espera 3 segundos) ===\n");
	result = sandbox(timeout_function, 3, true);
	printf("Resultado: %d (esperado: 0)\n\n", result);
	//printf("=== Test 6: División por cero ===\n");
	//result = sandbox(divide_by_zero, 2, true);
	//printf("Resultado: %d (esperado: 0)\n\n", result);
	printf("=== Test 7: NULL function ===\n");
	result = sandbox(NULL, 2, true);
	printf("Resultado: %d (esperado: -1)\n\n", result);
	printf("=== Test 8: Verbose false ===\n");
	result = sandbox(segfault_function, 2, false);
	printf("Resultado: %d (esperado: 0, sin mensaje)\n\n", result);
	return (0);
}
