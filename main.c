#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// int	main(void)
// {
// 	t_env *head;
// 	printf("head = %ld\n", head);
// 	char *ptr = head;
// 	printf("ptr = %ld\n", ptr);
// 	// printf("pointer = %ld\n", ptr);
// }


// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>


// char *get_next_line(int fd) 
// {
//     char *string = malloc(10000), *copy = string;
//     while (read(fd, copy, 1) > 0 && *copy++ != '\n');
//     return (copy > string) ? (*copy = 0, string) : (free(string), NULL);
// }

// int main()
// {
//     int a = 0;
//     // while (1)
//     // {
        
//         printf("%s", get_next_line(a));
//     // }
    
// }

// int main()
// {
//     char *ptr = malloc(20);
//     ptr[0] = '1';
//     ptr[1] = '2';
//     ptr[2] = '3';
//     ptr[3] = '4';
//     ptr[4] = '\0';
//     ptr[5] = '8';
//     ptr[4] = '\0';
//     int i = 0;
//     while(ptr[i])
//     {
//         printf("%c", ptr[i++]);
//     }
//     printf(" - ");
//     while(ptr[++i])
//         printf("%c", ptr[i]);
//     printf("\n");
// }



// int main()
// {
//     char    arr[] = "123456";

//     printf("%d\n", strlen(arr));
//     printf("%d\n", strlen(arr + 1));
//     printf("%d\n", strlen(arr + 5));
// }

// int main()
// {
//     int *a;

//     a = malloc(size)
// }