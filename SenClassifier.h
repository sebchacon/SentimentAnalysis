#include "DSString.h"
#include <map>
#include <vector> 
#include <cstdio>
#include <fstream>
using std::vector;
using std::map;

class SenClassifier{

public:
    SenClassifier();
    SenClassifier(const SenClassifier &) = default;
    ~SenClassifier() = default;

    void train(char*);
    void predict(char*);
    void tokenize(DSString &);
    void evaluatePrediction(char*);
    void writeFile(std:: ostream &, int);

private:
    double prediction = 0;
    map<DSString, int> theMap;
    vector<DSString> words;
    vector<double> scores;
    vector<DSString> tweets;
    vector<int> sents;

};
