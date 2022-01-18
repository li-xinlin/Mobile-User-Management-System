#pragma warning(disable:4996)
#include<stdio.h>

#include<string.h>
#include<stdlib.h>
#include<time.h>	
#define NUM 50					//��������� 
#define sizeuser sizeof(User)	//һ���û���Ϣ����Ҫ���ڴ�ռ��С 
struct Date
{
	int year;
	int month;
	int day;
};
typedef struct Date Date;
struct User
{
	char id[20];		//���֤�� 
	char password[12];	//����
	char name[10];		//�û����� 
	char sex[4];		//�Ա� 
	int age;			//���� 
	char num[3][12];	//�ֻ���
	char job[10];		//ְҵ 
	char adress[10];	//סַ 
	double fee;			//���� 
	double dayfee;		//�շ��� 
	Date date; 			//�ϴν���ϵͳʱ�� 
};
typedef struct User User;
//����Ϊ�û����ݴ���ĺ���ԭ�� 
int readUser(User user[],int n);					//�����û���Ϣ�����֤��Ϊ0������涨����ʱֹͣ ,������ʵ�ʶ������� 
void printUser(User *user,int n);					//����û���¼
int equal(User u1,User u2,int con);					//����con�����ж�����User���������Ƿ����
int larger(User u1,User u2,int con);				//����con�����Ƚ�����User�������ݴ�С
void sortUser(User user[],int n,int con);			//���򣬰�con����
int searchUser(User user[],int n, User u,int con,int f[]);	//��������(con)������u��ȵ�Ԫ��
int insertUser(User user[],int n, User u);			//�������в���һ��Ԫ��-
int checkrepeatid(User user[],char id[],int i);		//���֤�Ų��ظ�
int checkrepeatnum(User user[],char num[],int i);	//�ֻ��Ų��ظ�
int deleteUser(User user[],int n, User u);			//��������ɾ��һ��Ԫ��
void getdate(Date *da); 							//��ȡϵͳ���� 
int sum(int y,int m,int d);
void fees(User *user,int n);    					 //ʵ�ֿ۳�ÿ�»����ײͷ�
void addmoney(User *user,int n,int find);			//��ֵ 
//����Ϊ���֤����غ��� 
int checkid(char s[]);							//У�����֤�ŵĺ�������������Ϸ������֤�Ų���¼��
int Judge(int year,int month,int day);			//���ںϷ����ж�
int IsLeapYear(int year);						//�����ж�
int idage(char id[]);							//���֤���ж����� 
//����Ϊ�ļ���ش���ĺ���ԭ�� 
int createFile(User user[]);					//������ʼ�������ļ� 
int readFile(User user[]);						//��ȡ�ļ��������ڽṹ�������� 
void saveFile(User user[],int n);				//���ṹ������д���ļ� 
//����Ϊ�˵���صĺ���ԭ�� 
void printHead();								//��ӡ��ͷ�������ݹ��࣬���г���ʱ��ȫ����ʾ 
void menu();									//�����˵�����
void menuManager();								//����Ա�˵�����
void menuUser();								//�û��˵� 
void runmenuUser(User user[],int n);			//�û���¼
int checkPassword(User user[],int n,char id[],char password[]);		//�û���¼У��
int runmenuManager(User user[],int n);			//����Ա��¼
void menuShow();								//��ʾ�û���Ϣ�˵�����
void menuSearch();								//�û���Ϣ��ѯ�˵����� 
void menuManage();								//�û���Ϣ����˵�����
int runMain(User user[],int n, int choice);		//��Ӧһ���˵��¸����ܵ�ִ�� 
void runmenuShow(User user[],int n);			//��Ӧ��ʾ�û���Ϣ 
int runmenuSearch(User user[], int n);			//��Ӧ�û���Ϣ��ѯ 
int runmenuManage(User user[],int n);			//��Ӧ�û���Ϣ����
void passwordmanager();		
//������
int main()
{
	User user[NUM];
	int choice,n;
	n=readFile(user);
	if(!n)
	{
		printf("\t\t\t\t��ǰ�����ݣ����������Ա�˺�����¼�����ݣ�\n"); 
		passwordmanager();
		n=createFile(user);
	}
	do
	{
		fees(user,n);						//����ϵͳʵ�ֿ۷� 
		menu();
		scanf("%d",&choice);
		if(choice>=0&&choice<=2)
			n=runMain(user,n,choice);
		else
			printf("\t\t\t\t�����������������룡\n");
	}while(choice);
	saveFile(user,n);
	return 0;
}

