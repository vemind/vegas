#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 60

typedef struct Customer           
{ //乘客信息
  char Name[8];                   //姓名
  int Amount;                     //定票数
  char Rank;                      //舱位等级
  int IDinfor;                    //个人信息
  struct Customer *Next;          //指向下一乘客结点
}Customer;

typedef struct Flight           
{ //航班信息
  char Des_Name[10];             //终点站名
  char Flight_No[6];             //航班号
  char Plane_No[6];              //飞机型号
  int Week_Day;                  //飞行周日
  int Customer_Amount;           //乘员定额
  int Free_Amount;               //剩余票数
  int Price[3];                  //舱位等级的价格
  Customer *CustName;            //该航班的已定票乘客名单 
  Customer *ReplName;            //该航班的候补乘客名单
  struct Flight *Next;           //指示下一航班结点
}Flight,*PFlight;

int Customer_Count=0;            //所有航班的定票乘客总数
Flight *Head=NULL;               /////航班头指针
Flight *p2;                      //航班结点指针
Customer *Custp1[MAX];           //各航班乘客结点指针
Customer *Replp1[MAX];           //各条航班候补乘客结点指针
int IsEmpty=1;                   //是否有定票乘客
int IsReplace=1;                 //是否有候补乘客
Customer *prior;                 //满足要求的定票乘客的前结点，以作删除操作
int shouldsave=0;

//询问是否继续的函数
char Continue()      
{
  char answer;
  while(1)
  {  
    printf("\n\t  您是否想继续(Y/N)?");
    scanf("%s",&answer);
    system("cls");
    if(answer=='y'||answer=='Y')
        return 'y';
    else if(answer=='n'||answer=='N')
        return 'n';
    else
          printf("\n\t输入有误，请重新输入!");
    
  }
}

//操作出错函数
void ErrorMess()
{
  printf("\n\t对不起，您的操作有误!");
  getch();
}

//系统退出函数
int ExitSystem()
{
  char answer;
  printf("\n\t 您是否想要退出系统(Y/N)?");
  scanf("%s",&answer);
  if(answer=='y'||answer=='Y')    return 1;
  else    return 0;
}
int Find_Line1(PFlight L, char *key)
{ //核对航班是否唯一
  int flag=0;          //该标志位0表示未找到相关信息，反之即找到，以下标志位同理
  Flight *p1;
  p1=L;                //赋航班首地址
  if(p1==p2) return flag;     //首航班不作比较
  while(p1!=p2 && p1!=NULL)   //本航班号不纳入比较范围，否则会提示航班不唯一
  {
    if(strcmp(p1->Flight_No,key)==0)
    {
        flag=1;  break;
    }
    p1=p1->Next;/*指向下一航班结点*/
  }
    return flag;
}

