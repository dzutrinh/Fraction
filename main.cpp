/*
Copyright 2018 Trinh D.D. Nguyen

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include "fraction.hpp"

using namespace std;

string msgPause = "\nPress ENTER to continue...";
string msgInvalidInput = "\nInvalid input.";
string msgToggle[2] = {"no ", "yes"};

class FractionTest
{
public:
    FractionTest();
    ~FractionTest();

private:
    void run();
    int menu();
    void input(CFraction & lhs, CFraction & rhs);
    void output(CFraction & lhs, CFraction &rhs, CFraction & result, char op);

    void add(CFraction & lhs, CFraction & rhs, CFraction & result);
    void sub(CFraction & lhs, CFraction & rhs, CFraction & result);
    void mul(CFraction & lhs, CFraction & rhs, CFraction & result);
    void div(CFraction & lhs, CFraction & rhs, CFraction & result);
    void reduce();

    // helpers
    void pause(std::string msg);
    void clearScreen();
};

FractionTest::FractionTest()
{
    CFraction::autoReduce = true;
    run();
}

FractionTest::~FractionTest()
{
}

void FractionTest::run()
{
    int         choice;
    bool        done = false;
    CFraction   lhs, rhs, result;

    do {
        choice = menu();
        switch(choice)
        {
        case 1:
            add(lhs, rhs, result);
            break;
        case 2:
            sub(lhs, rhs, result);
            break;
        case 3:
            mul(lhs, rhs, result);
            break;
        case 4:
            div(lhs, rhs, result);
            break;
        case 5:
            reduce();
            break;
        case 6:
            CFraction::autoReduce = !CFraction::autoReduce;
            break;
        case 0:
            done = true;
            break;
        default:
            pause(msgInvalidInput);
            break;
        }
    } while(!done);
}

void FractionTest::pause(std::string msg)
{
    cout << msg << endl;
    cin.ignore();
    cin.get();
}

int FractionTest::menu()
{
    int choice;
    clearScreen();
    cout << "+------------------------+" << endl;
    cout << "|                        |" << endl;
    cout << "| C + +  F R A C T I O N |" << endl;
    cout << "|                        |" << endl;
    cout << "+-----[ MAIN MENU ]------+" << endl;
    cout << "| [1] Addition           |" << endl;
    cout << "| [2] Subtraction        |" << endl;
    cout << "| [3] Multiplication     |" << endl;
    cout << "| [4] Division           |" << endl;
    cout << "| [5] Reduction          |" << endl;
    cout << "+------------------------+" << endl;
    cout << "| [6] Auto reduce: " << msgToggle[CFraction::autoReduce] << "   |" << endl;
    cout << "+------------------------+" << endl;
    cout << "| [0] Exit               |" << endl;
    cout << "+------------------------+" << endl;
    cout << "Your choice: ";
    cin >> choice;
    cout << endl;
    return choice;
}

void FractionTest::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void FractionTest::input(CFraction & lhs, CFraction & rhs)
{
    cout << "Fraction A: "; cin >> lhs;
    cout << "Fraction B: "; cin >> rhs;
}

void FractionTest::output(CFraction & lhs, CFraction &rhs, CFraction & result, char op)
{
    if (CFraction::autoReduce)
    {
        cout << "A " << op << " B = ";
        cout << lhs << " " << op << " " << rhs << " = ";
        cout << result << endl;
    }
    else
    {
        cout << "A " << op << " B = ";
        cout << lhs << " " << op << " " << rhs << " = ";
        cout << result << " (" << result.reduce() << ")" << endl;
    }
}

void FractionTest::add(CFraction & lhs, CFraction &rhs, CFraction & result)
{
    input(lhs, rhs);
    result = lhs + rhs;
    output(lhs, rhs, result, '+');
    pause(msgPause);
}

void FractionTest::sub(CFraction & lhs, CFraction &rhs, CFraction & result)
{
    input(lhs, rhs);
    result = lhs - rhs;
    output(lhs, rhs, result, '-');
    pause(msgPause);
}

void FractionTest::mul(CFraction & lhs, CFraction &rhs, CFraction & result)
{
    input(lhs, rhs);
    result = lhs * rhs;
    output(lhs, rhs, result, '*');
    pause(msgPause);
}

void FractionTest::div(CFraction & lhs, CFraction &rhs, CFraction & result)
{
    input(lhs, rhs);
    result = lhs / rhs;
    output(lhs, rhs, result, '/');
    pause(msgPause);
}

void FractionTest::reduce()
{
    CFraction   f;
    cout << "Fraction: ";
    cin >> f;
    cout << "Result: " << f.reduce() << endl;
    pause(msgPause);
}

FractionTest    gApp;

int main() { return 0; }
