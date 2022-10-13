if avr-gcc -Os -mmcu=attiny10 -o tmp.elf *.c
then
	avr-objcopy -j .text -j .data -O ihex tmp.elf tmp.hex
	avrdude -p t10 -c usbasp -P usb -U flash:w:tmp.hex
	rm tmp.elf
	rm tmp.hex
fi