//3-2. 航班查找函数
int Find_Line2(PFlight L, char *key, PFlight *p2, int *Flight_No)
{
  int flag=0;   //该标志位0表示未找到相关信息，反之即找到
  Flight *p1;
  p1=L;         //赋航班首结点
  while(p1!=NULL)   
  {
    if(strcmp(p1->Flight_No,key)==0)  //不包括当前航班
    {
        flag=1;
        *p2=p1;
        break;
    }
    p1=p1->Next;                      //指向下一航班结点
    if(p1!=NULL)  Flight_No++;        //遇结束符不作统计范围  
  }
  return flag;
}
//4.按目的地查询航班函数
void Line_search()
{
  char Desname[50];   ////查询终点站航班关键字
  Flight *p1;
  p1=Head;	
  if(Head==NULL)
  {
     printf("\n\t没有到达您想要的终点站的航班!");
	 getch();
     return;
  }
 
  printf("\n\t请输入终点站名:");
  scanf("%s",Desname);
  printf("\n\t您所查询的航班的信息:\n");
  printf("\n______________________________________________________________\n");
  while(p1!=NULL)
  {
	  if(strcmp(p1->Des_Name,Desname)==0)
	  {
        printf("Des_Name Flight_No Plane_No Week_Day Cust_Num Free_Num 1_Price 2_Price 3_Price\n");   
        printf("\n%-9s%-10s%-9s%-9d%-9d%-9d%-8d%-8d%-8d",p1->Des_Name,p1->Flight_No,p1->Plane_No,p1->Week_Day,
	             p1->Customer_Amount,p1->Free_Amount,p1->Price[0],p1->Price[1],p1->Price[2]);            
	  }
      p1=p1->Next;
  }	
  printf("\n______________________________________________________________\n");
  Continue();
}	
//5.添加新航班函数
void Line_Add()
{
  PFlight *p1,p;   ////建立临时航班结点
  p1=&Head;      ////传航班链表头指针的地址
  while(1)
  {
    if(Head==NULL) //航班为空*/
    {
        *p1=(PFlight)malloc(sizeof(Flight));
		(*p1)->Next=NULL;
		 p2=Head;   ////建立首个航班*/
	}
    else
	{
		 p1=&p;  ////p1指向新的地址空间，以保持头指针　Head 的值不变！！！
        *p1=(PFlight)malloc(sizeof(Flight));   ////建立新航班结点
         p2->Next=*p1;   ////前一航班结点指向当前航班结点*/
         p2=*p1;         ////保留当前航班结点地址  
    }
	printf("\n\t添加新的航班!\n");
    printf("\n\t请输入终点站名:");
        scanf("%s",&(p2->Des_Name));   
    while(1)         
    { //数据合法性检验
        printf("\n\t请输入唯一的航班号:");
           scanf("%s",&(p2->Flight_No));
        if (Find_Line1(Head, p2->Flight_No))   ////存在航班号
               printf("\n\t航班号已经存在!\n");
        else   break;
    }
    printf("\n\t请输入飞机型号:");
       scanf("%s",&(p2->Plane_No));
    while(1)
    {   
        printf("\n\t请输入航班日期（请输入1—7）:");
        scanf("%d",&(p2->Week_Day)); 
        if(p2->Week_Day<1 || p2->Week_Day>7) 
              printf("\n\t输入日期有误，请重新输入!\n");
        else  break;
    }
    printf("\n\t请输入座位数量:");
       scanf("%d",&p2->Customer_Amount);
    printf("\n\t请输入头等舱的价钱:");
       scanf("%d",&p2->Price[0]);
    printf("\n\t请输入二等舱的价钱:");
       scanf("%d",&p2->Price[1]);
    printf("\n\t请输入三等舱的价钱:");
       scanf("%d",&p2->Price[2]);
    p2->Free_Amount=p2->Customer_Amount;     //剩余票数与乘员定额相同
    p2->CustName=NULL;                       //该航班定票乘客头指针为空
    p2->ReplName=NULL;	                     //初始候补名单为空 
	shouldsave=1;
    if(Continue()=='n')
    {
        p2->Next=NULL;  return;               //航班的下一结点为空       
    }
  }//endwhile(1)
}//end
// 6.判航班是否为空函数
int Empty_Flight()
{
  if(Head==NULL)
  {
    system("cls");
    printf("\n\t对不起，航班不存在，按任意键返回!");
    getch();
    return 1;
  }
  else
    return 0;
}

