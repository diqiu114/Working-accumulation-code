#ifndef MIX_C_CPP_H
#define MIX_C_CPP_H


#ifndef __cplusplus
#endif

#ifdef __cplusplus

class mix_c_cpp
{
private:
    /* data */
    

public:
    mix_c_cpp(/* args */);
    ~mix_c_cpp();
    int return_val();
    int val = 10;
};

extern "C" {
#endif
    
int get_val_from_cpp();
void InitCppObj();

#ifdef __cplusplus
}
#endif

#endif
