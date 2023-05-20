#include<iostream>  
#include<string>
#include<windows.h> 
#include<fstream>
#include<stdio.h>
#include<iomanip>
#include"booksystem.h"
using namespace std; 
/*    */
#define long 10//取图书数据最长数据长度+1 
class book//图书类 
{
private:
	
	string id;//编号 
	string name;//图书名字 
	string  writer;//作者 
	string home;//出版社 
	double  money;//金额    
	string  type;//类别 
	int  sl;//库存 
public:
	
	book *next;//构建链表 
	friend ostream & operator <<(ostream& out,book &b);//重载输出 
	friend istream & operator >>(istream& in,book &b);//重载输入 
	string getid(){return id;}
	string getname(){return name;}
	string getwriter(){return writer;}
	string gethome(){return home;}
	double getmoney(){
		if(money>30&&money<100)
			return (money-30)*30;
		else if(money>=100)return money+30;
		else return money;}
	void zengjiatime(){
		if(money<30)money=money+1;
	}
	string gettype(){return type;}
	int getsl(){return sl;}
	void inid(){cin>>id;}
	void inname(){cin>>name;}
	void inwriter(){cin>>writer;}
	void inhome(){cin>>home;}
	void inmoney(){cin>>money ;}
	void intype(){cin>>type;}
	void insl(){cin>>sl;}
	void swapbook(book *p1);//图书信息交换 
}; 

ostream & operator <<(ostream& out,book &b)
{
	
	
	out<<setw(long)<<setiosflags(ios::left)<<b.getid()<<"\t\t";
	out<<setw(long)<<setiosflags(ios::left)<<b.getname()<<"\t\t";
	out<<setw(long)<<setiosflags(ios::left)<<b.getwriter()<<"\t\t";
	out<<setw(long)<<setiosflags(ios::left)<<b.gethome()<<"\t\t";
	out<<setw(long)<<setiosflags(ios::left)<<b.getmoney()<<"\t\t";
	out<<setw(long)<<setiosflags(ios::left)<<b.gettype()<<"\t\t";
	out<<setw(long)<<setiosflags(ios::left)<<b.getsl()<<endl;
	return out;
}
istream & operator >>(istream& in,book &b)
{
	
	in>>b.id>>b.name>>b.writer>>b.home>>b.money>>b.type>>b.sl;
	return in;
}
class System//系统 
{
protected:
	void addbook(book **p);//添加图书 
	void showbook(book *p);//展示图书 
	void xiugaibook(book *p);//修改图书 
	void savefile(book *p);//把图书信息存入文件 
	void findbook(book *p);//查找图书并显示信息 
	void shanchubook(book **p);//删除图书 
	int chongfuid(book p); //图书重复id检测 
	int type(book p);//图书类别命名检测 
	void typebook(book *p);//图书分类展示 
	void menu();//系统菜单 
	void weihumenu();//子菜单 
	int duqufile(book **p);//从文件读取图书信息 
	void typesave(book *p);//把图书根据类保存到新的文件
	void paixu(book *p); //排序图书 
	
private:
	book *book1;//图书链表头部 
	book *tbook;//tbook为锁定图书链表尾部位置
public:
	System()//构造系统时生成图书链表并展示菜单 
	{
		book1=NULL;
		duqufile(&book1);
		menu();
	}
	
	
};

