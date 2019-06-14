COMP=g++
ARQ=genetic_algorithm
TRAIN=arquivos/treinamento.txt
TEST=arquivos/teste.txt

all: run

run: comp
	./$(ARQ) $(TRAIN) $(TEST)

comp:
	$(COMP) $(ARQ).cpp -o $(ARQ) -std=c++11