//7.航班查看函数
int Line_See()
{
  Flight *p1;
  system("cls");
  p1=Head;
  if(Empty_Flight()) return 0;    ////航班为空
  printf("\n\n\t航班信息:\n");
  printf("\n_________________________________________________________________\n");
  printf("Des_Name Flight_No Plane_No Week_Day Cust_Num Free_Num 1_Price 2_Price 3_Price\n");
  while(p1!=NULL)
  {
	printf("\n%-9s%-10s%-9s%-9d%-9d%-9d%-8d%-8d%-8d",p1->Des_Name,p1->Flight_No,
p1->Plane_No,p1->Week_Day,
	p1->Customer_Amount,p1->Free_Amount,p1->Price[0],p1->Price[1],p1->Price[2]);
    p1=p1->Next; 
      }
  printf("\n___________________________________________________________________\n"); 
  printf("\n\t按任意键返回!\n");
  getch();
  return 1;
}
void LinemanageMenu()
  {
    char c;
    system("cls");
	while(1)
	{
	   printf("\n\t\t航班管理菜单:");
	   printf("\n________________________________________________________________\n\n");
	   printf("\t1.添加新的航班\n");
	   printf("\t2.查询航班\n");
	   printf("\t3.查看航班\n");
	   printf("\t4.返回主菜单\n");
	   printf("\n__________________________________________________________________\n");
	   printf("\t请选择您想要的服务:");
       scanf("%s",&c);
	   switch(c)
	   {
        case '1':Line_Add();break;
		case '2':Line_search();break;
        case '3':Line_See();break;
        case '4':return;
	   }
	}
        
}
//9订票办理函数
void bookingMenu()
{
  int Ticket_Count,IDinfor,i,flag=0;
  int Flight_No=0;       //记录满足条件的航班的定票结点
  Flight *p1;            //记下满足条件的航班结点地址
  Customer *c1;          //临时性定票乘员结点
  Customer *c2;          //临时性候补乘员结点
  char answer[7];        //用户输入的航班数据
  char temp;
  char c;
  int tag=0;             //候补乘客标志位
  int IsRepl=0;          //是否执行候补操作标志位
  if(Empty_Flight())     //航班为空
     return;
  while(1)
  {
    printf("\n\t现在您可以订票!");
    flag=0;              //标志位清零以重新作出判断 
    Flight_No=0;
    tag=0;
    printf("\n\t请输入航班号:");
       scanf("%s",&answer);
    if(Find_Line2(Head,answer,&p1,&Flight_No)) //调用航班查找函数，若存在则进行以下操作
    {
        while(1)                     
        {//数据合法性检验
          printf("\n\t请输入您想要订购的票的数量:");
             scanf("%d",&Ticket_Count);
          if(Ticket_Count==0)
          {
            printf("\n\t请再次输入飞机型号:\n");
            getch();
          }
          else  break;
        }
        if(p1->Free_Amount>=Ticket_Count)
        {   
          Customer_Count++;                  //定票乘客总数增1
          flag=1;                            //表明进入了订票实际操作
          IsRepl=1;                          //定票量满足，无需进入候补操作
          if(p1->CustName==NULL)             //首个定票乘客，并记录相关属性
          {   
            Custp1[Flight_No]=c1=(Customer*)malloc(sizeof(Customer));  //建立该航班的首位乘客结点
            p1->CustName=Custp1[Flight_No];
          }
          else                               //建立该航班的后续乘客结点
          {
            c1=(Customer*)malloc(sizeof(Customer)); //分配新乘客结点  
            Custp1[Flight_No]->Next=c1;
            Custp1[Flight_No]=c1;
          }
            IsEmpty=0;                                //定票成员不为空
            Custp1[Flight_No]->Amount=Ticket_Count;          //订票数
            IDinfor=p1->Customer_Amount-p1->Free_Amount+1;   //算出座位号
            Custp1[Flight_No]->IDinfor=IDinfor;              //赋座位号 
            p1->Free_Amount-=Ticket_Count;                   //减去定票数 
            printf("\n\t请输入您的姓名:");
               scanf("%s",&Custp1[Flight_No]->Name); 
            while(1)                            
            { //数据合法性检验
                printf("\n\t请输入舱位等级:");
                   scanf("%s",&Custp1[Flight_No]->Rank);
                if(!(Custp1[Flight_No]->Rank>='1'&&Custp1[Flight_No]->Rank<='3'))
                {
                  printf("\n\t输入有误，请重新输入!");
                  getch();
                }
                else    break;
            }
            printf("\n\t请输入您的ID信息:");
			   scanf("%d",&Custp1[Flight_No]->IDinfor);
            if(Ticket_Count<10)                    //为显示规整，作相应处理 
                printf("\n\t");
            else
                printf("\n\t");
			printf("\n\t恭喜您订票成功！\n");
            for(i=1; i<=Ticket_Count; i++)                   //打印座位号 
            {   
            	printf("\n\t您所预定的座位号是%d",IDinfor++);
                if(i%10==0)
                   printf("\n\t");
            }
            printf("\n");   
        }//endif(满足定票数) 
        else if(p1->Free_Amount==0)
        {
          printf("\n\t对不起，票已售完!\n");
          IsRepl=0;
        }
        else
        {
          printf("\n\t对不起，当前没有多余的票!\n");
          IsRepl=0;
        }
        if(!IsRepl) 
        {
          printf("\n\t您是否想成为候补乘客(Y/N)?");
          scanf("%s",&temp);
          if(temp=='y'||temp=='Y')    //以下为候补操作 
          {
            if(p1->ReplName==NULL)
            {
                c2=(Customer*)malloc(sizeof(Customer));  //建立该航班的首位候

//补乘客结点
				Replp1[Flight_No]=c2;                    ////保存
				p1->ReplName=Replp1[Flight_No];
            }
            else
            {
                c2=(Customer*)malloc(sizeof(Customer)); ////新客户
                Replp1[Flight_No]->Next=c2;
                Replp1[Flight_No]=c2;
            }
            IsReplace=0;                                  //候补乘客不为空
            tag=1;                                  //已选择列入候补乘客名单
            Replp1[Flight_No]->Amount=Ticket_Count;
            printf("\n\t请输入您的姓名:");
            scanf("%s",&Replp1[Flight_No]->Name); 
            Replp1[Flight_No]->IDinfor=IDinfor;           //候补乘客的座位
            Replp1[Flight_No]->Amount=Ticket_Count;       //候补乘客的订票数
            while(1)                           
            { //数据合法性检验
                printf("\n\t请输入舱位等级:");
                   scanf("%s",&Replp1[Flight_No]->Rank);
                printf("\n\t请输入您的ID信息:");
                   scanf("%d",&Replp1[Flight_No]->IDinfor);
                if(!(Replp1[Flight_No]->Rank>='1'&&Replp1[Flight_No]->Rank<='3'))
                {
                  printf("\n\t输入有误，请重新输入.");
                  getch();
                }
                else  break;
            }
            printf("\n\t没有剩余座位!\n");                //候补乘客无座提示
			shouldsave=1;
          }//end if(进入候补名单)		  
        }//end if(票数满足)
    }//end if(航班存在)
    else
        printf("\n\t对不起，航班不存在!\n");               //航班不存在
    if(flag)                                 //此处不作处理，则会地址溢出
        Custp1[Flight_No]->Next=NULL;             //末位定票乘客的指针置空
    if(tag)
    {
        Replp1[Flight_No]->Next=NULL;          //末位候补乘客的指针置空
        printf("\n\t您已经成功排入候补订票队列中!\n");
    }
   printf("\n\t是否退出菜单？:(y/n)");
   scanf("%s",&c);
   if(c=='y')  return; 
  }//endwhile(1)
}//end   
//10订票乘客信息
void Display_Reserve()
{
  Flight *p1;    ////
  Customer *c1;  ////
  system("cls");
  p1=Head;
  if(Empty_Flight())    return;
  printf("\n\t订票乘客信息");
  if(IsEmpty)
  {
    printf("\n\t对不起，没有订票乘客信息!\n");
    getch();
    return;
  }
 printf("\n___________________________________________________________________\n"); 
 printf("Name    Flight_No Plane_No Tic_Amount Des_Name Rank_No  ID\n");
  while(p1!=NULL)
  {
    if(p1->CustName!=NULL)
    {
        c1=p1->CustName;
        while(c1!=NULL)
        {
          printf("\n%-8s%-10s%-9s%-11d%-9s%-9c%-9d",c1->Name,p1->Flight_No,p1->Plane_No,
c1->Amount,p1->Des_Name,c1->Rank,c1->IDinfor);          
          if(p1->Free_Amount>=1)
                printf("\n\n\t还有多余的票!\n");
          else
                printf("\n\n\t票已售完!\n"); 
          c1=c1->Next; 
         
        }
    }
    p1=p1->Next;
    printf("\n\n___________________________________________________________\n");
  }//endwhile   
  printf("\n\t按任意键返回!");
  getch();
  return;
}//end