void System::menu()//主菜单 
{   
    	SetColor(10,0);
	cout<<"=======================================================" <<endl;
	cout<<"\t"<<"欢迎进入图书库存管理系统"<<endl;
		SetColor(14,0);
	cout<<"\t1.系统维护"<<endl;
		SetColor(7,0);
	cout<<"\t2.查找图书"<<endl;
		SetColor(14,0);
	cout<<"\t3.展示全部图书"<<endl;
		SetColor(7,0);
	cout<<"\t4.分类展示图书"<<endl;
		SetColor(14,0);
	cout<<"\t5.图书类别提取"<<endl;
		SetColor(7,0);
	cout<<"\t6.保存数据并退出系统"<<endl;
	cout<<endl;
		SetColor(10,0);
	cout<<"注：《罚金/借书时间》小于30为借书天数/大于为罚金"<<endl; 
	cout<<"=======================================================" <<endl;
	cout<<"请输入你的操作命令:"; 
	char n;//若定义为int类型，输入符号或汉字会刷屏，缺点是不能接受两位以上的字符 
	cin>>n;  
	while(n<'1'||n>'6')
	{cout<<"输入错误，请重新输入"<<endl;
		cout<<"请输入你的操作命令:";
		cin>>n;
	}
	switch (n)//根据指令选择功能函数 
	{
		case '1':weihumenu();break;
		case '2':findbook(book1);break;
		
		
		case '3':showbook(book1);break;
		case '4':typebook(book1);break;
		case '6':savefile(book1);
		cout<<"正在保存数据退出"<<endl;
		Sleep(300);
		exit(0); 
		case '5':typesave(book1);break;		
		
	}
	
	
}
void System::weihumenu()//子菜单 
{
	system("cls");
	SetColor(10,0);
	cout<<"========================================================================================================================" <<endl;
	cout<<"\t\t\t\t\n"<<"                                                 系统维护"<<endl;
	SetColor(14,0);
	printf("\t1.增加图书\n");
	SetColor(7,0);
    printf("\t2.修改图书\n");
	SetColor(14,0);
	printf("\t3.删除图书\n");
	SetColor(7,0);
	printf("\t4.排序图书\n");
	SetColor(14,0);
	cout<<"\t5.返回上一级"<<endl;
	SetColor(10,0);
	cout<<"======================================================================================================================== " <<endl;
	cout<<"请输入你的操作命令:"; 
	char n;//若定义为int类型，输入符号或汉字会刷屏，缺点是不能接受两位以上的字符 
	cin>>n;
	while(n<'1'||n>'5')
	{
		cout<<"输入错误，请重新输入"<<endl;
		cout<<"请输入你的操作命令:";
		cin>>n;
	}
	switch (n)//根据指令选择功能函数 
	{
		case '1':addbook(&book1);break;
		case '2':xiugaibook(book1);break;
		case '3':shanchubook(&book1);break;
		case '4':paixu(book1);break;
		case '5':cout<<"正在返回"<<endl; 
		Sleep(3000);
		system("cls");
		menu(); 
		exit(0);
	}
}
void System::addbook( book **p)//用链表的方式添加图书 
{
	char n;
	cout<<"请输入图书信息（类别只能为文学，教育，管理，生活，艺术）："<<endl; 
	book *temp;
	temp=new book;
	cout<<"编号\t\t\t书名\t\t\t作者\t\t\t出版社\t\t\t罚金/借书时间\t\t\t类别\t\t\t库存量"<<endl;  
	cin>>(*temp);
	if(chongfuid(*temp))//检测添加的图书编号是否冲突 
	{
		cout<<"输入图书编号重复"<<endl;
		cout<<"正在返回"<<endl; 
		
		Sleep(3000);
		system("cls");
		weihumenu(); 
		exit(0);
	}
	if(type(*temp))//检测添加的图书类别是否符合 
	{
		cout<<"输入图书类别有误(文学，教育，管理，生活，艺术)"<<endl;
		cout<<"正在返回"<<endl; 
		
		Sleep(3000);
		system("cls");
		weihumenu();
		exit(0); 
	}
	
	if(*p==NULL)//检测链表是否为空链表 
	{
		temp->next=NULL;
		*p=temp;
	}
	else
	{
		temp->next=NULL;
		(tbook)->next=temp;
	}
	tbook=temp;//锁定链表尾部 
	cout<<"录入成功，是否继续添加？（y或n):"; 
	cin>>n;
	while(n!='n'&&n!='y')
	{
		cout<<"输入错误，请重新输入（y或n)："<<endl;
		cin>>n;
	}
	if(n=='y')
	{
		addbook(&book1);
		exit(0);
	}
	else{
		cout<<"正在返回......"<<endl;
		Sleep(3000);
		system("cls");
		weihumenu();
		exit(0); }
}
void System::showbook(book *p)//展示图书列表 
{
	book *t1=p;
	int n=0,i=0;//n控制换行，i计数 
	cout<<"编号\t\t\t书名\t\t\t作者\t\t\t出版社\t\t\t罚金/借书时间\t\t\t类别\t\t\t库存量"<<endl; 
	while(t1!=NULL)
	{
		cout<<*t1<<endl;
		n++;
		i++;
		if(n>9)
		{
			cout<<endl<<endl;
			n-=10;
		}
		t1=t1->next;
	}
	cout<<"一共有"<<i<<"本图书"<<endl;
	
	system("pause"); 
	cout<<"正在返回"<<endl; 
	
	Sleep(3000);
	system("cls");
	menu(); 
	exit(0);
} 
void System::xiugaibook(book *p)//修改图书信息 
{
	string s;
	char n;
	book *t,temp;
	t=p;
	cout<<"请输入待修改的图书编号(输入“cancel”取消):";
	cin>>s;
	if(s=="cancel"){system("cls");weihumenu();exit(0);}//返回菜单 
	while(t!=NULL)//查找图书 
	{
		if(t->getid()==s)break;
		else{t=t->next;}
	}
	if(t==NULL)
	{
		cout<<"查询不到该图书"<<endl<<"正在返回"<<endl;
		Sleep(3000);
		xiugaibook(p);
		exit(0);
	}
	else
	{
		system("cls");
		temp=*t;
			SetColor(10,0);
		cout<<"目前该图书信息为"<<endl;
		cout<<"编号\t\t\t书名\t\t\t作者\t\t\t出版社\t\t\t罚金/借书时间\t\t\t类别\t\t\t库存量"<<endl; 
		cout<<*t<<endl;
		cout<<"===================================================="<<endl; 
			SetColor(14,0);
		cout<<"1.编号"<<endl;
			SetColor(7,0);
		cout<<"2.书名"<<endl;
			SetColor(14,0);
		cout<<"3.作者"<<endl;
			SetColor(7,0);
		cout<<"4.出版社"<<endl;
			SetColor(14,0);
		cout<<"5.罚金/借出天数"<<endl;
			SetColor(7,0);
		cout<<"6.类别"<<endl;
			SetColor(14,0);
		cout<<"7.库存量"<<endl;
			SetColor(7,0);
		cout<<"8.返回上一级"<<endl;
			SetColor(10,0);
		cout<<"请选择要修改的图书数据：";
		cin>>n;
		
		while(n<'1'||n>'8')
		{
			cout<<"输入错误，请重新输入"<<endl;
			cout<<"请选择要修改的图书数据：";
			cin>>n;
			
		}
		if(n=='8')
		{
			cout<<"正在返回"<<endl; 
			Sleep(3000);
			xiugaibook(p);
			exit(0);
			
		}
		cout<<"输入修改后的数据（类别只能为文学，教育，管理，生活，艺术）："<<endl; 
		
		switch (n)//temp为临时变量，因为编号和类别需要二次判断 
		{
			case '1':temp.inid();break;
			case '2':t->inname();break;
			case '3':t->inwriter();break;
			case '4':t->inhome();break;
			case '5':t->inmoney();break;
			case '6':temp.intype();break;
			case '7':t->insl();break;
			
		}
		if(n=='1')//重复id检测 
		{
			
			if(chongfuid(temp))
			{
				
				cout<<"输入图书编号重复,";
				
				xiugaibook(p);
				exit(0);
			} 
			else
			{
				*t=temp;
			}
		}
		if(n=='6')//检测类别是否正确 
		{
			if(type(temp))
			{
				cout<<"输入图书类别有误（文学，教育，管理，生活，艺术)"<<endl;
				xiugaibook(p);
				exit(0);
			}
			else
			{
				*t=temp;
			}
		}
		cout<<"目前该图书信息为"<<endl;
		cout<<"编号\t\t\t书名\t\t\t作者\t\t\t出版社\t\t\t罚金/借书时间\t\t\t类别\t\t\t库存量"<<endl; 
		cout<<*t<<endl;
		system("pause"); 
		cout<<"正在返回"<<endl; 
		Sleep(300);
		system("cls");
		weihumenu();
		exit(0);
	}
	
	
};
int System::duqufile(book **p)//从文件读取数据，返回值只为了中断函数 
{
	int i=0;
	
	ifstream infile("file.txt",ios::in);
	if(!infile)
	{
		cout<<"图书文件不存在，正在创建。。。。"<<endl;//文件不存在 
		Sleep(3000);
		system("cls");
		return 0;
		
	} 
	while(!infile.eof())
	{
		
		book *temp;
		temp=new book;
		
		infile>>(*temp);
		if(infile.eof()){break;}//提取到结尾跳出 
		i++;
		
		if(*p==NULL)
		{
			temp->next=NULL;
			*p=temp;
		}
		else
		{
			temp->next=NULL;
			tbook->next=temp;
		}
		tbook=temp;
		
		
	}
	if(i==0){
		cout<<"当前图书列表为空。。。。"<<endl;
		Sleep(3000);
		system("cls");
	}
	else{
		cout<<"正在读取数据。。。。。"<<endl;
		Sleep(3000);
		system("cls");
	} 
	infile.close();
	return 1;
	
} 
void System::savefile(book *p)//把链表数据存入文件 
{
	book *t=p,*temp;
	p->zengjiatime();
	fstream outfile("file.txt",ios::out);
	if(!outfile)
	{
		cout<<"文件保存失败"<<endl;
		exit(0);
	}
	
	while(t!=NULL)
	{
		outfile<<*t;
		temp=t;
		t=t->next;
		delete temp;//释放链表空间 
		
	}
	outfile.close();
	
}
void System::findbook(book *p)//查找图书 
{
	char n;
	cout<<"请选择搜索方式(1.编号\t2.书名):"<<endl;
	cin>>n;
	while(n!='1'&&n!='2')
	{
		cout<<"输入错误，请重新输入"<<endl;
		cout<<"请选择搜索方式(1.编号\t2.书名):"<<endl;
		cin>>n;
	}
	if(n=='1')
	{
		string s;
		
		book *t;
		t=p;
		cout<<"请输入待查找的图书编号(输入“cancel”取消):";
		cin>>s;
		if(s=="cancel"){system("cls");menu();exit(0);}
		while(t!=NULL)
		{
			if(t->getid()==s)break;
			else{t=t->next;}
		}
		if(t==NULL){
			cout<<"查询不到该图书"<<endl<<"正在返回"<<endl;
			Sleep(3000);
			findbook(p);
			exit(0);
			
		}
		else
		{
			cout<<"目前该图书信息为"<<endl;
			cout<<"编号\t\t\t书名\t\t\t作者\t\t\t出版社\t\t\t罚金/借书时间\t\t\t类别\t\t\t库存量"<<endl; 
			cout<<*t<<endl;
			system("pause"); 
			system("cls");
			menu();
			exit(0);
		}	
	}
	else 
	{
		string s;
		book *t;
		t=p;
		int i=0;
		cout<<"请输入待修改的图书名字(输入“cancel”取消):";
		cin>>s;
		if(s=="cancel"){system("cls");menu();exit(0);}
		cout<<"编号\t\t\t书名\t\t\t作者\t\t\t出版社\t\t\t罚金/借书时间\t\t\t类别\t\t\t库存量"<<endl; 
		while(t!=NULL)
		{
			if(t->getname()==s)
			{
				cout<<*t;
				t=t->next;
				i++;
			} 
			else{t=t->next;}
		}
		if(t==NULL&&i==0){
			cout<<"查询不到该图书"<<endl<<"正在返回"<<endl;
			Sleep(3000);
			findbook(p);
			exit(0);
			
		}
		else
		{
			
			system("pause"); 
			system("cls");
			menu();
			exit(0);
		}	
	}
	
	
	
	
	
}
void System::shanchubook(book **p)//删除函数 
{
	string s;
	book *t,*t1;
	t=*p;
	char n;
	cout<<"请输入待删除的图书编号(输入“cancel”取消):";
	cin>>s;
	if(s=="cancel"){system("cls");weihumenu();exit(0);}
	if(t->getid()==s)//先排除图书在链表头的情况 
	{
		cout<<"该图书信息为："<<endl;
		cout<<"编号\t\t\t书名\t\t\t作者\t\t\t出版社\t\t\t罚金/借书时间\t\t\t类别\t\t\t库存量"<<endl; 
		cout<<*t;
		cout<<"删除后不可恢复，是否删除？（y或n):";
		cin>>n;
		while(n!='n'&&n!='y')
		{
			cout<<"输入错误，请重新输入（n或y)："<<endl;
			cin>>n;
		}	
		if(n=='y')
		{
			(*p)=(*p)->next;// 移动链表头至下一个位置 
			delete t;//释放链表首地址 
			cout<<"删除成功，正在返回"<<endl; 
			Sleep(3000);
			system("cls");
			weihumenu();
			exit(0);
		}		
		else{
			cout<<"正在返回......"<<endl;
			Sleep(3000);
			system("cls");
			weihumenu();
			exit(0); }
		
	}
	while(t!=NULL)
	{
		if(t->getid()==s)break;
		
		else{
			t1=t;//锁定目标图书的下一地址 
			t=t->next;}
	}
	if(t==NULL)
	{
		cout<<"查询不到该图书"<<endl<<"正在返回"<<endl;
		Sleep(3000);
		shanchubook(p);
		exit(0);
	}
	else
	{
		cout<<"该图书信息为："<<endl;
		cout<<"编号\t\t\t书名\t\t\t作者\t\t\t出版社\t\t\t罚金/借书时间\t\t\t类别\t\t\t库存量"<<endl; 
		cout<<*t;
		cout<<"删除后不可恢复，是否删除？（y或n):";
		cin>>n;
		while(n!='n'&&n!='y')
		{
			cout<<"输入错误，请重新输入（'n或'y)："<<endl;
			cin>>n;
		}	
		if(n=='y')
		{
			t1->next=t->next;//把目标图书地址截取出来 
			delete t;
			cout<<"删除成功，正在返回"<<endl; 
			Sleep(3000);
			system("cls");
			weihumenu();
			exit(0);
		}		
		else{
			cout<<"正在返回......"<<endl;
			Sleep(3000);
			system("cls");
			weihumenu();
			exit(0); }
		
		
	}
	
}
int System::chongfuid(book p)//图书重复id检测 
{
	
	book *t=book1;
	while(t!=NULL)
	{
		if(t->getid()==p.getid())break;
		else{t=t->next;}
	}
	if(t==NULL){
		return 0;//无重复返回0 
		
	}
	else
	{
		return 1;//有重复返回1 
	}
	
}
int System::type(book p)//类别检测 
{
	if(p.gettype()=="文学"||p.gettype()=="教育"||p.gettype()=="管理"||p.gettype()=="生活"||p.gettype()=="艺术") 
	{
		return 0;//符合返回0 
	}
	else return 1;
}
void System::typebook(book *p)//类别打印 
{
	char t;
	book *t1=p;
	string s;
	int i=0,n=0;
	cout<<"请输入要查看的图书类别"<<endl;
	cout<<"1.文学"<<endl;
	cout<<"2.教育"<<endl;
	cout<<"3.管理"<<endl;
	cout<<"4.生活"<<endl;
	cout<<"5.艺术"<<endl;
	cout<<"6.返回上一级"<<endl; 
	cin>>t;
	while(t<'1'||t>'6')
	{
		cout<<"输入错误，请重新输入"<<endl;
		cout<<"请选择要查看的图书类别";
		cin>>t;
		
	}
	if(t=='6')
	{
		cout<<"正在返回......"<<endl; 
		Sleep(3000);
		system("cls");
		menu(); 
		exit(0);
	} 
	switch (t)
	{
		case '1':s="文学";break;
		case '2':s="教育";break;
		case '3':s="管理";break;
		case '4':s="生活";break;
		case '5':s="艺术";break;
	}
	cout<<"编号\t\t\t书名\t\t\t作者\t\t\t出版社\t\t\t罚金/借书时间\t\t\t类别\t\t\t库存量"<<endl; 
	while(t1!=NULL)
	{
		if(t1->gettype()==s)
		{
			cout<<*t1<<endl;
			i++;
			n++;
		}
		t1=t1->next;
		if(n>9)
		{
			system("pause");
			
			n-=10;
		}
	}
	cout<<s<<"类的图书总共有"<<i<<"本"<<endl;
	system("pause"); 
	cout<<"正在返回"<<endl; 
	
	Sleep(3000);
	system("cls");
	menu(); 
	exit(0);
}

