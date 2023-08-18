#include "cpp_run_main.h"
#include "rtthread.h"
#include "test_cpp.h"

cpp_run_main::cpp_run_main(/* args */)
{
}

cpp_run_main::~cpp_run_main()
{
}


int CppRunMianInit(void)
{
    rt_kprintf("cpp run mian ==== init\r\n");
    return 0;
}


void CppRunMian(void* info)
{
    rt_kprintf("cpp run mian ==== run\r\n");
    
    test_cpp test_cpp_obj;

    rt_kprintf("now val:%d\r\n", test_cpp_obj.get_val());

    test_cpp_obj.change_val();

    rt_kprintf("now val:%d\r\n", test_cpp_obj.get_val());

    test_cpp_obj.print();
    while(1){
        rt_thread_mdelay(10);
    }
}
