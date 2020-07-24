#ifdef UNIT_TEST

#include <unity.h>
#include <ChargeController.h>
#include <MockIOPin.h>
#include <MockGwizPack.h>
#include <EEPROMSettings.h>

ChargeController *myCC;
MockIOPin *acConnStatus;
MockGwizPack *pack;
EEPROMSettings settings;

void setUp(void)
{
    acConnStatus = new MockIOPin((uint32_t)1);
    pack = new MockGwizPack();

    myCC = new ChargeController(acConnStatus, pack);
    acConnStatus->setPinValue(1);               // starting point is tht AC is not connected
    settings.OverVSetpoint = 4.2;               // cell voltage upper limit  
}

void tearDown(void)
{
    delete myCC;
    delete pack;
}

void testACDetection()
{
    TEST_ASSERT_EQUAL(IDLE, myCC->state);    //expect it to be in IDLE state on creation

    acConnStatus->setPinValue(0);            // when charger plugged in to mains AC
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGING, myCC->state);    // Then the charge controller should change to the CHARGING state

    acConnStatus->setPinValue(1);            // when charger disconnected from mains
    myCC->service();
    TEST_ASSERT_EQUAL(IDLE, myCC->state);    // Then the charge controller should go back to the idle state
}

void testCellVoltageLimit()
{
    acConnStatus->setPinValue(0);            // when charger plugged in to mains AC
    pack->setHighestCellVoltage(3.8);        // and all cells below the voltage limit
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGING, myCC->state);    // The charge controller should be in the CHARGING state
    
    pack->setHighestCellVoltage(4.2);        // then if the voltage reaches the limit
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGE_COMPLETE, myCC->state);    // charging should stop

}


int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(testACDetection);
    RUN_TEST(testCellVoltageLimit);

    UNITY_END();
}

#endif