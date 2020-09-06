/***************************************************************************************************
* @file     main.c
* @brief    Example of usage of the software timer module
* @author   Giuliano Motter
* @date     08/2020
* @details  github.com/TSMotter
***************************************************************************************************/
#include "gm_timer.h"

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

void delay(int mili_seconds);
void Tim_Call_Back(char *Data, uint16_t DataLen);

int main()
{
    soft_tim_st *stTimer1 = NULL;
    soft_tim_st *stTimer2 = NULL;
    char DataTIM1[] = "Timer1";
    char DataTIM2[] = "Timer2";

    // Always call this function beforea allocating the timers
    SofTim_InitializeModule();
    
    stTimer1 = SofTim_AllocateTimer(1000, TRUE, &Tim_Call_Back, DataTIM1, strlen(DataTIM1));
    if(stTimer1 == NULL)
    {
        // Handle error here...
        printf("\nUnable to create Timer1\n");
        return 0;
    }
    
    stTimer2 = SofTim_AllocateTimer(5000, FALSE, &Tim_Call_Back, DataTIM2, strlen(DataTIM2));
    if(stTimer2 == NULL)
    {
        // Handle error here...
        printf("\nUnable to create Timer2\n");
        return 0;
    }

    SofTim_StartTimer(stTimer1);
    SofTim_StartTimer(stTimer2);

    // Loop executing with known period of 1ms
    // On an embedded application this could be a hardware timer ISR
    // or even an RTOS Timer callback, for example
    while(1)
    {
        SofTim_Tick();
        delay(1);
    }
}


void delay(int mili_seconds) 
{ 
    // Storing start time 
    tick_type start_time = clock(); 

    // looping till required time is not achieved 
    while (clock() < start_time + mili_seconds); 
} 

void Tim_Call_Back(char *Data, uint16_t DataLen)
{
    printf("\n Hello, this is %s Callback! \n", Data);
}

