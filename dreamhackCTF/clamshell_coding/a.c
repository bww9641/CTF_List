#include<stdio.h>

int func(int argc, char* argv[]) {
    int sum = 0;
    while (argc-- && argc > 1) {
        int val = 0;
        val = (argv[argc][0] - 0x30) * 10 + argv[argc][1] - 0x30;
        if (val % 3 == 0)
            sum += val;
        else
            sum += val * 2;
    }
    return sum % 100;
}

int main(int argc, char** argv)
{
    return func(argc, argv);
}