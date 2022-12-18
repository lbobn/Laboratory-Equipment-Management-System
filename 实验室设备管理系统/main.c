#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct zhanghu	
{
	char admin[20];
	char password[20];
};
struct shebei
{
	int num;				//编号
	char name[200];		//名称
	char sys[20];		//所属实验室
	char date_buy[11];	//购入日期
	char price[10];		//价格
	char kucun[10];		//库存
	char date_birth[11];	//生产日期
	struct shebei *next;
};
int menu_1();					//登录菜单
void zhuce();					//账户注册
int denglu();					//账户登录
int menu_2();					//主菜单
struct shebei*load();				//文件读取至链表
void save(struct shebei*head);	//链表写入文件
struct shebei*chuangjian();		//新链表创建及保存
void show(struct shebei*head);	//链表打印
void shebei_add();				//链表末尾追加
int shebei_change();				//设备修改
int shebei_del();				//设备删除
void shebei_find_1();
void shebei_find_1();
void shebei_find_1();
void shebei_find_1();
void shebei_find_1();
int shebei_FIND();				//设备查找
void shebei_tongji();				//按实验室统计
void data_exchange(struct shebei*m,struct shebei*n);//交换两节点数据
void shebei_sort_numup();
void shebei_sort_numdown();
void shebei_sort_nameup();
void shebei_sort_namedown();
void shebei_sort_sysup();
void shebei_sort_sysdown();
int shebei_SORT_MENU();			//排序

int main()
{
	int choice_1,choice_2=10;
	printf("\t\t\t\t欢迎使用实验室设备管理系统!\n");
	/******************注册登录****************/
	choice_1=menu_1();
	while(choice_1!=0 && choice_2==10)
	{
		switch(choice_1)
		{
		case 1:choice_2=denglu();break;
		case 2:zhuce();break;
		default:return 0;
		}
		if(choice_2!=11)
		{	
			choice_1=menu_1();}
	}
	/*****************主界面*******************/
	if(choice_1)
	{
		for(choice_2=menu_2();choice_2!=0;choice_2=menu_2())
			switch(choice_2)
		{
			case 1:system("cls");chuangjian();break;//创建
			case 2:system("cls");show(load());break;//显示
			case 3:system("cls");shebei_add();break;//增加
			case 4:system("cls");if(shebei_FIND()==1)	
					   printf("————————————————————操作成功————————————————————\n");
				break;//查询
			case 5:system("cls");shebei_tongji();break;//统计
			case 6:if(shebei_change()==1)	
				   {system("cls");
						printf("	————————————————————修改成功————————————————————\n");}
				   else					
				   {system("cls");
						printf("——-———————————————未找到此设备，修改失败——-—————————————\n");}
				   break;//修改
			case 7:if(shebei_del()==1)	
				   {system("cls");
						printf("————————————————————删除成功————————————————————\n");}
				   else					
				   {system("cls");
						printf("—————————————————-未找到此设备，修改失败———————————————-\n");}
				   break;//删除
			case 8:system("cls");if(shebei_SORT_MENU()==1);
						printf("————————————————————操作成功————————————————————\n");
					break;//排序
			default:;
		}
	}
}

/*
***************初始操作*******************************************
*/
int menu_1()
{
	int n;
	printf("\t\t\t\t********************************\n");
	printf("\t\t\t\t*           1.登录             *\n");
	printf("\t\t\t\t*           2.注册             *\n");
	printf("\t\t\t\t*           0.退出             *\n");
	printf("\t\t\t\t********************************\n");
	printf("请输入您的选择：");
	scanf("%d",&n);
	return n;
}

void zhuce()
{
	FILE*fp;
	char yhm[20],mima_0[20],mima_1[20];
	struct zhanghu s;
	struct zhanghu*p=&s;
	int t=0,i,m=0;
	do{
		printf("请输入用户名：\n");
		scanf("%s",yhm);
		printf("请输入密码：\n");
		scanf("%s",mima_0);
		printf("请再一次输入密码：\n");
		scanf("%s",mima_1);
		if(strcmp(mima_0,mima_1)==0)
			{system("cls");
			 printf("注册成功！\n");
			 t=1;
			break;}
		else
		{
			m++;
			if(m>2)	{system("cls");printf("您已3次输入不一致，已退出此操作！\n");}
			else printf("密码不一致，请重新输入：\n");}
	}while(t==0 && m<3);
/***********保存到账户文件**************************************/
	if(m<3)
	{
	for(i=0;mima_0[i]!='\0';i++)
		mima_0[i]+=10;                                     //密码加密
	strcpy(p->admin,yhm);		strcpy(p->password,mima_0);
	if((fp=fopen("zhanghu.txt","ab"))==NULL)
		{printf("cuowu0");exit(0);}
	if((fwrite(&s,sizeof(struct zhanghu),1,fp))!=1)
		{printf("写入数据错误！");exit(0);}
	fclose(fp);
	}
}

