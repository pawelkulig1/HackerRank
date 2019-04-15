#include <iostream>
#include <string>


using namespace std;

// Complete the extraLongFactorials function below.
class BigInteger{
    std::string number;

public:
    BigInteger(std::string number) : number(number) {}
    BigInteger(): number("0"){}
    BigInteger operator*(int);
    BigInteger operator+(BigInteger);
    BigInteger operator=(BigInteger);

    friend std::ostream& operator<<(std::ostream &stream, BigInteger &bi);

};

BigInteger BigInteger::operator+(const BigInteger bi2)
{
    std::string shorterContainer;
    std::string longerContainer;

    if(number.size() > bi2.number.size())
    {
        shorterContainer = bi2.number;
        longerContainer = number;    
    }
    else
    {
        shorterContainer = number;
        longerContainer = bi2.number;
    }

    for(int i=shorterContainer.size();i<longerContainer.size();i++)
    {
        shorterContainer = "0" + shorterContainer;
    }

    std::reverse(shorterContainer.begin(), shorterContainer.end());
    std::reverse(longerContainer.begin(), longerContainer.end());

    bool carry = false;
    std::string outNumber = "";

    for(int i=0;i<longerContainer.size();i++)
    {
        int smallSum = std::stoi(std::to_string(shorterContainer[i] - '0')) + 
            std::stoi(std::to_string(longerContainer[i] - '0')) + static_cast<int>(carry);
        carry = false;
        if(smallSum >= 10) carry = true;
        outNumber += std::to_string(smallSum % 10);
    }
    
    if(carry) outNumber+="1";
    std::reverse(outNumber.begin(), outNumber.end());
    BigInteger ret(outNumber);
    return ret;
}

BigInteger BigInteger::operator*(int num)
{
    //not so fast to calculate but fast to write - old cpu's way
    BigInteger ret;
    for(int i=0;i<num;i++)
    {
        ret = ret + (*this);
    }
    return ret;
}

BigInteger BigInteger::operator=(BigInteger bi2)
{
    this->number = bi2.number;
    return *this;
}

std::ostream& operator<<(std::ostream &stream, BigInteger &bi)
{
    stream << bi.number;
    return stream;
}

void extraLongFactorials(int n) {
    BigInteger bi("1");

    for(int i=2;i<=n;i++)
    {
        bi = bi * i;
    }
    std::cout<<bi<<std::endl;
}

int main()
{
    extraLongFactorials(280);
    return 0;
}