//����Ϊ�û����ݴ���ĺ���
int checkid(char id[])	//���֤��У�麯�����������֤�ű�׼GB11643-1999����ȷ����1�����󷵻�0�� 
{
	int b,c,e,i,idyear,idmonth,idday;
	char d;
	idyear=(id[6]-48)*1000+(id[7]-48)*100+(id[8]-48)*10+(id[9]-48);
	idmonth=(id[10]-48)*10+(id[11]-48);
	idday=(id[12]-48)*10+(id[13]-48);
	e=Judge(idyear,idmonth,idday);   //���ںϷ���
	b=7*(id[0]-48)+9*(id[1]-48)+10*(id[2]-48)+5*(id[3]-48)+8*(id[4]-48)+4*(id[5]-48)+2*(id[6]-48)+1*(id[7]-48)+6*(id[8]-48)+3*(id[9]-48)+7*(id[10]-48)+9*(id[11]-48)+10*(id[12]-48)+5*(id[13]-48)+8*(id[14]-48)+4*(id[15]-48)+2*(id[16]-48);
	c=b%11;
	switch(c)
	{
		case 0: d='1';break;
		case 1: d='0';break;
		case 2: d='X';break;
		case 3: d='9';break;
		case 4: d='8';break;
		case 5: d='7';break;			
		case 6: d='6';break;
		case 7: d='5';break;
		case 8: d='4';break;
		case 9: d='3';break;
		case 10: d='2';break;
	}
	for(i=0;i<17;i++)
	{
		if(id[i]<48||id[i]>57)
			return 0;
	}
	if(d==id[17]&&strlen(id)==18&&e==1)
	{
		return 1;
	} 
	else
	{
		return 0;
	}
}
int Judge(int year,int month,int day)	//���ںϷ����ж�
{
	int i,a=1,b[4]={4,6,9,11},nowyear;
	time_t timep;
	struct tm *p;
	time(&timep);
	p=localtime(&timep);
	nowyear=(1900+p->tm_year);
	if(year<1900||year>nowyear||month<=0||month>12||day<=0||day>31)
		a=0;
	for(i=0;i<4;i++)
		if(month==b[i]&&day>30)
			a=0;
	if(month==2){
		if(IsLeapYear(year)&&day>28)
			a=0;
		if((!IsLeapYear(year))&&day>29)
			a=0;
	}
	return a;
}
int IsLeapYear(int year)	//�����ж�
{
	int a=1;
	if(year%4==0&&year%100!=0||year%400==0)
		a=0;
	return a;
}
 
int checkrepeatid(User user[],char id[],int i)		//���֤�Ų���
{
	int j;
	for(j=0;j<i;j++)
	{
		if(!strcmp(user[j].id,id))
			return 1;
	}
	return 0;
}

int checkrepeatnum(User user[],char num[],int i)	//�ֻ��Ų���
{
	int j,k;
	if(strcmp(num,"0"))
	{
		for(k=0;k<3;k++)
		{
			for(j=0;j<i;j++)
			{
				if(!strcmp(user[j].num[k],num))
					return 1;
			}
		}
		return 0;
	}
	else return 0;
} 

int readUser(User *user,int n)		//�����û���Ϣ�����֤��Ϊ0������涨����ʱֹͣ ,������ʵ�ʶ������� 
{
	int i,j;
	Date da;
	char pass[12]; 
	getdate(&da);
	for(i=0;i<n;i++)
	{
		system("cls");
		printf("\t\t\t\t������һ����Ϣ(���֤��Ϊ0ʱ��������)\n");
		printf("\t\t\t\t���֤�� :");
		scanf("%s",user[i].id);
		while((strcmp(user[i].id,"0"))&&((!checkid(user[i].id))||(checkrepeatid(user,user[i].id,i))))//�ж����֤���Ƿ�Ϸ�
		{
			printf("\t\t\t\t���֤�Ų��Ϸ����������û��ظ������������룺");
			scanf("%s",user[i].id);
		} 
		if(!strcmp(user[i].id,"0"))
			break;
		printf("\t\t\t\t�������룺");
		scanf("%s",user[i].password);
		printf("\t\t\t\t���ٴ��������룺");
		scanf("%s",pass);
		while(strcmp(user[i].password,pass))
		{
			printf("\t\t\t\t�������벻ͬ������������\n");
			printf("\t\t\t\t�������룺");
			scanf("%s",user[i].password);
			printf("\t\t\t\t���ٴ��������룺");
			scanf("%s",pass);
		}
		printf("\t\t\t\t���� :");
		scanf("%s",user[i].name);
		if((user[i].id[16]-48)%2)				//�����֤���ж��Ա�
		{
			strcpy(user[i].sex,"��");
		}
		else {
			strcpy(user[i].sex,"Ů");
		}
		user[i].age=idage(user[i].id);			//�����֤���ж�����

		printf("\t\t\t\t�ֻ���1:");
		scanf("%s",user[i].num[0]);
		while(checkrepeatnum(user,user[i].num[0],i))	//��ֹ�ֻ����ظ�
		{
			printf("\t\t\t\t�ֻ����������ظ������������룺");
			scanf("%s",user[i].num[0]);
		}
		printf("\t\t\t\t�ֻ���2:\n");
		printf("\t\t\t\t(��ʾ�����û�У�������0)");
		scanf("%s",user[i].num[1]);
		while(checkrepeatnum(user,user[i].num[1],i)||(!strcmp(user[i].num[1],user[i].num[0])))
		{
			printf("\t\t\t\t�ֻ����������ظ������������룺");
			scanf("%s",user[i].num[1]);
		}
		if(strcmp(user[i].num[1],"0"))
		{
			printf("\t\t\t\t�ֻ���3:\n");
			printf("\t\t\t\t(��ʾ�����û��������0)");
			scanf("%s",user[i].num[2]);
			while(checkrepeatnum(user,user[i].num[2],i)||(!strcmp(user[i].num[2],user[i].num[0]))||(!strcmp(user[i].num[2],user[i].num[1])))
			{
				printf("\t\t\t\t�ֻ����������ظ������������룺");
				scanf("%s",user[i].num[2]);
			}
		}
		else
		{
			strcpy(user[i].num[2],"0");
		}
		printf("\t\t\t\tְλ :");
		scanf("%s",user[i].job);
		printf("\t\t\t\tסַ :"); 
		scanf("%s",user[i].adress);
		printf("\t\t\t\t��ѡ���ײͣ�\n");
		printf("\t\t\t\t 1. 0.5Ԫÿ��  2. 1Ԫÿ��  3. 2Ԫÿ��\n\t\t\t\t��ѡ��");
		scanf("%d",&j);
		while(j<1||j>3)
		{
			printf("\t\t\t\t����ȷѡ��\n");
			printf("\t\t\t\t 1. 0.5Ԫÿ��  2. 1Ԫÿ��  3. 2Ԫÿ��\n\t\t\t\t��ѡ��");
			scanf("%d",&j);
		} 
		switch(j)
		{
			case 1: user[i].dayfee=0.5;
					break;
			case 2: user[i].dayfee=1;
					break;
			case 3: user[i].dayfee=2;
					break;
		} 
		user[i].fee=0;
		user[i].date=da;
	}
	return i;
}

