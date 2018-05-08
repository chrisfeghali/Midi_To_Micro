#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define FILE_NAME1 "midifile.txt"
#define FILE_NAME2 "midievents.txt"
#define FILE_NAME3 "MidiToMicro.txt"

#define PPQ 0.15  						//Increase/decrease 0.15 for faster/slower song

void PrintArr(FILE *fp, long long int arr[], int len, char* str);
int ReadFourNums(int arr[], int *p);
int GetNum (char c, FILE *fp);
int GetNote(int num);

int main (void){
	int a[100000] = {0};
	int b[100000] = {0};
	long long int notes[10000] = {0};
	long int times[100000] = {0};
	long long int TimeDelay[10000] = {0};
	long long int NoteDuration[10000] = {0};
	long long int NoteNum[10000] = {0};
	int i = 0;
	int x = 0;
	int count = 0,NoteCount = 0 ;
	int ppq;
	int LineCount = 0;
	int line2 = 1, line6 =0;
	char* TD = "TimeDelay";
	char* N = "Notes";
	char* NN = "NoteNum";
	FILE *fp;
	FILE *fp2;
	FILE *fp3;
	fp2 = fopen(FILE_NAME2, "r");

	if(fp2 == NULL){
		printf("Can't open %s\n", FILE_NAME2);
	} else {

		printf("%s was opened. \n", FILE_NAME2);
		char c2;
		while ((c2 = getc(fp2)) != EOF){
			if (c2 == '|'){
				LineCount++;
				if(LineCount == (2 + 8*line2)){
					times[line2++] = GetNum(c2,fp2);
					printf("time %lld \n", times[line2 - 1]);
					LineCount++;
				}
				if(LineCount == (14+16*line6)){
					line6++;
					c2 = getc(fp2);
					notes[NoteCount++] = GetNote((GetNum(c2,fp2)));
					printf("note to send is %d\n", notes[NoteCount - 1]);
					LineCount++;
				}
			}
		}

		fclose(fp2);
		for (int i = 0, k=0; i < line2 - 1;i+=2,k++){
			TimeDelay[k] = ((times[i+1] - times[i])*600)/(PPQ* 240); 
			NoteDuration[k] = ((times[i+2] - times[i+1])*60000)/PPQ * 240);
			printf("Time2 - Time1 %d = %d - %d = %d\n",(k+1) ,(times[i+2]),(times[i+1]), (times[i+2] - times[i+1]) );
			printf("Time delay %d\n", TimeDelay[k]);
			printf("Note Duration %lld\n", NoteDuration[k]);
		}

		printf("line 2 is %d\n", line2);

		for(int i =0; i < NoteCount ;i++){
			NoteNum[i] = NoteDuration[i]/(notes[i]*2);
			printf("NoteNum %d is %lld\n",(i+1), NoteNum[i]);
		}

		printf("Times at 126 and 127: %lld and %lld", times[125], times[126]);
		printf("NoteDuration at 126 %lld\n", NoteDuration[125]);
		printf("note at 126 %lld\n", notes[125]);
		fp3 =  fopen(FILE_NAME3, "w");
		
		if(fp3 == NULL){
			printf("Can't open %s\n", FILE_NAME3);
		} else {
			PrintArr(fp3, notes, NoteCount, N);
			PrintArr(fp3, NoteNum, NoteCount, NN);
			PrintArr(fp3, TimeDelay, NoteCount, TD);
		}
	}
}
	
void PrintArr(FILE *fp,long long int arr[], int len, char* str){
	int i;
	fprintf(fp,"NoteCount is %d\n", len);
	fprintf(fp, "\n %s array: ", str);
	fprintf(fp, "{");
	for (i = 0; i < (len - 1);i++){
		fprintf(fp, " %lld,",arr[i]);
		if (((i+1) % 19) == 0){
			fprintf(fp, "\\\n");
		}
	}
	fprintf(fp, " %d", arr[i]);
	fprintf(fp, "};\n\n");
	
}

int ReadFourNums(int arr[], int *p){
	int x = *p;
	int num = arr[x]*16*16*16 + arr[++x]*16*16 + arr[++x]*16 + arr[++x];
	x++;
	*p = x;
	return num;
}

int GetNum (char c, FILE *fp){
	int a[10000] = {0}, z = 0, i= 0;
	c = getc(fp);
	switch (c){
		case '0':
			a[i++] = 0;
			break;
		case '1':
			a[i++] = 1;
			break;
		case '2':
			a[i++] = 2;
			break;
		case '3':
			a[i++] = 3;
			break;
		case '4':
			a[i++] = 4;
			break;
		case '5':
			a[i++] = 5;
			break;
		case '6':
			a[i++] = 6;
			break;
		case '7':
			a[i++] = 7;
			break;
		case '8':
			a[i++] = 8;
			break;
		case '9':
			a[i++] = 9;
			break;
		default:
			break;
	}
	
	while ((c = getc(fp)) != '|'){
		switch (c){
			case '0':
				a[i++] = 0;
				break;
			case '1':
				a[i++] = 1;
				break;
			case '2':
				a[i++] = 2;
				break;
			case '3':
				a[i++] = 3;
				break;
			case '4':
				a[i++] = 4;
				break;
			case '5':
				a[i++] = 5;
				break;
			case '6':
				a[i++] = 6;
				break;
			case '7':
				a[i++] = 7;
				break;
			case '8':
				a[i++] = 8;
				break;
			case '9':
				a[i++] = 9;
				break;
			default:
				break;
		}
	}
	i--;
	int j = i;
	for(int k=0;i>0;k++,i--){
		int x = i;
		for(;x!=0;x--){
			a[k]*=10;
		}
	}
	for (;j>=0;j--){
	  z+= a[j];
	}
	return z;
}

