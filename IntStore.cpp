// FILE: IntStore.cpp
//       Implementation file for the IntStore class
//       (See IntStore.h for documentation.)
// 

#include <iostream>
#include "IntStore.h"
using namespace std;

IntStore::IntStore()
{
    data[0] = 0;
}

bool IntStore::empty() const
{
    if (data[0])
        return false;
    else
        return true;
}

int IntStore::countDistinct() const
{
    int i = 0;
    for (int x = 0; x < MAX_SIZE; x++){
        if (data[x])
            i++;
    }
    return i;
}

int IntStore::countAll() const
{
    int i = 0;
    for (int x = 0; x < MAX_SIZE; x++){
        if (freq[x])
            i = i + freq[x];
    }
    return i;
}

int IntStore::countTarget(int target) const
{
    int found = 0;
    for (int x = 0; x < MAX_SIZE; x++){
        if(target == data[x])
            found = freq[x];
        return found;
    }
    return 0;
}

int IntStore::valAt(int pos) const
{
    return data[pos - 1];
}

int IntStore::freqAt(int pos) const
{
    return freq[pos - 1];
}

double IntStore::avg() const
{
    double dataTotal = 0,
           freqTotal = 0,
           avg = 0;
    for (int x = 0; x < MAX_SIZE; x++){
        dataTotal = dataTotal + (data[x] * freq[x]);
        freqTotal = freqTotal + freq[x];
    }
    avg = dataTotal/freqTotal;
    return avg;
}

void IntStore::reset()
{
    for (int x = 0; x < MAX_SIZE; x++){
        data[x]=0;
        freq[x]=0;
    }
}

bool IntStore::add(int item, int copies)
{
    for (int x = 0; x < MAX_SIZE; x++){
        if(data[x] == item){
            data[x] = item;
            freq[x] = freq[x] + copies;
            return true;
        }
        else if(data[x] == 0){
            data[x] = item;
            freq[x] = copies;
            return true;
        }
    }
    return false;
}

int IntStore::add(const IntStore& addend)
{
    int distinct = 0;
    int i = 0;
    for (int x = 0; x < MAX_SIZE; x++){
        for (i = 0; i < MAX_SIZE; i++){
            if (data[x] == 0 && addend.data[i] == 0) return distinct;
            else if (data[i] == addend.data[x]){
                freq[i] = freq[i] + addend.freq[x];
                i = 10;
                distinct++;
            }
            else if (data[i] == 0 && addend.data[x] != 0){
                data[i] = addend.data[x];
                freq[i] = addend.freq[x];
                i = 10;
                if(data[i] != 0) distinct++;
            }
            else if (addend.data[x] == 0) i = 10;
        }
        i++;
    }
    return distinct;
    
}

bool IntStore::remOne(int target)
{
    for (int x = 0; x < MAX_SIZE; x++){
        if(data[x] == target){
            freq[x] = freq[x] - 1;
            if(freq[x] == 0){
                for (int i = x; i < MAX_SIZE; i++){
                    if(data[i]){
                        data[i] = data[i+1];
                        freq[i] = freq[i+1];
                    }
                }
            }
            return true;
        }
    }
    return false;
}

int IntStore::remAll(int target)
{
    int total = 0;
    for (int x = 0; x < MAX_SIZE; x++){
        if(data[x] == target){
            total = freq[x];
            data[x] = 0;
            freq[x] = 0;
            for (int i = x+1; i < MAX_SIZE; i++){
                if(data[i]){
                    data[i-1] = data[i];
                    freq[i-1] = freq[i];
                    data[i] = 0;
                    freq[i] = 0;
                }
            }
        }
    }
    return total;
}

bool similar(const IntStore& is1, const IntStore& is2)
{
    int x = 1;
    while (x <= 10){
        int i = 1;
        while (i <= 10){
            if (i == 10 && is1.valAt(x) != is2.valAt(i)) return false;
            else if(is1.valAt(i) == is2.valAt(x)) i = 10;
            else if(i != 10 && is1.valAt(x) != is2.valAt(i)) i++;
            else
                return false;
            
            i++;
        }
        x++;
    }
    return true;
}