int denglu()
{
	struct zhanghu read;
	struct zhanghu*p=&read;
	char yhm[20],mima[20];
	FILE*fp;
	int n=0,i,j,t=0;
	if((fp=fopen("zhanghu.txt","rb"))==NULL)
	{	system("cls");
		printf("不存在账户文件，请注册\n");return 10;}
	for(i=4;i>=0;i--)
	{
		printf("请输入用户名：\n");
		scanf("%s",yhm);
		printf("请输入密码：\n");
		scanf("%s",mima);
		rewind(fp);
		while(t==0 && fp!=NULL && n==0)
		{
		if((fread(&read,sizeof(struct zhanghu),1,fp))!=NULL)
		{if(strcmp(p->admin,yhm)==0)	
			{
				t=1;n=1;
				for(j=0;p->password[j]!='\0';j++)
					p->password[j]-=10;					//密码解密
				if(strcmp(p->password,mima)==0)
					{system("cls");
					printf("登录成功！\n");
					return 11;}
				else		
				{
					n=0;t=0;					
					if(i==4)
					{	system("cls");
						printf("用户名或密码输入错误，请重新输入！\n");}
					else
					{	system("cls");
						printf("登录失败！您还有%d次机会！\n",i);
						if(i==0) return 10;
					}
					break;
				}
			}
		}
		else 
			{system("cls");
			printf("此账户不存在！\n");
			return 10;}
		}
	}
	fclose(fp);
}

/*
***************主菜单*********************************************
*/
int menu_2()
{
	int n;
	printf("\t\t\t\t********************************\n");
	printf("\t\t\t\t*         1.创建新数据表       *\n");
	printf("\t\t\t\t*         2.显示设备信息       *\n");
	printf("\t\t\t\t*         3.增加设备           *\n");
	printf("\t\t\t\t*         4.查询设备           *\n");
	printf("\t\t\t\t*         5.统计设备           *\n");
	printf("\t\t\t\t*         6.修改设备           *\n");
	printf("\t\t\t\t*         7.删除设备           *\n");
	printf("\t\t\t\t*         8.对设备排序         *\n");
	printf("\t\t\t\t*         0.退出               *\n");
	printf("\t\t\t\t********************************\n");
	printf("请输入您的选择：");
	scanf("%d",&n);
	return n;
}

struct shebei*load()
{
    struct shebei*head,*p,*q,*tail;FILE*fp;char ch;
	head=NULL,p=NULL;
	if((fp=fopen("shebei.txt","rb"))==NULL)
	{printf("打开设备文件失败！");return;}
	if(ch=getc(fp)==EOF)	{head==NULL;return head;}
	else fseek(fp,-1L,1);
	while(ch=getc(fp)!=EOF)
	{
		fseek(fp,-1L,1);
		q=(struct shebei*)malloc(sizeof(struct shebei));
		fscanf(fp,"%d%s%s%s%s%s%s\n",&q->num,q->name,q->sys,q->date_buy,q->price,q->kucun,q->date_birth);
		if(head==NULL)
	{head=q;head->next=NULL;p=head;}
	else{
	p->next=q;
	p=q;}
	}
	p->next=NULL;
	fclose(fp);
	return head;
}

void save(struct shebei*head)
{	
	struct shebei*q;FILE*fp;
	q=head;
	
	if((fp=fopen("shebei.txt","wb"))==NULL)
	{printf("打开设备文件失败！");return;}
	while(q)
	{
		fprintf(fp,"%d %s %s %s %s %s %s\n",q->num,q->name,q->sys,q->date_buy,q->price,q->kucun,q->date_birth);
		q=q->next;
	}
	fclose(fp);
}

struct shebei*chuangjian()
{
	
