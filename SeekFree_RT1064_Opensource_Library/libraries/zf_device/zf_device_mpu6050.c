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
* �ļ�����          zf_device_mpu6050
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
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   ��� IIC ͨ�����Ŷ�Ӧ��ϵ
*                   SCL                 �鿴 zf_device_mpu6050.h �� MPU6050_SOFT_IIC_SCL �궨��
*                   SDA                 �鿴 zf_device_mpu6050.h �� MPU6050_SOFT_IIC_SDA �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ������������
*
*                   Ӳ�� IIC ͨ�����Ŷ�Ӧ��ϵ
*                   SCL                 �鿴 zf_device_mpu6050.h �� MPU6050_IIC_SCL �궨��
*                   SDA                 �鿴 zf_device_mpu6050.h �� MPU6050_IIC_SDA �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_delay.h"
#include "zf_driver_iic.h"
#include "zf_driver_soft_iic.h"

#include "zf_device_mpu6050.h"

int16 mpu_gyro_x = 0, mpu_gyro_y = 0, mpu_gyro_z = 0;                           // ��������������      gyro (������)
int16 mpu_acc_x = 0, mpu_acc_y = 0, mpu_acc_z = 0;                              // ������ٶȼ�����    acc (accelerometer ���ٶȼ�)

#if MPU6050_USE_SOFT_IIC
static soft_iic_info_struct mpu6050_iic_struct;

#define mpu6050_write_register(reg, data)       (soft_iic_write_8bit_register(&mpu6050_iic_struct, (reg), (data)))
#define mpu6050_read_register(reg)              (soft_iic_read_8bit_register(&mpu6050_iic_struct, (reg)))
#define mpu6050_read_registers(reg, data, len)  (soft_iic_read_8bit_registers(&mpu6050_iic_struct, (reg), (data), (len)))
#else
#define mpu6050_write_register(reg, data)       (iic_write_8bit_register(MPU6050_IIC, MPU6050_DEV_ADDR, (reg), (data)))
#define mpu6050_read_register(reg)              (iic_read_8bit_register(MPU6050_IIC, MPU6050_DEV_ADDR, (reg)))
#define mpu6050_read_registers(reg, data, len)  (iic_read_8bit_registers(MPU6050_IIC, MPU6050_DEV_ADDR, (reg), (data), (len)))
#endif

//-------------------------------------------------------------------------------------------------------------------
// �������     MPU6050 �Լ�
// ����˵��     void
// ���ز���     uint8           1-�Լ�ʧ�� 0-�Լ�ɹ�
// ʹ��ʾ��     if(mpu6050_self1_check())
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8 mpu6050_self1_check (void)
{
    uint8 dat = 0, return_state = 0;
    uint16 timeout_count = 0;

    mpu6050_write_register(PWR_MGMT_1, 0x00);                                   // �������״̬
    mpu6050_write_register(SMPLRT_DIV, 0x07);                                   // 125HZ������
    while(0x07 != dat)
    {
        if(timeout_count ++ > MPU6050_TIMEOUT_COUNT)
        {
            return_state =  1;
            break;
        }
        dat = mpu6050_read_register(SMPLRT_DIV);
        system_delay_ms(10);
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ MPU6050 ���ٶȼ�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     mpu6050_get_acc();                              // ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void mpu6050_get_acc (void)
{
    uint8 dat[6];

    mpu6050_read_registers(ACCEL_XOUT_H, dat, 6);  
    mpu_acc_x = (int16)(((uint16)dat[0] << 8 | dat[1]));
    mpu_acc_y = (int16)(((uint16)dat[2] << 8 | dat[3]));
    mpu_acc_z = (int16)(((uint16)dat[4] << 8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ MPU6050 ����������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     mpu6050_get_gyro();                             // ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void mpu6050_get_gyro (void)
{
    uint8 dat[6];

    mpu6050_read_registers(GYRO_XOUT_H, dat, 6);  
    mpu_gyro_x = (int16)(((uint16)dat[0] << 8 | dat[1]));
    mpu_gyro_y = (int16)(((uint16)dat[2] << 8 | dat[3]));
    mpu_gyro_z = (int16)(((uint16)dat[4] << 8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʼ�� MPU6050
// ����˵��     void
// ���ز���     uint8           1-��ʼ��ʧ�� 0-��ʼ���ɹ�
// ʹ��ʾ��     mpu6050_init();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 mpu6050_init (void)
{
    uint8 return_state = 0;
#if MPU6050_USE_SOFT_IIC
    soft_iic_init(&mpu6050_iic_struct, MPU6050_DEV_ADDR, MPU6050_SOFT_IIC_DELAY, MPU6050_SCL_PIN, MPU6050_SDA_PIN);
#else
    iic_init(MPU6050_IIC, MPU6050_DEV_ADDR, MPU6050_IIC_SPEED, MPU6050_SCL_PIN, MPU6050_SDA_PIN);
#endif
    system_delay_ms(100);                                                       // �ϵ���ʱ

    do
    {
        if(mpu6050_self1_check())
        {
            // �������������˶�����Ϣ ������ʾ����λ��������
            // ��ô���� MPU6050 �Լ������ʱ�˳���
            // ���һ�½�����û������ ���û������ܾ��ǻ���
            zf_log(0, "MPU6050 self check error.");
            return_state = 1;
            break;
        }
        mpu6050_write_register(PWR_MGMT_1, 0x00);                               // �������״̬
        mpu6050_write_register(SMPLRT_DIV, 0x07);                               // 125HZ������
        mpu6050_write_register(MPU6050_CONFIG, 0x04);
        mpu6050_write_register(GYRO_CONFIG, 0x18);                              // 2000
        mpu6050_write_register(ACCEL_CONFIG, 0x10);                             // 8g
        mpu6050_write_register(USER_CONTROL, 0x00);
        mpu6050_write_register(INT_PIN_CFG, 0x02);
    }while(0);
    return return_state;
}
