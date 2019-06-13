#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

struct Moda {
  int value, qtd;
};

bool compare(vector<float> v1, vector<float> v2) {
  return (v1.at(v1.size() - 1) < v2.at(v2.size() - 1));
}

bool modaCompare(Moda m1, Moda m2) {
  return (m1.qtd < m2.qtd);
}

int knn(vector<vector <float> >& samples, vector<float> test, vector<int> attr, int k) {
  float dist = 0, aux = 0;

  for (int i = 0; i < samples.size(); i++) {
    for (int j = 0; j < attr.size(); j++) {
      aux = samples.at(i).at(j) - test.at(j);
      dist += pow(aux, 2);
    }

    dist = sqrt(dist);

    samples.at(i).push_back(dist);
  }

  sort(samples.begin(), samples.end(), compare);

  vector<Moda> moda = vector<Moda>();

  for (int i = 0, element = 0, flag = 0, size = samples.at(0).size() - 1; i < k; i++, flag = 0) {
    element = static_cast<int>(samples.at(i).at(size));
    for (int j = 0; j < moda.size(); j++) {

      if (moda.at(j).value == element) {
        moda.at(j).qtd++;
        flag = 1;
        break;
      }
    }

    if (flag == 0) {
      moda.push_back({ element, 1 });
    }
  }

  sort(moda.begin(), moda.end(), modaCompare);

  // Exibe as classes por quantidade
  // for (int i = 0; i < moda.size(); i++) {
  //   cout << moda.at(i).value << "  |  " << moda.at(i).qtd << endl;
  // }

  return moda.at(0).value;
}

void parseLine(string line, vector<float>* parsedLine) {

  stringstream token(line);

  string intermediate;

  while(getline(token, intermediate, ' ')) {
    (*parsedLine).push_back(atof(intermediate.c_str()));
  }

} 

void getSamples(char* file, vector<vector <float> >* samples) {
  ifstream train;
  string line;

  train.open(file, ios::in);
  
  if (!train.is_open()) {
    cout << "falha na abertura do arquivo" << endl;
    exit(1);
  }


  while (getline(train, line)) {
    vector<float> lineParsed = vector<float>();
     parseLine(line, &lineParsed);

    (*samples).push_back(lineParsed);

  }
}

int main(int argc, char** argv) {
  if (argc < 3) {
    cout << "Parametros insuficientes" << endl;
    exit(0);
  }
  vector<vector <float> > samples = vector<vector <float> >();
  getSamples(argv[1], &samples);

  vector<vector <float> > tests = vector<vector <float> >();
  getSamples(argv[2], &tests);

  vector<int> attrs;

  for (int i = 0; i < 132; i++) {
    attrs.push_back(i);
  }

  vector<int> accuracy = vector<int>();

  for(int i = 0, current = -1; i < tests.size(); i++, current = -1) {
    current = knn(samples, tests.at(i), attrs, 1);

    //cout << "element " << i << " is " << tests.at(i).at(tests.at(i).size() - 1) << " knn results " << current << endl;

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

  cout << "Acurracy = " << (values * 100 / accuracy.size()) << "%" << endl;

  return 0;
}
