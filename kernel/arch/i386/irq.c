#include <kernel/pic.h>
#include <drivers/keyboard.h>

void int32() { /* Timer */
    pic_send_eoi(0);
}

void int33() { /* Keyboard Handler */
    pic_send_eoi(1);
    keyboard_interrupt();
}

void int34() {
    pic_send_eoi(2);
}

void int35() {
    pic_send_eoi(3);
}

void int36() {
    pic_send_eoi(4);
}

void int37() {
    pic_send_eoi(5);
}

void int38() {
    pic_send_eoi(6);
}

void int39() {
    pic_send_eoi(7);
}

void int40() {
    pic_send_eoi(8);
}

void int41() {
    pic_send_eoi(9);
}

void int42() {
    pic_send_eoi(10);
}

void int43() {
    pic_send_eoi(11);
}

void int44() {
    pic_send_eoi(12);
}

void int45() {
    pic_send_eoi(13);
}

void int46() {
    pic_send_eoi(14);
}

void int47() {
    pic_send_eoi(15);
}
