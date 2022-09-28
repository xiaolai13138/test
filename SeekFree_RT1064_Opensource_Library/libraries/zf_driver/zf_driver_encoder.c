/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 即（RT1064DVL6A 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 RT1064DVL6A 开源库的一部分
* 
* RT1064DVL6A 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_driver_encoder
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "fsl_qtmr.h"
#include "zf_driver_gpio.h"

#include "zf_driver_encoder.h"

#define QTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_IpgClk)
#define QTIMER_PIN_CONF  SPEED_100MHZ | KEEPER_EN | DSE_R0_6 //配置QTIMER引脚默认配置

TMR_Type * qtimer_index[] = TMR_BASE_PTRS;

void qtimer_iomuxc(encoder_index_enum qtimern, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin)
{
    switch(qtimern)
    {
        case QTIMER1_ENCOEDER1:
        {
            if      (QTIMER1_ENCOEDER1_CH1_C0  == ch1_pin)  afio_init(C0 , GPIO_AF1, QTIMER_PIN_CONF);
            if      (QTIMER1_ENCOEDER1_CH2_C1  == ch2_pin)  afio_init(C1 , GPIO_AF1, QTIMER_PIN_CONF);
        }break;
        
        case QTIMER1_ENCOEDER2:
        {
            if      (QTIMER1_ENCOEDER2_CH1_C2  == ch1_pin)  afio_init(C2 , GPIO_AF1, QTIMER_PIN_CONF);
            if      (QTIMER1_ENCOEDER2_CH2_C24 == ch2_pin)  afio_init(C24, GPIO_AF1, QTIMER_PIN_CONF);
        }break;
        
        case QTIMER2_ENCOEDER1:
        {
            if      (QTIMER2_ENCOEDER1_CH1_C3  == ch1_pin)  afio_init(C3 , GPIO_AF1, QTIMER_PIN_CONF);
            if      (QTIMER2_ENCOEDER1_CH2_C4  == ch2_pin)  afio_init(C4 , GPIO_AF1, QTIMER_PIN_CONF);
        }break;
        
        case QTIMER2_ENCOEDER2:
        {
            if      (QTIMER2_ENCOEDER2_CH1_C5  == ch1_pin)  afio_init(C5 , GPIO_AF1, QTIMER_PIN_CONF);
            if      (QTIMER2_ENCOEDER2_CH2_C25 == ch2_pin)  afio_init(C25, GPIO_AF1, QTIMER_PIN_CONF);
        }break;

        case QTIMER3_ENCOEDER1:
        {
            if      (QTIMER3_ENCOEDER1_CH1_B16 == ch1_pin)  afio_init(B16, GPIO_AF1, QTIMER_PIN_CONF);
            else if (QTIMER3_ENCOEDER1_CH1_C6  == ch1_pin)  afio_init(C6 , GPIO_AF1, QTIMER_PIN_CONF);
            
            else if (QTIMER3_ENCOEDER1_CH2_B17 == ch2_pin)  afio_init(B17, GPIO_AF1, QTIMER_PIN_CONF);
            else if (QTIMER3_ENCOEDER1_CH2_C7  == ch2_pin)  afio_init(C7 , GPIO_AF1, QTIMER_PIN_CONF);
        }break;
        
        case QTIMER3_ENCOEDER2:
        {
            if      (QTIMER3_ENCOEDER2_CH1_B18 == ch1_pin)  afio_init(B18, GPIO_AF1, QTIMER_PIN_CONF);
            else if (QTIMER3_ENCOEDER2_CH1_C8  == ch1_pin)  afio_init(C8 , GPIO_AF1, QTIMER_PIN_CONF);
            
            if      (QTIMER3_ENCOEDER2_CH2_B19 == ch2_pin)  afio_init(B19, GPIO_AF1, QTIMER_PIN_CONF);
            else if (QTIMER3_ENCOEDER2_CH2_C26 == ch2_pin)  afio_init(C26, GPIO_AF1, QTIMER_PIN_CONF);
        }break;
        
        case QTIMER4_ENCOEDER1:
        {
            if      (QTIMER4_ENCOEDER1_CH1_C9  == ch1_pin)  afio_init(C9 , GPIO_AF1, QTIMER_PIN_CONF);
            if      (QTIMER4_ENCOEDER1_CH2_C10 == ch2_pin)  afio_init(C10, GPIO_AF1, QTIMER_PIN_CONF);
        }break;
        
        case QTIMER4_ENCOEDER2:
        {
            if      (QTIMER4_ENCOEDER2_CH1_C11 == ch1_pin)  afio_init(C11, GPIO_AF1, QTIMER_PIN_CONF);
            if      (QTIMER4_ENCOEDER2_CH2_C27 == ch2_pin)  afio_init(C27, GPIO_AF1, QTIMER_PIN_CONF);
        }break;
        
        default: zf_assert(0);break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ENCODER 接口获取编码器计数
// 参数说明     encoder_n       ENCODER 模块号 参照 zf_driver_encoder.h 内 encoder_index_enum 枚举体定义
// 返回参数     int16           编码器数值
// 使用示例     encoder_get_count(QTIMER1_ENCOEDER1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
int16 encoder_get_count (encoder_index_enum encoder_n)
{
    uint8 qtimer_cha;
    qtimer_cha = (encoder_n % 2) * 2;//计算A通道
    return QTMR_GetCurrentTimerCount(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ENCODER 清空编码器计数
// 参数说明     encoder_n       ENCODER 模块号 参照 zf_driver_encoder.h 内 encoder_index_enum 枚举体定义
// 返回参数     void
// 使用示例     encoder_clear_count(QTIMER1_ENCOEDER1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void encoder_clear_count (encoder_index_enum encoder_n)
{
    uint8 qtimer_cha;
    qtimer_cha = (encoder_n % 2) * 2;//计算A通道
    qtimer_index[encoder_n / 2]->CHANNEL[qtimer_cha].CNTR = 0;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ENCODER 接口初始化 正交编码器使用
// 参数说明     encoder_n       ENCODER 模块号 参照 zf_driver_encoder.h 内 encoder_index_enum 枚举体定义
// 参数说明     ch1_pin         ENCODER 通道 1 参照 zf_driver_encoder.h 内 encoder_channel1_enum 枚举体定义
// 参数说明     ch2_pin         ENCODER 通道 2 参照 zf_driver_encoder.h 内 encoder_channel2_enum 枚举体定义
// 返回参数     void
// 使用示例     encoder_quad_init(QTIMER1_ENCOEDER1, QTIMER1_ENCOEDER1_CH1_C0, QTIMER1_ENCOEDER1_CH2_C1);
// 备注信息     使用的编码器是正交编码器才可以使用此函数接口
//              如果是所谓的 “兼容正交编码器” 的编码器 麻烦先确定它到底是不是输出的正交编码器
//              这个接口只能给输出正交编码信号的编码器用
//-------------------------------------------------------------------------------------------------------------------
void encoder_quad_init (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin)
{
    uint8 qtimer_cha;
    qtmr_config_t qtmrConfig;
    
    zf_assert(encoder_n == ((ch1_pin / 12) + (ch1_pin % 12 / 2) + 1));                          // ch1_pin 必须与 encoder_n 匹配
    zf_assert(encoder_n == ((ch2_pin / 12) + (ch2_pin % 12 / 2) + 1));                          // ch2_pin 必须与 encoder_n 匹配
    
    qtimer_iomuxc(encoder_n, ch1_pin, ch2_pin);

    qtimer_cha = (encoder_n % 2) * 2;//计算A通道
    
    QTMR_GetDefaultConfig(&qtmrConfig);
    qtmrConfig.primarySource = (qtmr_primary_count_source_t)(qtimer_cha);
    qtmrConfig.secondarySource = (qtmr_input_source_t)(qtimer_cha + 1);
    QTMR_Init(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha), &qtmrConfig);//第一次初始化便于打开时钟
    QTMR_Deinit(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha));           //复位外设
    QTMR_Init(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha), &qtmrConfig);//重新初始化设置正确的参数
    
    QTMR_StartTimer(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha), kQTMR_PriSrcRiseEdgeSecDir);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ENCODER 接口初始化 带方向编码器使用
// 参数说明     encoder_n       ENCODER 模块号 参照 zf_driver_encoder.h 内 encoder_index_enum 枚举体定义
// 参数说明     ch1_pin         ENCODER 通道 1 参照 zf_driver_encoder.h 内 encoder_channel1_enum 枚举体定义
// 参数说明     ch2_pin         ENCODER 通道 2 参照 zf_driver_encoder.h 内 encoder_channel2_enum 枚举体定义
// 返回参数     void
// 使用示例     encoder_dir_init(QTIMER1_ENCOEDER1, QTIMER1_ENCOEDER1_CH1_C0, QTIMER1_ENCOEDER1_CH2_C1);
// 备注信息     使用的编码器是带方向输出的增量式编码器才可以使用此函数接口
//              ch1_pin 将作为脉冲输入计数 ch2_pin 将作为计数方向控制引脚
//              此方式下 在出现反复正反转的情况下 计数方向将不是完全可靠的
//              只有读取时刻的 ch2_pin 的电平决定整个计数值的正负符号
//              同时 ch1_pin 只能选择 CH1 通道的引脚
//-------------------------------------------------------------------------------------------------------------------
void encoder_dir_init (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin)
{
    // RT1064单片机对正交解码与方向输出的两种编码都支持，因此使用同一个函数接口进行采集
    encoder_quad_init(encoder_n, ch1_pin, ch2_pin);
}
