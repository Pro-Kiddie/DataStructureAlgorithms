//Problem:https://nus.kattis.com/problems/faktor

//Read in the 2 numbers, no. of articles & desired impact factor 
//Find out the maximum number of citations required = no. of articles * desired impact factor
//Decrease max no by 1
//Divide by no. of articles and ceil() the result
//Check if result > (Impact Factor - 1), continue decrease max no if true
//Minimum no of citations required = max no + 1

#include <iostream>
#include <math.h>

int main(){
    int no_articles, impact_factor;
    int max_citations, min_citations;
    std::cin >> no_articles >> impact_factor;
    max_citations = no_articles * impact_factor;
    do{
        max_citations--;
    }while(std::ceil(max_citations/(double)no_articles) > (impact_factor-1));
    //When break out of the loop, min_citations will be just nice for impact factor to <= (desired_impact_factor-1)
    std::cout << ++max_citations << std::endl;
    return 0;
}

void test(){
    char** a = new char* [3];
}