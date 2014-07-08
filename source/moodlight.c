/* 
 *
 * Sample Program to manipulate background color
 *
 */


#include <stdio.h>
#include "../include/ripdraw.h"

#define COLOR_MAX 0xff
#define COLOR_STEP (0xff)/2
#define LAYER 1

int main(int argc, char **argv)
{
        int i;
	int  ret;

	int red;
	int green;
	int blue;


/* open port to Ripdraw device */
       	RD_INTERFACE* rd_interface = RdInterfaceInit("/dev/ttyACM0");

	/* check for verbose input from command line */
	if (argc > 1)
	{
		rd_interface->verbose = atoi(argv[1]);
		if (rd_interface->verbose < 0)
		{
			rd_interface->verbose = 0;
		}
	}


	/* Issue Reset command to clear everything from Ripdraw display */
	ret = Rd_Reset(rd_interface);
        if (ret != 0) return ret;
	
	/* enable layer */
	ret = Rd_SetLayerEnable(rd_interface, 1 , RD_TRUE);
    	if (ret != 0) return ret;
    	
	/* walk thru red */
	for (red = COLOR_STEP; red < COLOR_MAX; red = red + COLOR_STEP)
	{
		green=0;
		blue = 0; 
		/* set backlight color */
    		ret = Rd_SetLayerBackColor(rd_interface, 1 , Rd_Color(red, green, blue, 0xFF));
    		if (ret != 0) return ret;

		ret = Rd_ComposeLayersToPage(rd_interface, 1);
   		if (ret != 0) return ret;
	}
	
	/* walk thru green */
	for (green = COLOR_STEP; green < COLOR_MAX; green = green + COLOR_STEP)
	{
		red=0;
		blue = 0; 
		/* set backlight color */
    		ret = Rd_SetLayerBackColor(rd_interface, 1 , Rd_Color(red, green, blue, 0xFF));
    		if (ret != 0) return ret;

		ret = Rd_ComposeLayersToPage(rd_interface, 1);
   		if (ret != 0) return ret;
	}
	
	/* walk thru blue */
	for (blue = COLOR_STEP; blue < COLOR_MAX; blue = blue + COLOR_STEP)
	{
		red=0;
		green = 0; 
		/* set backlight color */
    		ret = Rd_SetLayerBackColor(rd_interface, 1 , Rd_Color(red, green, blue, 0xFF));
    		if (ret != 0) return ret;

		ret = Rd_ComposeLayersToPage(rd_interface, 1);
   		if (ret != 0) return ret;
	}

	/* blend all colors */
	for (red = COLOR_STEP; red < COLOR_MAX; red = red + COLOR_STEP)
	{
		for (green =COLOR_STEP; green < COLOR_MAX; green = green + COLOR_STEP)
		{
			for (blue =COLOR_STEP; blue < COLOR_MAX; blue = blue + COLOR_STEP)
			{
				/* set backlight color */
    				ret = Rd_SetLayerBackColor(rd_interface, 1 , Rd_Color(red, green, blue, 0xFF));
    				if (ret != 0) return ret;

				ret = Rd_ComposeLayersToPage(rd_interface, 1);
   				if (ret != 0) return ret;
			}
		}
	}
		
	RdInterfaceClose(rd_interface);

	printf("\nRet: %d\n", ret);
	printf("Done!\n");
	return 0;
}