int idage(char id[])//���֤���ж����� 
{
	int idyear,nowyear,age;
	time_t timep;
	struct tm *p;
	time(&timep);
	p=localtime(&timep);
	nowyear=(1900+p->tm_year);
	idyear=(id[6]-48)*1000+(id[7]-48)*100+(id[8]-48)*10+(id[9]-48);
	age=nowyear-idyear;
	return age;
}

void printUser(User *user, int n)   //��������û�����Ϣ��¼
{
    int i;
    for (i=0; i<n; i++)
    {
        printf("%8s", user[i].name);
		printf("%5s", user[i].sex);
		printf("%5d", user[i].age);
		printf("%14s",user[i].num[0]);
		printf("%12s",user[i].num[1]);
		printf("%12s",user[i].num[2]);
		printf("%20s ",user[i].id);
		printf("%6.2f",user[i].fee);
        printf("%10s",user[i].job);
        printf("%10s",user[i].adress);
		printf("\n\n");
    }
}

int equal (User u1, User u2, int con)      //����con�����ж�����User���������Ƿ���� -��� 
{
	int i;
    if (con==1)                                       //�������con��ֵΪ1����Ƚ�����
	{
		if(strcmp(u1.name, u2.name)==0)
			return 1;
		else return 0;
	}
  	if (con==2)                             		//�������con��ֵΪ2����Ƚ��ֻ��� 
    {
		for(i=0;i<3;i++)
			{
				if(strcmp(u1.num[i], u2.num[0])==0)   return 1;
			}       
    }
    if (con==3)                       			   //�������con��ֵΪ3����Ƚ����֤�� 
	{
		 if(strcmp(u1.id, u2.id)==0)   return 1;
        	else return 0;
	} 
	else 
		return 0; 								//�����������0
}

int larger(User u1,User u2,int con) 			//����con�����Ƚ�����User�������ݴ�С
{
	if(con==1)                           		 //1--�Ƚ�����
		if(strcmp(u1.name,u2.name)==1)
			return 1;
	if(con==2)                              	  //2---�ȽϺ���
		if(strcmp(u1.num[0],u2.num[0])==1)
			return 1;
	if(con==3)                                     //3----�Ƚ����֤
		if(strcmp(u1.id,u2.id)==1)
			return 1;
	if(con==4)                        			 //4--�Ƚ�����
		return u1.age>u2.age;
	return 0;
}

void sortUser(User user[], int n, int con)   //ѡ�����򣬰�con������С��������-��� 
{
    int i, j, min;                                 //min�������汾����СԪ�ص��±�
    User u;
    for(i=0; i<n-1; i++)                           //����ѭ����n-1��
    {
        min=i;
        for (j=i+1; j<n; j++)                       //Ѱ�ұ�����СԪ�����ڵ��±�
        {
            if(larger(user[min], user[j], con))
                min=j;
        }
        if (i!=min)                               //��֤������СԪ�ص����±�Ϊi��λ��
        {
            u=user[i];
            user[i]=user[min];
            user[min]=u;
        }
    }
}

