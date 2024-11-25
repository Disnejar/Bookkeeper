#include <vector>
#include <chrono>

struct Operation
{
    time_t dateTime;


};

struct Transaction
{

};

struct Account
{
    char* name;

    std::vector<Transaction*> transactions;

    Account(char* name);

    int GetTotal();
};
