#include "utility/EPD_12in48b.h"
#include "GUI_Paint.h"

#define MAX_STR_BUFF 128

struct payload
{
    int count;
    char message[100];
    float humids[10];
    float temps[10];
    float heats[10];
    unsigned long long last_updates[10];
};

int draw_normal_message(struct payload pl)
{
    DEV_Delay_ms(500);
    // SPI initialization
    DEV_ModuleInit();

    printf("### *** Init \r\n");
    DEV_TestLED();
    EPD_12in48B_Init();

    printf("### *** Clear \r\n");
    EPD_12in48B_Clear();
    printf("### *** NewImage \r\n");
    // 1.Apply for a drawing cache
    UBYTE *Image = NULL;
    UWORD xsize = 1304, ysize = 984 / 2; // 1304 x 492// Not enough memory to allocate 1304*984 of memory
    UDOUBLE Imagesize = ((xsize % 8 == 0) ? (xsize / 8) : (xsize / 8 + 1)) * ysize;
    if ((Image = (UBYTE *)malloc(Imagesize)) == NULL)
    {
        printf("### *** Failed to apply for black memory...\r\n");
        while (1)
            ;
    }

    printf("### *** Paint_NewImage\r\n");
    Paint_NewImage(Image, 1304, 492, 0, WHITE);
    char str_buffer[MAX_STR_BUFF];
    time_t unixTime;
    struct tm *timeInfo;
    char t_buffer[80];

    // 2.Drawing on the img
    printf("### *** 1.Drawing up Half screen black\r\n");
    Paint_Clear(WHITE);
    // Paint_DrawImage(gImage_240x240logo, 50, 3, 240, 240);
    // Paint_DrawPoint(300, 82, BLACK, DOT_PIXEL_4X4, DOT_FILL_AROUND);
    // Paint_DrawString_EN(350, 70, "12.48inch e-paper", &Font24, WHITE, BLACK);
    // Paint_DrawPoint(300, 164, BLACK, DOT_PIXEL_4X4, DOT_FILL_AROUND);
    // Paint_DrawString_EN(350, 152, "1304 * 984 pixel", &Font24, WHITE, BLACK);
    // int d = 400;
    // int x1 = 800, y1 = 50, x2 = x1+d, y2 = y1+d;
    // int x0 = (x1+x2)/2, y0 = (y1+y2)/2, r = d/2;
    // Paint_DrawRectangle(x1, y1, x2, y2, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_3X3);
    // Paint_DrawLine(x1, y1, x2, y2, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    // Paint_DrawLine(x2, y1, x1, y2, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    // Paint_DrawCircle(x0, y0, r, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);

    Paint_DrawString_EN(40, 50, "Berlin weather by districts", &Font24, WHITE, BLACK);
    // Paint_DrawRectangle(40, 20, 435, 60, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_3X3);
    Paint_DrawLine(40, 200, 1244, 200, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    Paint_DrawLine(40, 200, 40, 491, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    Paint_DrawLine(1244, 200, 1244, 491, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    Paint_DrawLine(607, 200, 607, 491, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    Paint_DrawLine(40, 491, 1244, 491, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);

    Paint_DrawString_EN(60, 220, "Lichtenberg:", &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Temperatur: %.2fC", pl.temps[0]);
    Paint_DrawString_EN(60, 280, str_buffer, &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Humidity: %.2fC", pl.humids[0]);
    Paint_DrawString_EN(60, 320, str_buffer, &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Feels like: %.2fC", pl.heats[0]);
    Paint_DrawString_EN(60, 360, str_buffer, &Font24, WHITE, BLACK);
    unixTime = pl.last_updates[0];
    timeInfo = localtime(&unixTime);
    strftime(t_buffer, sizeof(t_buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    snprintf(str_buffer, MAX_STR_BUFF, "Last Updated: %s", t_buffer);
    Paint_DrawString_EN(60, 400, str_buffer, &Font20, WHITE, BLACK);

    Paint_DrawString_EN(627, 220, "Mitte:", &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Temperatur: %.2fC", pl.temps[1]);
    Paint_DrawString_EN(627, 280, str_buffer, &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Humidity: %.2fC", pl.humids[1]);
    Paint_DrawString_EN(627, 320, str_buffer, &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Feels like: %.2fC", pl.heats[1]);
    Paint_DrawString_EN(627, 360, str_buffer, &Font24, WHITE, BLACK);
    unixTime = pl.last_updates[1];
    timeInfo = localtime(&unixTime);
    strftime(t_buffer, sizeof(t_buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    snprintf(str_buffer, MAX_STR_BUFF, "Last Updated: %s", t_buffer);
    Paint_DrawString_EN(627, 400, str_buffer, &Font20, WHITE, BLACK);

    EPD_12in48B_SendBlack1(Image);

    // printf("2.Drawing down Half screen black\r\n");
    Paint_Clear(WHITE);
    // Paint_DrawImage(gImage_240x240logo, 50, 246, 240, 240);
    // Paint_DrawPoint(300, 322, BLACK, DOT_PIXEL_4X4, DOT_FILL_AROUND);
    // Paint_DrawString_EN(350, 310, "www.waveshare.com", &Font24, WHITE, BLACK);
    // Paint_DrawPoint(300, 404, BLACK, DOT_PIXEL_4X4, DOT_FILL_AROUND);
    // Paint_DrawString_EN(350, 392, "www.waveshare.net", &Font24, WHITE, BLACK);

    //-----
    Paint_DrawLine(40, 0, 40, 291, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    Paint_DrawLine(1244, 0, 1244, 291, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    Paint_DrawLine(40, 291, 1244, 291, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    Paint_DrawLine(607, 0, 607, 291, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);

    Paint_DrawString_EN(60, 20, "Spandau:", &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Temperatur %.2fC", pl.temps[2]);
    Paint_DrawString_EN(60, 80, str_buffer, &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Humidity: %.2fC", pl.humids[2]);
    Paint_DrawString_EN(60, 120, str_buffer, &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Feels like: %.2fC", pl.heats[2]);
    Paint_DrawString_EN(60, 160, str_buffer, &Font24, WHITE, BLACK);
    unixTime = pl.last_updates[2];
    timeInfo = localtime(&unixTime);
    strftime(t_buffer, sizeof(t_buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    snprintf(str_buffer, MAX_STR_BUFF, "Last Updated: %s", t_buffer);
    Paint_DrawString_EN(60, 200, str_buffer, &Font20, WHITE, BLACK);

    Paint_DrawString_EN(627, 20, "Pankow:", &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Temperatur: %.2fC", pl.temps[3]);
    Paint_DrawString_EN(627, 80, str_buffer, &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Humidity: %.2fC", pl.humids[3]);
    Paint_DrawString_EN(627, 120, str_buffer, &Font24, WHITE, BLACK);
    snprintf(str_buffer, MAX_STR_BUFF, "Feels like: %.2fC", pl.heats[3]);
    Paint_DrawString_EN(627, 160, str_buffer, &Font24, WHITE, BLACK);
    unixTime = pl.last_updates[3];
    timeInfo = localtime(&unixTime);
    strftime(t_buffer, sizeof(t_buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    snprintf(str_buffer, MAX_STR_BUFF, "Last Updated: %s", t_buffer);
    Paint_DrawString_EN(627, 200, str_buffer, &Font20, WHITE, BLACK);

    EPD_12in48B_SendBlack2(Image);

    // printf("3.Drawing up Half screen red\r\n");
    // Paint_Clear(WHITE);
    // Paint_DrawImage(gImage_240x240logo, 50, 246, 240, 240);
    // Paint_DrawPoint(300, 322, BLACK, DOT_PIXEL_4X4, DOT_FILL_AROUND);
    // Paint_DrawString_CN(350, 300, "微雪电子ABC", &Font24CN, WHITE, BLACK);
    // Paint_DrawPoint(300, 404, BLACK, DOT_PIXEL_4X4, DOT_FILL_AROUND);
    // Paint_DrawString_CN(350, 380, "abc微雪电子", &Font24CN, WHITE, BLACK);
    // EPD_12in48B_SendRed1(Image);

    // printf("4.Drawing down Half screen red\r\n");
    // Paint_Clear(WHITE);
    // Paint_DrawImage(gImage_240x240logo, 50, 3, 240, 240);
    // Paint_DrawPoint(300, 82, BLACK, DOT_PIXEL_4X4, DOT_FILL_AROUND);
    // Paint_DrawString_EN(350, 70, "esp32 test code", &Font24, WHITE, BLACK);
    // Paint_DrawPoint(300, 164, BLACK, DOT_PIXEL_4X4, DOT_FILL_AROUND);
    // Paint_DrawString_EN(350, 152, "hello world", &Font24, WHITE, BLACK);
    // Paint_DrawRectangle(x1, y1, x2, y2, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_3X3);
    // Paint_DrawLine(x1, y1, x2, y2, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_2X2);
    // Paint_DrawLine(x2, y1, x1, y2, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_2X2);
    // Paint_DrawCircle(x0, y0, r, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
    // EPD_12in48B_SendRed2(Image);

    EPD_12in48B_TurnOnDisplay();
    DEV_Delay_ms(2000);

    // clear for Long-term preservation
    //  printf("clear... \r\n");
    //  EPD_12in48B_Clear();
    EPD_12in48B_Sleep();

    free(Image);
    Image = NULL;

    return 0;
}

int draw_wakeup_button_msg()
{
    DEV_Delay_ms(500);
    // SPI initialization
    DEV_ModuleInit();

    printf("Init \r\n");
    DEV_TestLED();
    EPD_12in48B_Init();

    printf("Clear \r\n");
    EPD_12in48B_Clear();
    printf("NewImage \r\n");
    // 1.Apply for a drawing cache
    UBYTE *Image = NULL;
    UWORD xsize = 1304, ysize = 984 / 2; // 1304 x 492// Not enough memory to allocate 1304*984 of memory
    UDOUBLE Imagesize = ((xsize % 8 == 0) ? (xsize / 8) : (xsize / 8 + 1)) * ysize;
    if ((Image = (UBYTE *)malloc(Imagesize)) == NULL)
    {
        printf("Failed to apply for black memory...\r\n");
        while (1)
            ;
    }

    printf("Paint_NewImage\r\n");
    Paint_NewImage(Image, 1304, 492, 0, WHITE);
    char str_buffer[MAX_STR_BUFF];
    time_t unixTime;
    struct tm *timeInfo;
    char t_buffer[80];

    // 2.Drawing on the img
    printf("1.Drawing up Half screen black\r\n");
    Paint_Clear(WHITE);
    // Paint_DrawImage(gImage_240x240logo, 50, 3, 240, 240);
    // Paint_DrawPoint(300, 82, BLACK, DOT_PIXEL_4X4, DOT_FILL_AROUND);
    // Paint_DrawString_EN(350, 70, "12.48inch e-paper", &Font24, WHITE, BLACK);
    // Paint_DrawPoint(300, 164, BLACK, DOT_PIXEL_4X4, DOT_FILL_AROUND);
    // Paint_DrawString_EN(350, 152, "1304 * 984 pixel", &Font24, WHITE, BLACK);
    // int d = 400;
    // int x1 = 800, y1 = 50, x2 = x1+d, y2 = y1+d;
    // int x0 = (x1+x2)/2, y0 = (y1+y2)/2, r = d/2;
    // Paint_DrawRectangle(x1, y1, x2, y2, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_3X3);
    // Paint_DrawLine(x1, y1, x2, y2, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    // Paint_DrawLine(x2, y1, x1, y2, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    // Paint_DrawCircle(x0, y0, r, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);

    Paint_DrawString_EN(40, 50, "Test wake up message!", &Font24, WHITE, BLACK);
    // Paint_DrawRectangle(40, 20, 435, 60, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_3X3);
    Paint_DrawLine(40, 200, 1244, 200, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    Paint_DrawLine(40, 200, 40, 491, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    Paint_DrawLine(1244, 200, 1244, 491, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    Paint_DrawLine(607, 200, 607, 491, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);
    Paint_DrawLine(40, 491, 1244, 491, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_3X3);

    EPD_12in48B_SendBlack1(Image);

    EPD_12in48B_TurnOnDisplay();
    DEV_Delay_ms(2000);

    // clear for Long-term preservation
    //  printf("clear... \r\n");
    //  EPD_12in48B_Clear();
    printf("sleep... \r\n");
    EPD_12in48B_Sleep();

    free(Image);
    Image = NULL;

    return 0;
}