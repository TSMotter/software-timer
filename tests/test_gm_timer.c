/***************************************************************************************************
 * @file     test_gm_timer.c
 * @brief    Unity tests for the software timer module
 * @author   Giuliano Motter
 * @date     08/2020
 * @details  github.com/TSMotter
 ***************************************************************************************************/
#include "unity.h"
#include "gm_timer.h"

int CallbackCounter = 0;

void CallBackTestFunc(void *par1, uint16_t par2)
{
  CallbackCounter++;
}

void setUp(void)
{
  CallbackCounter = 0;
  SofTim_InitializeModule();
}

void tearDown(void)
{
  // clean stuff up here
}

/***************************************************************************************************
 * @brief Test case for creating the max number of timer instances
 ***************************************************************************************************/
void test_SofTim_AllocateTimer(void)
{
  soft_tim_st stTimers[MAX_SOFT_TIM_INSTANCES];

  // Create MAX_SOFT_TIM_INSTANCES timers
  for (int k = 0; k < MAX_SOFT_TIM_INSTANCES; k++)
  {
    TEST_ASSERT_NOT_EQUAL(
        false, SofTim_AllocateTimer(&stTimers[k], 1000, true, CallBackTestFunc,
                                    NULL, 0));
  }
}

/***************************************************************************************************
 * @brief Test case for Freeing one timer instance and then creating a new one
 ***************************************************************************************************/
void test_SofTim_FreeTimer(void)
{
  soft_tim_st stTimers[MAX_SOFT_TIM_INSTANCES];
  soft_tim_st stAnotherTimer;

  // Create MAX_SOFT_TIM_INSTANCES timers
  for (int k = 0; k < MAX_SOFT_TIM_INSTANCES; k++)
  {
    TEST_ASSERT_NOT_EQUAL(
        false, SofTim_AllocateTimer(&stTimers[k], 1000, true, CallBackTestFunc,
                                    NULL, 0));
  }

  // Free the timer last created
  TEST_ASSERT_NOT_EQUAL(
      false, SofTim_FreeTimer(&stTimers[MAX_SOFT_TIM_INSTANCES - 1]));

  // Try creating a new one
  TEST_ASSERT_NOT_EQUAL(false, SofTim_AllocateTimer(&stAnotherTimer, 1000, true,
                                                    CallBackTestFunc, NULL, 0));
}

/***************************************************************************************************
 * @brief Test case for failing if trying to create more timers then the max
 *instances allowed
 ***************************************************************************************************/
void test_SofTim_MaxInstances(void)
{
  soft_tim_st stTimers[MAX_SOFT_TIM_INSTANCES];
  soft_tim_st stAnotherTimer;

  // Create MAX_SOFT_TIM_INSTANCES timers
  for (int k = 0; k < MAX_SOFT_TIM_INSTANCES; k++)
  {
    TEST_ASSERT_NOT_EQUAL(
        false, SofTim_AllocateTimer(&stTimers[k], 1000, true, CallBackTestFunc,
                                    NULL, 0));
  }

  // This call should not be able to create a new timer instance
  TEST_ASSERT_EQUAL(false, SofTim_AllocateTimer(&stAnotherTimer, 1000, true,
                                                CallBackTestFunc, NULL, 0));
}

/***************************************************************************************************
 * @brief Test case for trying to create a timer instance with invalid period
 *timer
 ***************************************************************************************************/
void test_SofTim_InvalidPeriod(void)
{
  soft_tim_st stTimer;

  // Try to create a timer with invalid period
  TEST_ASSERT_EQUAL(false, SofTim_AllocateTimer(&stTimer, 0xFFFF, true,
                                                CallBackTestFunc, NULL, 0));
}

/***************************************************************************************************
 * @brief Test case to check that callback is in fact called for one shot timer
 ***************************************************************************************************/
void test_SofTim_OneShotCallbackIsCalled(void)
{
  soft_tim_st stOneShotTimer;
  uint16_t    period = 100;

  // Create a timer
  TEST_ASSERT_NOT_EQUAL(false,
                        SofTim_AllocateTimer(&stOneShotTimer, period, false,
                                             CallBackTestFunc, NULL, 0));

  TEST_ASSERT_NOT_EQUAL(false, SofTim_StartTimer(&stOneShotTimer));

  while (CallbackCounter == 0)
  {
    SofTim_Tick();
  }

  TEST_ASSERT_EQUAL(1, CallbackCounter);
}

/***************************************************************************************************
 * @brief Test case to check that callback is in fact called for periodic timer
 ***************************************************************************************************/
void test_SofTim_PeriodicCallbackIsCalled(void)
{
  soft_tim_st stPeriodicTimer;
  uint16_t    period = 100;

  // Create a timer
  TEST_ASSERT_NOT_EQUAL(false,
                        SofTim_AllocateTimer(&stPeriodicTimer, period, true,
                                             CallBackTestFunc, NULL, 0));

  TEST_ASSERT_NOT_EQUAL(false, SofTim_StartTimer(&stPeriodicTimer));

  while (CallbackCounter < 2)
  {
    SofTim_Tick();
  }

  TEST_ASSERT_EQUAL(2, CallbackCounter);
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_SofTim_AllocateTimer);
  RUN_TEST(test_SofTim_FreeTimer);
  RUN_TEST(test_SofTim_MaxInstances);
  RUN_TEST(test_SofTim_InvalidPeriod);
  RUN_TEST(test_SofTim_OneShotCallbackIsCalled);
  RUN_TEST(test_SofTim_PeriodicCallbackIsCalled);

  return UNITY_END();
}