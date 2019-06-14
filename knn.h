#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

vector<vector <float> > samples = vector<vector <float> >();
vector<vector <float> > tests = vector<vector <float> >();

void print(vector<int> vec, string separator) {
  for (int i = 0; i < vec.size(); i++) {
    cout << vec.at(i);
    if ((i + 1) < vec.size())
      cout << separator;
  }
  cout << endl;
}

struct Moda {
  int value, qtd;
};

bool compare(vector<float> v1, vector<float> v2) {
  return (v1.at(v1.size() - 1) < v2.at(v2.size() - 1));
}

bool moda_compare(Moda m1, Moda m2) {
  return (m1.qtd > m2.qtd);
}

int knn(vector<float> test, vector<int> attr, int k) {
  float dist = 0, aux = 0;

  for (int i = 0; i < samples.size(); i++) {
    for (int j = 0, k = 0; j < attr.size(); j++) {
      k = attr.at(j);
      aux = samples.at(i).at(k) - test.at(k);
      dist += pow(aux, 2);
    }
    dist = sqrt(dist);
    samples.at(i).push_back(dist);
    dist = 0;
  }

  sort(samples.begin(), samples.end(), compare);

  vector<Moda> moda = vector<Moda>();

  for (int i = 0, currentClass = 0, flag = 0, positionClass = samples.at(0).size() - 2; i < k; i++, flag = 0) {
    currentClass = static_cast<int>(samples.at(i).at(positionClass));

    for (int j = 0; j < moda.size(); j++) {

      if (static_cast<int>(moda.at(j).value) == currentClass) {
        moda.at(j).qtd++;
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      moda.push_back({ currentClass, 1 });
    }
  }

  sort(moda.begin(), moda.end(), moda_compare);
  // Exibe as classes por quantidade
  // for (int i = 0; i < moda.size(); i++) {
  //   cout << moda.at(i).value << "  |  " << moda.at(i).qtd << endl;
  // }

  return moda.at(0).value;
}

void parse_line(string line, vector<float>* parsedLine) {

  stringstream token(line);

  string intermediate;

  while(getline(token, intermediate, ' ')) {
    (*parsedLine).push_back(atof(intermediate.c_str()));
  }
} 

void get_sets(char* file_training, char* file_test) {
  ifstream file;
  string line;

  file.open(file_training, ios::in);

  if (!file.is_open()) {
    cout << "falha na abertura do arquivo" << endl;
    exit(1);
  }

  while (getline(file, line)) {
    vector<float> lineParsed = vector<float>();
    parse_line(line, &lineParsed); 

    samples.push_back(lineParsed);
  }
  file.close();
  // ------------------------------------------------------
  file.open(file_test, ios::in);

  if (!file.is_open()) {
    cout << "falha na abertura do arquivo" << endl;
    exit(1);
  }

  while (getline(file, line)) {
    vector<float> lineParsed = vector<float>();
    parse_line(line, &lineParsed);

    tests.push_back(lineParsed);
  }
}

double prepare_knn(vector<int>& attrs, int k) {
  vector<int> accuracy = vector<int>();

  vector<int> formated_attrs = vector<int>();

  for (int i = 0; i < attrs.size(); i++) {
    if (attrs.at(i))
      formated_attrs.push_back(i);
  }

  for(int i = 0, current = -1; i < tests.size(); i++, current = -1) {
    current = knn(tests.at(i), formated_attrs, k);

    accuracy.push_back((current == tests.at(i).at(tests.at(i).size() - 1)) ?
      1: 0
    );
    // Apaga as distancias
    for (int i = 0; i < samples.size(); i++) {
      samples.at(i).pop_back();
    }
  }

  int values = 0;

  for (int i = 0; i < accuracy.size(); i++) {
    values += accuracy.at(i);
  }
  int a = accuracy.size();
  double b = (values * 100);
  double c = (b / a);

  
  cout << "Accuracy = " << c << "%" << endl;
  return c;
}
