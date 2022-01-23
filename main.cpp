#include <iostream>
#include <fstream>
#include <math.h>
#include <omp.h>
#include <vector>

char* dataPath = "../../data";
const char* isPrimeFile = "isPrime.txt";
const char* liarCounter = "liars.txt";

bool isDevider(int b, int c)
{
    return b % c == 0;
}

bool isOdd(int c)
{
    return !isDevider(c, 2);
}

//  Assumes that c is always even
int getHighestPowerOf2(int c) 
{
    return (c & (~(c - 1)));
}

//  Assumes that c is always a power of 2
int getExponentOf2(int c)
{
    return log(c) / log(2);
}

/*
*   We want to prepare our number n for court:  n = 2^m * d + 1
*   which is the equivalent to:                 (n - 1) / 2^m = d
*
*   Note: d will always be  odd
*/
void PrepareN(const int n, int& d, int& m)
{
    int c = getHighestPowerOf2(n - 1);
    d = (n - 1) / c;
    m = getExponentOf2(c);
}

//  Used to evaluate if a suspect is really prime or not
std::vector<int> getStarWitnesses(int n)
{
    if (n < 1373653)
    {
        return { 2, 3 };
    }
    else if(n < 9080191) 
    {
        return { 31, 73 };
    }
    else if (n < 25326001)
    {
        return { 2, 3, 5 };
    }
    else 
    {
        return { 2, 13, 23, 1662803 };
    }
}


bool TestWithness_MillerRabin(int n, int a)
{
    int d, m;
    PrepareN(n, d, m);
    int x = (int)pow(a, d) % n;
    if (x == 1 || x == n - 1)
    {
        return false;
    }
    for(int i = 0; i < m-1; i++)
    {
        x = (int)pow(x, 2) % n;
        if(x == n-1)
        {
            return false;
        }
    }
    return true;
}


bool isPrime(int n) 
{
    std::vector<int> starWithness = getStarWitnesses(n);
    for (auto it = starWithness.begin(); it != starWithness.end(); it++) 
    {
        if (TestWithness_MillerRabin(n, *it))
        {
            return false;
        }
    }
    return true;
}


int main () 
{
    std::ofstream myfile;
    myfile.open(strcat(dataPath, isPrimeFile));
    myfile << "2:1\n3:1\n";

    int initNumb = 5;
    std::numeric_limits<int>::max();
    for (int i = initNumb; i < 100; i += 2)
    {
       myfile << i + ":" + isPrime(i);
       myfile << "\n";
    }

    myfile.close();
    
    return 0;
}