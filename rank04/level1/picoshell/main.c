#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int picoshell(char **cmds[]);

void test_simple_pipe()
{
	    printf("=== Test 1: ls | grep pic ===\n");
	        char **cmds[] = {
			        (char *[]){"ls", NULL},
				        (char *[]){"grep", "pic", NULL},
					        NULL
							    };
		    picoshell(cmds);
		        printf("\n");
}

void test_triple_pipe()
{
	    printf("=== Test 2: ls | grep .c | wc -l ===\n");
	        char **cmds[] = {
			        (char *[]){"ls", NULL},
				        (char *[]){"grep", ".c", NULL},
					        (char *[]){"wc", "-l", NULL},
						        NULL
								    };
		    picoshell(cmds);
		        printf("\n");
}

void test_echo_sed()
{
	    printf("=== Test 3: echo 'squalala' | sed 's/a/b/g' ===\n");
	        char **cmds[] = {
			        (char *[]){"echo", "squalala", NULL},
				        (char *[]){"sed", "s/a/b/g", NULL},
					        NULL
							    };
		    picoshell(cmds);
		        printf("\n");
}

void test_cat_grep()
{
	    printf("=== Test 4: cat picoshell.c | grep int ===\n");
	        char **cmds[] = {
			        (char *[]){"cat", "picoshell.c", NULL},
				        (char *[]){"grep", "int", NULL},
					        NULL
							    };
		    picoshell(cmds);
		        printf("\n");
}

void test_long_pipeline()
{
	    printf("=== Test 5: ls | grep .c | cat | wc -l ===\n");
	        char **cmds[] = {
			        (char *[]){"ls", NULL},
				        (char *[]){"grep", ".c", NULL},
					        (char *[]){"cat", NULL},
						        (char *[]){"wc", "-l", NULL},
							        NULL
									    };
		    picoshell(cmds);
		        printf("\n");
}

int main()
{
	    test_simple_pipe();
	        test_triple_pipe();
		    test_echo_sed();
		        test_cat_grep();
			    test_long_pipeline();
			        
			        return 0;
}