//11.候补乘客信息
void Display_Replace()
{
  Flight *p1;
  Customer *c1;
  system("cls");
  p1=Head;
  if(Empty_Flight())    return;
  printf("\n\t候补乘客信息!");
  if(IsReplace)
  {
    printf("\n\t对不起，没有候补乘客!\n");
    getch();
    return;
  }
  printf("\n___________________________________________________________________\n"); 
  printf("Name Flight_No Plane_No Tic_Amount Des_Name Rank_No    ID\n");
  while(p1!=NULL)
  {
    if(p1->ReplName!=NULL)
    {
        c1=p1->ReplName;
        while(c1!=NULL)
        {
          printf("\n%-8s%-10s%-9s%-11d%-9s%-9c%-9d",c1->Name,p1->Flight_No,p1->Plane_No,
c1->Amount,p1->Des_Name,c1->Rank,c1->IDinfor);
          if( p1->Free_Amount>=1)
            printf("\n\t还有多余的票!\n");
          else
            printf("\n\t票已售完!\n"); 
          c1=c1->Next; 
        }
    }
    p1=p1->Next; 
  }//endwhile   
  printf("\n\n_________________________________________________________________\n"); 
  printf("\n\t按任意键返回!");
  getch();
  return;
}//end

//12.退票办理函数
void RefundticketMenu()
{
  int Flight_No=0,flag=0;             //记录满足条件的航班的定票结点 
  Flight *p1;                         //记下满足条件的航班结点地址 
  Customer *c2,*c4;                   //临时性定票乘员结点 
  Customer *c3,*c5;                   //临时性候补乘员结点 
  char answer[7],name[7];             //用户输入的航班数据 
  int tag=0;             //若第二乘客满足条件，则它的首地址会发生冲突，注意此处 
  int IDinfor;           //记录座位号 
  if(Empty_Flight())     //航班为空 
    return;
  printf("\n\t现在开始进行退票手续");
  if(IsEmpty)
  {
    printf("\n\t对不起，乘客不存在!");
    getch();
    return;
  }
  while(1)
  {
    flag=0;
    tag=0;
    Flight_No=0;
    printf("\n\t请输入航班号:");
    scanf("%s",&answer);
    if(Find_Line2(Head, answer, &p1, &Flight_No))   ////航班存在 
    {
        c2=p1->CustName;                            //指向该航班乘客名单的首地址
        printf("\n\t请输入您的姓名:");
        scanf("%s",&name);
        if(c2==NULL)                                //该航班无定票乘客 
        {
          printf("\n\t对不起，乘客不存在!.");
          if(Continue()=='n')  return;              //是否继续操作            
        }
        else     
          while(c2!=NULL)                           //查找有无此乘客名 
          {
            if(strcmp(c2->Name,name)==0)     //此外括号不能省略，否则功能会转变 
            {
                if(c2==p1->CustName)                //若为首位乘客满足  
                {
                  prior=p1->CustName;               //记录指针 
                  IDinfor=c2->IDinfor;
                  flag=1;
                  break;
                }
            }
            else if(c2->Next!=NULL)                 //记录满足航班的的前结点地址 
            {
                if(strcmp(c2->Next->Name,name)==0)
                {
                  tag=1;                            //特别注意此处
                  prior=c2;               //记录满足定乘客的前一地址，以作删除操作
                  IDinfor=c2->Next->IDinfor;
                  flag=1;
                  break;
                }
            }
            c2=c2->Next;                            //指向下一乘客结点 
			shouldsave=1;
          }//endwhile 
          if(!flag)
             printf("\n\t对不起，乘客不存在!\n");
    }//if(存在该航班)
    else
        printf("\n\t对不起，航班不存在!\n");
    if(flag)
    {
        if(prior==p1->CustName&&!tag)   //首结点满足条件且一个乘客，则该航班定票乘客置空
        {
          if(prior->Next==NULL)         //仅一乘客，头指针置空 
          {
            p1->Free_Amount+=prior->Amount;
            p1->CustName=NULL;
          }
          else   
          {
            p1->Free_Amount+=prior->Next->Amount;
            p1->CustName=prior->Next;               //指向下一乘客结点 
          }
        }
        else
        {
          p1->Free_Amount+=prior->Next->Amount;
          prior->Next=prior->Next->Next;            //删除操作 
        }
        Customer_Count--;
        if(Customer_Count==0)  IsEmpty=1;          
		shouldsave=1;
    }//endif
    if(flag) 
    { //存在退票操作
        c3=p1->ReplName; 
        while(c3!=NULL)
        {
           if(c3->Amount<=p1->Free_Amount) //候补乘客的定票数小于或等于剩余票数 
		   {          
             printf("\n\t候补乘客已经存在!\n");
             c4=(Customer*)malloc(sizeof(Customer));
			 Custp1[Flight_No]->Next=c4;
             //c4=Custp1[Flight_No]->Next=(Customer*)malloc(sizeof(Customer)); 

//分配新结点
             c4->Next=NULL;
             IsEmpty=0;
             if(p1->CustName==NULL)  p1->CustName=c4;              
             strcpy(c4->Name,c3->Name);
             c4->Rank=c3->Rank;
             c4->Amount=c3->Amount;
             c4->IDinfor=IDinfor;
             p1->Free_Amount-=c3->Amount;               //减去相应的票数
             Customer_Count++;
             if(c3->Next==NULL)  IsReplace=1;           //无候补乘客            

 
             if(p1->ReplName==c3)
			 {
                if(p1->ReplName->Next==NULL)  p1->ReplName=NULL;  //删除
                else   p1->ReplName=c3->Next; 
			 }
             else   c5->Next=c3->Next->Next;
             break;   
		   }//endif
           if(c3->Next!=NULL) 
              if(c3->Next->Amount<=p1->Free_Amount)
                c5=c3;
              c3=c3->Next;                      //指向下一候补乘客结点 
		      shouldsave=1;
		}//endwhile
        printf("\n\t退票成功！");
        getch();
        return;
    }//endif(存在此乘客)
	shouldsave=1;
    if(Continue()=='n')  return;
  }//endwhile(1)
}//end
//13.乘客管理子菜单函数
void CustomermagMenu()
{
  char c;
  system("cls");
  while(1)
  {
     printf("\n\t\t乘客管理菜单:\n");
     printf("\n____________________________________________________________\n\n"); 
     printf("\t1.乘客信息\n");
     printf("\t2.候补乘客信息\n");
     printf("\t3.返回主菜单\n");
     printf("\n______________________________________________________________\n");
     printf("\t请选择您想要的服务:");
     scanf("%s",&c);
     switch(c)
     {
        case'1':    Display_Reserve();break;
        case'2':    Display_Replace();break;
        case'3':    return;
        default:    ErrorMess();
     }
  }
}
int main()
{
  Flight *p1;
  char c;
  p1=Head;
  system("color 1f");                            //屏幕颜色设定
  system("mode con: cols=78 lines=35"); 
  do{
       system("cls");
       printf("\n\t\t             航空客运订票系统主菜单\n"); 
       printf("\n****************************************************************\n"); 
       printf("\t                 1.航 班 管 理 菜 单\n");
       printf("\t                 2.订 票 办 理 菜 单\n");
       printf("\t                 3.退 票 办 理 菜 单\n");
       printf("\t                 4.乘 客 管 理 菜 单\n");
       printf("\t                 5.退 出 系 统\n");
       printf("\n*****************谢谢使用航空客运订票系统！*********************\n");
       printf("请选择您想要的服务:");
         scanf("%s",&c);
         switch(c)
		 {
            case '1':  LinemanageMenu();break;           //航班管理 
            case '2':  bookingMenu();break;              //订票办理 
            case '3':  RefundticketMenu();break;         //退票办理
            case '4':  CustomermagMenu();break;          //乘客管理
            case '5':  exit(0);    
            default:   break;
		 }
  }while(c!='5');
}
