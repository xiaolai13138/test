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
* �ļ�����          main
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

#include "zf_common_headfile.h"
#include "fsl_ocotp.h"

// ���µĹ��̻��߹����ƶ���λ�����ִ�����²���
// ��һ�� �ر��������д򿪵��ļ�
// �ڶ��� project->clean  �ȴ��·�����������

// *************************** ����Ӳ������˵�� ***************************
// ʹ����ɿƼ� CMSIS-DAP | ARM ��������������
//      ֱ�ӽ���������ȷ�����ں��İ�ĵ������ؽӿڼ���
// 
// ʹ�� USB-TTL ģ������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      USB-TTL-RX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_TX_PIN �궨������� Ĭ�� A9
//      USB-TTL-TX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_RX_PIN �궨������� Ĭ�� A10
//      USB-TTL-GND         ���İ��Դ�� GND
//      USB-TTL-3V3         ���İ� 3V3 ��Դ



// *************************** ���̲���˵�� ***************************
// ע�����ǲ��ɻָ��Ĳ��������������
// ע�����ǲ��ɻָ��Ĳ��������������
// ע�����ǲ��ɻָ��Ĳ��������������
// 
// ʹ�ñ����̿���ֱ����дRT1064��Ƭ�ڱ���˿
// ͨ����д����˿֮�󣬺��İ�����ʱ����Ҫʹ���ⲿ��boot_cfg���ţ�ֱ��ʹ��Ƭ�ڵı���˿״̬����������
// ͨ�������ķ��������������Ϊʹ����boot_cfg���ţ����³����ں�����ʱ�����˴���Ĳ������²����������⡣
//
// 1.���İ���¼��ɱ����̣�����ʹ�ú��İ���������������� USB-TTL ģ�飬�ڶϵ�������������
// 
// 2.���������������� USB-TTL ģ�����ӵ��ԣ�����ϵ�
// 
// 3.������ʹ�ô������ִ򿪶�Ӧ�Ĵ��ڣ����ڲ�����Ϊ zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨�� Ĭ�� 115200�����İ尴�¸�λ����
// 
// 4.�����ڴ��������Ͽ������´�����Ϣ��
//    6000000
//    OCOTP Write operation success!



#define EXAMPLE_OCOTP_FREQ_HZ (CLOCK_GetFreq(kCLOCK_IpgClk))
#define EXAMPLE_OCOTP_FUSE_MAP_ADDRESS 0x06
#define EXAMPLE_OCOTP_FUSE_WRITE_VALUE 0x18

uint8  burn_success;
uint32 fuse_value;

int main(void)
{
    uint32 version;
    
    clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
    debug_init();                   // ���Զ˿ڳ�ʼ��
    
    // �˴���д�û����� ���������ʼ�������

    // ��ʼ��GPIO B9 Ϊ��� Ĭ������͵�ƽ
    OCOTP_Init(OCOTP, EXAMPLE_OCOTP_FREQ_HZ);
	
	version = OCOTP_GetVersion(OCOTP);
	
	printf("%x\r\n",version);
	
	fuse_value = OCOTP_ReadFuseShadowRegister(OCOTP, 0x00); // ��ȡ��ǰ����˿��״̬

    // �˴���д�û����� ���������ʼ�������
    
    while(1)
    {
        //�˴���д��Ҫѭ��ִ�еĴ���
		if (0x00U == (OCOTP_LOCK_BOOT_CFG_MASK & OCOTP_ReadFuseShadowRegister(OCOTP, 0x00)))
		{
			if (kStatus_Success == OCOTP_WriteFuseShadowRegister(OCOTP, EXAMPLE_OCOTP_FUSE_MAP_ADDRESS, EXAMPLE_OCOTP_FUSE_WRITE_VALUE))
			{
				printf("OCOTP Write operation success!\r\n");
				burn_success = 1; // ��д�ɹ�
			}
			else
			{
				printf("OCOTP write operation failed. Access deny!\r\n");
				burn_success = 0; // ��дʧ��
			}
		}
		while(1);
    }
}


