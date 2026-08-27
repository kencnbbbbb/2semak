#include <iostream>
#include <map>
using namespace std; 
int sum( const map <int, int>& container)
{
    int sum = 0;
    for (const auto& pair : container) {
        sum += pair.second;
    }
    return sum;
}
int keys( const map <int, int>& container)
{
    int keys = 0;
    for (const auto& pair : container) {
        keys += pair.first;
    }
    return keys;
}
int main(){
map<int,int> numbers = {
    {1,10},
    {2,20},
    {3,30}
};
cout << "Сумма значений " << sum(numbers) << endl;
cout << "Сумма ключей " << keys(numbers) << endl;


    return 0;
}