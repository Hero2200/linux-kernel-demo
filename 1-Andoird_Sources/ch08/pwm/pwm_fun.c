#include "pwm_fun.h"
void pwm_start(void)
{
	unsigned tmp;
  
	tmp = ioread32(S3C64XX_GPFCON);
	
        tmp &=~(0x3U << 30);  // 前两位清零 ~(0x3U << 30):001111111111111111111 .... 11
        tmp |=  (0x2U << 30); //  第1位设为1

	iowrite32(tmp, S3C64XX_GPFCON);

}

void pwm_stop( void )
{
	unsigned tmp;
	tmp = ioread32(S3C64XX_GPFCON);  
        tmp &= ~(0x3U << 30);
	iowrite32(tmp, S3C64XX_GPFCON);
}