	struct shebei*head,*p,*tail;
	int number,r;
	head=NULL;
	tail=NULL;
	printf("\t\t警告\n此操作会删除之前的所有数据，是否继续？\n\t1.继续\n\t2.退出\n请输入您的选择：");
	scanf("%d",&r);
	if(r==2)	return NULL;
	system("cls");
	printf("请输入设备编号(输入0结束)：");
	scanf("%d",&number);
	while(number!=0)
	{
		
		p=(struct shebei*)malloc(sizeof(struct shebei));
		p->num=number;
		/********************数据输入**********************/
		printf("请输入设备名称：");	scanf("%s",p->name);
		printf("请输入所属实验室：");	scanf("%s",p->sys);
		printf("请输入购买日期（用“-”隔开）：");scanf("%s",p->date_buy);
		printf("请输入价格：");		scanf("%s",p->price);
		printf("请输入库存：");		scanf("%s",p->kucun);
		printf("请输入生产日期（用“-”隔开）：");	scanf("%s",p->date_birth);
		/********************连接链表*********************/
		p->next=NULL;
		if(head==NULL)	head=p;
		else		tail->next=p;
		tail=p;
		system("cls");
		printf("请输入下个设备的编号(输入0结束)：");
		scanf("%d",&number);
	}
	save(head);
	return head;
}

void show(struct shebei*head)
{
	struct shebei*p;
	p=head;
	if(head==NULL)	{printf("无数据！\n");return;}
	printf("编号   设备名称            所属实验室   购买日期      价格     库存       生产日期\n");
	while(p)
	{
		printf("%5d %-20s %-10s   %-10s  %-10s %-10s %-10s\n",p->num,p->name,p->sys,p->date_buy,p->price,p->kucun,p->date_birth);
		p=p->next;
	}
}

void shebei_add()
{
	struct shebei*head,*p,*tail,*q;
	int number;
	head=load();p=head;
	if(head==NULL)	{printf("无任何数据，请创建！\n");return;}
	while(p->next!=NULL)	p=p->next;
	tail=p;
	printf("请输入设备编号（输入0结束）：");
	scanf("%d",&number);
	while(number!=0)
	{
		
		q=(struct shebei*)malloc(sizeof(struct shebei));
		q->num=number;
		/********************数据输入**********************/
		printf("请输入设备名称：");	scanf("%s",q->name);
		printf("请输入所属实验室：");	scanf("%s",q->sys);
		printf("请输入购买日期（用“-”隔开）：");scanf("%s",q->date_buy);
		printf("请输入价格：");		scanf("%s",q->price);
		printf("请输入库存：");		scanf("%s",q->kucun);
		printf("请输入生产日期（用“-”隔开）：");	scanf("%s",q->date_birth);
		/********************连接链表*********************/
		q->next=NULL;
		if(tail==NULL)	tail=q;
		else		tail->next=q;
		tail=q;
		system("cls");
		printf("请输入下个设备的编号(输入0结束)：");
		scanf("%d",&number);
	}
	save(head);

}

