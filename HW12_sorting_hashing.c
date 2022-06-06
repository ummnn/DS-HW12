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

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
    printf("[----- [�̵���] [2019038027] -----]\n\n");
	char command; //��ɾ �����ϴ� ����
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
		scanf(" %c", &command); //��ɾ �Է¹޴´�

		switch(command) {
		case 'z': case 'Z': //z or Z�� ���
			initialize(&array); //initialize �Լ� ����
			break;
		case 'q': case 'Q': //q or Q�� ���
			freeArray(array); //freeArray�Լ� ����
			break;
		case 's': case 'S': //s or S�� ���
			selectionSort(array);
			break;
		case 'i': case 'I': //i or I�� ���
			insertionSort(array);
			break;
		case 'b': case 'B': //b or B�� ���
			bubbleSort(array);
			break;
		case 'l': case 'L': //i or I�� ���
			shellSort(array);
			break;
		case 'k': case 'K': //k or K�� ���
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H': //h or H�� ���
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E': //e or E�� ���
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P': //p or P�� ���
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q or Q�� �Էµ� �� ���� �ݺ�

	return 1;
}
//initialize �Լ�
int initialize(int** a)
{
	int *temp = NULL;

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) { //*a�� NULL�̶��
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //int * MAX_ARRAY_SIZE�� ũ�⸸ŭ �޸� �Ҵ�
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else //NULL�� �ƴ϶��
		temp = *a; //temp�� *a ����

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}
//�޸� ���� �Լ�
int freeArray(int *a)
{
	if(a != NULL) //a�� NULL�� �ƴ϶�� �ݺ�
		free(a); //�޸� �Ҵ� ����
	return 0;
}

//��� �Լ�
void printArray(int *a)
{
	if (a == NULL) { //a�� NULL�� ��
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); //�迭�� ����Ѵ�
	printf("\n");
}

//�������� �Լ�
int selectionSort(int *a)
{
	int min; //�ּڰ�
	int minindex; //�ּڰ��� �ε���
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //printArray�Լ� ����

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //minindex�� i����
		min = a[i]; //min�� a[i] ����
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) //min�� a[j]���� ũ�ٸ�
			{
				min = a[j]; //min�� a[j] ����
				minindex = j; //minindex�� j����
			}
		}
		a[minindex] = a[i]; //a[minindex]�� a[i]����
		a[i] = min; //a[i]�� min ����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //printArray�Լ� ����
	return 0;
}
//�������� �Լ�
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; //t�� a[i] ����
		j = i; //j�� i ����
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1]; //a[j]�� a[j-1] ����
			j--; //j - 1
		}
		a[j] = t; //a[j]�� t ���� 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //printArray�Լ� ����

	return 0;
}

//�������� �Լ�
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) //a[j-1]�� a[j]���� ũ�ٸ�
			{
				t = a[j-1]; //t�� a[j-1]�� ����
				a[j-1] = a[j]; //a[j-1]�� a[j]����
				a[j] = t; //a[j]�� t ����
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //printArray�Լ� ����

	return 0;
}

//shell���� �Լ�
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //v�� a[j] ����
				k = j; //k�� j����
				while (k > h-1 && a[k-h] > v) //k�� h-1���� ũ�ų� a[k-h]�� v���� ũ�ٸ� �ݺ�
				{
					a[k] = a[k-h]; //a[k]�� a[k-h] ����
					k -= h; //k�� k-h ����
				}
				a[k] = v; //a[k]�� v ����
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //printArray�Լ� ����

	return 0;
}
//quick���� �Լ�
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; //v�� a[n-1]����
		i = -1; //i�� -1 ����
		j = n - 1; //j�� n-1 ����

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break; //i�� j���� ũ�ٸ� break
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i]; //t�� a[i] ����
		a[i] = a[n-1]; //a[i]�� a[n-1] ����
		a[n-1] = t; //a[n-1]�� t ����

		quickSort(a, i); //quickSort �Լ� ����
		quickSort(a+i+1, n-i-1); //quickSort �Լ� ����
	}


	return 0;
}
//hashCode �Լ�
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //key % MAX_HASH_TABLE_SIZE ����
}
//hashing �Լ�
int hashing(int *a, int **ht)
{
	int *hashtable = NULL; //hashtable NULL�� �ʱ�ȭ

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) { //*ht�� NULL�̶��
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1; //key�� -1����
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



