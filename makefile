
all: Bonusexe
    
Bonusexe: Bonusobj
	gcc -o p5 p5.o -L/usr/lib/x86_64-linux-gnu/ -lgsl -lgslcblas -lm
	del .\p5.o
    
Bonusobj: ./src/p5.c
	gcc -c -o p5.o ./src/p5.c -I/usr/include
     
clean:
	del .\p5.exe