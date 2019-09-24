![逐飞LOGO](https://images.gitee.com/uploads/images/2019/0924/114256_eaf16bad_1699060.png "逐飞科技logo 中.png")
# 逐飞科技I.MX-RT1064开源库
#### 简介
本项目为逐飞科技基于恩智浦“IMXRT1064_SDK”制作的IMXRT1064高性能MCU(以下简称RT1064)开源库。简化了部分SDK库函数功能的使用步骤，便于使用RT1064参加竞赛以及进行产品开发。

#### 本开源库的优势
1.  **外置SDRAM加速：** 
- 本开源库将用户代码+中断函数+中断向量表在上电后自动加载到外置SDRAM。相较于官方库，可以实现更加迅速的中断响应及中断处理速度。极大地提升了运行速度。
2.  **优化TCM空间分配：** 
- 将DTCM的空间从默认的128KB提高到了448KB，可以提供更多的高性能TCM空间。便于保存更多更大的变量或数组。
3.  **指定代码运行位置：** 
- 提供了简单的方法以指定代码在不同的RAM内运行，当计算一些多而复杂的运算时，可以将代码放入ITCM内以获得最高的运行速度。具体可以参考开源库内的库例程。
4.  **支持快速GPIO与ROM API：** 
- 对快速GPIO提供了支持，快速GPIO最高能达到150M的IO翻转速率，以此实现更高的IO操作速率。提供了ROM API的支持，可以方便的操作片内的Flash以实现保存数据。

#### 环境准备
1.  **RT1064硬件环境：** 
- 推荐使用本公司RT1064核心板，[点击此处购买](https://item.taobao.com/item.htm?spm=a1z10.3-c.w4002-9998537997.49.4b7549ccjhU2eC&id=601759245205)，由于本开源库需要将用户代码+中断函数+中断向量表在上电后自动加载到外置SDRAM， **故不支持无外置SDRAM的核心板** 。
2.  **软件开发环境：** 
（IAR或MDK可任选其一）
- IAR 推荐使用版本：IAR Embedded Workbench for ARM V8.32.4。（以下简称IAR）
- MDK 推荐使用版本：MDK v5.24及以上。（5.26版本后加入了对DAP仿真器V2版本的支持，可以使用本公司DAP仿真器的WinUSB模式进行更高速的下载）
3.  **仿真器：** 
（DAP仿真器及J-Link仿真器可任选其一）
- DAP仿真器：推荐使用本公司DAP仿真器，双下载模式，可以在支持的环境下实现更高下载速度。
- J-Link仿真器：请确保您的J-Link仿真器硬件版本为V9或更高（不支持J-Link OB）。且J-Link驱动版本为V6.40或更高。

#### 使用说明

1.  **下载开源库：** 点击页面右侧的克隆/下载按钮，将工程文件保存到本地。您可以使用git克隆（Clone）或下载ZIP压缩包的方式来下载。推荐使用git将工程目录克隆到本地，这样可以使用git随时与我们的开源库保持同步。关于码云与git的使用教程可以参考以下链接 [https://gitee.com/help](https://gitee.com/help)。
2.  **打开工程：** 将下载好的工程文件夹打开（若下载的为ZIP文件，请先解压压缩包）。在打开工程前，请务必确保您的IDE满足环境准备章节的要求。否则可能出现打开工程时报错，提示丢失目录信息等问题。
- 若您使用的IDE为IAR，则工程文件保存在Project/IAR文件夹下。
- 若您使用的IDE为MDK，则工程文件保存在Project/MDK文件夹下。

#### 逐飞科技RT1064核心板
![逐飞科技RT1064核心板](https://images.gitee.com/uploads/images/2019/0924/114657_c8e12b59_1699060.jpeg "逐飞科技RT1064核心板.jpg")


