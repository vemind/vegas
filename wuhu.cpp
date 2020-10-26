#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 60

typedef struct Customer           
{ //�˿���Ϣ
  char Name[8];                   //����
  int Amount;                     //��Ʊ��
  char Rank;                      //��λ�ȼ�
  int IDinfor;                    //������Ϣ
  struct Customer *Next;          //ָ����һ�˿ͽ��
}Customer;

typedef struct Flight           
{ //������Ϣ
  char Des_Name[10];             //�յ�վ��
  char Flight_No[6];             //�����
  char Plane_No[6];              //�ɻ��ͺ�
  int Week_Day;                  //��������
  int Customer_Amount;           //��Ա����
  int Free_Amount;               //ʣ��Ʊ��
  int Price[3];                  //��λ�ȼ��ļ۸�
  Customer *CustName;            //�ú�����Ѷ�Ʊ�˿����� 
  Customer *ReplName;            //�ú���ĺ򲹳˿�����
  struct Flight *Next;           //ָʾ��һ������
}Flight,*PFlight;

int Customer_Count=0;            //���к���Ķ�Ʊ�˿�����
Flight *Head=NULL;               /////����ͷָ��
Flight *p2;                      //������ָ��
Customer *Custp1[MAX];           //������˿ͽ��ָ��
Customer *Replp1[MAX];           //��������򲹳˿ͽ��ָ��
int IsEmpty=1;                   //�Ƿ��ж�Ʊ�˿�
int IsReplace=1;                 //�Ƿ��к򲹳˿�
Customer *prior;                 //����Ҫ��Ķ�Ʊ�˿͵�ǰ��㣬����ɾ������
int shouldsave=0;

//ѯ���Ƿ�����ĺ���
char Continue()      
{
  char answer;
  while(1)
  {  
    printf("\n\t  ���Ƿ������(Y/N)?");
    scanf("%s",&answer);
    system("cls");
    if(answer=='y'||answer=='Y')
        return 'y';
    else if(answer=='n'||answer=='N')
        return 'n';
    else
          printf("\n\t������������������!");
    
  }
}

//����������
void ErrorMess()
{
  printf("\n\t�Բ������Ĳ�������!");
  getch();
}

//ϵͳ�˳�����
int ExitSystem()
{
  char answer;
  printf("\n\t ���Ƿ���Ҫ�˳�ϵͳ(Y/N)?");
  scanf("%s",&answer);
  if(answer=='y'||answer=='Y')    return 1;
  else    return 0;
}
int Find_Line1(PFlight L, char *key)
{ //�˶Ժ����Ƿ�Ψһ
  int flag=0;          //�ñ�־λ0��ʾδ�ҵ������Ϣ����֮���ҵ������±�־λͬ��
  Flight *p1;
  p1=L;                //�������׵�ַ
  if(p1==p2) return flag;     //�׺��಻���Ƚ�
  while(p1!=p2 && p1!=NULL)   //������Ų�����ȽϷ�Χ���������ʾ���಻Ψһ
  {
    if(strcmp(p1->Flight_No,key)==0)
    {
        flag=1;  break;
    }
    p1=p1->Next;/*ָ����һ������*/
  }
    return flag;
}