void shebei_find_1()
{
	struct shebei*head,*p;int n=0,sum=0,temp;
	head=load();p=head;
	printf("请输入设备编号：");	scanf("%d",&temp);
	do
	{
		if(head==NULL)	{printf("无数据！\n");return;}
		else
		{
			if(p->num==temp)
			{
				if(sum==0)	printf("编号   设备名称            所属实验室   购买日期      价格     库存       生产日期\n");				
				printf("%5d %-20s %-10s   %-10s  %-10s %-10s %-10s\n",p->num,p->name,p->sys,p->date_buy,p->price,p->kucun,p->date_birth);
				sum++;
			}
			n++;
			p=p->next;
		}
	}while(p!=NULL);
	if(sum==0)	printf("未找到设备编号为%d的数据!\n",temp);
}
void shebei_find_2()
{
	struct shebei*head,*p;int n=0,sum=0;char str[20];
	head=load();p=head;
	printf("请输入设备名称：");	scanf("%s",str);
	do
	{
		if(p==NULL)	{printf("无数据！\n");return;}
		else
		{
			if(strcmp(p->name,str)==0)
			{
				if(sum==0)	printf("编号   设备名称            所属实验室   购买日期      价格     库存       生产日期\n");				
				printf("%5d %-20s %-10s   %-10s  %-10s %-10s %-10s\n",p->num,p->name,p->sys,p->date_buy,p->price,p->kucun,p->date_birth);
				sum++;
			}
			n++;
			p=p->next;
		}
	}while(p!=NULL);
	if(sum==0)	printf("未找到设备名称为%s的数据!\n",str);
}
void shebei_find_3()
{
	struct shebei*head,*p;int n=0,sum=0;char str[20];
	head=load();p=head;
	printf("请输入设备所属实验室：");	scanf("%s",str);
	do
	{
		if(p==NULL)	{printf("无数据！\n");return;}
		else
		{
			if(strcmp(p->sys,str)==0)
			{
				if(sum==0)	printf("编号   设备名称            所属实验室   购买日期      价格     库存       生产日期\n");				
				printf("%5d %-20s %-10s   %-10s  %-10s %-10s %-10s\n",p->num,p->name,p->sys,p->date_buy,p->price,p->kucun,p->date_birth);
				sum++;
			}
			n++;
			p=p->next;
		}
	}while(p!=NULL);
	if(sum==0)	printf("未找到所属实验室为%s的数据!\n",str);
}
void shebei_find_4()
{
	struct shebei*head,*p;int n=0,sum=0;char str1[20],str2[20];
	head=load();p=head;
	printf("请输入设备名称及所属实验室：");	scanf("%s%s",str1,str2);
	do
	{
		if(p==NULL)	{printf("无数据！\n");return;}
		else
		{
			if(strcmp(p->name,str1)==0 && strcmp(p->sys,str2)==0)
			{
				if(sum==0)	printf("编号   设备名称            所属实验室   购买日期      价格     库存       生产日期\n");				
				printf("%5d %-20s %-10s   %-10s  %-10s %-10s %-10s\n",p->num,p->name,p->sys,p->date_buy,p->price,p->kucun,p->date_birth);
				sum++;
			}
			n++;
			p=p->next;
		}
	}while(p!=NULL);
	if(sum==0)	printf("未找到设备名称为%s且所属实验室为%s的数据!\n",str1,str2);
}
int shebei_FIND()
{
	int n;
	printf("请选择查找方式\n\t1.编号\n\t2.设备名称\n\t3.所属实验室\n\t4.设备名称&所属实验室\n\t0.退出此操作\n请输入您的选择：");
	scanf("%d",&n);
	if(n==0)		return 0;
	switch(n)
	{
	case 1:shebei_find_1();break;
	case 2:shebei_find_2();break;
	case 3:shebei_find_3();break;
	case 4:shebei_find_4();break;
	default:;
	}
	return 1;
}

int shebei_change()
{
	struct shebei*head,*p,*q;int Num,r=0,num_0;
	head=load();p=head;
	printf("请输入要修改的设备编号：");
	scanf("%d",&Num);
	do
	{
		if(p->num==Num)	{r=1;break;}
		else {q=p;p=p->next;}
	}while(q->next!=NULL);
	if(r==0)		{printf("未找到此设备！\n");return 0;}
	else
	{
		printf("请输入设备编号(输入0则退出此操作且不保存)：");	
		scanf("%d",&num_0);
		if(num_0==0)	return 0;else p->num=num_0;
		printf("请输入设备名称：");	scanf("%s",p->name);
		printf("请输入所属实验室：");	scanf("%s",p->sys);
		printf("请输入购买日期（用“-”隔开）：");scanf("%s",p->date_buy);
		printf("请输入价格：");		scanf("%s",p->price);
		printf("请输入库存：");		scanf("%s",p->kucun);
		printf("请输入生产日期（用“-”隔开）：");	scanf("%s",p->date_birth);
	}
	save(head);
	return 1;
}

int shebei_del()
{
	struct shebei*head,*p,*q;int Num,r=0;
	head=load();p=head;
	printf("请输入要删除的设备编号：");
	scanf("%d",&Num);
	do
	{
		if(p->num==Num)	{r=1;break;}
		else {q=p;p=p->next;}
	}while(q->next!=NULL);
	if(r==0)		{printf("未找到此设备！\n");return 0;}
	else
	{
		if(p==head)	head=p->next;
		else		q->next=p->next;
		free(p);
	}
	save(head);
	return 1;
}

void shebei_tongji()
{
	struct shebei*head,*p;int num=0,n[5]={0};
	head=load();p=head;
	do
	{
		if(head==NULL)	{printf("数据为0\n");return;}
		if(strcmp(p->sys,"wuli")==0)	n[0]++;
		else
			if(strcmp(p->sys,"huaxue")==0)	n[1]++;
			else
				if(strcmp(p->sys,"shengwu")==0)		n[2]++;
				else
					if(strcmp(p->sys,"jisuanji")==0)	n[3]++;
					else		n[4]++;
		num++;
		p=p->next;
	}while(p!=NULL);
	printf("共有%d组数据，其中：\n",num);
	if(n[0]!=0)	printf("属于物理实验室的有%d组\n",n[0]);
	if(n[1]!=0)	printf("属于化学实验室的有%d组\n",n[1]);
	if(n[2]!=0)	printf("属于生物实验室的有%d组\n",n[2]);
	if(n[3]!=0)	printf("属于计算机实验室的有%d组\n",n[3]);
	if(n[4]!=0)	printf("属于其他实验室的有%d组\n",n[4]);
}

