//swap array cell/subarray
void swap(int* xp, int* yp) {
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
	return;
}

// cetak larik (jenis bilangan bulat dengan for, cetak per angka)
void printArray(int arr[],int size) {
	int i;
	int n = 0;
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	return;
}

//selection search
void sort(int arr[], char *arr2[], int n, int mode) {
	int i;
	int j;
	int min_idx;
	char temp[100];
	// cek satu-satu
	if (mode == 0){
		for (i = 0; i < n - 1; i++) {
			// cari nilai minimum
			min_idx = i;
			for (j = i + 1; j < n; j++){
				if (arr[j] < arr[min_idx]){
					min_idx = j;
				}
			// tukar isi larik
			}
			swap(&arr[min_idx], &arr[i]);
			strcpy(temp, arr2[min_idx]);
			strcpy(arr2[min_idx], arr2[i]);
			strcpy(arr2[i], temp);
		}
	}
	else{
		for(i=0; i<n; i++){
			for(j=0; j<n-1-i; j++){
	      		if(strcmp(arr2[j], arr2[j+1]) > 0){
	        	//tukar isi larik
	        	swap(&arr[j], &arr[j+1]);
	        	strcpy(temp, arr2[j]);
	        	strcpy(arr2[j], arr2[j+1]);
	        	strcpy(arr2[j+1], temp);
	      		}
	    	}
  		}
	}
	return;
}
void capword(char arr[]){
	int i = 0;
	for(i=0; arr[i]!='\0'; i++){
		//cek huruf kecil
		if(i==0){
			if((arr[i]>='a' && arr[i]<='z'))
				arr[i]=arr[i]-32; //jadikan huruf besar, nomor ASCII
			continue;
		}
		if(arr[i]==' '){//cek spasi
			//jika spasi ditemukan, cek selanjutnya
			++i;
			//jika huruf kecil
			if(arr[i]>='a' && arr[i]<='z'){
				arr[i]=arr[i]-32;
				continue;
			}
		}
		else{
			//jika ada huruf besar
			if(arr[i]>='A' && arr[i]<='Z')
				arr[i]=arr[i]+32;
		}
	}
}

