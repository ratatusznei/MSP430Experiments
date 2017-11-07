#include "SambaTopKeys.h"

void Samba_init () {
	// Make these ones output to GND
	setBits(MatrixDIR, WRITE_KEYS);
	clearBits(MatrixOUT, WRITE_KEYS);

	// Make these ones read
	clearBits(MatrixDIR, READ_KEYS);

	// Pull ups
	setBits(MatrixREN, READ_KEYS);
	setBits(MatrixOUT, READ_KEYS);	

	// Interrupt en, high to low transition
	setBits(MatrixIE, READ_KEYS);
	setBits(MatrixIES, READ_KEYS);
	MatrixIFG = 0;

	// Clear SELs
	clearBits(MatrixSEL, READ_KEYS | WRITE_KEYS);
	clearBits(MatrixSEL2, READ_KEYS | WRITE_KEYS);
}

char Samba_getPressedCollumn (char rowPin) {
	// Check first collumn
	clearBits(MatrixOUT, Keys1470);
	setBits(MatrixOUT, Keys258E | Keys369C);

	if (isLOW(rowPin)) {
		clearBits(MatrixOUT, Keys1470 | Keys258E | Keys369C);
		return '1';
	}

	// Check second collumn
	clearBits(MatrixOUT, Keys258E);
	setBits(MatrixOUT, Keys1470 | Keys369C);

	if (isLOW(rowPin)) {
		clearBits(MatrixOUT, Keys1470 | Keys258E | Keys369C);
		return '2';
	}

	// Check third collumn
	clearBits(MatrixOUT, Keys369C);
	setBits(MatrixOUT, Keys1470 | Keys258E);

	if (isLOW(rowPin)) {
		clearBits(MatrixOUT, Keys1470 | Keys258E | Keys369C);
		return '3';
	}

	clearBits(MatrixOUT, Keys1470 | Keys258E | Keys369C);
	return '\0';
}

char Samba_debounceLOW (char pin) {
	char debounceCounter = DEBOUNCE_DELAY;

	while (debounceCounter--) {
		if (isHIGH(pin)) {
			return 0;
		}
	}

	return 1;
}

char Samba_getchar () {
	while ((MatrixIN & READ_KEYS) == READ_KEYS) {
		// Wait button press
	}

	if (isLOW(Keys123)) {
		if (Samba_debounceLOW(Keys123)) {
			switch (Samba_getPressedCollumn(Keys123)) {
			case '1':
				return '1';
			case '2':
				return '2';
			case '3': 
				return '3';
			}
		}
	}

	if (isLOW(Keys456)) {
		if (Samba_debounceLOW(Keys456)) {
			switch (Samba_getPressedCollumn(Keys456)) {
			case '1':
				return '4';
			case '2':
				return '5';
			case '3': 
				return '6';
			}
		}
	}

	if (isLOW(Keys789)) {
		if (Samba_debounceLOW(Keys789)) {
			switch (Samba_getPressedCollumn(Keys789)) {
			case '1':
				return '7';
			case '2':
				return '8';
			case '3': 
				return '9';
			}
		}
	}

	if (isLOW(Keys0EC)) {
		if (Samba_debounceLOW(Keys0EC)) {
			switch (Samba_getPressedCollumn(Keys0EC)) {
			case '1':
				return '0';
			case '2':
				return 'E';
			case '3': 
				return 'C';
			}
		}
	}

	return '\0';
}