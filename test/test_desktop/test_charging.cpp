#ifdef UNIT_TEST

#include <unity.h>
#include <ChargeController.h>
#include <MockIOPin.h>

void test_ac_detection()
{
   MockIOPin acConnStatus((uint32_t)1);
   acConnStatus.setPinValue(1);     

    ChargeController myCC(&acConnStatus);
    myCC.init();
    TEST_ASSERT_EQUAL(IDLE, myCC.state);    //expect it to be in IDLE state on creation

    acConnStatus.setPinValue(0);            // when charger plugged in to mains AC
    myCC.service();
    TEST_ASSERT_EQUAL(AC_CONNECTED, myCC.state);    // Then the charge controller should change to the AC_CONNECTED state

    acConnStatus.setPinValue(1);            // when charger disconnected from mains
    myCC.service();
    TEST_ASSERT_EQUAL(IDLE, myCC.state);    // Then the charge controller should go back to the idle state
}

int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_ac_detection);

    UNITY_END();
}

#endif