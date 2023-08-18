#include "test_cpp.h"
#include "rtthread.h"

test_cpp::test_cpp(/* args */)
{

}

test_cpp::~test_cpp()
{
}

void test_cpp::change_val()
{
    val = 20;
}

int test_cpp::get_val()
{
    return val;
}

void test_cpp::print(void)
{
    // std::string str = "test";
    // char*p=(char*)str.data();
    // rt_kprintf("%s\r\n", p);

    rt_kprintf("sizeof %d\r\n", sizeof(this->struct_val));
}
