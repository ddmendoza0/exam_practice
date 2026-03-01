#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ft_popen(const char *file, char *const argv[], char type);

//Test 1: Read from ls
void test_read_ls()
{
	printf("=== Test 1: Leer salida de ls ===\n");
	int fd = ft_popen("ls", (char *const []){"ls", "-la", NULL}, 'r');	    
	if (fd == -1)
	{
		printf("Error: ft_popen falló\n");
		return;
	}	        
	char buf[1024];
	ssize_t bytes;
	while ((bytes = read(fd, buf, sizeof(buf) - 1)) > 0)
	{
		buf[bytes] = '\0';
		printf("%s", buf);
	}   
	close(fd);
        printf("\n");
}

//Test 2: Reed from echo
void test_read_echo()
{
	printf("=== Test 2: Leer salida de echo ===\n");
	int fd = ft_popen("echo", (char *const []){"echo", "Hola desde el pipe!", NULL}, 'r');    
	if (fd == -1)
	{
		printf("Error: ft_popen falló\n");
		return;
	}	        
	char buf[100];
	ssize_t bytes = read(fd, buf, sizeof(buf) - 1);
	buf[bytes] = '\0';
	printf("Leído: %s", buf);			        
	close(fd);
	printf("\n");
}

//Test 3: Write to wc -c
void test_write_wc()
{
	printf("=== Test 3: Escribir a wc -c ===\n");
	int fd = ft_popen("wc", (char *const []){"wc", "-c", NULL}, 'w');
     	if (fd == -1)
	{
		printf("Error: ft_popen falló\n");
		return;
	}
	char *text = "Contando caracteres!";
	write(fd, text, strlen(text));
	close(fd);
	sleep(1);
	printf("\n");
}

//Test 4: Pipeline
void test_pipeline()
{
	printf("=== Test 4: Pipeline ls | grep ft ===\n");
	int fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	dup2(fd, STDIN_FILENO);
	close(fd);
	fd = ft_popen("grep", (char *const []){"grep", "ft_popen", NULL}, 'r');                        
	char buf[1024];
	ssize_t bytes;
	while ((bytes = read(fd, buf, sizeof(buf) - 1)) > 0)
	{
		buf[bytes] = '\0';
		printf("%s", buf);
	}
	close(fd);
}

int main()
{
	test_read_ls();
	test_read_echo();
	test_write_wc();
	test_pipeline();
	return 0;
}
