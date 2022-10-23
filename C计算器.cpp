 /*本程序可以实现四则运算、单层括号的运算、输出结果
允许为分数。*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

char Stack[100]; //当作一个栈使用，存储运算符
int top = -1, k;
int rank[100];
void Push(char a){
	top++;
	Stack[top] = a;
}				//定义入栈
char Pop(){
	char ch;
	ch = Stack[top];
	top--;
	return ch;
}				//定义出栈

int chengfang(int a,int b){
	int c = 1;
	for(int i = 0; i < b; i++){
		c = c*a;
	}
	return c;
}

int main(){
	printf("简易计算器\n");
	flag1 : printf("请您输入您想求解的式子\n请不要加等号并按如例子所示的格式输入1+（2+3）*4\n注意：最多只能实现一层括号运算\n");
	//建立并初始化内存空间
	top = -1;
	char c[100],res[100];
	int n = 0;
	char yunsuanfu[100];
	int shuzi[100];
	int shu[100];
	for(int i = 0; i <100; i++){
		Stack[i] = '\0';
		c[i] = '\0';
		yunsuanfu[i] = '\0';
		res[i] = '\0';
		shuzi[i] = 0;
		shu[i] = 0;
	}
	//接收输入数据
	char ch = '\0';
	ch = getchar();
	while(ch != '\n'){
		c[n++] = ch;
		ch = getchar();
	}
	//分拣算式中的数和运算符并进行错误输入排查
	int shucount = 0,suanfu = 0,j = 0,k = 0;
	for(int i = 0; c[i] != '\0'; i++){
		if(c[i] >= '0' && c[i] <= '9'){
			j++;
			shuzi[shucount] = (c[i]-('1'-1));
   			shucount++;
			if(c[i+1] > '9' || c[i+1] < '0'){
				int m = 0;
				for(int m = 0; m < j; m++){
					shu[k] = shu[k]+shuzi[shucount-j +m]*chengfang(10,(j-m-1));
				}
				k++;
			}
		}
		else{
			if(c[i] >= '(' && c[i] <= '/'){
				yunsuanfu[suanfu] = c[i];
				suanfu++;
				j = 0;
			}
			else{
				printf("请按规则输入算式!!!");
				goto flag1;
			}
		}
	}
	//对运算符优先级进行标注,便于实际运算时比较
	rank['('] = 0;
    rank['+'] = 1;
	rank['-'] = 1;
	rank['*'] = 2;
	rank['/'] = 2;
	int m;
	for(m = 0; m<n; m++) {	//先浏览全部式子处理括号
		if(c[m] == '(') 	//‘(’直接入栈
			Push(c[m]);
		else
			if(c[m] == ')'){
				ch = Pop();
			while(ch != '('){
				res[k++] = ch;
				ch = Pop();
			}
		}					//')'不断出栈，直到遇到‘(’
		else {
			if(c[m] >= '0' && c[m] <= '9')
			res[k++] = c[m];
			else{
				res[k++] = '#';
				while(top >- 1 && rank[c[m]] <= rank[Stack[top]])
				res[k++] = Pop();
				Push(c[m]);
			}
		}
	}
	while(top > -1){
		res[k++] = Pop();
	}
	int r = 0;
	float t[2];
	n = -1;
	while(r<k){
		if(res[r] >= '0' && res[r] <= '9'){
			n++;
			t[n] = res[r]-48;
			r++;
			while(res[r] >= '0' && res[r] <= '9')
			{
				t[n] = t[n]*10+res[r]-48;
				r++;
			}
		}
		else if(res[r] == '#')
			r++;
		else{
			switch(res[r]){
			case '+':
				t[n-1] = t[n]+t[n-1];
				n--;
				break;
			case '-':
				t[n-1] = t[n-1]-t[n];
				n--;
				break;
			case '*':
				t[n-1] = t[n]*t[n-1];
				n--;
				break;
			case '/':
				if(t[n] == 0){
					printf("0不能做除数！！!");
				}
				t[n-1] = t[n-1]/t[n];
				n--;
				break;
			}							//根据运算符进行运算
			r++;
		}
	}
    printf("= %f\n",t[n]);
    flag2 : printf("您接下来要：1、离开 2、继续计算（请输入操作序号）\n");
    int s;
    scanf("%d",&s);
    switch(s){
    	case 1:
    		return 0;
    	case 2:
    		goto flag1;
		default :
			printf("请您正确输入！！！");
			goto flag2;
		}
	return 0;
}
