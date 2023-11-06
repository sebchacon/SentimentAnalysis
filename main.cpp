#include <iostream>
#include "SenClassifier.h"
#include "DSString.h"


int main(int argc, char* argv[])
{  

    char* trainingFile = argv[1];
    char* testingFile = argv[2];
    char* answerKey = argv[3];

    SenClassifier sen;
    //DSString test1("Abeerz,I'm hungry  .. I want some Pancakes and Honey !! Yum Yum");
    //sen.tokenize(test1);

    sen.train(trainingFile);
    //sen.predict(testingFile);
    //sen.evaluatePrediction(answerKey);


    return 0;
}