//3-2. ������Һ���
int Find_Line2(PFlight L, char *key, PFlight *p2, int *Flight_No)
{
  int flag=0;   //�ñ�־λ0��ʾδ�ҵ������Ϣ����֮���ҵ�
  Flight *p1;
  p1=L;         //�������׽��
  while(p1!=NULL)   
  {
    if(strcmp(p1->Flight_No,key)==0)  //��������ǰ����
    {
        flag=1;
        *p2=p1;
        break;
    }
    p1=p1->Next;                      //ָ����һ������
    if(p1!=NULL)  Flight_No++;        //������������ͳ�Ʒ�Χ  
  }
  return flag;
}
//4.��Ŀ�ĵز�ѯ���ຯ��
void Line_search()
{
  char Desname[50];   ////��ѯ�յ�վ����ؼ���
  Flight *p1;
  p1=Head;	
  if(Head==NULL)
  {
     printf("\n\tû�е�������Ҫ���յ�վ�ĺ���!");
	 getch();
     return;
  }
 
  printf("\n\t�������յ�վ��:");
  scanf("%s",Desname);
  printf("\n\t������ѯ�ĺ������Ϣ:\n");
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
//5.����º��ຯ��
void Line_Add()
{
  PFlight *p1,p;   ////������ʱ������
  p1=&Head;      ////����������ͷָ��ĵ�ַ
  while(1)
  {
    if(Head==NULL) //����Ϊ��*/
    {
        *p1=(PFlight)malloc(sizeof(Flight));
		(*p1)->Next=NULL;
		 p2=Head;   ////�����׸�����*/
	}
    else
	{
		 p1=&p;  ////p1ָ���µĵ�ַ�ռ䣬�Ա���ͷָ�롡Head ��ֵ���䣡����
        *p1=(PFlight)malloc(sizeof(Flight));   ////�����º�����
         p2->Next=*p1;   ////ǰһ������ָ��ǰ������*/
         p2=*p1;         ////������ǰ�������ַ  
    }
	printf("\n\t����µĺ���!\n");
    printf("\n\t�������յ�վ��:");
        scanf("%s",&(p2->Des_Name));   
    while(1)         
    { //���ݺϷ��Լ���
        printf("\n\t������Ψһ�ĺ����:");
           scanf("%s",&(p2->Flight_No));
        if (Find_Line1(Head, p2->Flight_No))   ////���ں����
               printf("\n\t������Ѿ�����!\n");
        else   break;
    }
    printf("\n\t������ɻ��ͺ�:");
       scanf("%s",&(p2->Plane_No));
    while(1)
    {   
        printf("\n\t�����뺽�����ڣ�������1��7��:");
        scanf("%d",&(p2->Week_Day)); 
        if(p2->Week_Day<1 || p2->Week_Day>7) 
              printf("\n\t����������������������!\n");
        else  break;
    }
    printf("\n\t��������λ����:");
       scanf("%d",&p2->Customer_Amount);
    printf("\n\t������ͷ�Ȳյļ�Ǯ:");
       scanf("%d",&p2->Price[0]);
    printf("\n\t��������Ȳյļ�Ǯ:");
       scanf("%d",&p2->Price[1]);
    printf("\n\t���������Ȳյļ�Ǯ:");
       scanf("%d",&p2->Price[2]);
    p2->Free_Amount=p2->Customer_Amount;     //ʣ��Ʊ�����Ա������ͬ
    p2->CustName=NULL;                       //�ú��ඨƱ�˿�ͷָ��Ϊ��
    p2->ReplName=NULL;	                     //��ʼ������Ϊ�� 
	shouldsave=1;
    if(Continue()=='n')
    {
        p2->Next=NULL;  return;               //�������һ���Ϊ��       
    }
  }//endwhile(1)
}//end
// 6.�к����Ƿ�Ϊ�պ���
int Empty_Flight()
{
  if(Head==NULL)
  {
    system("cls");
    printf("\n\t�Բ��𣬺��಻���ڣ������������!");
    getch();
    return 1;
  }
  else
    return 0;
}

//7.����鿴����
int Line_See()
{
  Flight *p1;
  system("cls");
  p1=Head;
  if(Empty_Flight()) return 0;    ////����Ϊ��
  printf("\n\n\t������Ϣ:\n");
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
  printf("\n\t�����������!\n");
  getch();
  return 1;
}
void LinemanageMenu()
  {
    char c;
    system("cls");
	while(1)
	{
	   printf("\n\t\t�������˵�:");
	   printf("\n________________________________________________________________\n\n");
	   printf("\t1.����µĺ���\n");
	   printf("\t2.��ѯ����\n");
	   printf("\t3.�鿴����\n");
	   printf("\t4.�������˵�\n");
	   printf("\n__________________________________________________________________\n");
	   printf("\t��ѡ������Ҫ�ķ���:");
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
//9��Ʊ������
void bookingMenu()
{
  int Ticket_Count,IDinfor,i,flag=0;
  int Flight_No=0;       //��¼���������ĺ���Ķ�Ʊ���
  Flight *p1;            //�������������ĺ������ַ
  Customer *c1;          //��ʱ�Զ�Ʊ��Ա���
  Customer *c2;          //��ʱ�Ժ򲹳�Ա���
  char answer[7];        //�û�����ĺ�������
  char temp;
  char c;
  int tag=0;             //�򲹳˿ͱ�־λ
  int IsRepl=0;          //�Ƿ�ִ�к򲹲�����־λ
  if(Empty_Flight())     //����Ϊ��
     return;
  while(1)
  {
    printf("\n\t���������Զ�Ʊ!");
    flag=0;              //��־λ���������������ж� 
    Flight_No=0;
    tag=0;
    printf("\n\t�����뺽���:");
       scanf("%s",&answer);
    if(Find_Line2(Head,answer,&p1,&Flight_No)) //���ú�����Һ�������������������²���
    {
        while(1)                     
        {//���ݺϷ��Լ���
          printf("\n\t����������Ҫ������Ʊ������:");
             scanf("%d",&Ticket_Count);
          if(Ticket_Count==0)
          {
            printf("\n\t���ٴ�����ɻ��ͺ�:\n");
            getch();
          }
          else  break;
        }
        if(p1->Free_Amount>=Ticket_Count)
        {   
          Customer_Count++;                  //��Ʊ�˿�������1
          flag=1;                            //���������˶�Ʊʵ�ʲ���
          IsRepl=1;                          //��Ʊ�����㣬�������򲹲���
          if(p1->CustName==NULL)             //�׸���Ʊ�˿ͣ�����¼�������
          {   
            Custp1[Flight_No]=c1=(Customer*)malloc(sizeof(Customer));  //�����ú������λ�˿ͽ��
            p1->CustName=Custp1[Flight_No];
          }
          else                               //�����ú���ĺ����˿ͽ��
          {
            c1=(Customer*)malloc(sizeof(Customer)); //�����³˿ͽ��  
            Custp1[Flight_No]->Next=c1;
            Custp1[Flight_No]=c1;
          }
            IsEmpty=0;                                //��Ʊ��Ա��Ϊ��
            Custp1[Flight_No]->Amount=Ticket_Count;          //��Ʊ��
            IDinfor=p1->Customer_Amount-p1->Free_Amount+1;   //�����λ��
            Custp1[Flight_No]->IDinfor=IDinfor;              //����λ�� 
            p1->Free_Amount-=Ticket_Count;                   //��ȥ��Ʊ�� 
            printf("\n\t��������������:");
               scanf("%s",&Custp1[Flight_No]->Name); 
            while(1)                            
            { //���ݺϷ��Լ���
                printf("\n\t�������λ�ȼ�:");
                   scanf("%s",&Custp1[Flight_No]->Rank);
                if(!(Custp1[Flight_No]->Rank>='1'&&Custp1[Flight_No]->Rank<='3'))
                {
                  printf("\n\t������������������!");
                  getch();
                }
                else    break;
            }
            printf("\n\t����������ID��Ϣ:");
			   scanf("%d",&Custp1[Flight_No]->IDinfor);
            if(Ticket_Count<10)                    //Ϊ��ʾ����������Ӧ���� 
                printf("\n\t");
            else
                printf("\n\t");
			printf("\n\t��ϲ����Ʊ�ɹ���\n");
            for(i=1; i<=Ticket_Count; i++)                   //��ӡ��λ�� 
            {   
            	printf("\n\t����Ԥ������λ����%d",IDinfor++);
                if(i%10==0)
                   printf("\n\t");
            }
            printf("\n");   
        }//endif(���㶨Ʊ��) 
        else if(p1->Free_Amount==0)
        {
          printf("\n\t�Բ���Ʊ������!\n");
          IsRepl=0;
        }
        else
        {
          printf("\n\t�Բ��𣬵�ǰû�ж����Ʊ!\n");
          IsRepl=0;
        }
        if(!IsRepl) 
        {
          printf("\n\t���Ƿ����Ϊ�򲹳˿�(Y/N)?");
          scanf("%s",&temp);
          if(temp=='y'||temp=='Y')    //����Ϊ�򲹲��� 
          {
            if(p1->ReplName==NULL)
            {
                c2=(Customer*)malloc(sizeof(Customer));  //�����ú������λ��

//���˿ͽ��
				Replp1[Flight_No]=c2;                    ////����
				p1->ReplName=Replp1[Flight_No];
            }
            else
            {
                c2=(Customer*)malloc(sizeof(Customer)); ////�¿ͻ�
                Replp1[Flight_No]->Next=c2;
                Replp1[Flight_No]=c2;
            }
            IsReplace=0;                                  //�򲹳˿Ͳ�Ϊ��
            tag=1;                                  //��ѡ������򲹳˿�����
            Replp1[Flight_No]->Amount=Ticket_Count;
            printf("\n\t��������������:");
            scanf("%s",&Replp1[Flight_No]->Name); 
            Replp1[Flight_No]->IDinfor=IDinfor;           //�򲹳˿͵���λ
            Replp1[Flight_No]->Amount=Ticket_Count;       //�򲹳˿͵Ķ�Ʊ��
            while(1)                           
            { //���ݺϷ��Լ���
                printf("\n\t�������λ�ȼ�:");
                   scanf("%s",&Replp1[Flight_No]->Rank);
                printf("\n\t����������ID��Ϣ:");
                   scanf("%d",&Replp1[Flight_No]->IDinfor);
                if(!(Replp1[Flight_No]->Rank>='1'&&Replp1[Flight_No]->Rank<='3'))
                {
                  printf("\n\t������������������.");
                  getch();
                }
                else  break;
            }
            printf("\n\tû��ʣ����λ!\n");                //�򲹳˿�������ʾ
			shouldsave=1;
          }//end if(���������)		  
        }//end if(Ʊ������)
    }//end if(�������)
    else
        printf("\n\t�Բ��𣬺��಻����!\n");               //���಻����
    if(flag)                                 //�˴�������������ַ���
        Custp1[Flight_No]->Next=NULL;             //ĩλ��Ʊ�˿͵�ָ���ÿ�
    if(tag)
    {
        Replp1[Flight_No]->Next=NULL;          //ĩλ�򲹳˿͵�ָ���ÿ�
        printf("\n\t���Ѿ��ɹ�����򲹶�Ʊ������!\n");
    }
   printf("\n\t�Ƿ��˳��˵���:(y/n)");
   scanf("%s",&c);
   if(c=='y')  return; 
  }//endwhile(1)
}//end   
//10��Ʊ�˿���Ϣ
void Display_Reserve()
{
  Flight *p1;    ////
  Customer *c1;  ////
  system("cls");
  p1=Head;
  if(Empty_Flight())    return;
  printf("\n\t��Ʊ�˿���Ϣ");
  if(IsEmpty)
  {
    printf("\n\t�Բ���û�ж�Ʊ�˿���Ϣ!\n");
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
                printf("\n\n\t���ж����Ʊ!\n");
          else
                printf("\n\n\tƱ������!\n"); 
          c1=c1->Next; 
         
        }
    }
    p1=p1->Next;
    printf("\n\n___________________________________________________________\n");
  }//endwhile   
  printf("\n\t�����������!");
  getch();
  return;
}//end

//11.�򲹳˿���Ϣ
void Display_Replace()
{
  Flight *p1;
  Customer *c1;
  system("cls");
  p1=Head;
  if(Empty_Flight())    return;
  printf("\n\t�򲹳˿���Ϣ!");
  if(IsReplace)
  {
    printf("\n\t�Բ���û�к򲹳˿�!\n");
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
            printf("\n\t���ж����Ʊ!\n");
          else
            printf("\n\tƱ������!\n"); 
          c1=c1->Next; 
        }
    }
    p1=p1->Next; 
  }//endwhile   
  printf("\n\n_________________________________________________________________\n"); 
  printf("\n\t�����������!");
  getch();
  return;
}//end

