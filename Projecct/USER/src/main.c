/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.24
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


//整套推荐IO查看Projecct文件夹下的TXT文本



//打开新的工程或者工程移动了位置务必执行以下操作
//第一步 关闭上面所有打开的文件
//第二步 project  clean  等待下方进度条走完

//下载代码前请根据自己使用的下载器在工程里设置下载器为自己所使用的



#include "headfile.h"


int main(void)
{
	DisableGlobalIRQ();
    board_init();//务必保留，本函数用于初始化MPU 时钟 调试串口
    ips200_init();
    EnableGlobalIRQ(0);
    //修改显示屏 显示字符或者字符串的函数为void lcd_showstr(uint16 x,uint16 y,const int8 dat[]); 主要将存放字符的数组类型切换为const int8  TFT 1.14IPS 2.0ips oled全部都修改
    //修改1.14ips最上方备注
    //增加并口屏幕引脚选择的说明，只能选择快速GPIO支持的引脚
    //修改flash写入与读取函数的buf类型为uint32
    //增加flash操作函数的参数范围
    while (1)
    {
        
    }
}





