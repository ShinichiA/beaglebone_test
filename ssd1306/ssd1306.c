#include "ssd1306.h"
// ----------------------------------------- FONT ---------------------------------------------

/*
** Array Variable to store the letters.
*/
const unsigned char SSD1306_font[][SSD1306_DEF_FONT_SIZE] =
    {
        {0x00, 0x00, 0x00, 0x00, 0x00}, // space
        {0x00, 0x00, 0x2f, 0x00, 0x00}, // !
        {0x00, 0x07, 0x00, 0x07, 0x00}, // "
        {0x14, 0x7f, 0x14, 0x7f, 0x14}, // #
        {0x24, 0x2a, 0x7f, 0x2a, 0x12}, // $
        {0x23, 0x13, 0x08, 0x64, 0x62}, // %
        {0x36, 0x49, 0x55, 0x22, 0x50}, // &
        {0x00, 0x05, 0x03, 0x00, 0x00}, // '
        {0x00, 0x1c, 0x22, 0x41, 0x00}, // (
        {0x00, 0x41, 0x22, 0x1c, 0x00}, // )
        {0x14, 0x08, 0x3E, 0x08, 0x14}, // *
        {0x08, 0x08, 0x3E, 0x08, 0x08}, // +
        {0x00, 0x00, 0xA0, 0x60, 0x00}, // ,
        {0x08, 0x08, 0x08, 0x08, 0x08}, // -
        {0x00, 0x60, 0x60, 0x00, 0x00}, // .
        {0x20, 0x10, 0x08, 0x04, 0x02}, // /

        {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
        {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
        {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
        {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
        {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
        {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
        {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
        {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
        {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
        {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9

        {0x00, 0x36, 0x36, 0x00, 0x00}, // :
        {0x00, 0x56, 0x36, 0x00, 0x00}, // ;
        {0x08, 0x14, 0x22, 0x41, 0x00}, // <
        {0x14, 0x14, 0x14, 0x14, 0x14}, // =
        {0x00, 0x41, 0x22, 0x14, 0x08}, // >
        {0x02, 0x01, 0x51, 0x09, 0x06}, // ?
        {0x32, 0x49, 0x59, 0x51, 0x3E}, // @

        {0x7C, 0x12, 0x11, 0x12, 0x7C}, // A
        {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
        {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
        {0x7F, 0x41, 0x41, 0x22, 0x1C}, // D
        {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
        {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
        {0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
        {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
        {0x00, 0x41, 0x7F, 0x41, 0x00}, // I
        {0x20, 0x40, 0x41, 0x3F, 0x01}, // J
        {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
        {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
        {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
        {0x7F, 0x04, 0x08, 0x10, 0x7F}, // N
        {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
        {0x7F, 0x09, 0x09, 0x09, 0x06}, // P
        {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
        {0x7F, 0x09, 0x19, 0x29, 0x46}, // R
        {0x46, 0x49, 0x49, 0x49, 0x31}, // S
        {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
        {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
        {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
        {0x3F, 0x40, 0x38, 0x40, 0x3F}, // W
        {0x63, 0x14, 0x08, 0x14, 0x63}, // X
        {0x07, 0x08, 0x70, 0x08, 0x07}, // Y
        {0x61, 0x51, 0x49, 0x45, 0x43}, // Z

        {0x00, 0x7F, 0x41, 0x41, 0x00}, // [
        {0x55, 0xAA, 0x55, 0xAA, 0x55}, // Backslash (Checker pattern)
        {0x00, 0x41, 0x41, 0x7F, 0x00}, // ]
        {0x04, 0x02, 0x01, 0x02, 0x04}, // ^
        {0x40, 0x40, 0x40, 0x40, 0x40}, // _
        {0x00, 0x03, 0x05, 0x00, 0x00}, // `

        {0x20, 0x54, 0x54, 0x54, 0x78}, // a
        {0x7F, 0x48, 0x44, 0x44, 0x38}, // b
        {0x38, 0x44, 0x44, 0x44, 0x20}, // c
        {0x38, 0x44, 0x44, 0x48, 0x7F}, // d
        {0x38, 0x54, 0x54, 0x54, 0x18}, // e
        {0x08, 0x7E, 0x09, 0x01, 0x02}, // f
        {0x18, 0xA4, 0xA4, 0xA4, 0x7C}, // g
        {0x7F, 0x08, 0x04, 0x04, 0x78}, // h
        {0x00, 0x44, 0x7D, 0x40, 0x00}, // i
        {0x40, 0x80, 0x84, 0x7D, 0x00}, // j
        {0x7F, 0x10, 0x28, 0x44, 0x00}, // k
        {0x00, 0x41, 0x7F, 0x40, 0x00}, // l
        {0x7C, 0x04, 0x18, 0x04, 0x78}, // m
        {0x7C, 0x08, 0x04, 0x04, 0x78}, // n
        {0x38, 0x44, 0x44, 0x44, 0x38}, // o
        {0xFC, 0x24, 0x24, 0x24, 0x18}, // p
        {0x18, 0x24, 0x24, 0x18, 0xFC}, // q
        {0x7C, 0x08, 0x04, 0x04, 0x08}, // r
        {0x48, 0x54, 0x54, 0x54, 0x20}, // s
        {0x04, 0x3F, 0x44, 0x40, 0x20}, // t
        {0x3C, 0x40, 0x40, 0x20, 0x7C}, // u
        {0x1C, 0x20, 0x40, 0x20, 0x1C}, // v
        {0x3C, 0x40, 0x30, 0x40, 0x3C}, // w
        {0x44, 0x28, 0x10, 0x28, 0x44}, // x
        {0x1C, 0xA0, 0xA0, 0xA0, 0x7C}, // y
        {0x44, 0x64, 0x54, 0x4C, 0x44}, // z

        {0x00, 0x10, 0x7C, 0x82, 0x00}, // {
        {0x00, 0x00, 0xFF, 0x00, 0x00}, // |
        {0x00, 0x82, 0x7C, 0x10, 0x00}, // }
        {0x00, 0x06, 0x09, 0x09, 0x06}  // ~ (Degrees)
};

struct i2c_client *client_data_ptr = NULL;

uint8_t SSD1306_LineNum = 0;
uint8_t SSD1306_CursorPos = 0;
uint8_t SSD1306_FontSize = SSD1306_DEF_FONT_SIZE;

/*
** This function writes the data into the I2C client
**
**  Arguments:
**      buff -> buffer to be sent
**      len  -> Length of the data
**
*/
int I2C_Write(unsigned char *buf, unsigned int len)
{
    /*
    ** Sending Start condition, Slave address with R/W bit,
    ** ACK/NACK and Stop condtions will be handled internally.
    */
    int ret = i2c_master_send(client_data_ptr, buf, len);

    return ret;
}

/*
** This function reads one byte of the data from the I2C client
**
**  Arguments:
**      out_buff -> buffer wherer the data to be copied
**      len      -> Length of the data to be read
**
*/
int I2C_Read(unsigned char *out_buf, unsigned int len)
{
    /*
    ** Sending Start condition, Slave address with R/W bit,
    ** ACK/NACK and Stop condtions will be handled internally.
    */
    int ret = i2c_master_recv(client_data_ptr, out_buf, len);

    return ret;
}

void SSD1306_Write(bool is_cmd, unsigned char data)
{
    unsigned char buf[2] = {0};
    int ret;

    /*
    ** First byte is always control byte. Data is followed after that.
    **
    ** There are two types of data in SSD_1306 OLED.
    ** 1. Command
    ** 2. Data
    **
    ** Control byte decides that the next byte is, command or data.
    **
    ** -------------------------------------------------------
    ** |              Control byte's | 6th bit  |   7th bit  |
    ** |-----------------------------|----------|------------|
    ** |   Command                   |   0      |     0      |
    ** |-----------------------------|----------|------------|
    ** |   data                      |   1      |     0      |
    ** |-----------------------------|----------|------------|
    **
    ** Please refer the datasheet for more information.
    **
    */
    if (is_cmd == true)
    {
        buf[0] = 0x00;
    }
    else
    {
        buf[0] = 0x40;
    }

    buf[1] = data;

    ret = I2C_Write(buf, 2);
}

void SSD1306_GoToNextLine(void)
{
    /*
    ** Increment the current line number.
    ** roll it back to first line, if it exceeds the limit.
    */
    SSD1306_LineNum++;
    SSD1306_LineNum = (SSD1306_LineNum & SSD1306_MAX_LINE);

    SSD1306_SetCursor(SSD1306_LineNum, 0); /* Finally move it to next line */
}

void SSD1306_PrintChar(unsigned char c)
{
    uint8_t data_byte;
    uint8_t temp = 0;

    /*
    ** If we character is greater than segment len or we got new line charcter
    ** then move the cursor to the new line
    */
    if (((SSD1306_CursorPos + SSD1306_FontSize) >= SSD1306_MAX_SEG) ||
        (c == '\n'))
    {
        SSD1306_GoToNextLine();
    }

    // print charcters other than new line
    if (c != '\n')
    {

        /*
        ** In our font array (SSD1306_font), space starts in 0th index.
        ** But in ASCII table, Space starts from 32 (0x20).
        ** So we need to match the ASCII table with our font table.
        ** We can subtract 32 (0x20) in order to match with our font table.
        */
        c -= 0x20; // or c -= ' ';

        do
        {
            data_byte = SSD1306_font[c][temp]; // Get the data to be displayed from LookUptable

            SSD1306_Write(false, data_byte); // write data to the OLED
            SSD1306_CursorPos++;

            temp++;

        } while (temp < SSD1306_FontSize);
        SSD1306_Write(false, 0x00); // Display the data
        SSD1306_CursorPos++;
    }
}

void SSD1306_String(unsigned char *str)
{
    while (*str)
    {
        SSD1306_PrintChar(*str++);
    }
}

void SSD1306_InvertDisplay(bool need_to_invert)
{
    if (need_to_invert)
    {
        SSD1306_Write(true, 0xA7); // Invert the display
    }
    else
    {
        SSD1306_Write(true, 0xA6); // Normal display
    }
}

void SSD1306_SetCursor(uint8_t lineNo, uint8_t cursorPos)
{
    /* Move the Cursor to specified position only if it is in range */
    if ((lineNo <= SSD1306_MAX_LINE) && (cursorPos < SSD1306_MAX_SEG))
    {
        SSD1306_LineNum = lineNo;      // Save the specified line number
        SSD1306_CursorPos = cursorPos; // Save the specified cursor position

        SSD1306_Write(true, 0x21);                // cmd for the column start and end address
        SSD1306_Write(true, cursorPos);           // column start addr
        SSD1306_Write(true, SSD1306_MAX_SEG - 1); // column end addr

        SSD1306_Write(true, 0x22);             // cmd for the page start and end address
        SSD1306_Write(true, lineNo);           // page start addr
        SSD1306_Write(true, SSD1306_MAX_LINE); // page end addr
    }
}

/*
** This function is specific to the SSD_1306 OLED.
** This function sets the brightness of  the display.
**
**  Arguments:
**      brightnessValue   -> true  - invert display
**
*/
void SSD1306_SetBrightness(uint8_t brightnessValue)
{
    SSD1306_Write(true, 0x81);            // Contrast command
    SSD1306_Write(true, brightnessValue); // Contrast value (default value = 0x7F)
}

/*
** This function is specific to the SSD_1306 OLED.
** This function Scrolls the data right/left in horizontally.
**
**  Arguments:
**      is_left_scroll   -> true  - left horizontal scroll
                            false - right horizontal scroll
        start_line_no    -> Start address of the line to scroll
        end_line_no      -> End address of the line to scroll
**
*/
void SSD1306_StartScrollHorizontal(bool is_left_scroll,
                                          uint8_t start_line_no,
                                          uint8_t end_line_no)
{
    if (is_left_scroll)
    {
        // left horizontal scroll
        SSD1306_Write(true, 0x27);
    }
    else
    {
        // right horizontal scroll
        SSD1306_Write(true, 0x26);
    }

    SSD1306_Write(true, 0x00);          // Dummy byte (dont change)
    SSD1306_Write(true, start_line_no); // Start page address
    SSD1306_Write(true, 0x00);          // 5 frames interval
    SSD1306_Write(true, end_line_no);   // End page address
    SSD1306_Write(true, 0x00);          // Dummy byte (dont change)
    SSD1306_Write(true, 0xFF);          // Dummy byte (dont change)
    SSD1306_Write(true, 0x2F);          // activate scroll
}

void SSD1306_StartScrollVerticalHorizontal(bool is_vertical_left_scroll,
                                                  uint8_t start_line_no,
                                                  uint8_t end_line_no,
                                                  uint8_t vertical_area,
                                                  uint8_t rows)
{

    SSD1306_Write(true, 0xA3);          // Set Vertical Scroll Area
    SSD1306_Write(true, 0x00);          // Check datasheet
    SSD1306_Write(true, vertical_area); // area for vertical scroll

    if (is_vertical_left_scroll)
    {
        // vertical and left horizontal scroll
        SSD1306_Write(true, 0x2A);
    }
    else
    {
        // vertical and right horizontal scroll
        SSD1306_Write(true, 0x29);
    }

    SSD1306_Write(true, 0x00);          // Dummy byte (dont change)
    SSD1306_Write(true, start_line_no); // Start page address
    SSD1306_Write(true, 0x00);          // 5 frames interval
    SSD1306_Write(true, end_line_no);   // End page address
    SSD1306_Write(true, rows);          // Vertical scrolling offset
    SSD1306_Write(true, 0x2F);          // activate scroll
}

void SSD1306_Fill(unsigned char data)
{
    unsigned int total = 128 * 8; // 8 pages x 128 segments x 8 bits of data
    unsigned int i = 0;

    // Fill the Display
    for (i = 0; i < total; i++)
    {
        SSD1306_Write(false, data);
    }
}

int SSD1306_DisplayInit(struct i2c_client *client)
{
    client_data_ptr = client;
    msleep(100); // delay

    /*
    ** Commands to initialize the SSD_1306 OLED Display
    */
    SSD1306_Write(true, 0xAE); // Entire Display OFF
    SSD1306_Write(true, 0xD5); // Set Display Clock Divide Ratio and Oscillator Frequency
    SSD1306_Write(true, 0x80); // Default Setting for Display Clock Divide Ratio and Oscillator Frequency that is recommended
    SSD1306_Write(true, 0xA8); // Set Multiplex Ratio
    SSD1306_Write(true, 0x3F); // 64 COM lines
    SSD1306_Write(true, 0xD3); // Set display offset
    SSD1306_Write(true, 0x00); // 0 offset
    SSD1306_Write(true, 0x40); // Set first line as the start line of the display
    SSD1306_Write(true, 0x8D); // Charge pump
    SSD1306_Write(true, 0x14); // Enable charge dump during display on
    SSD1306_Write(true, 0x20); // Set memory addressing mode
    SSD1306_Write(true, 0x00); // Horizontal addressing mode
    SSD1306_Write(true, 0xA1); // Set segment remap with column address 127 mapped to segment 0
    SSD1306_Write(true, 0xC8); // Set com output scan direction, scan from com63 to com 0
    SSD1306_Write(true, 0xDA); // Set com pins hardware configuration
    SSD1306_Write(true, 0x12); // Alternative com pin configuration, disable com left/right remap
    SSD1306_Write(true, 0x81); // Set contrast control
    SSD1306_Write(true, 0x80); // Set Contrast to 128
    SSD1306_Write(true, 0xD9); // Set pre-charge period
    SSD1306_Write(true, 0xF1); // Phase 1 period of 15 DCLK, Phase 2 period of 1 DCLK
    SSD1306_Write(true, 0xDB); // Set Vcomh deselect level
    SSD1306_Write(true, 0x20); // Vcomh deselect level ~ 0.77 Vcc
    SSD1306_Write(true, 0xA4); // Entire display ON, resume to RAM content display
    SSD1306_Write(true, 0xA6); // Set Display in Normal Mode, 1 = ON, 0 = OFF
    SSD1306_Write(true, 0x2E); // Deactivate scroll
    SSD1306_Write(true, 0xAF); // Display ON in normal mode

    // Clear the display
    SSD1306_Fill(0x00);
    return 0;
}
