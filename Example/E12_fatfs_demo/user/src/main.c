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

// ���µĹ��̻��߹����ƶ���λ�����ִ�����²���
// ��һ�� �ر��������д򿪵��ļ�
// �ڶ��� project->clean  �ȴ��·�����������

// *************************** ����Ӳ������˵�� ***************************
// �鿴���İ�˵���飬�����İ��SD�����������������
//
// ʹ����ɿƼ� CMSIS-DAP | ARM ��������������
//      ֱ�ӽ���������ȷ�����ں��İ�ĵ������ؽӿڼ���
// 
// ʹ�� USB-TTL ģ������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      USB-TTL-RX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_TX_PIN �궨������� Ĭ�� B12
//      USB-TTL-TX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_RX_PIN �궨������� Ĭ�� B13
//      USB-TTL-GND         ���İ��Դ�� GND
//      USB-TTL-3V3         ���İ� 3V3 ��Դ

// *************************** ���̲���˵�� ***************************
// 1.���İ���¼��ɱ����̣�����ʹ�ú��İ���������������� USB-TTL ģ�飬�ڶϵ�������������
// 
// 2.���������������� USB-TTL ģ�����ӵ��ԣ�����ϵ�
// 
// 3.������ʹ�ô������ִ򿪶�Ӧ�Ĵ��ڣ����ڲ�����Ϊ zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨�� Ĭ�� 115200�����İ尴�¸�λ����
// 
// 4.�����ڴ��������Ͽ������´�����Ϣ��
//    FATFS �ļ�ϵͳʾ������

//    �����SD��

//    �����ļ�ϵͳ�С������������Ҫһ���Ƚϳ���ʱ��
// 
// 
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�


#define BUFFER_SIZE (512U)


static FATFS g_fileSystem; // �ļ�ϵͳ�ṹ�����
static FIL g_fileObject;   // �ļ��ṹ�����


// д�뻺����
AT_DTCM_SECTION_ALIGN(uint8_t g_bufferWrite[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_DESCRIPTOR_BUFFER_ALIGN_SIZE));

// ��ȡ������
AT_DTCM_SECTION_ALIGN(uint8_t g_bufferRead[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)], MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_DESCRIPTOR_BUFFER_ALIGN_SIZE));



//SD����Ҫʹ�õ������� B23 C30 D4 D12 D13 D14 D15 D16 D17
//������İ���������ϵ���ȷ����Щ�˿���û�������������裨ȷ�ϲ��뿪�ش���OFF ��û�в�  ������˷�ģ�顢2��IPS������Ļ������ת����ģ�飩
//�����п��ܵ��������޷�ʹ��


//��ʹ��ǰ�뽫���İ��J1 J3���ߺ���������
uint32 temp;
int main(void)
{
    clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
    debug_init();                   // ���Զ˿ڳ�ʼ��
    
    // �˴���д�û����� ���������ʼ�������

    // �˴���д�û����� ���������ʼ�������
    
    FRESULT error;
    DIR directory;                  // Ŀ¼�ṹ�����
    FILINFO fileInformation;
    UINT bytesWritten;
    UINT bytesRead;
    const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};
    volatile bool failedFlag = false;
    char ch = '0';
    BYTE work[FF_MAX_SS];
   
    printf("\r\nFATFS �ļ�ϵͳʾ������\r\n");
    
    printf("\r\n�����SD��\r\n");
	sdio_init();                    // ��ʼ��SDIO�ӿڲ��ȴ�SD������

    if (f_mount(&g_fileSystem, driverNumberBuffer, 0U))
    {
        printf("����ʧ��\r\n");
        return -1;
    }

#if (FF_FS_RPATH >= 2U)
    error = f_chdrive((char const *)&driverNumberBuffer[0U]);
    if (error)
    {
        printf("�ı�������ʧ��\r\n");
        return -1;
    }
#endif

#if FF_USE_MKFS
    printf("\r\n�����ļ�ϵͳ�С������������Ҫһ���Ƚϳ���ʱ��\r\n");
	// ��SD���ļ�ϵͳ�������֮�󣬾Ͳ���Ҫ��ÿ�ζ�������
	// ��Ϊÿ�δ������ǻ��SD����ʽ��һ��ģ�ÿ�ζ���ʽ�����׵��¿�����
    if (f_mkfs(driverNumberBuffer, 0U, work, sizeof(work)))
    {
        printf("�����ļ�ϵͳʧ��\r\n");
        return -1;
    }
