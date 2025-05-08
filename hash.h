#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;

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
        int num[28];
        int len = k.size();
        int temp = 0;

        // First translate each char in the string
        for (int i = 0; i < k.size(); i++) {
            num[i] = letterDigitToNumber(k[len-i-1]);
        }

        unsigned long long w[5] = {0};

        for (int i = 0; (i + 6) <= k.size(); i = i + 6) {
            int exp = 36;
            for (int j = 0; j < 6; j++) {
                if (j == 0) {
                    w[4 - i/6] += num[j+i];
                } else {
                    w[4 - i/6] += num[j+i] * exp;
                    exp = exp * 36;
                }
            }
        }

        if (len % 6 != 0) {
            temp = k.size()%6;
            // cout << temp << endl;
        }

        int exp = 36;
        for (int j = 0; j < temp; j++) {
            if (j == 0) {
                w[4 - len/6] += num[j + len-temp];
            } else {
                w[4 - len/6] += num[j + len-temp] * exp;
                exp = exp * 36;
            }
        }

        // check for final non-6 letters
        unsigned long long h = 0;
        for (int i = 0; i < 5; i++) {
            h += rValues[i] * w[i];
        }

        // cout << w[4] << endl;
        // cout << w[3] << endl;
        return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        int ascii = letter;
        // Uppercase char
        if (ascii >= 65 && ascii <= 90) {
            return ascii - 65;
        }
        // number
        else if (ascii >= 48 && ascii <= 57) {
            return ascii - 22;
        } else {
            return ascii - 97;
        }
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
