#include "mix_c_cpp.h"

static mix_c_cpp obj;

mix_c_cpp::mix_c_cpp(/* args */)
{

}

mix_c_cpp::~mix_c_cpp()
{

}


int mix_c_cpp::return_val()
{
    return val;
}

int get_val_from_cpp()
{
    return obj.val;
}

void InitCppObj()
{
    
}


