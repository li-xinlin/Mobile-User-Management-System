#pragma warning(disable:4996)
#include<stdio.h>

#include<string.h>
#include<stdlib.h>
#include<time.h>	
#define NUM 50					//最大数据量 
#define sizeuser sizeof(User)	//一个用户信息所需要的内存空间大小 
struct Date
{
	int year;
	int month;
	int day;
};
typedef struct Date Date;
struct User
{
	char id[20];		//身份证号 
	char password[12];	//密码
	char name[10];		//用户姓名 
	char sex[4];		//性别 
	int age;			//年龄 
	char num[3][12];	//手机号
	char job[10];		//职业 
	char adress[10];	//住址 
	double fee;			//费用 
	double dayfee;		//日费用 
	Date date; 			//上次进入系统时间 
};
typedef struct User User;
//以下为用户数据处理的函数原型 
int readUser(User user[],int n);					//读入用户信息，身份证号为0或读满规定条数时停止 ,并返回实际读入条数 
void printUser(User *user,int n);					//输出用户记录
int equal(User u1,User u2,int con);					//根据con条件判断两个User类型数据是否相等
int larger(User u1,User u2,int con);				//根据con条件比较两个User类型数据大小
void sortUser(User user[],int n,int con);			//排序，按con条件
int searchUser(User user[],int n, User u,int con,int f[]);	//根据条件(con)查找与u相等的元素
int insertUser(User user[],int n, User u);			//向数组中插入一个元素-
int checkrepeatid(User user[],char id[],int i);		//身份证号查重复
int checkrepeatnum(User user[],char num[],int i);	//手机号查重复
int deleteUser(User user[],int n, User u);			//从数组中删除一个元素
void getdate(Date *da); 							//获取系统日期 
int sum(int y,int m,int d);
void fees(User *user,int n);    					 //实现扣除每月基础套餐费
void addmoney(User *user,int n,int find);			//充值 
//以下为身份证号相关函数 
int checkid(char s[]);							//校验身份证号的函数，必须输入合法的身份证号才能录入
int Judge(int year,int month,int day);			//日期合法性判断
int IsLeapYear(int year);						//闰年判断
int idage(char id[]);							//身份证号判断年龄 
//以下为文件相关处理的函数原型 
int createFile(User user[]);					//建立初始的数据文件 
int readFile(User user[]);						//读取文件内容置于结构体数组中 
void saveFile(User user[],int n);				//将结构体数组写入文件 
//以下为菜单相关的函数原型 
void printHead();								//打印表头，因数据过多，运行程序时请全屏显示 
void menu();									//顶级菜单函数
void menuManager();								//管理员菜单函数
void menuUser();								//用户菜单 
void runmenuUser(User user[],int n);			//用户登录
int checkPassword(User user[],int n,char id[],char password[]);		//用户登录校验
int runmenuManager(User user[],int n);			//管理员登录
void menuShow();								//显示用户信息菜单函数
void menuSearch();								//用户信息查询菜单函数 
void menuManage();								//用户信息管理菜单函数
int runMain(User user[],int n, int choice);		//对应一级菜单下各功能的执行 
void runmenuShow(User user[],int n);			//对应显示用户信息 
int runmenuSearch(User user[], int n);			//对应用户信息查询 
int runmenuManage(User user[],int n);			//对应用户信息管理
void passwordmanager();		
//主函数
int main()
{
	User user[NUM];
	int choice,n;
	n=readFile(user);
	if(!n)
	{
		printf("\t\t\t\t当前无数据，请输入管理员账号密码录入数据：\n"); 
		passwordmanager();
		n=createFile(user);
	}
	do
	{
		fees(user,n);						//进入系统实现扣费 
		menu();
		scanf("%d",&choice);
		if(choice>=0&&choice<=2)
			n=runMain(user,n,choice);
		else
			printf("\t\t\t\t输入有误，请重新输入！\n");
	}while(choice);
	saveFile(user,n);
	return 0;
}

