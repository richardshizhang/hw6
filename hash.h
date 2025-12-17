#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5];
        HASH_INDEX_T arr[28];
        int start = 28-k.length();
        for (int i = 0; i< 28; i++){
            if (i < start){
                arr[i] = 0;
            }
            else{
                arr[i] = letterDigitToNumber(k[i-start]);
            }
        }
        //manually doing w[0] because it's 4 long instead of 6 long
        unsigned long long output = arr[0];
        for (int j = 1; j<4; j++){
                output *= 36;
                output += arr[j];
            }
            w[0] = output;
        for (int m = 1; m<5; m++){       
            int start_index = m*6-2;     
            output = arr[start_index];
            for (int j = start_index+1; j<start_index+6; j++){
                output *= 36;
                output += arr[j];
            }
            w[m] = output;
        }
        HASH_INDEX_T res = 0;
        for (int i = 0; i<5; i++){
            res += rValues[i]*w[i];
        }
        return res;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'a' && letter <= 'z'){
            return 0 + (letter - 'a');
        }
        if (letter >= 'A' && letter <= 'Z'){// to lower case
            return 0 + (letter - 'A');
        }
        if (letter >= '0' && letter <= '9'){
            return 26 + (letter - '0');
        }
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
