野火写的很好

https://doc.embedfire.com/mcu/stm32/f103zhinanzhe/std/zh/latest/book/SPI.html#id2



## 简述

spi是单主多从全双工的数据通信协议



## 注意点

spi中有CPOL/CPHA概念

CPOL(Clock Polarity)：时钟极性

CPHA(Clock Phase)：时钟相位



CPOA：决定时钟初始电平状态，0：低电平，1：高电平

CPHA：决定采样发生在时钟哪个边沿，0：基数边沿，1：偶数边沿