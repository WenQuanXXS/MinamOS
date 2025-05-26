unsigned char port_byte_in (unsigned short port){
    unsigned char result;
    //get the byte from the port
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (unsigned short port, unsigned char data){
    //send the byte to the port
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in (unsigned short port){
    //get the word from the port
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (unsigned short port, unsigned short data){
    //send the word to the port
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}