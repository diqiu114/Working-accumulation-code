#ifndef TEST_CPP_H
#define TEST_CPP_H

// #include "iostream"
// #include "string"

class test_cpp
{
private:
    /* data */
    int val = 10;
    struct test_struct
    {
        int num;
        char ch;
    };
    struct test_struct struct_val;

public:
    test_cpp(/* args */);
    ~test_cpp();

    void change_val();
    int get_val();

    void print(void);
};


#endif