//以下为用户数据处理的函数
int checkid(char id[])	//身份证号校验函数，依据身份证号标准GB11643-1999，正确返回1，错误返回0， 
{
	int b,c,e,i,idyear,idmonth,idday;
	char d;
	idyear=(id[6]-48)*1000+(id[7]-48)*100+(id[8]-48)*10+(id[9]-48);
	idmonth=(id[10]-48)*10+(id[11]-48);
	idday=(id[12]-48)*10+(id[13]-48);
	e=Judge(idyear,idmonth,idday);   //日期合法性
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
int Judge(int year,int month,int day)	//日期合法性判断
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
int IsLeapYear(int year)	//闰年判断
{
	int a=1;
	if(year%4==0&&year%100!=0||year%400==0)
		a=0;
	return a;
}
 
int checkrepeatid(User user[],char id[],int i)		//身份证号查重
{
	int j;
	for(j=0;j<i;j++)
	{
		if(!strcmp(user[j].id,id))
			return 1;
	}
	return 0;
}

int checkrepeatnum(User user[],char num[],int i)	//手机号查重
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

int readUser(User *user,int n)		//读入用户信息，身份证号为0或读满规定条数时停止 ,并返回实际读入条数 
{
	int i,j;
	Date da;
	char pass[12]; 
	getdate(&da);
	for(i=0;i<n;i++)
	{
		system("cls");
		printf("\t\t\t\t请输入一条信息(身份证号为0时结束输入)\n");
		printf("\t\t\t\t身份证号 :");
		scanf("%s",user[i].id);
		while((strcmp(user[i].id,"0"))&&((!checkid(user[i].id))||(checkrepeatid(user,user[i].id,i))))//判断身份证号是否合法
		{
			printf("\t\t\t\t身份证号不合法或与其他用户重复，请重新输入：");
			scanf("%s",user[i].id);
		} 
		if(!strcmp(user[i].id,"0"))
			break;
		printf("\t\t\t\t设置密码：");
		scanf("%s",user[i].password);
		printf("\t\t\t\t请再次输入密码：");
		scanf("%s",pass);
		while(strcmp(user[i].password,pass))
		{
			printf("\t\t\t\t两次输入不同，请重新输入\n");
			printf("\t\t\t\t设置密码：");
			scanf("%s",user[i].password);
			printf("\t\t\t\t请再次输入密码：");
			scanf("%s",pass);
		}
		printf("\t\t\t\t姓名 :");
		scanf("%s",user[i].name);
		if((user[i].id[16]-48)%2)				//由身份证号判断性别
		{
			strcpy(user[i].sex,"男");
		}
		else {
			strcpy(user[i].sex,"女");
		}
		user[i].age=idage(user[i].id);			//由身份证号判断年龄

		printf("\t\t\t\t手机号1:");
		scanf("%s",user[i].num[0]);
		while(checkrepeatnum(user,user[i].num[0],i))	//防止手机号重复
		{
			printf("\t\t\t\t手机号与其他重复，请重新输入：");
			scanf("%s",user[i].num[0]);
		}
		printf("\t\t\t\t手机号2:\n");
		printf("\t\t\t\t(提示：如果没有，请输入0)");
		scanf("%s",user[i].num[1]);
		while(checkrepeatnum(user,user[i].num[1],i)||(!strcmp(user[i].num[1],user[i].num[0])))
		{
			printf("\t\t\t\t手机号与其他重复，请重新输入：");
			scanf("%s",user[i].num[1]);
		}
		if(strcmp(user[i].num[1],"0"))
		{
			printf("\t\t\t\t手机号3:\n");
			printf("\t\t\t\t(提示：如果没有请输入0)");
			scanf("%s",user[i].num[2]);
			while(checkrepeatnum(user,user[i].num[2],i)||(!strcmp(user[i].num[2],user[i].num[0]))||(!strcmp(user[i].num[2],user[i].num[1])))
			{
				printf("\t\t\t\t手机号与其他重复，请重新输入：");
				scanf("%s",user[i].num[2]);
			}
		}
		else
		{
			strcpy(user[i].num[2],"0");
		}
		printf("\t\t\t\t职位 :");
		scanf("%s",user[i].job);
		printf("\t\t\t\t住址 :"); 
		scanf("%s",user[i].adress);
		printf("\t\t\t\t请选择套餐：\n");
		printf("\t\t\t\t 1. 0.5元每天  2. 1元每天  3. 2元每天\n\t\t\t\t请选择：");
		scanf("%d",&j);
		while(j<1||j>3)
		{
			printf("\t\t\t\t请正确选择：\n");
			printf("\t\t\t\t 1. 0.5元每天  2. 1元每天  3. 2元每天\n\t\t\t\t请选择：");
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

int idage(char id[])//身份证号判断年龄 
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

void printUser(User *user, int n)   //输出所有用户的信息记录
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

int equal (User u1, User u2, int con)      //根据con条件判断两个User类型数据是否相等 -朱慧 
{
	int i;
    if (con==1)                                       //如果参数con的值为1，则比较姓名
	{
		if(strcmp(u1.name, u2.name)==0)
			return 1;
		else return 0;
	}
  	if (con==2)                             		//如果参数con的值为2，则比较手机号 
    {
		for(i=0;i<3;i++)
			{
				if(strcmp(u1.num[i], u2.num[0])==0)   return 1;
			}       
    }
    if (con==3)                       			   //如果参数con的值为3，则比较身份证号 
	{
		 if(strcmp(u1.id, u2.id)==0)   return 1;
        	else return 0;
	} 
	else 
		return 0; 								//其余情况返回0
}

int larger(User u1,User u2,int con) 			//根据con条件比较两个User类型数据大小
{
	if(con==1)                           		 //1--比较名字
		if(strcmp(u1.name,u2.name)==1)
			return 1;
	if(con==2)                              	  //2---比较号码
		if(strcmp(u1.num[0],u2.num[0])==1)
			return 1;
	if(con==3)                                     //3----比较身份证
		if(strcmp(u1.id,u2.id)==1)
			return 1;
	if(con==4)                        			 //4--比较年龄
		return u1.age>u2.age;
	return 0;
}

void sortUser(User user[], int n, int con)   //选择法排序，按con条件由小到大排序-朱慧 
{
    int i, j, min;                                 //min用来储存本趟最小元素的下标
    User u;
    for(i=0; i<n-1; i++)                           //控制循环的n-1趟
    {
        min=i;
        for (j=i+1; j<n; j++)                       //寻找本趟最小元素所在的下标
        {
            if(larger(user[min], user[j], con))
                min=j;
        }
        if (i!=min)                               //保证本趟最小元素到达下标为i的位置
        {
            u=user[i];
            user[i]=user[min];
            user[min]=u;
        }
    }
}

int insertUser(User user[], int n, User u)      //向数组中插入一个元素                      
{
	
	user[n]=u;
	n++;																				
    return n;                                           //返回现有元素个数
}

int searchUser(User user[],int n, User u,int con,int f[])	//根据条件(con)查找与u相等的元素-陈天福 
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

int deleteUser(User user[],int n, User u)        //删除元素
{
	int i,j;
	for(i=0;i<n;i++)
	{
		if(equal(user[i],u,3))                //按身份证查找并删除用户信息
			break;
	}
	if(i==n)
	{
		printf("\t\t\t\t该用户不存在！\n");
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

void getdate(Date *da)    //获取当前年月日
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
			s+=366;	//闰年
		else							
		s+=365;		//平年
	if(y%4==0 && y%100!=0 || y%400==0)
		x[2]=29;
	for(i=1;i<m;i++)
		s+=x[i];	//整月的天数
	s+=d;			//日的天数
	return s;		//返回总天数
}

void fees(User *user,int n)     //实现扣除每月基础套餐费
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
	printf("\t\t\t\t请输入充值金额：");
	scanf("%lf",&money);
	user[find].fee+=money;
	printf("\t\t\t\t充值成功！\n");
	printf("\t\t\t\t按回车键继续：");
	scanf("%c%c",&a,&b);
} 

//以下为用二进制文件实现数据的保存 
int createFile(User user[])	//建立初始的数据文件 
{
	FILE *fp;
	int n;
	char a,b;
	if((fp=fopen("user.dat","wb"))==NULL)	//以写入方式打开 
	{
		printf("\t\t\t\tcan not open file!\n");
		exit(0);	
	}
	printf("\t\t\t\t请输入用户信息，按回车键继续：");
	scanf("%c%c",&a,&b);
	n=readUser(user,NUM);
	fwrite(user,sizeuser,n,fp);
	fclose(fp);
	return n;
}

int readFile(User user[])		//读取文件内容置于结构体数组中 
{
	FILE *fp;
	int i =0;
	if((fp=fopen("user.dat","rb"))==NULL)	//以读取方式打开 
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
	return i;			//返回数据条数 
}

void saveFile(User user[],int n)	//将结构体数组写入文件 
{
	FILE *fp;
	if((fp=fopen("user.dat","wb"))==NULL)	//以写入方式打开 
	{
		printf("\t\t\t\tcan not open file!\n");
		exit(0);	
	}
	fwrite(user,sizeuser,n,fp);
	fclose(fp);
}

//以下为用户界面，多级菜单函数
void printHead()	//打印表头，因数据过多，运行程序时请全屏显示 
{
	printf("\n%7s%7s%5s%11s%14s%12s%16s%11s%10s%9s\n\n","姓名","性别","年龄","手机号1","手机号2","手机号3","身份证号","余额","职业","住址"); 
}

void menu()	//顶级菜单函数 
{
	system("cls");
	printf("\t\t\t\t----------------------------------\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|      移动用户管理系统          |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|         1.移动用户             |\n\t\t\t\t|");
	printf("                                |\n"); 
	printf("\t\t\t\t|         2.管理员               |\n\t\t\t\t|");
	printf("                                |\n"); 
	printf("\t\t\t\t|         0.退出                 |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t----------------------------------\n");
	printf("\t\t\t\t|   制作：李新林 陈天福 朱慧     |\n");
	printf("\t\t\t\t----------------------------------\n\n");
	printf("\t\t\t\t请选择你的身份："); 
}

void menuManager()	//管理员菜单函数 
{
	system("cls");
	printf("\t\t\t\t----------------------------------\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t| 管理员你好!你可以做以下操作    |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|        1.显示用户信息          |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t|        2.用户信息查询          |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t|        3.用户信息管理          |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|        4.话费充值              |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|        0.返回上一级            |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t----------------------------------\n\n");
	printf("\t\t\t\t请输入你的选择："); 
}

void menuUser()	//用户菜单
{
	system("cls");
	printf("\t\t\t\t----------------------------------\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|   用户你好!你可以做以下操作    |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|        1.显示个人信息          |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t|        2.修改个人信息          |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t|        3.我的通话套餐          |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t|        4.话费充值              |\n\t\t\t\t|");
	printf("                                |\n");
	printf("\t\t\t\t|        0.返回上一级            |\n\t\t\t\t|"); 
	printf("                                |\n");
	printf("\t\t\t\t----------------------------------\n\n");
	printf("\t\t\t\t请输入你的选择："); 
}

void menuShow()	//显示用户信息菜单函数
{
	system("cls");
	printf("\t\t\t\t--------------------------------------------\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|\t\t 显示用户信息              |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         1.按姓名顺序排序显示             |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         2.按年龄顺序排序显示             |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         3.按身份证号顺序排序显示         |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         0.返回上层菜单                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t--------------------------------------------\n\n");
	printf("\t\t\t\t请输入你的选择："); 
} 

void menuSearch()	//用户信息查询菜单函数 
{
	printf("\t\t\t\t--------------------------------------------\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|\t   用户信息查询                    |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|充值、修改、删除用户信息时先进入此菜单查询|\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         1.按用户名查询                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         2.按手机号查询                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         3.按身份证号查询                 |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         0.返回上层菜单                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t--------------------------------------------\n\n");
	printf("\t\t\t\t请输入你的选择："); 
} 

void menuManage()	//用户信息管理菜单函数
{
	system("cls");
	printf("\t\t\t\t--------------------------------------------\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|\t   用户信息管理                    |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         1.新增移动用户                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         2.删除用户数据                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         3.修改用户信息                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         4.增加用户手机号码               |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         5.注销用户手机号码               |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t|         0.返回上层菜单                   |\n\t\t\t\t|");
	printf("                                          |\n");
	printf("\t\t\t\t--------------------------------------------\n\n");
	printf("\t\t\t\t请输入你的选择："); 
} 
int runMain(User user[],int n, int choice)	//对应一级菜单下各功能的执行 
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

void runmenuUser(User user[],int n)		//用户登录
{
	char id[20],password[12],new[10],a,b;
	int i,choice,find,f[NUM],choice2;
	User u;
	i=0;
	printf("\t\t\t\t请先输入身份证号与密码登录\n");
	printf("\t\t\t\t身份证号：");
	scanf("%s",id);
	printf("\t\t\t\t密码：");
	scanf("%s",password);
	while(checkPassword(user,n,id,password))
	{
		i++;
		if(i==3)
		{
			printf("\t\t\t\t错误超过三次！\n");
			exit(1);
		}
		printf("\t\t\t\t身份证号与密码不匹配，请重新输入\n");
		printf("\t\t\t\t身份证号：");
		scanf("%s",id);
		printf("\t\t\t\t密码：");
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
			printf("\t\t\t\t请输入有效的选择：");
			scanf("%d",&choice);
		}
		switch(choice)
		{
			case 1: printHead();
					printUser(&user[f[0]],1);
					printf("\t\t\t\t按回车键继续：");
					scanf("%c%c",&a,&b);
					break;
			case 2: printf("\t\t\t\t请选择修改项目：\n");
					printf("\t\t\t\t（注：用户名、身份证号、手机号不可修改）\n");
					printf("\n\t\t\t\t 1.职业 \n\n\t\t\t\t 2.住址\n\n\t\t\t\t 0.返回\n\n\t\t\t\t请输入你的选择：");
					scanf("%d",&choice2);
					do
					{
						switch(choice2)
						{
							case 1: printf("\t\t\t\t请输入新的职业：");
									scanf("%s",&new);
									if(strcmp(new,"0"))
									{
										strcpy(user[f[0]].job,new);
										printf("\t\t\t\t修改成功！\n");
									} 
									else
									{
										printf("\t\t\t\t已退出修改！\n");
									}
									printf("\t\t\t\t按回车键继续：");
									scanf("%c%c",&a,&b);
									choice2=0;
									break;
							case 2:  printf("\t\t\t\t请输入新的住址：");
									scanf("%s",&new);
									if(strcmp(new,"0"))
									{
										strcpy(user[f[0]].adress,new);
										printf("\t\t\t\t修改成功！\n");
									} 
									else
									{
										printf("\t\t\t\t已退出修改！\n");
									}
									printf("\t\t\t\t按回车键继续：");
									scanf("%c%c",&a,&b);
									choice2=0;
									break;
							case 0: break;
						}
					}while(choice2);
					break;
			case 3: printf("\n\t\t\t\t您当前的套餐为%.2f元每天，修改套餐请联系管理员。\n",user[f[0]].dayfee);
					printf("\n\t\t\t\t按回车键继续：");
					scanf("%c%c",&a,&b);
					break;
			case 4: addmoney(user,n,f[0]);
					break;
			case 0: break;
		}
	}while(choice);

}

int checkPassword(User user[],int n,char id[],char password[])		//用户登录校验
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

int runmenuManager(User user[],int n)	//管理员登录
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
			printf("\t\t\t\t请输入有效的选择：");
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
			case 4: printf("\t\t\t\t请先查找用户：\n");
					printf("\t\t\t\t按回车键进入查询菜单：");
					scanf("%c%c",&a,&b);	
					find=runmenuSearch(user,n);
					if(find>NUM)
					{
						printf("\t\t\t\t无法充值，按回车键继续：");
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

void passwordmanager()			//管理员登录 
{
	int i=0;
	char pass[12],u[12];
	printf("\t\t\t\t请输入管理员账号：");
	scanf("%s",u);
	printf("\t\t\t\t请输入管理员密码：");
	scanf("%s",pass);
	while(strcmp(pass,"123456")!=0||strcmp(u,"123456")!=0)
	{	
		i++;
		if(i==3)
		{
			printf("\t\t\t\t错误超过三次！\n");
			exit(1);
		}
		printf("\t\t\t\t密码输入错误，请重新输入：\n");
		printf("\t\t\t\t请输入管理员账号：");
		scanf("%s",u);
		printf("\t\t\t\t请输入管理员密码：");
		scanf("%s",pass);
	}
}

void runmenuShow(User user[],int n)	//对应显示用户信息 
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
					sortUser(user,n,1);	//con为1表示按姓名排序
					printUser(user,n);
					printf("\t\t\t\t按回车键继续：");
					scanf("%c%c",&a,&b);
					break;
			case 2: printHead();
					sortUser(user,n,4);	//con为2表示按年龄排序
					printUser(user,n);
					printf("\t\t\t\t按回车键继续：");
					scanf("%c%c",&a,&b);
					break;
			case 3: printHead();
					sortUser(user,n,3);	//con为3表示按身份证号排序
					printUser(user,n);
					printf("\t\t\t\t按回车键继续：");
					scanf("%c%c",&a,&b);
					break;
			case 0: break;
		}
	}while(choice); 
}
int runmenuSearch(User user[], int n)	//对应用户信息查询 
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
			case 1:	printf("\t\t\t\t请输入要查询的用户名： ");
				   	scanf("%s",u.name);
					break;
			case 2:	printf("\t\t\t\t请输入要查询的手机号： ");
				   	scanf("%s",u.num[0]);
					break;	
			case 3:	printf("\t\t\t\t请输入要查询的身份证号： ");
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
				printf("\t\t\t\t找不到相关用户！\n");
				printf("\t\t\t\t按回车键继续：");
				scanf("%c%c",&a,&b);
				return (NUM+1);
			} else if(find==1)
				{
					printHead();
					printUser(&user[f[0]],1);
					printf("\t\t\t\t找到一位用户，按回车键继续：");
					scanf("%c%c",&a,&b);
					return f[0]; 
				}
				else
				{
					printf("\t\t\t\t找到大于一位用户，请增加查询条件：\n");
					printf("\t\t\t\t按回车键继续：");
					scanf("%c%c",&a,&b);
					menuSearch();
					scanf("%d",&choice2);
					while(choice2==choice1)
					{ 
						printf("\t\t\t\t这个条件已经用过了，请输入其他条件：");
						scanf("%d",&choice2);
					}
					switch(choice2)			//如果找到多条数据，则一定是根据用户名查询，因为手机号、身份证号唯一 
					{
						case 2:	printf("\t\t\t\t请输入要查询的手机号： ");
							   	scanf("%s",u.num[0]);
								break;	
						case 3:	printf("\t\t\t\t请输入要查询的身份证号： ");
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
							printf("\t\t\t\t找不到相关用户！\n");
							printf("\t\t\t\t按回车键继续：");
							scanf("%c%c",&a,&b);
							return (NUM+1);
						} else {
								printHead();
								printUser(&user[f[0]],1);
								printf("\t\t\t\t找到一位用户，按回车键继续：");
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
			case 1: printf("\t\t\t\t请输入要增加的用户信息，按回车键继续：");
					scanf("%c%c",&a,&b);
					readUser(&u,1);
					while(checkrepeatid(user,u.id,n)||checkrepeatnum(user,u.num[0],n)||checkrepeatnum(user,u.num[1],n)||checkrepeatnum(user,u.num[2],n))
					{
						printf("\t\t\t\t身份证号或手机号与原数据库重复，请重新录入信息：\n\t\t\t\t按回车键继续：");
						scanf("%c%c",&a,&b);
						readUser(&u,1);
					}
					if(strcmp(u.id,"0"))
					{
						n=insertUser(user,n,u);
						printf("\t\t\t\t录入信息成功！\n");
					}
					else printf("\t\t\t\t已退出新增用户！\n");
					printf("\t\t\t\t按回车键继续：");
					scanf("%c%c",&a,&b);
					break;
			case 2: printf("\t\t\t\t请先查找用户信息：\n");
					printf("\t\t\t\t按回车键进入查询菜单：");
					scanf("%c%c",&a,&b);	
					find=runmenuSearch(user,n);
					if(find<=NUM)
					{
						printf("\t\t\t\t是否要删除，1. 删除  0.不删除 \n");
						printf("\t\t\t\t请输入你的选择：");
						scanf("%d",&de);
						if(de)
						{
							strcpy(u.id,user[find].id);
							n=deleteUser(user,n,u);
							printf("\t\t\t\t已删除上方的一条信息！\n");
						}
						else
						{
							printf("\t\t\t\t已退出删除!\n");
						}
					}
					printf("\t\t\t\t按回车键继续：");
					scanf("%c%c",&a,&b);
					break;
			case 3: printf("\t\t\t\t请先查找用户信息：\n");
					printf("\t\t\t\t按回车键进入查询菜单：");
					scanf("%c%c",&a,&b);	
					find=runmenuSearch(user,n);
					if(find<=NUM)
					{
						printf("\t\t\t\t请选择修改项目：\n");
						printf("\t\t\t\t（注：用户名、身份证号、手机号不可修改）\n\n");
						printf("\n\t\t\t\t 1.职业 \n\n\t\t\t\t 2.住址\n\n\t\t\t\t 3.套餐\n\n\t\t\t\t 0.返回\n\n\t\t\t\t请输入你的选择：");
						scanf("%d",&choice2);
						do
						{
							switch(choice2)
							{
								case 1: printf("\t\t\t\t请输入新的职业：");
										scanf("%s",&new);
										if(strcmp(new,"0"))
										{
											strcpy(user[find].job,new);
											printf("\t\t\t\t修改成功！\n");
										} 
										else
										{
											printf("\t\t\t\t已退出修改！\n");
										}
										printf("\t\t\t\t按回车键继续：");
										scanf("%c%c",&a,&b);
										choice2=0;
										break;
								case 2:  printf("\t\t\t\t请输入新的住址：");
										scanf("%s",&new);
										if(strcmp(new,"0"))
										{
											strcpy(user[find].adress,new);
											printf("\t\t\t\t修改成功！\n");
										} 
										else
										{
											printf("\t\t\t\t已退出修改！\n");
										}
										printf("\t\t\t\t按回车键继续：");
										scanf("%c%c",&a,&b);
										choice2=0;
										break;
								case 3: printf("\t\t\t\t请选择新的套餐：\n");
										printf("\t\t\t\t 1. 0.5元每天  2. 1元每天  3. 2元每天\n\t\t\t\t请选择：");
										scanf("%d",&j);
										while(j<0||j>3)
										{
											printf("\t\t\t\t请正确选择：\n");
											printf("\t\t\t\t 1. 0.5元每天  2. 1元每天  3. 2元每天\n\t\t\t\t请选择：");
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
											printf("\t\t\t\t修改成功！\n");
										} 
										else
										{
											printf("\t\t\t\t已退出修改！\n");
										}
										printf("\t\t\t\t按回车键继续：");
										scanf("%c%c",&a,&b);
										choice2=0;
										break;
								case 0: break;
							}
						}while(choice2);
					}
					else{
						printf("\t\t\t\t按回车键继续：");
						scanf("%c%c",&a,&b);
					}
					break;
			case 4: printf("\t\t\t\t请先查找用户信息：\n");
					printf("\t\t\t\t按回车键进入查询菜单：");
					scanf("%c%c",&a,&b);
					find=runmenuSearch(user,n);
					if(find<=NUM)
					{
					
						printf("\t\t\t\t请输入要增加的手机号：") ;
						scanf("%s",num); 
						if(strcmp(num,"0")==0)
						{
							printf("\t\t\t\t已退出修改！\n");
						}
						else if(!strcmp(user[find].num[1],"0"))
							{
								strcpy(user[find].num[1],num);
								printf("\t\t\t\t增加成功！\n");
							} else if (!strcmp(user[find].num[2],"0"))
								{
									strcpy(user[find].num[2],num);
									printf("\t\t\t\t增加成功！\n");
								} else {
										printf("\t\t\t\t！不能增加，每个用户最多只能有三个手机号！\n");
									}
					}
					printf("\t\t\t\t按回车键继续：");
					scanf("%c%c",&a,&b);
					break;
			case 5: printf("\t\t\t\t请先查找用户信息：\n");
					printf("\t\t\t\t按回车键进入查询菜单：");
					scanf("%c%c",&a,&b);
					find=runmenuSearch(user,n);
					if(find<=NUM)
					{
						printf("\t\t\t\t请输入要注销的手机号： ：") ;
						scanf("%s",num);
						if(strcmp(num,"0")==0)
						{
							printf("\t\t\t\t已退出注销！\n");
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
							printf("\t\t\t\t注销成功！\n");
						}
					}
					printf("\t\t\t\t按回车键继续：");
					scanf("%c%c",&a,&b);
					break;
			case 0: break;
		}
	}while(choice);
	return n;
}
