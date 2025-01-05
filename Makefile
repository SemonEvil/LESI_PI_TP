all: clean executable execute

executable: Menu.o openFuncionarios.o openEscolhas.o openEmenta.o MostrarRefeicao.o ListarUtentes.o ListarRefeicoes.o CalcularMediaCalorias.o TabelaEmenta.o main.o
	gcc -o cantina Menu.o openFuncionarios.o openEscolhas.o openEmenta.o MostrarRefeicao.o ListarUtentes.o ListarRefeicoes.o CalcularMediaCalorias.o TabelaEmenta.o main.o

Menu.o: 
	gcc -c Menu.c 

openFuncionarios.o:
	gcc -c openFuncionarios.c 

openEscolhas.o: 
	gcc -c openEscolhas.c 

openEmenta.o: 
	gcc -c openEmenta.c 

MostrarRefeicao.o:
	gcc -c MostrarRefeicao.c 

ListarUtentes.o:
	gcc -c ListarUtentes.c 

ListarRefeicoes.o: 
	gcc -c ListarRefeicoes.c 

CalcularMediaCalorias.o:
	gcc -c CalcularMediaCalorias.c 

TabelaEmenta.o: 
	gcc -c TabelaEmenta.c 

main.o: 
	gcc -c main.c 

execute: 
	./cantina

clean: 
	rm -f *.o cantina

