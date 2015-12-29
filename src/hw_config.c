#include "hw_config.h"

void NVIC_Configuration(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}


void SysTick_Configuration(void)
{
  if(SysTick_Config(SystemCoreClock / 1000))
  {
    while(1)
    {
      //
    }
  }
  NVIC_SetPriority(SysTick_IRQn,SYSTICK_IRQ_PRIORITY);
}

void Set_System(void)
{
  /* Enable for RTC use */
  // Enable PWR and BKP clock;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP,ENABLE);
  // Enable write access to Backup domain
  PWR_BackupAccessCmd(ENABLE);

  // DWT_Init();
  // init NVIC 
  NVIC_Configuration();


  // ToDo: something init for system 
}


void OLED_IO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef SPI_InitStructure;
  /* OLED Control Pins configure */
  RCC_APB2PeriphClockCmd(OLED_CS_GPIO_CLK | OLED_DC_GPIO_CLK | OLED_RST_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = OLED_CS_GPIO_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(OLED_CS_GPIO_PORT,&GPIO_InitStructure);

  OLED_RST_LOW();  // add a reset
  OLED_CS_HIGH();

  GPIO_InitStructure.GPIO_Pin = OLED_RST_GPIO_PIN;
  GPIO_Init(OLED_RST_GPIO_PORT,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = OLED_DC_GPIO_PIN;
  GPIO_Init(OLED_DC_GPIO_PORT,&GPIO_InitStructure);
  /* SPI Configure */
  RCC_APB2PeriphClockCmd(OLED_SPI_SCK_GPIO_CLK | OLED_SPI_MOSI_GPIO_CLK,ENABLE );
  OLED_SPI_CLK_CMD(OLED_SPI_CLK, ENABLE);
  // Configure OLED_MOSI pins: mosi
  GPIO_InitStructure.GPIO_Pin = OLED_SPI_MOSI_GPIO_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(OLED_SPI_MOSI_GPIO_PORT,&GPIO_InitStructure);
  // Configure OLED_SCK pins: sck
  GPIO_InitStructure.GPIO_Pin = OLED_SPI_SCK_GPIO_PIN;
  GPIO_Init(OLED_SPI_SCK_GPIO_PORT,&GPIO_InitStructure);

  SPI_InitStructure.SPI_BaudRatePrescaler = OLED_SPI_BAUDRATE_PRESCALER;
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  //  SPI_InitStructure.TIMode = SPI_TIMODE_DISABLE;
  //  SPI_InitStructure.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(OLED_SPI,&SPI_InitStructure);

  SPI_Cmd(OLED_SPI, ENABLE);
  OLED_RST_HIGH(); // now reset end begin work oled ...
}


uint8_t OLED_SPI_Write(uint8_t data)
{
  while(SPI_I2S_GetFlagStatus(OLED_SPI, SPI_I2S_FLAG_TXE) == RESET) ;

  SPI_I2S_SendData(OLED_SPI,data);

  while(SPI_I2S_GetFlagStatus(OLED_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  return SPI_I2S_ReceiveData(OLED_SPI);
}


