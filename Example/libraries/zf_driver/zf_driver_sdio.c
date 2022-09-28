/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library ����RT1064DVL6A ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
* 
* ���ļ��� RT1064DVL6A ��Դ���һ����
* 
* RT1064DVL6A ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
* 
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
* 
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
* 
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          zf_driver_sdio
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/


#include "fsl_debug_console.h"
#include "fsl_sd_disk.h"
#include "fsl_sd.h"
#include "sdmmc_config.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "zf_driver_delay.h"

#include "zf_driver_sdio.h"

#define SDHC_PIN_CONF   SPEED_200MHZ | PULL_EN | PULLUP_47K | DSE_R0 | SRE_FAST

void sdhc_iomuxc(void)
{
    
    afio_init(B23, GPIO_AF5, SPEED_200MHZ | KEEPER_EN | PULLDOWN_100K | DSE_R0_6);  // ��Դʹ������
    afio_init(C30, GPIO_AF6, SDHC_PIN_CONF);                                        // ��ѹ�л�����
    afio_init(D4 , GPIO_AF5, SDHC_PIN_CONF);                                        // ����������
                                                                                    
    afio_init(D12, GPIO_AF0, SDHC_PIN_CONF);                                        // CMD
    afio_init(D13, GPIO_AF0, SDHC_PIN_CONF);                                        // CLK
    afio_init(D14, GPIO_AF0, SDHC_PIN_CONF);                                        // DATA0
    afio_init(D15, GPIO_AF0, SDHC_PIN_CONF);                                        // DATA1
    afio_init(D16, GPIO_AF0, SDHC_PIN_CONF);                                        // DATA2
    afio_init(D17, GPIO_AF0, SDHC_PIN_CONF);                                        // DATA3
}


//-------------------------------------------------------------------------------------------------------------------
// �������     sdio ��ʼ��SDHCʱ�Ӳ��ȴ�SD������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��                     sdio_init();
//-------------------------------------------------------------------------------------------------------------------
void sdio_init (void)
{
    
    sdhc_iomuxc();
    
    BOARD_SD_Config(&g_sd, NULL, BOARD_SDMMC_SD_HOST_IRQ_PRIORITY, NULL);

    if (SD_HostInit(&g_sd) != kStatus_Success)
    {
        zf_assert(0);
    }

    if (SD_PollingCardInsert(&g_sd, kSD_Inserted) == kStatus_Success)
    {
        SD_SetCardPower(&g_sd, false);
        SD_SetCardPower(&g_sd, true);
    }
    else
    {
        zf_assert(0);
    }
}
