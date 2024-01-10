#include <stdio.h>

int binarysearch(int arr[], int key, int n){
	int low, mid, high;
	low = 0;
	high = n - 1;
	mid = (low + high) / 2;
	
	while(low < high && arr[mid] != key){
		if(arr[mid] > key){
			high = mid - 1;
		}
		else{
			low = mid + 1;
		}
		mid = (low + high) / 2;
	}
	
	if(arr[mid] == key)
		return mid;
	else
		return -1;
	
}

int main(){
	int arr[] = {1,2,3,4,5,6,7};
	int key = 3;
	printf("%d\n", binarysearch(arr, key, 7)); 
	return 0;
}
