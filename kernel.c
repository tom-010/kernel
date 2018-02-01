#include "messages.c"


char *current_line = "                                                                                ";
char current_line_position = 0;

void clear_current_line(void) {
    current_line_position = 0;
    for(int i=0; i<COLUMNS_IN_LINE; i++)
        current_line[i] = ' ';
}

void keyboard_handler_main(void) {
    unsigned char status;
    char keycode;

    /* write EOI */
    write_port(0x20, 0x20);

    status = read_port(KEYBOARD_STATUS_PORT);
    /* Lowest bit of status will be set if buffer is not empty */
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        if(keycode < 0)
            return;

        if(keycode == ENTER_KEY_CODE) {
            new_line();
            println(current_line);

            clear_current_line();
            return;
        }

        current_line[current_line_position++] = keyboard_map[(unsigned char) keycode];


        video_pointer[current_cursor_location++] = keyboard_map[(unsigned char) keycode];
        video_pointer[current_cursor_location++] = 0x07;
    }
}


void kmain(void) {
    clear_screen();
    welcome_message();

    idt_init();
    kb_init();

    while(1);
}