void data_exchange(struct shebei*m,struct shebei*n)
{	
	int numt;char namet[20],syst[10],datebuyt[11],pricet[10],kucunt[10],datebirtht[11];
	struct shebei*q,*p;
	p=m,q=n;
	numt=p->num;
	strcpy(namet,p->name);
	strcpy(syst,p->sys);
	strcpy(datebuyt,p->date_buy);
	strcpy(pricet,p->price);
	strcpy(kucunt,p->kucun);
	strcpy(datebirtht,p->date_birth);//放在中间变量
	p->num=q->num;
	strcpy(p->name,q->name);
	strcpy(p->sys,q->sys);
	strcpy(p->date_buy,q->date_buy);
	strcpy(p->price,q->price);
	strcpy(p->kucun,q->kucun);
	strcpy(p->date_birth,q->date_birth);//q所指数据赋予p
	q->num=numt;
	strcpy(q->name,namet);
	strcpy(q->sys,syst);
	strcpy(q->date_buy,datebuyt);
	strcpy(q->price,pricet);
	strcpy(q->kucun,kucunt);
	strcpy(q->date_birth,datebirtht);//中间变量赋予q
}
void shebei_sort_numup()
{
	struct shebei*head,*p,*q;
	head=load();p=head;q=p->next;
	while(p!=NULL)
	{
		q=p->next;
		while(q!=NULL)
		{
			if(q->num<p->num)
			{
				data_exchange(p,q);
			}
			q=q->next;
		}
		p=p->next;
	}
	show(head);
}
void shebei_sort_numdown()
{
	struct shebei*head,*p,*q;
	head=load();p=head;q=p->next;
	while(p!=NULL)
	{
		q=p->next;
		while(q!=NULL)
		{
			if(q->num>p->num)
			{
				data_exchange(p,q);
			}
			q=q->next;
		}
		p=p->next;
	}
	show(head);
}
void shebei_sort_nameup()
{
	struct shebei*head,*p,*q;
	head=load();p=head;q=p->next;
	while(p!=NULL)
	{
		q=p->next;
		while(q!=NULL)
		{
			if(strcmp(q->name,p->name)<0)
			{
				data_exchange(p,q);
			}
			q=q->next;
		}
		p=p->next;
	}
	show(head);
}
void shebei_sort_namedown()
{
	struct shebei*head,*p,*q;
	head=load();p=head;q=p->next;
	while(p!=NULL)
	{
		q=p->next;
		while(q!=NULL)
		{
			if(strcmp(q->name,p->name)>0)
			{
				data_exchange(p,q);
			}
			q=q->next;
		}
		p=p->next;
	}
	show(head);
}
void shebei_sort_sysup()
{
	struct shebei*head,*p,*q;
	head=load();p=head;q=p->next;
	while(p!=NULL)
	{
		q=p->next;
		while(q!=NULL)
		{
			if(strcmp(q->sys,p->sys)<0)
			{
				data_exchange(p,q);
			}
			q=q->next;
		}
		p=p->next;
	}
	show(head);
}
void shebei_sort_sysdown()
{
	struct shebei*head,*p,*q;
	head=load();p=head;q=p->next;
	while(p!=NULL)
	{
		q=p->next;
		while(q!=NULL)
		{
			if(strcmp(q->sys,p->sys)>0)
			{
				data_exchange(p,q);
			}
			q=q->next;
		}
		p=p->next;
	}
	show(head);
}
int shebei_SORT_MENU()
{
	int a,b;
	printf("您想按哪种方式排序：\n\t1.按编号\n\t2.按名称\n\t3.按所属实验室\n\t0.退出此操作\n请输入：");
	scanf("%d",&a);
	if(a==0)	return 0;
	printf("请选择排序规则\n\t1.升序\n\t2.降序\n请输入：");
	scanf("%d",&b);
	switch(a)
	{
	case 1:
			if(b==1)	shebei_sort_numup();
		    else		shebei_sort_numdown();break;
	case 2:
			if(b==1)	shebei_sort_nameup();
		    else		shebei_sort_namedown();break;
	case 3:
			if(b==1)	shebei_sort_sysup();
		    else		shebei_sort_sysdown();break;
	}
	return 1;
}