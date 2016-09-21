#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga.h>

// may need to be non-static in the future
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_GREEN, COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putnewline()
{
    terminal_column = 0;
    terminal_row = (terminal_row + 1) % VGA_HEIGHT;
}

void terminal_increment_cursor()
{
	if ( ++terminal_column == VGA_WIDTH )
	{
		terminal_column = 0;
		if ( ++terminal_row == VGA_HEIGHT )
		{
			terminal_row = 0;
		}
	}

}

void terminal_decrement_cursor()
{
	if ( terminal_column != 0 )
	{
        terminal_column -= 1;
	}

}

void terminal_putchar(char c)
{
    if(c == '\n') 
    {
        terminal_putnewline();
        return;
    }
    else if(c == '\b')
    {
        terminal_decrement_cursor();
        terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        return;
    }
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    terminal_increment_cursor();
}

void terminal_write(const char* data, size_t size)
{
	for ( size_t i = 0; i < size; i++ )
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}