void System::typesave(book *p)//按类保存 
{
	char t;
	book *t1=p;
	string s;
	int i=0;
	cout<<"请输入要提取的图书类别(多次提取仅保留最后一次保存的数据)"<<endl;
	cout<<"1.文学"<<endl;
	cout<<"2.教育"<<endl;
	cout<<"3.管理"<<endl;
	cout<<"4.生活"<<endl;
	cout<<"5.艺术"<<endl;
	cout<<"6.返回上一级"<<endl; 
	cin>>t;
	while(t<'1'||t>'6')
	{
		cout<<"输入错误，请重新输入"<<endl;
		cout<<"请选择要提取的图书类别";
		cin>>t;
		
	}
	if(t=='6')
	{
		cout<<"正在返回......"<<endl; 
		Sleep(3000);
		system("cls");
		menu(); 
		exit(0);
	} 
	switch (t)
	{
		case '1':s="文学";break;
		case '2':s="教育";break;
		case '3':s="管理";break;
		case '4':s="生活";break;
		case '5':s="艺术";break;
	}
	
	
	fstream outfile("type.txt",ios::out);
	if(!outfile)
	{
		cout<<"文件保存失败"<<endl;
		exit(0);
	}
	
	
	
	
	while(t1!=NULL)
	{
		if(t1->gettype()==s)
		{
			
			outfile<<*t1;
			i++;
			
		}
		t1=t1->next;
		
	}
	outfile.close();
	cout<<"提取成功，"<<s<<"类的图书总共有"<<i<<"本"<<endl;
	system("pause"); 
	cout<<"正在返回"<<endl; 
	
	Sleep(3000);
	system("cls");
	menu(); 
	exit(0);
}
void System::paixu(book *p1)//按需排序图书 
{
	book *p=p1,*t1=p1;
	int len=0,i,j;
	char n;
	cout<<"                                           1.借书时间降序"<<endl; 
	cout<<"                                           2.借书时间升序"<<endl; 
	cout<<"                                           3.库存降序"<<endl; 
	cout<<"                                           4.库存升序"<<endl; 
	cout<<"                                           5.返回上一级"<<endl;
	cout<<"                                           请选择排序方式：";
	cin>>n;
	while(n<'1'||n>'5')
	{
		cout<<"输入错误，请重新输入"<<endl;
		cout<<"请输入你的操作命令:";
		cin>>n;
	}
	if(n=='5')
	{
		cout<<"正在返回"<<endl; 
		
		Sleep(3000);
		system("cls");
		weihumenu(); 
		exit(0);
	}
	while(t1!=NULL)
	{
		len++;
		t1=t1->next;
	}
	t1=p1;
	for (i = 0; i < len - 1; i++)//根据需求进行排序 
	{
		p=t1;
		for (j = 0; j < len -1; j++)
		{
			if(n=='2'){
				if (p->getmoney() > p->next->getmoney()) 
				{
					p->swapbook(p->next);//交换两图书的信息 
				}
			}
			
			if(n=='1'){
				if (p->getmoney() < p->next->getmoney())
				{
					p->swapbook(p->next);
				}
			}
			
			if(n=='4'){
				if (p->getsl() > p->next->getsl())
				{
					p->swapbook(p->next);
				}
			}
			
			if(n=='3'){
				if (p->getsl() < p->next->getsl())
				{
					p->swapbook(p->next);
				}
			}
			
			p = p->next;
			
		}
	}
	
	cout<<"图书排序成功"<<endl; 
	system("pause"); 
	cout<<"正在返回"<<endl; 
	
	Sleep(3000);
	system("cls");
	weihumenu(); 
	exit(0);	
}
void book::swapbook(book *p1)//信息交换 
{
	string id=this->getid();
	string name=this->getname(); 
	string  writer=this->getwriter(); 
	string home=this->gethome();
	double  money=this->getmoney();   
	string  type=this->gettype();
	int  sl=this->getsl();
	this->id=p1->getid();
	this->name=p1->getname();
	this->writer=p1->getwriter();
	this->home=p1->gethome();
	this->money=p1->getmoney();
	this->type=p1->gettype();
	this->sl=p1->getsl();
	p1->id=id;
	p1->name=name;
	p1->writer=writer;
	p1->home=home;
	p1->money=money;
	p1->type=type;
	p1->sl=sl;	
}
int main()
{
	SetTitle("图书管理系统");
	System s1; //利用构造函数进入并运行系统 
	return 0;
}