//12.��Ʊ������
void RefundticketMenu()
{
  int Flight_No=0,flag=0;             //��¼���������ĺ���Ķ�Ʊ��� 
  Flight *p1;                         //�������������ĺ������ַ 
  Customer *c2,*c4;                   //��ʱ�Զ�Ʊ��Ա��� 
  Customer *c3,*c5;                   //��ʱ�Ժ򲹳�Ա��� 
  char answer[7],name[7];             //�û�����ĺ������� 
  int tag=0;             //���ڶ��˿������������������׵�ַ�ᷢ����ͻ��ע��˴� 
  int IDinfor;           //��¼��λ�� 
  if(Empty_Flight())     //����Ϊ�� 
    return;
  printf("\n\t���ڿ�ʼ������Ʊ����");
  if(IsEmpty)
  {
    printf("\n\t�Բ��𣬳˿Ͳ�����!");
    getch();
    return;
  }
  while(1)
  {
    flag=0;
    tag=0;
    Flight_No=0;
    printf("\n\t�����뺽���:");
    scanf("%s",&answer);
    if(Find_Line2(Head, answer, &p1, &Flight_No))   ////������� 
    {
        c2=p1->CustName;                            //ָ��ú���˿��������׵�ַ
        printf("\n\t��������������:");
        scanf("%s",&name);
        if(c2==NULL)                                //�ú����޶�Ʊ�˿� 
        {
          printf("\n\t�Բ��𣬳˿Ͳ�����!.");
          if(Continue()=='n')  return;              //�Ƿ��������            
        }
        else     
          while(c2!=NULL)                           //�������޴˳˿��� 
          {
            if(strcmp(c2->Name,name)==0)     //�������Ų���ʡ�ԣ������ܻ�ת�� 
            {
                if(c2==p1->CustName)                //��Ϊ��λ�˿�����  
                {
                  prior=p1->CustName;               //��¼ָ�� 
                  IDinfor=c2->IDinfor;
                  flag=1;
                  break;
                }
            }
            else if(c2->Next!=NULL)                 //��¼���㺽��ĵ�ǰ����ַ 
            {
                if(strcmp(c2->Next->Name,name)==0)
                {
                  tag=1;                            //�ر�ע��˴�
                  prior=c2;               //��¼���㶨�˿͵�ǰһ��ַ������ɾ������
                  IDinfor=c2->Next->IDinfor;
                  flag=1;
                  break;
                }
            }
            c2=c2->Next;                            //ָ����һ�˿ͽ�� 
			shouldsave=1;
          }//endwhile 
          if(!flag)
             printf("\n\t�Բ��𣬳˿Ͳ�����!\n");
    }//if(���ڸú���)
    else
        printf("\n\t�Բ��𣬺��಻����!\n");
    if(flag)
    {
        if(prior==p1->CustName&&!tag)   //�׽������������һ���˿ͣ���ú��ඨƱ�˿��ÿ�
        {
          if(prior->Next==NULL)         //��һ�˿ͣ�ͷָ���ÿ� 
          {
            p1->Free_Amount+=prior->Amount;
            p1->CustName=NULL;
          }
          else   
          {
            p1->Free_Amount+=prior->Next->Amount;
            p1->CustName=prior->Next;               //ָ����һ�˿ͽ�� 
          }
        }
        else
        {
          p1->Free_Amount+=prior->Next->Amount;
          prior->Next=prior->Next->Next;            //ɾ������ 
        }
        Customer_Count--;
        if(Customer_Count==0)  IsEmpty=1;          
		shouldsave=1;
    }//endif
    if(flag) 
    { //������Ʊ����
        c3=p1->ReplName; 
        while(c3!=NULL)
        {
           if(c3->Amount<=p1->Free_Amount) //�򲹳˿͵Ķ�Ʊ��С�ڻ����ʣ��Ʊ�� 
		   {          
             printf("\n\t�򲹳˿��Ѿ�����!\n");
             c4=(Customer*)malloc(sizeof(Customer));
			 Custp1[Flight_No]->Next=c4;
             //c4=Custp1[Flight_No]->Next=(Customer*)malloc(sizeof(Customer)); 

//�����½��
             c4->Next=NULL;
             IsEmpty=0;
             if(p1->CustName==NULL)  p1->CustName=c4;              
             strcpy(c4->Name,c3->Name);
             c4->Rank=c3->Rank;
             c4->Amount=c3->Amount;
             c4->IDinfor=IDinfor;
             p1->Free_Amount-=c3->Amount;               //��ȥ��Ӧ��Ʊ��
             Customer_Count++;
             if(c3->Next==NULL)  IsReplace=1;           //�޺򲹳˿�            

 
             if(p1->ReplName==c3)
			 {
                if(p1->ReplName->Next==NULL)  p1->ReplName=NULL;  //ɾ��
                else   p1->ReplName=c3->Next; 
			 }
             else   c5->Next=c3->Next->Next;
             break;   
		   }//endif
           if(c3->Next!=NULL) 
              if(c3->Next->Amount<=p1->Free_Amount)
                c5=c3;
              c3=c3->Next;                      //ָ����һ�򲹳˿ͽ�� 
		      shouldsave=1;
		}//endwhile
        printf("\n\t��Ʊ�ɹ���");
        getch();
        return;
    }//endif(���ڴ˳˿�)
	shouldsave=1;
    if(Continue()=='n')  return;
  }//endwhile(1)
}//end
//13.�˿͹����Ӳ˵�����
void CustomermagMenu()
{
  char c;
  system("cls");
  while(1)
  {
     printf("\n\t\t�˿͹���˵�:\n");
     printf("\n____________________________________________________________\n\n"); 
     printf("\t1.�˿���Ϣ\n");
     printf("\t2.�򲹳˿���Ϣ\n");
     printf("\t3.�������˵�\n");
     printf("\n______________________________________________________________\n");
     printf("\t��ѡ������Ҫ�ķ���:");
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
  system("color 1f");                            //��Ļ��ɫ�趨
  system("mode con: cols=78 lines=35"); 
  do{
       system("cls");
       printf("\n\t\t             ���տ��˶�Ʊϵͳ���˵�\n"); 
       printf("\n****************************************************************\n"); 
       printf("\t                 1.�� �� �� �� �� ��\n");
       printf("\t                 2.�� Ʊ �� �� �� ��\n");
       printf("\t                 3.�� Ʊ �� �� �� ��\n");
       printf("\t                 4.�� �� �� �� �� ��\n");
       printf("\t                 5.�� �� ϵ ͳ\n");
       printf("\n*****************ллʹ�ú��տ��˶�Ʊϵͳ��*********************\n");
       printf("��ѡ������Ҫ�ķ���:");
         scanf("%s",&c);
         switch(c)
		 {
            case '1':  LinemanageMenu();break;           //������� 
            case '2':  bookingMenu();break;              //��Ʊ���� 
            case '3':  RefundticketMenu();break;         //��Ʊ����
            case '4':  CustomermagMenu();break;          //�˿͹���
            case '5':  exit(0);    
            default:   break;
		 }
  }while(c!='5');
}
