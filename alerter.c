#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

// Simulates network alert and returns 200 for success, 500 for failure
int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    return 200; // Stub always succeeds
}

// Updates failure count based on the network alert response
void updateFailureCount(int returnCode) {
    if (returnCode != 200) {
        alertFailureCount++;
    }
}

// Converts Fahrenheit to Celsius and sends an alert
void alertInCelcius(float fahrenheit) {
    float celsius = (fahrenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celsius);
    updateFailureCount(returnCode);
}

// Tests the alertInCelcius function
void testAlertInCelcius() {
    // Test success scenario
    alertInCelcius(400.5);
    alertInCelcius(303.6);
    assert(alertFailureCount == 0);

    // Modify stub to simulate a failure
    int networkAlertStubWithFailure(float celcius) {
        return 500; // Simulate failure
    }
    networkAlertStub = networkAlertStubWithFailure; // Override stub

    alertFailureCount = 0; // Reset for testing
    alertInCelcius(400.5); // Expect failure count to be 1
    alertInCelcius(303.6); // Expect failure count to be 2
    assert(alertFailureCount == 2);
}

int main() {
    testAlertInCelcius();
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}

int main() {
    alertInCelcius(400.5);
    alertInCelcius(303.6);
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
