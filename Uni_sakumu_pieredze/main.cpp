#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

 

int main() {
    vector <int> firstNums;
    vector <int> secondNums;
    
    int x;
    while (1) {
        cout << "input x for first vector: ";
        cin >> x;
        if (x==0)
            break;
        if (count(begin(firstNums), end(firstNums), x) == 0)
            firstNums.push_back(x);
    }
    while (1) {
        cout << "input x for second vector: ";
        cin >> x;
        if (x==0)
            break;
        if (count(begin(secondNums), end(secondNums), x) == 0)
            secondNums.push_back(x);
    }
    cout<<"Unique first vector numbers: ";
    bool uniqueNum = true;
    
    for (auto n: firstNums){
        for (auto k: secondNums){
            if(n==k) uniqueNum = false;
        }
        if (uniqueNum == true) cout<<n<<" ";
        uniqueNum = true;
    }
    
    return 0;
}