int insertUser(User user[], int n, User u)      //�������в���һ��Ԫ��                      
{
	
	user[n]=u;
	n++;																				
    return n;                                           //��������Ԫ�ظ���
}

int searchUser(User user[],int n, User u,int con,int f[])	//��������(con)������u��ȵ�Ԫ��-���츣 
{
	int i,j=0,find=0;
	for(i=0;i<n;i++)
		if(equal(user[i],u,con))
		{
			f[j++]=i;
			find++;
		}
		return find;
}

int deleteUser(User user[],int n, User u)        //ɾ��Ԫ��
{
	int i,j;
	for(i=0;i<n;i++)
	{
		if(equal(user[i],u,3))                //�����֤���Ҳ�ɾ���û���Ϣ
			break;
	}
	if(i==n)
	{
		printf("\t\t\t\t���û������ڣ�\n");
		return n;
	}
	else
	{
		for(j=i;j<n;j++)
		{
			user[j]=user[j+1];
		}
		n--;
	 return n;
	}
}

void getdate(Date *da)    //��ȡ��ǰ������
{
	 time_t nowtime;
	 struct tm *timeinfo;
	 time( &nowtime );
	 timeinfo = localtime( &nowtime );
	 da->year= timeinfo->tm_year + 1900;
	 da->month = timeinfo->tm_mon + 1;
	 da->day= timeinfo->tm_mday;
}

