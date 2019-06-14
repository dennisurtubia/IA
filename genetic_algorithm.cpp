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
  sort(population.begin(), population.end(), population_compare);

  // selecionando os individuos de forma em que os 3 primeiros se repetem 6 vezes
  // e os dois piores se repetem 4
  copy(population.begin(), population.begin()+3, population.begin()+3);
  copy(population.begin()+8, population.end(), population.begin()+6);
  copy(population.begin()+8, population.end(), population.begin()+8);
}

void cross_over(vector<gene>& population, int population_size) {
  for(int n = 0; n < population.size() / 2; n++) {
    for(int i = 1; i < 10; i++) {
      swap(population.at(n).chromosome.at(i), population.at(population.size() - n - 1).chromosome.at(i));
    }

    for(int i = 40; i < 50; i++) {
      swap(population.at(n).chromosome.at(i), population.at(population.size() - n - 1).chromosome.at(i));
    }

    for(int i = 80; i < 90; i++) {
      swap(population.at(n).chromosome.at(i), population.at(population.size() - n - 1).chromosome.at(i));
    }
  }
}

void mutation(vector<gene>& population) {
  int bit = 0;
  
  for (int i = 0; i < population.size(); i++) {
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
  
  for(int j = 0; j < 6; j++) {
    cout << "---------------------- Geration " << (j + 1) << " ----------------------" << endl;
    for(int i = 0; i < population_size; i++) {
      p.at(i).accuracy = (prepare_knn(p.at(i).chromosome, 1)); //população e k
      // cout << p.at(i).accuracy << endl;
      print(p.at(i).chromosome, "");
    }
    // cout << "-------------------" << endl;

    selection(p);
    cross_over(p, population_size);
    mutation(p);
  }
  return 0;
}