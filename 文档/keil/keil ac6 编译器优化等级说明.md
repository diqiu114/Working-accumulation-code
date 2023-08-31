Arm C/C++ (AC6) Compiler
Options dialog for ARM Compiler 6.

Language / Code Generation
Execute-only Code

Generates execute-only code, and prevents the compiler from generating any data accesses to code sections. Sets the compiler control string -mexecute-only.

Optimization

Control compiler code optimization. Sets the compiler control string -Onum|string.

<default> — is the uVision default setting. Uses the default compiler level, or the setting from the uVision target or parent group. No compiler control string is set.

<默认值>-是uVision默认设置。使用默认编译器级别，或uVision目标或父组中的设置。未设置编译器控制字符串。

-O0 — is the compiler default level. Turns off most optimizations, except some simple source transformations. Using -O0 results in a faster compilation and build time, but produces slower code than the other optimization levels. Code size and stack usage are also significantly higher.

-O0是编译器默认级别。关闭大多数优化，但一些简单的源代码转换除外。使用-00可以加快编译和构建速度，但生成的代码比其他优化级别慢。代码大小和堆栈使用率也明显较高。

-O1 — restricted optimization. This optimization level provides a good debug experience with better code quality than -O0. Also the stack usage is improved over -O0. Arm recommends this option for a good debug experience.

-O1限制优化。此优化级别提供了良好的调试体验，代码质量优于-00。此外，堆栈使用率在-00以上得到了提高。Arm建议使用此选项以获得良好的调试体验。

-O2 — high optimization. The debug view might be less satisfactory because the mapping of object code to source code is not always clear. The compiler might perform optimizations that cannot be described by debug information.

-02高度优化。调试视图可能不太令人满意，因为目标代码到源代码的映射并不总是清晰的。编译器可能会执行调试信息无法描述的优化。

-O3 — maximum optimization. This option typically gives a poor debug view.

-03最大优化。此选项通常提供较差的调试视图。

AC6新增优化等级

-Ofast — Enable all the optimizations from -O3 along with other aggressive optimizations that might violate strict compliance with language standards, including -ffast-math.

-Ofast支持-03中的所有优化，以及其他可能违反严格遵守语言标准的激进优化，包括-ffast math。

-Os balanced — Balances code size against code speed. By default, the compiler performs optimizations to increase performance, at the expense of a possible increase in image size. Sets the compiler control string -Os.

-操作系统平衡了代码大小和代码速度。默认情况下，编译器会执行优化以提高性能，但可能会增加图像大小。设置编译器控制字符串-Os。

-Oz image size — optimize for code size. By default, the compiler performs optimizations to increase performance, at the expense of a possible increase in image size. Sets the compiler control string -Oz

-Oz图像大小针对代码大小进行优化。默认情况下，编译器会执行优化以提高性能，但可能会增加图像大小。设置编译器控制字符串-Oz。

选择Use default compiler version 6




arm官方文档：https://developer.arm.com/documentation/101407/0537/Dialogs/Project/Options/Compiler/Arm-C-C----AC6--Compiler 作者：N-777 https://www.bilibili.com/read/cv17091112?from=search 出处：bilibili