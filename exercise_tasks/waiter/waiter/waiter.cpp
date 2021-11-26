#include <iostream>
#include<stack>
#include<vector>


bool is_Prime(int num) {

    if (num == 0 || num == 1) {
        return false;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}


std::vector<int> getPrimes(std::vector<int>& primes, int q) {

    int i = 2;
    while (primes.size() < q) {

        if (is_Prime(i)) {
            primes.push_back(i);
        }
        i++;
    }
    return primes;
}


std::vector<int> waiter(std::vector<int> number, int q) {

    {
        std::vector<int> primes;
        getPrimes(primes, q);

        std::vector<int> answers;
        std::stack<int> a, b;

        for (int current : number)
        {
            a.push(current);
        }

        for (int i = 0; i < q; ++i)
        {
            std::stack<int> tempA;
            while (!a.empty())
            {
                if (a.top() % primes[i] == 0)
                {
                    b.push(a.top());
                }
                else
                {
                    tempA.push(a.top());
                }
                a.pop();
            }

            a = tempA;

            while (!b.empty())
            {
                answers.push_back(b.top());
                b.pop();
            }

            if (i == q - 1)
            {
                while (!a.empty())
                {
                    answers.push_back(a.top());
                    a.pop();
                }
            }
        }
        return answers;
    }
}


int main()
{
    
}

