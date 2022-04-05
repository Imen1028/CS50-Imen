#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
int number = 1;
do
{
    printf("Enter 1 for Exponential Smoothing\n"
    "Enter 2 for Exponential Smoothing with Trend Adjustment\n"
    "Enter 3 for Trend Projection\n");
    int months;
    int select = get_int("I want to calculate: ");
    if (select == 1) {
        months = get_int("How many months? ");

        float forecast[months];
        float smoothing_constant;
        float smoothing_constant_2;

        do
        {
        smoothing_constant = get_float("Smoothing constant: ");
        } while(smoothing_constant > 1 || smoothing_constant < 0);

        do
        {
        smoothing_constant_2 = get_float("Smoothing constant(2): ");
        } while(smoothing_constant_2 > 1 || smoothing_constant_2 < 0 );

        float actual_tonnage_unloaded[months];
        for (int i = 0; i < months - 1; i++)
        {
            actual_tonnage_unloaded[i] = get_int("actual_tonnage_unloaded(%i): ", i + 1);
        }

        float first_forecast = get_float("First forecast: ");
        forecast[0] = first_forecast;

        float absolute_deviation_1[months];
        float sum_of_absolute_deviations_1 = 0;
        float MAD_1;

        float sum_of_errors_squared_1 = 0;
        float MSE_1;

        float percent_error[months];
        float sum_of_percent_error = 0;
        float MAPE_1;

        for (int j = 0; j < months; j++)
        {
            forecast[j + 1] = forecast[j] + smoothing_constant * (actual_tonnage_unloaded[j] - forecast[j]);
            printf("Forecast%i(%.2f): %.3f\n", j + 1, smoothing_constant, forecast[j]);
            if (j < 8)
            {
            absolute_deviation_1[j] = fabsf(actual_tonnage_unloaded[j] - forecast[j]);
            sum_of_absolute_deviations_1 += absolute_deviation_1[j];

            sum_of_errors_squared_1 += absolute_deviation_1[j] * absolute_deviation_1[j];

            percent_error[j] = 100 * (fabsf(absolute_deviation_1[j]) / actual_tonnage_unloaded[j]);
            sum_of_percent_error += percent_error[j];
            }
            else if (j < 9)
            {
                MAD_1 = sum_of_absolute_deviations_1 / (months - 1);
                printf("MAD(%.2f): %.3f\n",smoothing_constant, MAD_1);

                MSE_1 = sum_of_errors_squared_1 / (months - 1);
                printf("MSE(%.2f): %.3f\n",smoothing_constant, MSE_1);

                MAPE_1 = sum_of_percent_error / (months - 1);
                printf("MAPE(%.2f): %.3f%%\n", smoothing_constant, MAPE_1);
            }
        }

        printf("---------\n");

        float absolute_deviation_2[months];
        float sum_of_absolute_deviations_2 = 0;
        float MAD_2;

        float sum_of_errors_squared_2 = 0;
        float MSE_2;

        float percent_error_2[months];
        float sum_of_percent_error_2 = 0;
        float MAPE_2;

        for (int k = 0; k < months; k++)
        {
            forecast[k + 1] = forecast[k] + smoothing_constant_2 * (actual_tonnage_unloaded[k] - forecast[k]);
            printf("Forecast%i(%.2f): %.3f\n", k + 1, smoothing_constant_2, forecast[k]);
            if (k < 8)
            {
            absolute_deviation_2[k] = fabsf(actual_tonnage_unloaded[k] - forecast[k]);
            sum_of_absolute_deviations_2 += absolute_deviation_2[k];

            sum_of_errors_squared_2 += absolute_deviation_2[k] * absolute_deviation_2[k];

            percent_error_2[k] = 100 * (fabsf(absolute_deviation_2[k]) / actual_tonnage_unloaded[k]);
            sum_of_percent_error_2 += percent_error_2[k];
            }
            else if (k < 9)
            {
                MAD_2 = sum_of_absolute_deviations_2 / (months - 1);
                printf("MAD(%.2f): %.3f\n",smoothing_constant_2, MAD_2);

                MSE_2 = sum_of_errors_squared_2 / (months - 1);
                printf("MSE(%.2f): %.3f\n",smoothing_constant_2, MSE_2);

                MAPE_2 = sum_of_percent_error_2 / (months - 1);
                printf("MAPE(%.2f): %.3f%%\n", smoothing_constant_2, MAPE_2);
            }
        }
    }
    else if (select == 2)
    {
        months = get_int("How many months? ");
        double actual_demand[months];
        for (int i = 0; i < months - 1; i++)
        {
            actual_demand[i] = get_double("Actual Demand(%i): ", i + 1);
        }

        double a = get_double("Alpha: ");
        double b = get_double("Beta:  ");

        double Ft[months];
        Ft[0] = get_double("First Ft: ");
        double Tt[months];
        Tt[0] = get_double("First Tt: ");

        double FIT[months];

        for (int j = 0; j < months; j++)
        {
            Ft[j + 1] = a * actual_demand[j] + (1 - a) * (Ft[j] + Tt[j]);

            Tt[j + 1] = b * (Ft[j+1] - Ft[j]) + (1 - b) * Tt[j];

            FIT[j] = Ft[j] + Tt[j];

            printf("Ft(%i): %.2f | ", j + 1, Ft[j]);
            printf("Tt(%i): %.2f | ", j + 1, Tt[j]);
            printf("FIT(%i): %.2f\n", j + 1, FIT[j]);
        }
        printf("---\n");

    }
    else if(select == 3)
    {
        int n = get_int("How many years? ");
        int year[n];
        double sum_year = 0;
        for(int i = 0; i < n; i++)
        {
            year[i] = i + 1;
            sum_year += year[i];
        }

        int epd[n];
        double sum_epd = 0;
        for (int j = 0; j < n; j++)
        {
            epd[j] = get_int("Electrical power demand(%i): ", j + 1);
            sum_epd += epd[j];
        }

        double squared_x[n];
        double sum_squared_x = 0;
        double xy[n];
        double sum_xy = 0;
        for (int k = 0; k < n; k++)
        {
            squared_x[k] = pow(year[k], 2);
            sum_squared_x += squared_x[k];

            xy[k] = year[k] * epd[k];
            sum_xy += xy[k];
        }

        double avr_x = sum_year / n;
        double avr_y = sum_epd / n;

        double b = ( sum_xy - (n * avr_x * avr_y) ) / (sum_squared_x - n * pow(avr_x, 2));
        double a = avr_y - b * avr_x;
        double y = 0;
        printf("y = %.2f + %.2f * x\n",a ,b);

        int x = get_int("x: ");
        y = a + b * x;
        printf("%.2f = %f + %f * %i\n",y, a, b, x);
        printf("---\n");
    }
    else
    {
        printf("---------------\n"
            "INVALID NUMBER!\n"
            "---------------\n");
    }
    number = get_int("If you want to continue, enter 1 \n"
                "If you want to exit, enter 2 \n");
    printf("---\n");
}while(number == 1);

return 0;
}