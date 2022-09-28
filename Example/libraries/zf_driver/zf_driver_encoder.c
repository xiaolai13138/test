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
* �ļ�����          zf_driver_encoder
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

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "fsl_qtmr.h"
#include "zf_driver_gpio.h"

#include "zf_driver_encoder.h"

#define QTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_IpgClk)
#define QTIMER_PIN_CONF  SPEED_100MHZ | KEEPER_EN | DSE_R0_6 //����QTIMER����Ĭ������

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
// �������     ENCODER �ӿڻ�ȡ����������
// ����˵��     encoder_n       ENCODER ģ��� ���� zf_driver_encoder.h �� encoder_index_enum ö���嶨��
// ���ز���     int16           ��������ֵ
// ʹ��ʾ��     encoder_get_count(QTIMER1_ENCOEDER1);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
int16 encoder_get_count (encoder_index_enum encoder_n)
{
    uint8 qtimer_cha;
    qtimer_cha = (encoder_n % 2) * 2;//����Aͨ��
    return QTMR_GetCurrentTimerCount(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ENCODER ��ձ���������
// ����˵��     encoder_n       ENCODER ģ��� ���� zf_driver_encoder.h �� encoder_index_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     encoder_clear_count(QTIMER1_ENCOEDER1);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void encoder_clear_count (encoder_index_enum encoder_n)
{
    uint8 qtimer_cha;
    qtimer_cha = (encoder_n % 2) * 2;//����Aͨ��
    qtimer_index[encoder_n / 2]->CHANNEL[qtimer_cha].CNTR = 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ENCODER �ӿڳ�ʼ�� ����������ʹ��
// ����˵��     encoder_n       ENCODER ģ��� ���� zf_driver_encoder.h �� encoder_index_enum ö���嶨��
// ����˵��     ch1_pin         ENCODER ͨ�� 1 ���� zf_driver_encoder.h �� encoder_channel1_enum ö���嶨��
// ����˵��     ch2_pin         ENCODER ͨ�� 2 ���� zf_driver_encoder.h �� encoder_channel2_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     encoder_quad_init(QTIMER1_ENCOEDER1, QTIMER1_ENCOEDER1_CH1_C0, QTIMER1_ENCOEDER1_CH2_C1);
// ��ע��Ϣ     ʹ�õı������������������ſ���ʹ�ô˺����ӿ�
//              �������ν�� ������������������ �ı����� �鷳��ȷ���������ǲ������������������
//              ����ӿ�ֻ�ܸ�������������źŵı�������
//-------------------------------------------------------------------------------------------------------------------
void encoder_quad_init (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin)
{
    uint8 qtimer_cha;
    qtmr_config_t qtmrConfig;
    
    zf_assert(encoder_n == ((ch1_pin / 12) + (ch1_pin % 12 / 2) + 1));                          // ch1_pin ������ encoder_n ƥ��
    zf_assert(encoder_n == ((ch2_pin / 12) + (ch2_pin % 12 / 2) + 1));                          // ch2_pin ������ encoder_n ƥ��
    
    qtimer_iomuxc(encoder_n, ch1_pin, ch2_pin);

    qtimer_cha = (encoder_n % 2) * 2;//����Aͨ��
    
    QTMR_GetDefaultConfig(&qtmrConfig);
    qtmrConfig.primarySource = (qtmr_primary_count_source_t)(qtimer_cha);
    qtmrConfig.secondarySource = (qtmr_input_source_t)(qtimer_cha + 1);
    QTMR_Init(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha), &qtmrConfig);//��һ�γ�ʼ�����ڴ�ʱ��
    QTMR_Deinit(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha));           //��λ����
    QTMR_Init(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha), &qtmrConfig);//���³�ʼ��������ȷ�Ĳ���
    
    QTMR_StartTimer(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha), kQTMR_PriSrcRiseEdgeSecDir);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ENCODER �ӿڳ�ʼ�� �����������ʹ��
// ����˵��     encoder_n       ENCODER ģ��� ���� zf_driver_encoder.h �� encoder_index_enum ö���嶨��
// ����˵��     ch1_pin         ENCODER ͨ�� 1 ���� zf_driver_encoder.h �� encoder_channel1_enum ö���嶨��
// ����˵��     ch2_pin         ENCODER ͨ�� 2 ���� zf_driver_encoder.h �� encoder_channel2_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     encoder_dir_init(QTIMER1_ENCOEDER1, QTIMER1_ENCOEDER1_CH1_C0, QTIMER1_ENCOEDER1_CH2_C1);
// ��ע��Ϣ     ʹ�õı������Ǵ��������������ʽ�������ſ���ʹ�ô˺����ӿ�
//              ch1_pin ����Ϊ����������� ch2_pin ����Ϊ���������������
//              �˷�ʽ�� �ڳ��ַ�������ת������� �������򽫲�����ȫ�ɿ���
//              ֻ�ж�ȡʱ�̵� ch2_pin �ĵ�ƽ������������ֵ����������
//              ͬʱ ch1_pin ֻ��ѡ�� CH1 ͨ��������
//-------------------------------------------------------------------------------------------------------------------
void encoder_dir_init (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin)
{
    // RT1064��Ƭ�������������뷽����������ֱ��붼֧�֣����ʹ��ͬһ�������ӿڽ��вɼ�
    encoder_quad_init(encoder_n, ch1_pin, ch2_pin);
}