int GetNote(int num){
	double x;
	int note;
	switch(num){
		case 12:
		x = 16.35;
		break;
		case 13:
		x = 17.32;
		break;
		case 14:
		x = 18.35;
		break;
		case 15:
		x = 19.45;
		break;
		case 16:
		x = 20.60;
		break;
		case 17:
		x = 21.83;
		break;
		case 18:
		x = 23.12;
		break;
		case 19:
		x = 24.50;
		break;
		case 20:
		x = 25.96;
		break;
		case 21:
		x = 27.50;
		break;
		case 22:
		x = 29.14;
		break;
		case 23:
		x = 30.87;
		break;
		case 24:
		x = 32.70;
		break;
		case 25:
		x = 34.65;
		break;
		case 26:
		x = 36.71;
		break;
		case 27:
		x = 38.89;
		break;
		case 28:
		x = 41.20;
		break;
		case 29:
		x = 43.65;
		break;
		case 30:
		x = 46.25;
		break;
		case 31:
		x = 49.00;
		break;
		case 32:
		x = 51.91;
		break;
		case 33:
		x = 55.00;
		break;
		case 34:
		x = 58.27;
		break;
		case 35:
		x = 61.74;
		break;
		case 36:
		x = 65.41;
		break;
		case 37:
		x = 69.30;
		break;
		case 38:
		x = 73.42;
		break;
		case 39:
		x = 77.78;
		case 40:
		x = 82.41;
		break;
		case 41:
		x = 87.31;
		break;
		case 42:
		x = 92.50;
		break;
		case 43:
		x = 98.00;
		break;
		case 44:
		x = 103.83;
		break;
		case 45:
		x = 110.00;
		break;
		case 46:
		x = 116.54;
		break;
		case 47:
		x = 123.47;
		break;
		case 48:
		x = 130.81;
		break;
		case 49:
		x = 138.59;
		break;
		case 50:
		x = 146.83;
		break;
		case 51:
		x = 155.56;
		break;
		case 52:
		x = 164.81;
		break;
		case 53:
		x = 174.61;
		break;
		case 54:
		x = 185.00;
		break;
		case 55:
		x = 196.00;
		break;
		case 56:
		x = 207.65;
		break;
		case 57:
		x = 220.00;
		break;
		case 58:
		x = 233.08;
		break;
		case 59:
		x = 246.94;
		break;
		case 60:
		x = 261.63;
		break;
		case 61:
		x = 277.18;
		break;
		case 62:
		x = 293.66;
		break;
		case 63:
		x = 311.13;
		break;
		case 64:
		x = 329.63;
		break;
		case 65:
		x = 349.23;
		break;
		case 66:
		x = 369.99;
		break;
		case 67:
		x = 392.00;
		break;
		case 68:
		x = 415.30;
		break;
		case 69:
		x = 440.00;
		break;
		case 70:
		x = 466.16;
		break;
		case 71:
		x = 493.88;
		break;
		case 72:
		x = 523.25;
		break;
		case 73:
		x = 554.39;
		break;
		case 74:
		x = 587.33;
		break;
		case 75:
		x = 622.25;
		break;
		case 76:
		x = 659.25;
		break;
		case 77:
		x = 698.46;
		break;
		case 78:
		x = 739.99;
		break;
		case 79:
		x = 783.99;
		break;
		case 80:
		x = 830.61;
		break;
		case 81:
		x = 880.00;
		break;
		case 82:
		x = 932.33;
		break;
		case 83:
		x = 987.77;
		break;
		case 84:
		x = 1046.50;
		break;
		case 85:
		x = 1108.73;
		break;
		case 86:
		x = 1174.66;
		break;
		case 87:
		x = 1244.51;
		break;
		case 88:
		x = 1318.51;
		break;
		case 89:
		x = 1396.91;
		break;
		case 90:
		x = 1479.98;
		break;
		case 91:
		x = 1567.98;
		break;
		case 92:
		x = 1661.22;
		break;
		case 93:
		x = 1760.00;
		break;
		case 94:
		x = 1864.66;
		break;
		case 95:
		x = 1975.53;
		break;
		case 96:
		x = 2093.00;
		break;
		case 97:
		x = 2217.456;
		break;
		case 98:
		x = 2349.32;
		break;
		case 99:
		x = 2489.02;
		break;
		case 100:
		x = 2637.02;
		break;
		case 101:
		x = 2793.83;
		break;
		case 102:
		x = 2959.96;
		break;
		case 103:
		x = 3135.96;
		break;
		case 104:
		x = 3322.44;
		break;
		case 105:
		x = 3520.00;
		break;
		case 106:
		x = 3729.31;
		break;
		case 107:
		x = 3951.07;
		break;
		case 108:
		x = 4186.01;
		break;
		case 109:
		x = 4434.92;
		break;
		case 110:
		x = 4698.63;
		break;
		case 111:
		x = 4978.03;
		break;
		case 112:
		x = 5274.04;
		break;
		case 113:
		x = 5587.65;
		break;
		case 114:
		x = 5919.91;
		break;
		case 115:
		x = 6271.93;
		break;
		case 116:
		x = 6644.88;
		break;
		case 117:
		x = 7040.00;
		break;
		case 118:
		x = 7458.62;
		break;
		case 119:
		x = 7902.13;
		break;
		default:
		break;
	}
	note = 1000000/(2*x);
	return note;
}

