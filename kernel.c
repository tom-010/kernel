

/*
 * All this kernel will do is clear the screen and write to it the string “Bavarian Coding Group”.
 *
 * In kernel.asm, we made a call to the function kmain(). So our C code will start executing at kmain()
 */
void kmain(void) {
    const char* str = "Bavarian Coding Group";
    char *vidptr = (char*)0xb8000; // video memory begins here -> We want output stuff
                                   // Pointer vidptr that points to the address 0xb8000.
                                   // This address is the start of video memory in protected mode.
                                   // The screen’s text memory is simply a chunk of memory in our address space.
                                   // The memory mapped input/output for the screen starts at 0xb8000 and
                                   // supports 25 lines, each line contain 80 ascii characters.
    unsigned int i = 0;
    unsigned int j = 0;

    /* this loops clears the screen
       there are 25 lines each of 80 columns;
       each element takes 2 bytes
    */
    while(j < 80 * 25 * 2) {
        /*
         Each character element in this text memory is represented by 16 bits (2 bytes),
         rather than 8 bits (1 byte) which we are used to.
        */

        // blank character
        vidptr[j] = ' '; // The first byte should have the representation of the character as in ASCII.

         /* attribute-byte - light grey on black screen */
        vidptr[j+1] = 0x07; // The second byte is the attribute-byte.
                            // This describes the formatting of the character including attributes such as color.
        j = j + 2;
    }

    j = 0;

    // This loop writes the string to video memory
    while(str[j] != '\0') {
        // The character's ascii
        vidptr[i] = str[j];
        // attribute-byte: give character black bg and light grey fore-ground
        vidptr[i+1] = 0x07;
        ++j;
        i = i+2;
    }
    return;
}

/*
Color Table
-----------
 0 - Black,
 1 - Blue,
 2 - Green,
 3 - Cyan,
 4 - Red,
 5 - Magenta,
 6 - Brown,
 7 - Light Grey,
 8 - Dark Grey,
 9 - Light Blue,
 10/a - Light Green,
 11/b - Light Cyan,
 12/c - Light Red,
 13/d - Light Magenta,
 14/e - Light Brown,
 15/f – White.

Example:
    To print the character s in green color on black background,
    we will store the character s in the first byte of the video
    memory address and the value 0x02 in the second byte.
    0 represents black background and 2 represents green foreground.
 */