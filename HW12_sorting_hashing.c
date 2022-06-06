/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
    printf("[----- [이동현] [2019038027] -----]\n\n");
	char command; //명령어를 저장하는 변수
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령어를 입력받는다

		switch(command) {
		case 'z': case 'Z': //z or Z일 경우
			initialize(&array); //initialize 함수 실행
			break;
		case 'q': case 'Q': //q or Q일 경우
			freeArray(array); //freeArray함수 실행
			break;
		case 's': case 'S': //s or S일 경우
			selectionSort(array); //selectionSort 함수 실행
			break;
		case 'i': case 'I': //i or I일 경우
			insertionSort(array); //insertionSort 함수 실행
			break;
		case 'b': case 'B': //b or B일 경우
			bubbleSort(array); //bubbleSort 함수 실행
			break;
		case 'l': case 'L': //i or I일 경우
			shellSort(array); //shellSort함수 싫행
			break;
		case 'k': case 'K': //k or K일 경우
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //printArray함수 실행
			quickSort(array, MAX_ARRAY_SIZE); //quickSort 함수 실행
			printf("----------------------------------------------------------------\n");
			printArray(array); //printArray함수 실행

			break;

		case 'h': case 'H': //h or H일 경우
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //printArray 함수 실행
			hashing(array, &hashtable); //hashing 함수 실행
			printArray(hashtable); //printArray 함수 실행
			break;

		case 'e': case 'E': //e or E일 경우
			printf("Your Key = "); 
			scanf("%d", &key); //key를 입력받는다
			printArray(hashtable); //printArray함수 실행
			index = search(hashtable, key); //index에 search함수의 리턴값 저장
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P': //p or P일 경우
			printArray(array); //printArray함수 실행
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q or Q가 입력될 떄 까지 반복

	return 1;
}
//initialize 함수
int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) { //*a가 NULL이라면
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //int * MAX_ARRAY_SIZE의 크기만큼 메모리 할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else //NULL이 아니라면
		temp = *a; //temp에 *a 저장

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}
//메모리 해제 함수
int freeArray(int *a)
{
	if(a != NULL) //a가 NULL이 아니라면 반복
		free(a); //메모리 할당 해제
	return 0;
}

//출력 함수
void printArray(int *a)
{
	if (a == NULL) { //a가 NULL일 때
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); //배열을 출력한다
	printf("\n");
}

//선택정렬 함수
int selectionSort(int *a)
{
	int min; //최솟값
	int minindex; //최솟값의 인덱스
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //printArray함수 실행

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //minindex에 i저장
		min = a[i]; //min에 a[i] 저장
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) //min이 a[j]보다 크다면
			{
				min = a[j]; //min에 a[j] 저장
				minindex = j; //minindex에 j저장
			}
		}
		a[minindex] = a[i]; //a[minindex]에 a[i]저장
		a[i] = min; //a[i]에 min 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //printArray함수 실행
	return 0;
}
//삽입정렬 함수
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; //t에 a[i] 저장
		j = i; //j에 i 저장
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1]; //a[j]에 a[j-1] 저장
			j--; //j - 1
		}
		a[j] = t; //a[j]에 t 저장 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //printArray함수 실행

	return 0;
}

//버블정렬 함수
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //printArray함수 실행

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) //a[j-1]이 a[j]보다 크다면
			{
				t = a[j-1]; //t에 a[j-1]을 저장
				a[j-1] = a[j]; //a[j-1]에 a[j]저장
				a[j] = t; //a[j]에 t 저장
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //printArray함수 실행

	return 0;
}

//shell정렬 함수
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //printArray함수 실행

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //v에 a[j] 저장
				k = j; //k에 j저장
				while (k > h-1 && a[k-h] > v) //k가 h-1보다 크거나 a[k-h]가 v보다 크다면 반복
				{
					a[k] = a[k-h]; //a[k]에 a[k-h] 저장
					k -= h; //k에 k-h 저장
				}
				a[k] = v; //a[k]에 v 저장
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //printArray함수 실행

	return 0;
}
//quick정렬 함수
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; //v에 a[n-1]저장
		i = -1; //i에 -1 저장
		j = n - 1; //j에 n-1 저장

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break; //i가 j보다 크다면 break
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i]; //t에 a[i] 저장
		a[i] = a[n-1]; //a[i]에 a[n-1] 저장
		a[n-1] = t; //a[n-1]에 t 저장

		quickSort(a, i); //quickSort 함수 실행
		quickSort(a+i+1, n-i-1); //quickSort 함수 실행
	}


	return 0;
}
//hashCode 함수
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //key % MAX_HASH_TABLE_SIZE 리턴
}
//hashing 함수
int hashing(int *a, int **ht)
{
	int *hashtable = NULL; //hashtable NULL로 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) { //*ht가 NULL이라면
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1; //key에 -1저장
	int hashcode = -1; //hashcode에 -1 저장
	int index = -1; //index에 -1 저장
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; //key에 a[i] 저장
		hashcode = hashCode(key); //hashcode 함수 실행 후 hashcode에 저장
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //hashtable[hashcode]가 -1이라면
		{
			hashtable[hashcode] = key; //hashtable[hashcode]에 key 저장
		} else 	{

			index = hashcode; //index에 hashcode 저장

			while(hashtable[index] != -1) //hahstable[index]가 -1이 아니라면 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //index에 index+1 % MAX_HASH_TABLE 저장
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //hashtable[index]에 key 저장
		}
	}

	return 0;
}
//search 함수
int search(int *ht, int key)
{
	int index = hashCode(key); //index에 hashcCode함수 리턴값 저장

	if(ht[index] == key) //ht[index]가 key와 같다면
		return index; //index 리턴

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE; //index에 index % MAX_HASH_TABLE_SIZE 저장
	}
	return index; //index 리턴
}



