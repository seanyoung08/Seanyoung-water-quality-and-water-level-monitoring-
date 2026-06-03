#include "Debug.h"
#include "App_Display.h"
#include "Delay.h"

#include "App_Water_level.h"
#include "App_TDS.h"

#define TDS_WATER_LEVEL_MIN_CM 0.5

int	main()
{	
    App_Display_Init();
	App_Display_Back();
	Debug_init();
	App_TDS_Init();
	Debug_println("ADS1115 init ok");
	Delay_ms(2);
	int16_t v=Inf_ADS1115_ReadV();
	Debug_println("v=%dmV",v);
	App_Water_Level_Init();



	
	double water_level=0;
	double tds=0;
	char buffer[48]={0};

	while (1)
	{
		water_level=App_Water_Level_depth();
		sprintf((char *)buffer,"water_level=%0.2f                     ",water_level);
		App_Display_ASCII(0,110,buffer);
		if(water_level > TDS_WATER_LEVEL_MIN_CM){
			tds=App_TDS_Read();
		}else{
			tds=0;
		}
		sprintf((char *)buffer,"tds=%0.2f                     ",tds);
		App_Display_ASCII(0,150,buffer);
		Delay_ms(100);
	}
	

	
}



