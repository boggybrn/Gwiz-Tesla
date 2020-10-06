#ifdef UNIT_TEST

#include <unity.h>
#include <ChargeController.h>
#include <MockIOPin.h>
#include <MockGwizPack.h>
#include <EEPROMSettings.h>

ChargeController *myCC;
MockIOPin *acConnStatus;
MockIOPin *chgCurrentPin;
MockIOPin *chgVoltagePin;
MockGwizPack *pack;
EEPROMSettings settings;

void setUp(void)
{
    acConnStatus = new MockIOPin((uint32_t)1);
    chgCurrentPin = new MockIOPin((uint32_t)2);
    chgVoltagePin = new MockIOPin((uint32_t)2);

    pack = new MockGwizPack();

    myCC = new ChargeController(acConnStatus, chgCurrentPin, chgVoltagePin, pack);
    acConnStatus->setPinValue(1); // starting point is tht AC is not connected
    chgCurrentPin->setPinValue(22);
    chgVoltagePin->setPinValue(33);
    settings.OverVSetpoint = 4.2;  // cell voltage upper limit
    settings.UnderVSetpoint = 3.1; //cell vlotage lower limit
    settings.OverTSetpoint = 65;   //charging temperature upper limit
    settings.UnderTSetpoint = 1;   //charging temperature lower limit

    //default reasonable settings for initial conditions
    pack->setHighestCellVoltage(3.7);
    pack->setLowestTemperature(25);
    pack->setHighestTemperature(35);
}

void tearDown(void)
{
    delete myCC;
    delete pack;
    delete chgVoltagePin;
    delete chgCurrentPin;
    delete acConnStatus;
}

void whenACConnectedStartCharge()
{
    TEST_ASSERT_EQUAL(IDLE, myCC->state); //expect it to be in IDLE state on creation

    acConnStatus->setPinValue(0); // when charger plugged in to mains AC
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGING, myCC->state); // Then the charge controller should change to the CHARGING state
    TEST_ASSERT_EQUAL(ChargeController::max_charging_current, chgCurrentPin->getPinValue()); // and full charging current should be enabled
    TEST_ASSERT_EQUAL(ChargeController::max_charging_voltage, chgVoltagePin->getPinValue()); // and full charging voltage should be permitted

    acConnStatus->setPinValue(1); // when charger disconnected from mains
    myCC->service();
    TEST_ASSERT_EQUAL(IDLE, myCC->state); // Then the charge controller should go back to the idle state
}

void whenCellHighVoltageLimitReachedStopCharge()
{
    acConnStatus->setPinValue(0);     // when charger plugged in to mains AC
    pack->setHighestCellVoltage(3.8); // and all cells below the voltage limit
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGING, myCC->state); // The charge controller should be in the CHARGING state

    pack->setHighestCellVoltage(4.2); // then if the voltage reaches the limit
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGE_COMPLETE, myCC->state); // charging should stop
    TEST_ASSERT_EQUAL(ChargeController::min_charging_current, chgCurrentPin->getPinValue()); // and charging current should be set to the lowest level
    TEST_ASSERT_EQUAL(ChargeController::min_charging_voltage, chgVoltagePin->getPinValue()); // and charging voltage should be set to the lowest level
}

void whenHighVoltageLimitApproachedReduceChargingCurrent()
{
    acConnStatus->setPinValue(0);     // when charger plugged in to mains AC
    pack->setHighestCellVoltage(3.8); // and all cells below the voltage limit
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGING, myCC->state); // The charge controller should be in the CHARGING state
    TEST_ASSERT_EQUAL(0x00, chgCurrentPin->getPinValue());  // and full charging current should be applied

    pack->setHighestCellVoltage(4.18); // then if the voltage approaches the limit
    myCC->service();
    TEST_ASSERT_EQUAL(0x70, chgCurrentPin->getPinValue());  // the charging current should be reduced
    
    myCC->service();    // and if the voltage remains near or approaches the limit again
    TEST_ASSERT_EQUAL(0xB0, chgCurrentPin->getPinValue());  // the charging current should be reduced further

    myCC->service();    // and if the voltage remains near or approaches the limit again
    TEST_ASSERT_EQUAL(0xD0, chgCurrentPin->getPinValue());  // the charging current should be reduced further

    myCC->service();    // and if the voltage remains near or approaches the limit again
    TEST_ASSERT_EQUAL(0xE7, chgCurrentPin->getPinValue());  // the charging current should be reduced further

}

void whenUnderMinimumTemperatureDontCharge()
{
    pack->setLowestTemperature(0.5); // when it is too cold for charging
    acConnStatus->setPinValue(0);    // and then charger plugged in to mains AC
    myCC->service();

    TEST_ASSERT_EQUAL(TOO_COLD_TO_CHARGE, myCC->state); // Then the charge controller should go straignt to the too cold state

    pack->setLowestTemperature(1.5); // but if it warms beyond the limit, whilst the charger is still connected
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGING, myCC->state); // The charge controller should enter the CHARGING state
}

void whenOverMaximumTemperatureDontCharge()
{
    pack->setHighestTemperature(66); // when it is too hotfor charging
    acConnStatus->setPinValue(0);    // and then charger plugged in to mains AC
    myCC->service();

    TEST_ASSERT_EQUAL(TOO_HOT_TO_CHARGE, myCC->state); // Then the charge controller should go straight to the too hot state

    pack->setHighestTemperature(64); // but if it cools below the limit, whilst the charger is still connected
    myCC->service();
    TEST_ASSERT_EQUAL(CHARGING, myCC->state); // The charge controller should enter the CHARGING state
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(whenACConnectedStartCharge);
    RUN_TEST(whenHighVoltageLimitApproachedReduceChargingCurrent);
    RUN_TEST(whenCellHighVoltageLimitReachedStopCharge);
    RUN_TEST(whenUnderMinimumTemperatureDontCharge);
    RUN_TEST(whenOverMaximumTemperatureDontCharge);

    UNITY_END();
}

#endif