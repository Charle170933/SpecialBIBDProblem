#include<iostream>
#include<string>
#include<math.h>
using namespace std;
//判断数列是否包含某个数 
int belong(int a , int b[] , int n){
	if(n < 1) return 0;
	for(int i = 0 ; i < n ; i++){
		if(a == b[i]) return 1;
	}
	return 0;
}
//根据输入进行赋值
void get_value(string input , int &n , int &ID1 , int &ID2 , int &group , int &group_ID , int &type){
	int input_type = 0 , n_square = 0;
	for(int i = 0 ; i < input.length() ; i++){
		if(input[i] - ',' == 0) input_type++;	
	}
	type = input_type - 2;
	if(input_type == 2){
		for(int i = 0 ; i < input.length() ; i++){
			if(input[i] - ',' == 0) {
				input_type--;
				continue;
			}
			else if(input[i] -'G' == 0) continue;
			if(input_type == 2){
				n_square = n_square * 10 + input[i] - '0';
			}
			else if(input_type == 1){
				group =  group * 10 + input[i] - '0'; 
			}
			else{
				group_ID = group_ID * 10 + input[i] - '0';
			}
		}
	}
	else{
		for(int i = 0 ; i < input.length() ; i++){
			if(input[i] - ',' == 0) {
				input_type--;
				continue;
			}
			if(input_type == 3){
				n_square = n_square * 10 + input[i] - '0';
			}
			else if(input_type == 2){
				group =  group * 10 + input[i] - '0'; 
			}
			else if(input_type == 1){
				ID1 = ID1 * 10 + input[i] - '0';
			}
			else ID2 = ID2 * 10 + input[i] - '0';
		}
	}
	n = sqrt(n_square);
} 
//判断是否为质数 
int prime_number(int n){
	if(n == 1) return 0; 
	if(n == 2) return 1;
	else{
		for(int i = 2 ; i < sqrt(n) + 1 ; i++){
			if(n % i == 0) return 0;
		} 
	}
	return 1;
}
//判断W[y]数列生成过程是否符合要求 
int judge(int W[] , int n){
	int triangle[n][n];
	for(int i = 0 ; i < n ; i++) triangle[0][i] = 0;
	for(int i = 1 ; i <= n / 2 ; i++){
		triangle[1][i] = W[i];
		triangle[1][n-i] = n + 2 - W[i];
	}
	int s;
	for(int i = 2 ; i < n ; i++){
		for(int j = 1 ; j <= n - i ; j++){
			s = triangle[i-1][j] + triangle[i-1][j+1] - triangle[i-2][j+1]; 
			if(s < 0) s += n + 1;
			else if(s > n) s -= n + 1; 
			if(s == 0 || s == i) return 0;
			else{
				for(int k = 1 ; k < j ; k++) if(s == triangle[i][k]) return 0;
			}
			triangle[i][j] = s;
		}
	}
	return 1;
} 
//生成W(y)数列 
int make_array(int n , int W[]){
	int equal[n] , symetric[n] , mode_value[n][n];
	for(int i = 1 ; i < n ; i++){
		equal[i] = 0;
		symetric[i] = 0;
		for(int j = 0 ; j < n ; j++) mode_value[i][j] = 0;
	}
	W[1] = 2;
	equal[1] = 2;
	symetric[1] = n;
	mode_value[1][1] = 2;
	if(n % 2 == 0) W[n/2] = n/2 + 1;
	int j = 2 , i = 1;
	while(1){
		for(int k = 1 ; k < i ; k++){
			if(j == equal[k] || j == symetric[k] || (j + mode_value[k][i-1]) % (n+1) == 0 || (j + mode_value[k][i-1]) % (n+1) == i - k + 1){
				j++;
				break;
			}
			else if(j > n){
				i--;
				j = W[i] + 1;
				W[i] = 0;
				equal[i] = 0;
				symetric[i] = 0;
				for(int s = 1 ; s <= i ; s++) mode_value[s][i] = 0;
				break;
			}
			else{
				W[i] = j;
				j = 2;
				equal[i] = W[i];
				symetric[i] = n + 2 - W[i];
				for(int s = 1 ; s <= i ; s++) mode_value[s][i] = (mode_value[s][i-1] + W[i] ) % (n + 1);
				i++;
				break;
			}
		} 
		if(i > (n - 1) / 2){
			if(judge(W , n) == 1) return 1;
			else{
				i--;
				j = W[i] + 1;
				W[i] = 0;
				equal[i] = 0;
				symetric[i] = 0;
				for(int s = 1 ; s <= i ; s++) mode_value[s][i] = 0;
			}
		}
		if(i == 1){
			if(j > (n + 1) / 2) return 0;
			else{
				W[i] = j;
				j = 2;
				equal[i] = W[i];
				symetric[i] = n + 2 - W[i];
				mode_value[1][1] = W[i];
				i++;
			}
		}
	}
		
} 
//生成本源数列 
int make_original_array(int W[] , int original[] , int n){
	int trial[n] , add_value = 0 , flag = 1 ;
	if(n % 2 == 0){
		trial[0] = 1 ; 
		trial[1] = 0;
		for(int i = 3 ; i < n ; i++){
			trial[i] = W[i - 2]; 
		}
		for(int i = 3 ; i < n ; i++){
			flag = 1;
			add_value = i;
			for(int j = 3 ; j < n ; j++){
				add_value += trial[j];
				add_value = add_value % (n-1); 
				if(add_value == 1 || add_value == j){ //满足要求2和3且所得数不重复 
					flag = 0 ; 
					break;
				}
			
			}
			if(flag == 1){
				trial[2] = i;
				//for(int k = 0 ; k < n ; k++) cout << trial[k] << " ";
				//cout << endl;
				original[0] = 0;
				original[1] = i;
				for(int k = 3 ; k < n ; k++){
					add_value = 0;
					for(int s = 2 ; s <= k ; s++){
						add_value += trial[s];
					}
					original[k-1] = add_value % (n-1);
					if(original[k-1] == 0) original[k-1] = n - 1;
				}
			
				return 1;
			}
		}
	}
	else{
		int pos = 0;
		trial[0] = 1;
		trial[(n+1)/2] = 0;
		for(int i = 1 ; i < n - 2 ; i++){
			pos = i + (n+1)/2 + 1;
			if(pos > n - 1) pos = pos % (n-1);
			trial[pos] = W[i];	
		}
		for(int i = 3 ; i < n ; i++){
			pos = 0;
			flag = 1;
			add_value = i;
			for(int j = (n+1)/2 + 2 ; j < n + (n+1)/2 ; j++){
				pos = j;
				if(pos > n - 1) pos = pos % (n-1);
				add_value += trial[pos];
				add_value = add_value % (n-1); 
				if(add_value == 1 || add_value == pos){ //满足要求2和3且所得数不重复 
					flag = 0 ; 
					break;
				}
			
			}
			if(flag == 1){
				trial[(n+1)/2 + 1] = i;
				//for(int k = 0 ; k < n ; k++) cout << trial[k] << " ";
				//cout << endl;
				original[0] = 0;
				original[1] = i;
				for(int k = 3 ; k < n ; k++){
					pos = 0;
					add_value = 0;
					for(int s = 2 ; s <= k ; s++){
						pos = (n+1)/2 + s -1;
						if(pos > n - 1) pos = pos % (n-1);
						add_value += trial[pos];
					}
					original[k-1] = add_value % (n-1);
					if(original[k-1] == 0) original[k-1] = n - 1;
				}
			
				return 1;
			}
		}
	}
	return 0;
}