int sum(int y,int m,int d)      
{
	unsigned char x[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int i,s=0;
	for(i=2018;i<y;i++)
		if(i%4==0 && i%100!=0 || i%400==0)
			s+=366;	//����
		else							
		s+=365;		//ƽ��
	if(y%4==0 && y%100!=0 || y%400==0)
		x[2]=29;
	for(i=1;i<m;i++)
		s+=x[i];	//���µ�����
	s+=d;			//�յ�����
	return s;		//����������
}

void fees(User *user,int n)     //ʵ�ֿ۳�ÿ�»����ײͷ�
{
	Date da;
	int i;
	int day1,day2;
	int number=0;
	getdate(&da);
	day1=sum(user[0].date.year,user[0].date.month,user[0].date.day);
	day2=sum(da.year,da.month,da.day);
	number=day2-day1;
	for(i=0;i<n;i++)
	{
		user[i].date=da;
		user[i].fee=user[i].fee-user[i].dayfee*number;
	}
}

void addmoney(User *user,int n,int find)
{
	char a,b; 
	double money;
	printf("\t\t\t\t�������ֵ��");
	scanf("%lf",&money);
	user[find].fee+=money;
	printf("\t\t\t\t��ֵ�ɹ���\n");
	printf("\t\t\t\t���س���������");
	scanf("%c%c",&a,&b);
} 

//����Ϊ�ö������ļ�ʵ�����ݵı��� 
int createFile(User user[])	//������ʼ�������ļ� 
{
	FILE *fp;
	int n;
	char a,b;
	if((fp=fopen("user.dat","wb"))==NULL)	//��д�뷽ʽ�� 
	{
		printf("\t\t\t\tcan not open file!\n");
		exit(0);	
	}
	printf("\t\t\t\t�������û���Ϣ�����س���������");
	scanf("%c%c",&a,&b);
	n=readUser(user,NUM);
	fwrite(user,sizeuser,n,fp);
	fclose(fp);
	return n;
}

int readFile(User user[])		//��ȡ�ļ��������ڽṹ�������� 
{
	FILE *fp;
	int i =0;
	if((fp=fopen("user.dat","rb"))==NULL)	//�Զ�ȡ��ʽ�� 
	{
		return 0;
	} 
	fread(&user[i],sizeuser,1,fp);
	while(!feof(fp))
	{
		i++;
		fread(&user[i],sizeuser,1,fp);
	} 
	fclose(fp);
	return i;			//������������ 
}

void saveFile(User user[],int n)	//���ṹ������д���ļ� 
{
	FILE *fp;
	if((fp=fopen("user.dat","wb"))==NULL)	//��д�뷽ʽ�� 
	{
		printf("\t\t\t\tcan not open file!\n");
		exit(0);	
	}
	fwrite(user,sizeuser,n,fp);
	fclose(fp);
}

//����Ϊ�û����棬�༶�˵�����
void printHead()	//��ӡ��ͷ�������ݹ��࣬���г���ʱ��ȫ����ʾ 
{
	printf("\n%7s%7s%5s%11s%14s%12s%16s%11s%10s%9s\n\n","����","�Ա�","����","�ֻ���1","�ֻ���2","�ֻ���3","���֤��","���","ְҵ","סַ"); 
}

void menu()	//�����˵����� 
{
	system("cls");
	printf("\t\t\t\t----------------------------------\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|      �ƶ��û�����ϵͳ          |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|         1.�ƶ��û�             |\n\t\t\t\t|");
	printf("                                |\n"); 
	printf("\t\t\t\t|         2.����Ա               |\n\t\t\t\t|");
	printf("                                |\n"); 
	printf("\t\t\t\t|         0.�˳�                 |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t----------------------------------\n");
	printf("\t\t\t\t|   ������������ ���츣 ���     |\n");
	printf("\t\t\t\t----------------------------------\n\n");
	printf("\t\t\t\t��ѡ�������ݣ�"); 
}

void menuManager()	//����Ա�˵����� 
{
	system("cls");
	printf("\t\t\t\t----------------------------------\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t| ����Ա���!����������²���    |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|        1.��ʾ�û���Ϣ          |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t|        2.�û���Ϣ��ѯ          |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t|        3.�û���Ϣ����          |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|        4.���ѳ�ֵ              |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|        0.������һ��            |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t----------------------------------\n\n");
	printf("\t\t\t\t���������ѡ��"); 
}

void menuUser()	//�û��˵�
{
	system("cls");
	printf("\t\t\t\t----------------------------------\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|   �û����!����������²���    |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|        1.��ʾ������Ϣ          |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t|        2.�޸ĸ�����Ϣ          |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t|        3.�ҵ�ͨ���ײ�          |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t|        4.���ѳ�ֵ              |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|        0.������һ��            |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t----------------------------------\n\n");
	printf("\t\t\t\t���������ѡ��"); 
}

void menuShow()	//��ʾ�û���Ϣ�˵�����
{
	system("cls");
	printf("\t\t\t\t--------------------------------------------\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|\t\t ��ʾ�û���Ϣ              |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         1.������˳��������ʾ             |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         2.������˳��������ʾ             |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         3.�����֤��˳��������ʾ         |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         0.�����ϲ�˵�                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t--------------------------------------------\n\n");
	printf("\t\t\t\t���������ѡ��"); 
} 

void menuSearch()	//�û���Ϣ��ѯ�˵����� 
{
	printf("\t\t\t\t--------------------------------------------\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|\t   �û���Ϣ��ѯ                    |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|��ֵ���޸ġ�ɾ���û���Ϣʱ�Ƚ���˲˵���ѯ|\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         1.���û�����ѯ                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         2.���ֻ��Ų�ѯ                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         3.�����֤�Ų�ѯ                 |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         0.�����ϲ�˵�                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t--------------------------------------------\n\n");
	printf("\t\t\t\t���������ѡ��"); 
} 

void menuManage()	//�û���Ϣ����˵�����
{
	system("cls");
	printf("\t\t\t\t--------------------------------------------\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|\t   �û���Ϣ����                    |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         1.�����ƶ��û�                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         2.ɾ���û�����                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         3.�޸��û���Ϣ                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         4.�����û��ֻ�����               |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         5.ע���û��ֻ�����               |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         0.�����ϲ�˵�                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t--------------------------------------------\n\n");
	printf("\t\t\t\t���������ѡ��"); 
} 
int runMain(User user[],int n, int choice)	//��Ӧһ���˵��¸����ܵ�ִ�� 
{
	switch(choice)
	{
		case 1: runmenuUser(user,n);
				break;
		case 2: n=runmenuManager(user,n);
				break;
		case 0: system("cls");
				break;
	}
	return n;
}

void runmenuUser(User user[],int n)		//�û���¼
{
	char id[20],password[12],new[10],a,b;
	int i,choice,find,f[NUM],choice2;
	User u;
	i=0;
	printf("\t\t\t\t�����������֤���������¼\n");
	printf("\t\t\t\t���֤�ţ�");
	scanf("%s",id);
	printf("\t\t\t\t���룺");
	scanf("%s",password);
	while(checkPassword(user,n,id,password))
	{
		i++;
		if(i==3)
		{
			printf("\t\t\t\t���󳬹����Σ�\n");
			exit(1);
		}
		printf("\t\t\t\t���֤�������벻ƥ�䣬����������\n");
		printf("\t\t\t\t���֤�ţ�");
		scanf("%s",id);
		printf("\t\t\t\t���룺");
		scanf("%s",password);
		
	}
	strcpy(u.id,id);
	searchUser(user,n,u,3,f);
	do
	{
		menuUser();
		scanf("%d",&choice);
		while(choice<0||choice>4)
		{
			printf("\t\t\t\t��������Ч��ѡ��");
			scanf("%d",&choice);
		}
		switch(choice)
		{
			case 1: printHead();
					printUser(&user[f[0]],1);
					printf("\t\t\t\t���س���������");
					scanf("%c%c",&a,&b);
					break;
			case 2: printf("\t\t\t\t��ѡ���޸���Ŀ��\n");
					printf("\t\t\t\t��ע���û��������֤�š��ֻ��Ų����޸ģ�\n");
					printf("\n\t\t\t\t 1.ְҵ \n\n\t\t\t\t 2.סַ\n\n\t\t\t\t 0.����\n\n\t\t\t\t���������ѡ��");
					scanf("%d",&choice2);
					do
					{
						switch(choice2)
						{
							case 1: printf("\t\t\t\t�������µ�ְҵ��");
									scanf("%s",&new);
									if(strcmp(new,"0"))
									{
										strcpy(user[f[0]].job,new);
										printf("\t\t\t\t�޸ĳɹ���\n");
									} 
									else
									{
										printf("\t\t\t\t���˳��޸ģ�\n");
									}
									printf("\t\t\t\t���س���������");
									scanf("%c%c",&a,&b);
									choice2=0;
									break;
							case 2:  printf("\t\t\t\t�������µ�סַ��");
									scanf("%s",&new);
									if(strcmp(new,"0"))
									{
										strcpy(user[f[0]].adress,new);
										printf("\t\t\t\t�޸ĳɹ���\n");
									} 
									else
									{
										printf("\t\t\t\t���˳��޸ģ�\n");
									}
									printf("\t\t\t\t���س���������");
									scanf("%c%c",&a,&b);
									choice2=0;
									break;
							case 0: break;
						}
					}while(choice2);
					break;
			case 3: printf("\n\t\t\t\t����ǰ���ײ�Ϊ%.2fԪÿ�죬�޸��ײ�����ϵ����Ա��\n",user[f[0]].dayfee);
					printf("\n\t\t\t\t���س���������");
					scanf("%c%c",&a,&b);
					break;
			case 4: addmoney(user,n,f[0]);
					break;
			case 0: break;
		}
	}while(choice);

}

int checkPassword(User user[],int n,char id[],char password[])		//�û���¼У��
{
	User u;
	int f[NUM],find;
	strcpy(u.id,id);
	find=searchUser(user,n,u,3,f);
	if(!find)
	{
		return 1;
	}
	else if(strcmp(user[f[0]].password,password))
		{
			return 1;
		}
	return 0;
}

int runmenuManager(User user[],int n)	//����Ա��¼
{
	int choice,un,find;
	char a,b; 
	passwordmanager(); 
	do
	{
		menuManager();
		
		scanf("%d",&choice);
		while(choice<0||choice>4)
		{
			printf("\t\t\t\t��������Ч��ѡ��");
			scanf("%d",&choice);
		}
		switch(choice)
		{
			case 1: runmenuShow(user,n);
					break;
			case 2: un=runmenuSearch(user,n);
					break;
			case 3: n=runmenuManage(user,n);
					break;
			case 4: printf("\t\t\t\t���Ȳ����û���\n");
					printf("\t\t\t\t���س��������ѯ�˵���");
					scanf("%c%c",&a,&b);	
					find=runmenuSearch(user,n);
					if(find>NUM)
					{
						printf("\t\t\t\t�޷���ֵ�����س���������");
						scanf("%c%c",&a,&b);
					}
					else{
						addmoney(user,n,find);
					} 
					break;
			case 0: break;
		}
	}while(choice);
	return n;
}

void passwordmanager()			//����Ա��¼ 
{
	int i=0;
	char pass[12],u[12];
	printf("\t\t\t\t���������Ա�˺ţ�");
	scanf("%s",u);
	printf("\t\t\t\t���������Ա���룺");
	scanf("%s",pass);
	while(strcmp(pass,"123456")!=0||strcmp(u,"123456")!=0)
	{	
		i++;
		if(i==3)
		{
			printf("\t\t\t\t���󳬹����Σ�\n");
			exit(1);
		}
		printf("\t\t\t\t��������������������룺\n");
		printf("\t\t\t\t���������Ա�˺ţ�");
		scanf("%s",u);
		printf("\t\t\t\t���������Ա���룺");
		scanf("%s",pass);
	}
}

void runmenuShow(User user[],int n)	//��Ӧ��ʾ�û���Ϣ 
{
	int choice;
	char a,b;
	do
	{
		menuShow();
	
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printHead();
					sortUser(user,n,1);	//conΪ1��ʾ����������
					printUser(user,n);
					printf("\t\t\t\t���س���������");
					scanf("%c%c",&a,&b);
					break;
			case 2: printHead();
					sortUser(user,n,4);	//conΪ2��ʾ����������
					printUser(user,n);
					printf("\t\t\t\t���س���������");
					scanf("%c%c",&a,&b);
					break;
			case 3: printHead();
					sortUser(user,n,3);	//conΪ3��ʾ�����֤������
					printUser(user,n);
					printf("\t\t\t\t���س���������");
					scanf("%c%c",&a,&b);
					break;
			case 0: break;
		}
	}while(choice); 
}
int runmenuSearch(User user[], int n)	//��Ӧ�û���Ϣ��ѯ 
{
	int choice1,choice2,f[NUM],find;
	char a,b;
	User u;
	do
	{
		menuSearch();
	
		scanf("%d",&choice1);
		switch(choice1)
		{
			case 1:	printf("\t\t\t\t������Ҫ��ѯ���û����� ");
				   	scanf("%s",u.name);
					break;
			case 2:	printf("\t\t\t\t������Ҫ��ѯ���ֻ��ţ� ");
				   	scanf("%s",u.num[0]);
					break;	
			case 3:	printf("\t\t\t\t������Ҫ��ѯ�����֤�ţ� ");
				   	scanf("%s",u.id);
					break;
			case 0: return (NUM+1);
					break;
		}
		if(choice1>=1&&choice1<=3)
		{
			find=searchUser(user,n,u,choice1,f);
			if(!find)
			{
				printf("\t\t\t\t�Ҳ�������û���\n");
				printf("\t\t\t\t���س���������");
				scanf("%c%c",&a,&b);
				return (NUM+1);
			} else if(find==1)
				{
					printHead();
					printUser(&user[f[0]],1);
					printf("\t\t\t\t�ҵ�һλ�û������س���������");
					scanf("%c%c",&a,&b);
					return f[0]; 
				}
				else
				{
					printf("\t\t\t\t�ҵ�����һλ�û��������Ӳ�ѯ������\n");
					printf("\t\t\t\t���س���������");
					scanf("%c%c",&a,&b);
					menuSearch();
					scanf("%d",&choice2);
					while(choice2==choice1)
					{ 
						printf("\t\t\t\t��������Ѿ��ù��ˣ�����������������");
						scanf("%d",&choice2);
					}
					switch(choice2)			//����ҵ��������ݣ���һ���Ǹ����û�����ѯ����Ϊ�ֻ��š����֤��Ψһ 
					{
						case 2:	printf("\t\t\t\t������Ҫ��ѯ���ֻ��ţ� ");
							   	scanf("%s",u.num[0]);
								break;	
						case 3:	printf("\t\t\t\t������Ҫ��ѯ�����֤�ţ� ");
							   	scanf("%s",u.id);
								break;
						case 0: return (NUM+1); 
								break;
					} 
					if(choice2==2||choice2==3)
					{
						find=searchUser(user,n,u,choice2,f);
						if(!find)
						{
							printf("\t\t\t\t�Ҳ�������û���\n");
							printf("\t\t\t\t���س���������");
							scanf("%c%c",&a,&b);
							return (NUM+1);
						} else {
								printHead();
								printUser(&user[f[0]],1);
								printf("\t\t\t\t�ҵ�һλ�û������س���������");
								scanf("%c%c",&a,&b);
								return f[0];
								}
					}	 	
				}
		}
	}while(choice1);
}
int runmenuManage(User user[],int n)
{
	int choice,f[NUM],find,i,j,de,choice2;
	User u;
	char num[12],new[10],a,b;
	do
	{
		menuManage();
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("\t\t\t\t������Ҫ���ӵ��û���Ϣ�����س���������");
					scanf("%c%c",&a,&b);
					readUser(&u,1);
					while(checkrepeatid(user,u.id,n)||checkrepeatnum(user,u.num[0],n)||checkrepeatnum(user,u.num[1],n)||checkrepeatnum(user,u.num[2],n))
					{
						printf("\t\t\t\t���֤�Ż��ֻ�����ԭ���ݿ��ظ���������¼����Ϣ��\n\t\t\t\t���س���������");
						scanf("%c%c",&a,&b);
						readUser(&u,1);
					}
					if(strcmp(u.id,"0"))
					{
						n=insertUser(user,n,u);
						printf("\t\t\t\t¼����Ϣ�ɹ���\n");
					}
					else printf("\t\t\t\t���˳������û���\n");
					printf("\t\t\t\t���س���������");
					scanf("%c%c",&a,&b);
					break;
			case 2: printf("\t\t\t\t���Ȳ����û���Ϣ��\n");
					printf("\t\t\t\t���س��������ѯ�˵���");
					scanf("%c%c",&a,&b);	
					find=runmenuSearch(user,n);
					if(find<=NUM)
					{
						printf("\t\t\t\t�Ƿ�Ҫɾ����1. ɾ��  0.��ɾ�� \n");
						printf("\t\t\t\t���������ѡ��");
						scanf("%d",&de);
						if(de)
						{
							strcpy(u.id,user[find].id);
							n=deleteUser(user,n,u);
							printf("\t\t\t\t��ɾ���Ϸ���һ����Ϣ��\n");
						}
						else
						{
							printf("\t\t\t\t���˳�ɾ��!\n");
						}
					}
					printf("\t\t\t\t���س���������");
					scanf("%c%c",&a,&b);
					break;
			case 3: printf("\t\t\t\t���Ȳ����û���Ϣ��\n");
					printf("\t\t\t\t���س��������ѯ�˵���");
					scanf("%c%c",&a,&b);	
					find=runmenuSearch(user,n);
					if(find<=NUM)
					{
						printf("\t\t\t\t��ѡ���޸���Ŀ��\n");
						printf("\t\t\t\t��ע���û��������֤�š��ֻ��Ų����޸ģ�\n\n");
						printf("\n\t\t\t\t 1.ְҵ \n\n\t\t\t\t 2.סַ\n\n\t\t\t\t 3.�ײ�\n\n\t\t\t\t 0.����\n\n\t\t\t\t���������ѡ��");
						scanf("%d",&choice2);
						do
						{
							switch(choice2)
							{
								case 1: printf("\t\t\t\t�������µ�ְҵ��");
										scanf("%s",&new);
										if(strcmp(new,"0"))
										{
											strcpy(user[find].job,new);
											printf("\t\t\t\t�޸ĳɹ���\n");
										} 
										else
										{
											printf("\t\t\t\t���˳��޸ģ�\n");
										}
										printf("\t\t\t\t���س���������");
										scanf("%c%c",&a,&b);
										choice2=0;
										break;
								case 2:  printf("\t\t\t\t�������µ�סַ��");
										scanf("%s",&new);
										if(strcmp(new,"0"))
										{
											strcpy(user[find].adress,new);
											printf("\t\t\t\t�޸ĳɹ���\n");
										} 
										else
										{
											printf("\t\t\t\t���˳��޸ģ�\n");
										}
										printf("\t\t\t\t���س���������");
										scanf("%c%c",&a,&b);
										choice2=0;
										break;
								case 3: printf("\t\t\t\t��ѡ���µ��ײͣ�\n");
										printf("\t\t\t\t 1. 0.5Ԫÿ��  2. 1Ԫÿ��  3. 2Ԫÿ��\n\t\t\t\t��ѡ��");
										scanf("%d",&j);
										while(j<0||j>3)
										{
											printf("\t\t\t\t����ȷѡ��\n");
											printf("\t\t\t\t 1. 0.5Ԫÿ��  2. 1Ԫÿ��  3. 2Ԫÿ��\n\t\t\t\t��ѡ��");
											scanf("%d",&j);
										} 
										if(j)
										{
											switch(j)
											{
												case 1: user[find].dayfee=0.5;
														break;
												case 2: user[find].dayfee=1;
														break;
												case 3: user[find].dayfee=2;
														break;
											}
											printf("\t\t\t\t�޸ĳɹ���\n");
										} 
										else
										{
											printf("\t\t\t\t���˳��޸ģ�\n");
										}
										printf("\t\t\t\t���س���������");
										scanf("%c%c",&a,&b);
										choice2=0;
										break;
								case 0: break;
							}
						}while(choice2);
					}
					else{
						printf("\t\t\t\t���س���������");
						scanf("%c%c",&a,&b);
					}
					break;
			case 4: printf("\t\t\t\t���Ȳ����û���Ϣ��\n");
					printf("\t\t\t\t���س��������ѯ�˵���");
					scanf("%c%c",&a,&b);
					find=runmenuSearch(user,n);
					if(find<=NUM)
					{
					
						printf("\t\t\t\t������Ҫ���ӵ��ֻ��ţ�") ;
						scanf("%s",num); 
						if(strcmp(num,"0")==0)
						{
							printf("\t\t\t\t���˳��޸ģ�\n");
						}
						else if(!strcmp(user[find].num[1],"0"))
							{
								strcpy(user[find].num[1],num);
								printf("\t\t\t\t���ӳɹ���\n");
							} else if (!strcmp(user[find].num[2],"0"))
								{
									strcpy(user[find].num[2],num);
									printf("\t\t\t\t���ӳɹ���\n");
								} else {
										printf("\t\t\t\t���������ӣ�ÿ���û����ֻ���������ֻ��ţ�\n");
									}
					}
					printf("\t\t\t\t���س���������");
					scanf("%c%c",&a,&b);
					break;
			case 5: printf("\t\t\t\t���Ȳ����û���Ϣ��\n");
					printf("\t\t\t\t���س��������ѯ�˵���");
					scanf("%c%c",&a,&b);
					find=runmenuSearch(user,n);
					if(find<=NUM)
					{
						printf("\t\t\t\t������Ҫע�����ֻ��ţ� ��") ;
						scanf("%s",num);
						if(strcmp(num,"0")==0)
						{
							printf("\t\t\t\t���˳�ע����\n");
						} else
						{
							for(i=0;i<3;i++)
							{
								if (!strcmp(user[find].num[i],num))
								{ 
									strcpy(user[find].num[i],"0");
									break; 
								}
							}
							for(;i<2;i++)
							{
								strcpy(user[find].num[i],user[find].num[i+1]);
							}
							strcpy(user[find].num[2],"0");
							printf("\t\t\t\tע���ɹ���\n");
						}
					}
					printf("\t\t\t\t���س���������");
					scanf("%c%c",&a,&b);
					break;
			case 0: break;
		}
	}while(choice);
	return n;
}
