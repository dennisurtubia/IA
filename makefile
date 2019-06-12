COMP=g++
ARQ=knn
TRAIN=arquivos/treinamento.txt
TEST=arquivos/teste.txt

all: run

run: comp
	./$(ARQ) $(TRAIN) $(TEST)

comp:
	$(COMP) $(ARQ).cpp -o $(ARQ) -std=c++11