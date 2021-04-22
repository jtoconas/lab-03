//
// Laboratorio 3 -- Ejercicio 1
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  // para el open
#include <sys/stat.h>   // para el open
#include <fcntl.h>      // para el open
#include <string.h>     // para el strlen()
#include <unistd.h>     // para el fork, para el write
#include <sys/wait.h>   // para el waitpid

#define MAX_LONG 100

int main(int argc, char* argv[])
{    
    int fd;
    int h;
 
    // 1° abrir archivo en modo append, crearlo con permisos 0644 si no existe
    fd = open(argv[1], O_CREAT | O_APPEND | O_WRONLY, 0644);
    if(fd < 0){
        perror("Error al intentar abrir el archivo:");
        exit(EXIT_FAILURE);
    }    
    
    // 2° creamos el hijo
    h = fork();
    if(h == 0) {                                // si es el hijo
        char msjHijo[MAX_LONG] = "Hijo: ";
        strcat(msjHijo, argv[3]);
        strcat(msjHijo, "\n");
        write(fd, msjHijo, (int )strlen(msjHijo));
    }    
                                                
    else
        {                       // es el padre
            wait(NULL);         // espera a que el hijo termine. No se le pasa wstatus
            char msjPadre[MAX_LONG] = "Padre: ";
            strcat(msjPadre, argv[2]);
            strcat(msjPadre, "\n");
            write(fd, msjPadre, (int ) strlen(msjPadre));   
        }

    // ambos cierran el archivo
    close(fd);

    exit(EXIT_SUCCESS);
}