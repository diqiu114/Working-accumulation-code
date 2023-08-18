#ifndef CPP_RUN_MAIN_H
#define CPP_RUN_MAIN_H

#ifdef __cplusplus
/*=========== CPP ============*/
class cpp_run_main
{
private:
    /* data */
public:
    cpp_run_main(/* args */);
    ~cpp_run_main();
};


extern "C" {
#endif

/*=========== C ============*/
int CppRunMianInit(void);
void CppRunMian(void* info);

#ifdef __cplusplus
}
#endif

#endif
