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
    settings.UnderVSetpoint = 3.1;              //cell vlotage lower limit
    settings.OverTSetpoint = 65;                //charging temperature upper limit
    settings.UnderTSetpoint = 1;                //charging temperature lower limit    

    //default reasonable settings for initial conditions
    pack->setHighestCellVoltage(3.7);
    pack->setLowestTemperature(25);
    pack->setHighestTemperature(35); 
}

void tearDown(void)
{
    delete myCC;
    delete pack;
}

void whenACConnectedStartCharge()
{
    TEST_ASSERT_EQUAL(IDLE, myCC->state);    //expect it to be in IDLE state on creation

    acConnStatus->setPinValue(0);            // when charger plugged in to mains AC
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGING, myCC->state);    // Then the charge controller should change to the CHARGING state

    acConnStatus->setPinValue(1);            // when charger disconnected from mains
    myCC->service();
    TEST_ASSERT_EQUAL(IDLE, myCC->state);    // Then the charge controller should go back to the idle state
}

void whenCellHighVoltageLimitReachedStopCharge()
{
    acConnStatus->setPinValue(0);            // when charger plugged in to mains AC
    pack->setHighestCellVoltage(3.8);        // and all cells below the voltage limit
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGING, myCC->state);    // The charge controller should be in the CHARGING state
    
    pack->setHighestCellVoltage(4.2);        // then if the voltage reaches the limit
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGE_COMPLETE, myCC->state);    // charging should stop
}

void whenUnderMinimumTemperatureDontCharge()
{
    pack->setLowestTemperature(0.5);         // when it is too cold for charging
    acConnStatus->setPinValue(0);           // and then charger plugged in to mains AC
    myCC->service();
    myCC->service();                        // call twice as it hops via another state

    TEST_ASSERT_EQUAL(TOO_COLD_TO_CHARGE, myCC->state);    // Then the charge controller should remain in the IDLE state

    pack->setLowestTemperature(1.5);        // but if it warms beyond the limit, whilst the charger is still connected
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGING, myCC->state);    // The charge controller should enter the CHARGING state
}

int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(whenACConnectedStartCharge);
    RUN_TEST(whenCellHighVoltageLimitReachedStopCharge);
    RUN_TEST(whenUnderMinimumTemperatureDontCharge);

    UNITY_END();
}

#endif