#include<stdio.h>
#include<stdlib.h>

#define MAX 30000 // 質數陣列總量 
#define DIGITMAX 10 // 數字分割存取陣列總量 
#define RIGHTMAX 200 // 右截短陣列總量 
#define LEFTMAX 1000 // 左截短函式總量 

void findPrime( int a[] ); // 找質數函式 
int primeCheck( int ); // 左右截短質數找尋函式 

void primeOut( int a[], int ); // 輸出函式 

void digitSplit( int a[], int digitDis[] ); // 將各個質數進行位數分割函式 
int truncatablePrimeLeft( int digitDis[], int ); // 左截短質數函式 
int truncatablePrimeRight( int * , int , int * ); // 右截短質數函式 

int left[LEFTMAX], right[RIGHTMAX]; // 左截短函式陣列、右截短函式陣列 

int main(void)
{
	int a[MAX], digitDis[DIGITMAX]; // 總質數陣列、位數分割陣列 
	
	printf("運算中請稍後\n");
	
	printf("30000 個質數中尋找左右截短質數：\n");
	findPrime(a);
	/*
	primeOut(a, 1);
	*/
	printf("\n");
	putchar('\n');
	
	digitSplit(a, digitDis);
	
	printf("右截短質數：\n");
	primeOut(right, 2);
	
	printf("\n");
	putchar('\n');
	
	printf("左截短質數：\n");
	primeOut(left, 3);
	
	printf("\n");
	puts("臺中教育大學_萬宸維_撰寫\n");
	
	putchar('\n');
	
	system("pause");
	return 0;
}

int counter = 0; // 計算質數的計數器 

/* 初始找尋質數函式 */ 
void findPrime( int a[] )
{
	int flag = 1, j = 2; // flag to check if the number is prime, flag = 1 is prime 
	
	for( int i = 2 ; i <= 1e9 ; i++ ) // i mod j
	{
		for( int j = 2 ; j < i ; j++ )
		{
			flag = 1;
			
			if( i%j == 0 ) // i mod j = 0 means i isn;t a prime, so break
			{
				flag = 0;
				break;
			}
		}
		
		if( flag == 1 )
		{
			a[counter] = i;
			counter++;
		}
		
		if( counter == MAX ) // if counter is over the array index, findprime func stops 
			break;
	}
	
	return;
}

/* 對於左右截短質數之判斷函式 */ 
int primeCheck( int a )
{
	int flag;
	
	for( int i = 2 ; i < a || a == 1 ; i++ )
	{
		flag = 1;
		
		if( a%i == 0 || a == 1 ) // 1 isn't prime
		{
			flag = 0;
			return 0;
		}
	}
	
	if( flag == 1 )
	{
		return a;
	}
}

/* 質數輸出 */ 
void primeOut( int a[], int ins )
{
	int x;
	
	switch(ins) // check which prime will be output
	{
		case 1:
			x = counter;
				break;
				
		case 2:
			x = RIGHTMAX;
				break;
		
		case 3:
			x = LEFTMAX;
				break;
	}
	
	for( int i = 0 ; i < x ; i++ )
	{
		if( a[i] == 0 ) // if the a[i] = 0, it means there is no number inside the array, break
			break;
		
		printf("%d ", a[i]);
	}
	return;
}

/* 將數字進行各個位數的分割函式 */ 

void digitSplit( int a[], int digitDis[] )
{
	int flag = 1, countDig = 0, origin, leftBool, rightBool; 
	int countRight = 0, countLeft = 0;
	
	for( int i = 0 ;  i < counter ; i++ )
	{
		origin = a[i]; // let the original number gives to origin
		
		do // try to split the number to each digit
		{
			flag = origin/10; // flag stores other digits
			digitDis[countDig] = origin-flag*10; // origin-flag can get one digit
			origin = flag; // origin will refresh to flag
			
			countDig++; // countDig is the counter of digits
			
		}while( flag > 0 ); // flag < 0 means all the digits is splitted 
		
		
		leftBool = truncatablePrimeLeft( digitDis, countDig ); //  判斷目前數字是否是左截短質數，leftBool = 0 是 
		
		if( leftBool ) // 將左截短質數儲存於陣列 
		{
			left[countLeft] = a[i];
			countLeft++;
		}
		
		rightBool = truncatablePrimeRight( digitDis, countDig, &a[i] ); //  判斷目前數字是否是右截短質數，rightBool 是 
		
		if( rightBool ) // 將右截短質數儲存於陣列  
		{
			right[countRight] = a[i];
			countRight++;
		}
		
		countDig = 0; // let countDig retrieve initiality 
	}
}

/*
分割後的數字儲存於陣列會相反過來 
原數字：233
在陣列中：a[0] = 3, a[1] = 3, a[2] = 2
*/ 

/* 左截短質數函式 */ 
int truncatablePrimeLeft( int digitDis[] , int countDig )
{
	int times = 1, x = 0; // times 用來計算位數 1 倍、10倍... 
	
	for( int i = 0 ; i < countDig-1 ; i++ ) // 用來檢查是否為左截短，最後一位數不用計算 countDig 需要 -1 
	{
		x = x + digitDis[i]*times; // 左截短由個位數開始檢查，依次到十位數... 
		
		if( !primeCheck(x) || !digitDis[i] ) // 質數檢查未通過，並且數字為 0，不是左截短 
		{
			return 0;
		}
		
		times = times*10; 
	}
	
	return 1;
}

/* 右截短質數函式 */ 
int truncatablePrimeRight( int *ptrSplitNum , int countDig, int *ptrOriNum )
{
	int i = 0, fx; // 符合 f(k) = ( f(k-1)*a[k] )/10，所有位數算完此數會為 0 
	
	for( i ; i < countDig ; i++ )
	{
		if( i == 0 ) // 初始值 
			fx = (*ptrOriNum - *(ptrSplitNum+i))/10;
			
		else if( i > 0 && i < countDig )
			fx = (fx - *(ptrSplitNum+i))/10;
		
		if( i != countDig-1 ) // 最後一位不用計算 countDig 需要 -1 
			if( !primeCheck(fx) || ! *(ptrSplitNum+i)) // 質數檢查未通過，並且數字為 0，不是右截短 
				return 0;
	}
	
	return 1;
}
