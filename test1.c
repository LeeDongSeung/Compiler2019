/*binary search*/
int arr[11111];
int binarysearch(int x){
		int left = 0,right = 11111,mid;
		while(left<=right){
				mid = (left+right)/2;
				if(mid==x)return mid;
				else if(mid<x) left = mid+1;
				else right = mid-1;
		}
		return -1;
}

int main(){
		int i,goal,res;
		for(i=0;i<11111;i++){
				arr[i] = i;
		}
		goal = 100;
		res = binarysearch(goal);
		return 0;
}