int main(){
	int n = 0 ,ID1 = 0  , ID2 = 0 , group = 0 , group_ID = 0 , type = 0;
	string input;
	cin >> input;
	get_value(input , n , ID1 , ID2 , group , group_ID , type);
	int BIBD_group[n+1][n][n] , W[n - 2] , original[n - 1] , equivalence[n][n];
	//若输入为质数 
	if(prime_number(n) == 1){   
		for(int i = 0 ; i < n+1 ; i++){
			for(int j = 0 ; j < n ; j++){
				for(int k = 0 ; k < n ; k++){
					if(i < n)BIBD_group[i][j][k] = k * n + (j + i * k) % n;
					else BIBD_group[i][j][k] = j * n + k;
				}
			}
		}
	}
	//若输入为合数 
	else{
		for(int i = 1 ; i < n ; i++) W[i] = 0;
		if(make_array(n - 2, W) == 0){
			cout << "目前算法无法构造出符合要求的分组" << endl; //无法构造出W[y]数列 
			return 0;
		}
		else{
			for(int i = 1 ; i <= (n - 2) / 2 ; i++) W[n - 2 - i] = n - W[i];
			//for(int i = 1 ; i < n - 2 ; i++) cout << W[i] << " ";
			//cout << endl;
			if(make_original_array(W , original , n) == 1){
			//	for(int i = 0 ; i < n - 1 ; i++) cout << original[i] << " ";
			//	cout << endl;
				//生成等价数列
				int equi_pos;
				for(int i = 0 ; i < n ; i++){
					for(int j = 1 ; j < n ; j++){
						if(i == 0) equivalence[i][j] = j;
						else if(i == 1){
							if(n % 2 == 0) equivalence[i][j] = original[j-1];
							else{
								int pos;
								pos = j - (n+1)/2;
								if(pos < 0 ) pos += n-1;
								equivalence[i][j] = original[pos]; 
							}
						}
						else{
							equi_pos = j-1;
							if(equi_pos == 0 ) equi_pos = n-1;
							if(equivalence[i-1][equi_pos] == 0)equivalence[i][j] = 0 ;
							else if(equivalence[i-1][equi_pos] == n-1) equivalence[i][j] = 1 ;
							else equivalence[i][j] = equivalence[i-1][equi_pos] + 1;	
							
						}
					}
				} 
			//	for(int i = 0 ; i < n ; i++){
			//		for(int j = 1 ; j < n ; j++) cout << equivalence[i][j] << " ";
			//		cout << endl;
			//	}
				int BIBD_pos;
				for(int i = 0 ; i < n+1 ; i++){
					for(int j = 0 ; j < n ; j++){
						for(int k = 0 ; k < n ; k++){
							if(i == 0)BIBD_group[i][j][k] = k * n + j;
							else if(i == n) BIBD_group[i][j][k] = j * n + k;
							else{
								if(k != 0) {
									BIBD_pos = i + k - 1;
									if(BIBD_pos >= n) BIBD_pos = BIBD_pos - n + 1;
									BIBD_group[i][j][k] = k * n + equivalence[j][BIBD_pos];	
								}
								else BIBD_group[i][j][k] = j;
							}
						}
					}
				}
				
				
			}
			else{
				cout << " 目前算法无法构造出符合要求的分组"  << endl; //无法构造出本源数列 
				return 0;
			}
		}	
	} 
	if(type == 0){
		int number = 0;
		for(int i = 0 ; i < n+1 ; i ++){
			for(int j = 0 ; j < n ; j++){
				if(number == group_ID){
					for(int k = 0 ; k < n ; k++){
						cout << BIBD_group[i][j][k] << " ";
					}
					cout << endl;
				}
				number++;
			}
		}
	}
	else{
		int number = 0;
		for(int i = 0 ; i < n+1 ; i ++){
			for(int j = 0 ; j < n ; j++){
				if(belong(ID1 , BIBD_group[i][j] , n) == 1 &&  belong(ID2 , BIBD_group[i][j] , n) == 1){
					cout << "G" << number << endl;
				}
				number++;
			}
		}	
	}
	//验证程序 
	cout << "是否启动验证程序:(yes or no?)" << endl;
	string verify;
	cin >> verify ;
	int flag = 0 ; //设置标签 
	if(verify.compare("yes") == 0){
		for(int i = 0 ; i < n+1 ; i++){
			for(int j = 0 ; j < n ; j++){
				for(int k = 0 ; k < n ; k++){
					cout << BIBD_group[i][j][k] << " ";
				}
				cout << " | ";
			}
			cout << endl;
		}
		for(int i = 0 ; i < n*n-1 ; i++){
			for(int j = i+1 ; j < n ; j++){
				flag = 0;
				for(int k = 0 ; k < n+1 ; k++){
					for(int s = 0 ; s < n ; s++){
						if(belong(i , BIBD_group[k][s] , n) == 1 && belong(j , BIBD_group[k][s] , n) == 1) flag++;
					}
				}
				if(flag > 1){
					cout << "i 和 j 同时出现在至少两组内 , 结果错误" << endl; 
					return 0;
				}
			
			}
		}
		cout << "经验证 , BIBD_group数组符合所要求的性质 , 所以结果正确"  << endl;
	}
	
	return 0;
}
