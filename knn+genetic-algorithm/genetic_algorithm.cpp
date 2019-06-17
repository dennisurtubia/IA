#include <iostream>
#include <random>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include "./knn.h"

using namespace std;

struct gene {
  vector<int> chromosome;
  double accuracy;
};

void begin_population(vector<gene>& initial_population, int population_size, int number_of_attributes) { 
  srand(time(0));
  for(int i = 0; i < population_size; i++) {
    initial_population.push_back({vector<int>(), 0});
    for(int j = 0; j < number_of_attributes; j++) {
      initial_population.at(i).chromosome.push_back(rand() % 2);
    }
  }    
}

bool population_compare(gene p1, gene p2) {
  return p1.accuracy > p2.accuracy;
}

void selection(vector<gene>& population) {
  //método elitista, no qual mantém os 6 melhores genes com base na fitness
  sort(population.begin(), population.end(), population_compare);
}

void cross_over(vector<gene>& population, int population_size) {
  //mantém os 6 primeiros melhores e faz a mutação entre os 4 piores

  int slice_position = 0;
  for(int n = 0; n < 2; n++) {
    while (!slice_position)
      slice_position = (rand() % population_size);
    for(int i = 0; i < slice_position; i++) {
      swap(population.at(population.size() - 1 - (n * 2)).chromosome.at(i), population.at(population.size() - 2 - (n * 2)).chromosome.at(i));
    }
  }
}

void mutation(vector<gene>& population) {
  int bit = 0;
  
  for (int i = 6; i < population.size(); i++) {
    bit = (rand() % population.size());
    if ((rand() % 10) == (rand() % 10)) { 
      population.at(i).chromosome.at(bit) = !population.at(i).chromosome.at(bit);
    } 
  }
}

int main(int argc, char** argv) {
	if (argc < 3) {
    cout << "Parametros insuficientes" << endl;
    exit(0);
  }

  get_sets(argv[1], argv[2]);
  
  vector<gene> p;

	int population_size = 10;
  int number_of_attributes = 132;
  begin_population(p, population_size, number_of_attributes);
  gene best_gene = { vector<int>(number_of_attributes), 0 };
  
  for(int j = 0; j < 20; j++) {
    cout << "---------------------- Geration " << (j + 1) << " ----------------------" << endl;
    for(int i = 0; i < population_size; i++) {
      p.at(i).accuracy = (prepare_knn(p.at(i).chromosome, 1)); //população e k
      // cout << p.at(i).accuracy << endl;
      if (argc > 3 && !strcmp(argv[3], "--log")) {
        cout << "Acurracy of gene " << i << " is " << p.at(i).accuracy << "%" << endl;
      print(p.at(i).chromosome, "");
      }
            
      if (p.at(i).accuracy > best_gene.accuracy) {
        copy(p.at(i).chromosome.begin(), p.at(i).chromosome.end(), best_gene.chromosome.begin());
        best_gene.accuracy = p.at(i).accuracy;
      }
    }
    // cout << "-------------------" << endl;
    cout << "Best Acurracy " << " is " << best_gene.accuracy << "%" << endl;
    print(best_gene.chromosome, "");

    selection(p);
    cross_over(p, population_size);
    mutation(p);
  }
  return 0;
}