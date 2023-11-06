#include "SenClassifier.h"
#include <iostream>
SenClassifier::SenClassifier() // initializing our vector words and prediction to 0
{
    double prediction = 0;
    vector<DSString> words;
}
void SenClassifier::train(char *trainingFile)
{

    // char filename[] = trainingFile;
    char filename[] = "data/train_dataset_20k.csv";
    FILE *stream;
    char buffer[1000];
    stream = fopen(filename, "r");

    int first = 0; // next 7 lines get rid of the first line in training file
    while (fgets(buffer, sizeof(buffer), stream) != NULL)
    {
        ++first;
        if (first == 1)
            break;
    }

    size_t tweetCount = 1; // establish count to print updates 25,50,75, and 100 reading

    while (fgets(buffer, sizeof(buffer), stream) != NULL) // while not eof
    {

        if (tweetCount == 5000)
        {
            std::cout << std::endl
                      << "Reading tweets...25% finished" << std::endl;
        }
        if (tweetCount == 10000)
        {
            std::cout << "Reading tweets...50% finished" << std::endl;
        }
        if (tweetCount == 15000)
        {
            std::cout << "Reading tweets...75% finished" << std::endl;
        }

        DSString line(buffer);                     // convert our line to a dsstring
        int sent = line[0] - 48;                   // get sentiment value from first index
        DSString stringID = line.substring(2, 10); // get tweet ID
        // std::cout << stringID << std::endl;

        size_t begin = 0; // run a loop with to size_t's to get the index that our tweet starts at
        size_t comma = 0;
        while (comma != 5)
        {
            if (buffer[begin] == ',')
                ++comma;
            ++begin;
        }

        size_t tweetSize = line.getLength() - begin;       // get length of tweet so we can break it down
        DSString tweet = line.substring(begin, tweetSize); // break up line to just our tweet
        std::cout << tweet << std::endl;

        tokenize(tweet); // take out special characters and lowercase all letters to get every word to same base, fill vector with tokenized words
        size_t count = 0;

        for (auto word : words) // loop through vector and store in map
        {

            if (theMap.find(word) == theMap.end()) // if word is not found in map, make a new key that stores sent 1 or -1
            {
                if (sent == 4)
                    theMap[word] = 1;
                if (sent == 0)
                    theMap[word] = -1;
            }
            else // if word is found, ++ or -- based on sent found from index 0
            {
                if (sent == 4)
                    theMap[word] += 1;
                if (sent == 0)
                    theMap[word] -= 1;
            }
        }
        words.clear();   // clear vector for next line
        tweetCount += 1; // we have now read one more tweet
        // std::cout << tweet << std::endl;
    }
    std::cout << "Reading tweets...finished" << std::endl;

    fclose(stream); // close stream

    // std::map<DSString, int>::iterator it = theMap.begin();

    // while (it != theMap.end())
    // {

    //     std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;

    //     ++it;
    // }
}

void SenClassifier::predict(char *testingFile)
{

    char filename[] = "data/test_dataset_10k.csv"; // open test file to predict, same lines as before
    FILE *stream;
    char buffer[1000];
    stream = fopen(filename, "r");

    int first = 0;
    while (fgets(buffer, sizeof(buffer), stream) != NULL)
    {
        ++first;
        if (first == 1)
            break;
    }

    size_t tweetCount = 1;

    while (fgets(buffer, sizeof(buffer), stream) != NULL)
    {
        size_t begin = 0;
        size_t comma = 0;

        while (comma != 5)
        {
            if (buffer[begin] == ',')
                ++comma;
            ++begin;
        }
        ++begin;

        DSString line(buffer);
        size_t tweetSize = line.getLength() - begin;
        DSString tweet = line.substring(begin, tweetSize);
        DSString id = line.substring(0, 10);

        // tokenize(tweet);
        size_t count = 0;

        int indPrediction = 0; // sent for tweet

        for (auto word : words)
        {
            if (theMap.find(word) == theMap.end()) // if word is not found then ignore
                continue;
            else
                indPrediction += theMap[word]; // if word is found, add it to sent
        }

        double tweetScore = indPrediction / words.size(); // calculate prediction score for sent
        if (tweetScore > 0)
            tweetScore = 4;
        if (tweetScore < 0)
            tweetScore = 0;
        scores.push_back(tweetScore); // add tweet score and tweetID to vector for output file
        tweets.push_back(id);
    }
    fclose(stream); // close stream
}

void SenClassifier::tokenize(DSString &original)
{

    DSString tweet = original; // take in originak tweet
    // std::cout<< tweet << std::endl;
    tweet.cleanString(); // clean the tweet from uppcase and special characters
    // std::cout<< tweet << std::endl;

    size_t start = 0;
    for (size_t i = 0; i < tweet.getLength(); ++i)
    {

        // DSString blank;
        if (tweet[i] == ' ') // loop till sentence has a space (word is over when space)
        {
            size_t end = i - start;                      // find index when word ends for length
            DSString blank(tweet.substring(start, end)); //= tweet.substring(start, end); //substring tweet
            // std::cout<< blank << std::endl;
            DSString space(" ");
            DSString none("");
            if ((blank == space) || (blank == none))
            { // if string is empty/null then dont add it
                start = i + 1;
            }
            else
            {
                words.push_back(blank); // add word to vector
                start = i + 1;
            }
        }
    }
    DSString last(""); // my loop above would not take in last word so I manually do it here
    size_t end = tweet.getLength();
    last = tweet.substring(start, end);
    words.push_back(last); // add last word

    //    std::cout<< "check substrings: " << std::endl;
    //    for(size_t i = 0; i < words.size(); ++i){
    //        std::cout << "word number " << i << ":" << words.at(i) << std::endl;
    //    }
}

void SenClassifier::evaluatePrediction(char *answerKey)
{

    char filename2[] = "data/test_dataset_sentiment_10k.csv"; // open our answer key file
    FILE *stream2;
    char buffer[1000];
    stream2 = fopen(filename2, "r");
    int first = 0;
    while (fgets(buffer, sizeof(buffer), stream2) != NULL)
    {
        ++first;
        if (first == 1)
            break;
    }

    while (fgets(buffer, sizeof(buffer), stream2) != NULL) // while file ! eof, store sent scores in vector
    {
        DSString line(buffer);
        int sent = int(line[0]);
        sents.push_back(sent);
    }

    int correctTweets = 0; // loop through predictions and actual scores to see correctness
    for (size_t i = 0; i < sents.size(); ++i)
        if (sents.at(i) == scores.at(i))
            ++correctTweets;

    prediction = correctTweets / sents.size(); // calculate final prediction
    // std::cout<< prediction << std::endl;

    std::ofstream myfile; // write out my ouput files
    // CStringA output = T2A(DSString);
    myfile.open("results.csv", std::ofstream::out);
    for (size_t i = 0; i < tweets.size(); i++)
    {
        myfile << scores[i] << ", " << tweets[i] << "\0";
    }
    myfile.close();

    myfile.open("accuracy.csv", std::ofstream::out);
    myfile << prediction << "\0";

    for (size_t i = 0; i < tweets.size(); i++)
    {
        myfile << scores[i] << ", " << tweets[i] << "\0";
    }
    myfile.close();
}

void SenClassifier::writeFile(std::ostream &outputFile, int choice)
{
    if (choice == 1)
    {
        // outputFile.open(1st file )
        for (size_t i = 0; i < scores.size(); ++i)
        {
            // ouputFile
        }
        // ouputFile.close(1st file)
    }
    if (choice == 2)
    {
    }
}