#endif /* FF_USE_MKFS */
    
    printf("\r\n����Ŀ¼��\r\n");
    error = f_mkdir(_T("/dir_1"));
    if (error)
    {
        if (error == FR_EXIST)
        {
            printf("Ŀ¼�Ѵ���\r\n");
        }
        else
        {
            printf("Ŀ¼����ʧ��\r\n");
            return -1;
        }
    }

    printf("\r\n����һ���ļ��ڵ�ǰĿ¼��\r\n");
    error = f_open(&g_fileObject, _T("/dir_1/f_1.dat"), (FA_WRITE | FA_READ | FA_CREATE_ALWAYS));
    if (error)
    {
        if (error == FR_EXIST)
        {
            printf("�ļ��Ѵ���\r\n");
        }
        else
        {
            printf("�����ļ�ʧ��\r\n");
            return -1;
        }
    }

    printf("\r\n�ڵ�ǰĿ¼�У��ٴ���һ��Ŀ¼\r\n");
    error = f_mkdir(_T("/dir_1/dir_2"));
    if (error)
    {
        if (error == FR_EXIST)
        {
            printf("Ŀ¼�Դ���\r\n");
        }
        else
        {
            printf("Ŀ¼����ʧ��\r\n");
            return -1;
        }
    }

    printf("\r\n�г���Ŀ¼�е��ļ�\r\n");
    if (f_opendir(&directory, "/dir_1"))
    {
        printf("Ŀ¼��ʧ��\r\n");
        return -1;
    }

    for (;;)
    {
        error = f_readdir(&directory, &fileInformation);

        /* To the end. */
        if ((error != FR_OK) || (fileInformation.fname[0U] == 0U))
        {
            break;
        }
        if (fileInformation.fname[0] == '.')
        {
            continue;
        }
        if (fileInformation.fattrib & AM_DIR)
        {
            printf("�ļ��� : %s.\r\n", fileInformation.fname);
        }
        else
        {
            printf("��ͨ�ļ� : %s.\r\n", fileInformation.fname);
        }
    }

    memset(g_bufferWrite, 'a', sizeof(g_bufferWrite));
    g_bufferWrite[BUFFER_SIZE - 2U] = '\r';
    g_bufferWrite[BUFFER_SIZE - 1U] = '\n';

    printf("\r\nд��/��ȡ�ļ���ֱ����������\r\n");
    while (true)
    {
        if (failedFlag || (ch == 'q'))
        {
            break;
        }

        printf("\r\nд�����ݵ����洴�����ļ�\r\n");
        error = f_write(&g_fileObject, g_bufferWrite, sizeof(g_bufferWrite), &bytesWritten);
        if ((error) || (bytesWritten != sizeof(g_bufferWrite)))
        {
            printf("д���ļ�ʧ�� \r\n");
            failedFlag = true;
            continue;
        }

        /* Move the file pointer */
        if (f_lseek(&g_fileObject, 0U))
        {
            printf("�����ļ�ָ��λ��ʧ��\r\n");
            failedFlag = true;
            continue;
        }

        printf("��ȡ���洴�����ļ�\r\n");
        memset(g_bufferRead, 0U, sizeof(g_bufferRead));
        error = f_read(&g_fileObject, g_bufferRead, sizeof(g_bufferRead), &bytesRead);
        if ((error) || (bytesRead != sizeof(g_bufferRead)))
        {
            printf("��ȡ�ļ�ʧ��\r\n");
            failedFlag = true;
            continue;
        }

        printf("��ʼ�Ƚ�д�����ȡ�����Ƿ�һ��\r\n");
        if (memcmp(g_bufferWrite, g_bufferRead, sizeof(g_bufferWrite)))
        {
            printf("д�����ȡ���ݲ�һ��\r\n");
            failedFlag = true;
            continue;
        }
        printf("д�����ȡ����һ��\r\n");

        printf("\r\n����q�˳����� ���������ظ�ִ��д�����ȡ\r\n");
        ch = getchar();
        putchar(ch);
    }
    printf("\r\nʾ�����򲻻��ٽ��ж�ȡ����\r\n");

    if (f_close(&g_fileObject))
    {
        printf("\r\n�ر��ļ�ʧ��\r\n");
        return -1;
    }

    while (true)
    {
    }
}

// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б���
// 
// ����1��һֱ�ڴ����ļ�ϵͳ
//      ������̿��ܱȽϾã�����ȵ�30��
//
// ����2��һֱ��ʾ�����SD��
//      ����SD��û���
