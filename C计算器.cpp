 /*���������ʵ���������㡢�������ŵ����㡢������
����Ϊ������*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

char Stack[100]; //����һ��ջʹ�ã��洢�����
int top = -1, k;
int rank[100];
void Push(char a){
	top++;
	Stack[top] = a;
}				//������ջ
char Pop(){
	char ch;
	ch = Stack[top];
	top--;
	return ch;
}				//�����ջ

int chengfang(int a,int b){
	int c = 1;
	for(int i = 0; i < b; i++){
		c = c*a;
	}
	return c;
}

int main(){
	printf("���׼�����\n");
	flag1 : printf("����������������ʽ��\n�벻Ҫ�ӵȺŲ�����������ʾ�ĸ�ʽ����1+��2+3��*4\nע�⣺���ֻ��ʵ��һ����������\n");
	//��������ʼ���ڴ�ռ�
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
	//������������
	char ch = '\0';
	ch = getchar();
	while(ch != '\n'){
		c[n++] = ch;
		ch = getchar();
	}
	//�ּ���ʽ�е���������������д��������Ų�
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
				printf("�밴����������ʽ!!!");
				goto flag1;
			}
		}
	}
	//����������ȼ����б�ע,����ʵ������ʱ�Ƚ�
	rank['('] = 0;
    rank['+'] = 1;
	rank['-'] = 1;
	rank['*'] = 2;
	rank['/'] = 2;
	int m;
	for(m = 0; m<n; m++) {	//�����ȫ��ʽ�Ӵ�������
		if(c[m] == '(') 	//��(��ֱ����ջ
			Push(c[m]);
		else
			if(c[m] == ')'){
				ch = Pop();
			while(ch != '('){
				res[k++] = ch;
				ch = Pop();
			}
		}					//')'���ϳ�ջ��ֱ��������(��
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
					printf("0��������������!");
				}
				t[n-1] = t[n-1]/t[n];
				n--;
				break;
			}							//�����������������
			r++;
		}
	}
    printf("= %f\n",t[n]);
    flag2 : printf("��������Ҫ��1���뿪 2���������㣨�����������ţ�\n");
    int s;
    scanf("%d",&s);
    switch(s){
    	case 1:
    		return 0;
    	case 2:
    		goto flag1;
		default :
			printf("������ȷ���룡����");
			goto flag2;
		}
	return 0;
}
