#include <stdio.h>
#include <cs50.h>

#define AMEX "AMEX";
#define MASTERCARD "MASTERCARD";
#define VISA "VISA";
#define INVALID "INVALID";

string checkCard(long long number);

int main(void)
{
    // get card number from user
    long long cardNumber = get_long_long("Number: ");

    printf("%s\n", checkCard(cardNumber));

    return 0;
}

string checkCard(long long number)
{
    // get sum of numbers
    int sum = 0;
    bool multiply = false;
    int digits = 0;
    int firstNums;
    int tmpNumber;
    for (int i = 0; i < 16; i++)
    {
        digits++;
        int lastNum = number % 10;
        if (multiply)
        {
            int product = lastNum * 2;
            // if 2 digits, get first and second digit instead of the product
            if (product >= 10)
            {
                sum += product % 10;
                sum += product / 10;
            }
            else
            {
                sum += product;
            }
        }
        else
        {
            sum += lastNum;
        }
        multiply = !multiply;

        if (number >= 10)
        {
            tmpNumber = number;
            number /= 10;
        }
        else
        {
            firstNums = tmpNumber;
            break;
        }

    }

    // check if equal 0
    if (sum % 10 == 0 && digits >= 13)
    {
        if (((firstNums / 10 == 5) && (firstNums % 10 == 1 || firstNums % 10 == 2 || firstNums % 10 == 3 || firstNums % 10 == 4 || firstNums % 10 == 5 )) && digits == 16)
        {
            return MASTERCARD;
        } 
        else if ((firstNums == 37 || firstNums == 34) && digits == 15)
        {
            return AMEX;
        }
        else if ((firstNums / 10) == 4 && digits <= 16)
        {
            return VISA;
        }
        else
        {
            return INVALID;
        }
    }
    else 
    {
        return INVALID;
    }
}