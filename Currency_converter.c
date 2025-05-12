#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struct to hold exchange rates
typedef struct {
    float INRtoUSD;
    float INRtoEUR;
    float INRtoGBP;
} ExchangeRates;

// Function declarations
void showMainMenu();
void showConversionMenu();
void performConversion(float amount, int choice, ExchangeRates rates);
void logTransaction(float originalAmount, float convertedAmount, const char *from, const char *to);
ExchangeRates getExchangeRates();

int main() {
    int mainChoice, convChoice;
    float amount;
    ExchangeRates rates = getExchangeRates();

    printf("\n===========================================\n");
    printf("   🌍 Welcome to Pro Currency Converter 💱\n");
    printf("===========================================\n");

    while (1) {
        showMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &mainChoice);

        if (mainChoice == 0) {
            printf("\n👋 Thank you for using Pro Currency Converter. See you again!\n");
            break;
        } else if (mainChoice == 1) {
            showConversionMenu();
            printf("Choose a conversion option: ");
            scanf("%d", &convChoice);

            if (convChoice >= 1 && convChoice <= 6) {
                printf("Enter amount: ");
                scanf("%f", &amount);
                performConversion(amount, convChoice, rates);
            } else {
                printf("❌ Invalid conversion choice.\n");
            }
        } else {
            printf("❌ Invalid menu choice.\n");
        }

        printf("\n-------------------------------------------\n");
    }

    return 0;
}

// Function Definitions

void showMainMenu() {
    printf("\nMain Menu:\n");
    printf("1. Convert Currency\n");
    printf("0. Exit\n");
}

void showConversionMenu() {
    printf("\nConversion Options:\n");
    printf("1. INR to USD\n");
    printf("2. USD to INR\n");
    printf("3. INR to EUR\n");
    printf("4. EUR to INR\n");
    printf("5. INR to GBP\n");
    printf("6. GBP to INR\n");
}

void performConversion(float amount, int choice, ExchangeRates rates) {
    float result;
    char from[10], to[10];

    switch (choice) {
        case 1:
            result = amount * rates.INRtoUSD;
            sprintf(from, "INR"); sprintf(to, "USD");
            break;
        case 2:
            result = amount / rates.INRtoUSD;
            sprintf(from, "USD"); sprintf(to, "INR");
            break;
        case 3:
            result = amount * rates.INRtoEUR;
            sprintf(from, "INR"); sprintf(to, "EUR");
            break;
        case 4:
            result = amount / rates.INRtoEUR;
            sprintf(from, "EUR"); sprintf(to, "INR");
            break;
        case 5:
            result = amount * rates.INRtoGBP;
            sprintf(from, "INR"); sprintf(to, "GBP");
            break;
        case 6:
            result = amount / rates.INRtoGBP;
            sprintf(from, "GBP"); sprintf(to, "INR");
            break;
        default:
            printf("❌ Invalid conversion.\n");
            return;
    }

    printf("✅ %.2f %s = %.2f %s\n", amount, from, result, to);
    logTransaction(amount, result, from, to);
}

void logTransaction(float originalAmount, float convertedAmount, const char *from, const char *to) {
    FILE *log = fopen("conversion_log.txt", "a");
    if (log == NULL) {
        printf("⚠️ Unable to open log file.\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(log, "[%02d-%02d-%04d %02d:%02d] %.2f %s -> %.2f %s\n",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min,
            originalAmount, from, convertedAmount, to);

    fclose(log);
}

ExchangeRates getExchangeRates() {
    ExchangeRates rates;
    int custom;
    printf("\nDo you want to input custom exchange rates? (1 = Yes, 0 = No): ");
    scanf("%d", &custom);

    if (custom == 1) {
        printf("Enter INR to USD rate: ");
        scanf("%f", &rates.INRtoUSD);
        printf("Enter INR to EUR rate: ");
        scanf("%f", &rates.INRtoEUR);
        printf("Enter INR to GBP rate: ");
        scanf("%f", &rates.INRtoGBP);
    } else {
        rates.INRtoUSD = 0.012f;
        rates.INRtoEUR = 0.011f;
        rates.INRtoGBP = 0.0095f;
        printf("Using default exchange rates.\n");
    }

    return rates;
}
