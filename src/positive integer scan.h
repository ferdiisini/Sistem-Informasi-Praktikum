#include <ctype.h>

int positive_scanfd() {
	char str[10];
	char strclone[10];
	int alphabet = 0;
	int number = 0;
	int numflag = 0;
	int i;
	scanf("%s", &str);
	while (numflag != 1) {
		for (i = 0; str[i] != '\0'; i++) {
			// cek huruf dan simbol lainnya (selain angka)
			if (ispunct(str[i]) != 0 || isalpha(str[i]) != 0) {
				alphabet++;
			}
		}
		if (alphabet > 0||strlen(str)>9) {
			printf("\nInput tidak valid atau terlalu panjang! Untuk NPM, hanya 9 digit saja.\n");
			printf("Masukkan input kembali : ");
			scanf("%s", &str);
			alphabet = 0;
		}
		else {
			numflag = 1;
		}
	}
	strcpy(strclone, str);
	strrev(strclone);
	for (i = 0; strclone[i] != '\0'; i++) {
		number = (strclone[i] - 48) * pow(10, i) + number;
	}
	numflag = 0;
	return number;
}
