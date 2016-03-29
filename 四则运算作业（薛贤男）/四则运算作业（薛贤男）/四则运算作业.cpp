#include<iostream>
#include<string>
#include<stdlib.h>
#include<ctime>
#include<deque>
#include<stack>
#include<fstream>
#include<windows.h>
using namespace std;//PS：本算法参考http://blog.csdn.net/anye3000/article/details/7941231
int N,R;
int **add;
int **mul;
string GetProgramDir();
string programDir;
string turnString(int a)
{
	char turnChar[10];
	sprintf(turnChar,"%d",a);
	return turnChar;
}
string charToString(char c)
{
	string t(&c);
	return t;
}
bool isNumber(string c)//判断是否是数字
{
	char s=c[0];
	if((s=='+')||(s=='-')||(s=='/')||(s=='*')|| s=='(' || s==')') return false;
	return true;
}
bool isNotNum(char c)
{
	if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')')
		return true;
	return false;
}
//判断是否为括号  
bool isPra(string c)   
{  
	char s=c[0];
    if(s=='('||s==')')   
        return true;   
    else   
        return false;  
}  
string addPra(string operCharToString,int Num[],deque<string>& cal1)
{
	string t="";
	bool first=false;
	bool second=false;
	bool third=false;
	if(rand()%2==1){
		first=true;
		t+='('+turnString(Num[0])+operCharToString[0]+turnString(Num[1])+')';
		cal1.push_back("(");
		cal1.push_back(turnString(Num[0]));
		cal1.push_back(charToString(operCharToString[0]));
		cal1.push_back(turnString(Num[1]));
		cal1.push_back(")");
	}
	else{
		t+=turnString(Num[0])+operCharToString[0];
		cal1.push_back(turnString(Num[0]));
		cal1.push_back(charToString(operCharToString[0]));
	}
	if(rand()%2==1 && !first){
		second=true;
		t+='('+turnString(Num[1])+operCharToString[1]+turnString(Num[2])+')';
		cal1.push_back("(");
		cal1.push_back(turnString(Num[1]));
		cal1.push_back(charToString(operCharToString[1]));
		cal1.push_back(turnString(Num[2]));
		cal1.push_back(")");
	}
	else if(first){
		t+=operCharToString[1];
		cal1.push_back(charToString(operCharToString[1]));
	}
	else{
		t+=turnString(Num[1])+operCharToString[1];
		cal1.push_back(turnString(Num[1]));
		cal1.push_back(charToString(operCharToString[1]));
	}
	if(operCharToString.length()==3){
		if(rand()%2==1 && !second){
			t+='('+turnString(Num[2])+operCharToString[2]+turnString(Num[3])+')';
			cal1.push_back("(");
			cal1.push_back(turnString(Num[2]));
			cal1.push_back(charToString(operCharToString[2]));
			cal1.push_back(turnString(Num[3]));
			cal1.push_back(")");
		}
		else if(!second){
			t+=turnString(Num[2])+operCharToString[2]+turnString(Num[3]);
			cal1.push_back(turnString(Num[2]));
			cal1.push_back(charToString(operCharToString[2]));
			cal1.push_back(turnString(Num[3]));
		}
		else{
			t+=operCharToString[2]+turnString(Num[3]);
			cal1.push_back(charToString(operCharToString[2]));
			cal1.push_back(turnString(Num[3]));
		}
	}
	else if(!second){
		t+=turnString(Num[2]);
		cal1.push_back(turnString(Num[2]));
	}
	return t;
}
//获得符号的优先性  
int getPri(string c)   
{  
    switch(c[0])   
    {  
    case '+':  
    case '-':  
        return 0;   //如果是加减，返回0  
        break;  
    case '*':  
    case '/':  
        return 1;   //如果是乘除，返回1  
        break;  
    case '(':  
    case ')':  
        return -1;  //将括号设为最低优先级，因此括号不会被弹出，除非遇到右括号  
        break;  
     }  
}  
//判断符号的优先性  
void checkAuth(string c, stack<string>& cal2, deque<string>& cal3)   
{    
    if(cal2.empty())   
    {  
        cal2.push(c);  
        return;  
    }  
   
    if(isPra(c))   
    {  
        if(c=="(")   
            cal2.push(c);  
        else   
        {  
            //弹出所有元素直到遇到左括号  
            while(cal2.top()!="(")   
            {    
                string ch = cal2.top();  
               cal3.push_back(ch);  
                cal2.pop();  
            }  
  
            //当遇到左括号时，弹出但不加入cal3
            cal2.pop();    
        }  
    }  
    else    //如果不是括号  
    {  
        //取出栈顶元素，与当前符号进行优先性比较  
        string sym = cal2.top();    
  
        //比较两符号的优先性  
        if(getPri(c)<=getPri(sym))    
        {  
            //如果c的优先性比栈顶符号小或等于，弹出栈顶元素  
            cal2.pop();  
            //并将其压入cal3中  
            cal3.push_back(sym);  
            //递归调用checkAuth,比较当前符号c与下一个栈顶符号的优先性  
            checkAuth(c,cal2,cal3);     
        }  
        else   
        {  
            //如果c比栈顶符号优先级大，那将c压入cal2(操作符栈）中  
           cal2.push(c);    
        }  
    }     
}
//从cal1中取出元素，分配元素到cal2和cal3中 
void allocate(deque<string>& cal1, stack<string>& cal2, deque<string>& cal3)   
{    

    while(!cal1.empty())   
    {  
        string c = cal1.front();
        cal1.pop_front();  
  
        if(isNumber(c))  
        {  
            cal3.push_back(c);  
        }  
        else   
        {  
            //调用checkAuth函数，针对不同情况作出不同操作  
            checkAuth(c,cal2,cal3);  
        }  
  
    }
	//如果输入结束，将cal2的元素全部弹出，加入后缀表达式中  
    while(!cal2.empty())   
    {    
        string c = cal2.top();  
       cal3.push_back(c);  
        cal2.pop();  
    } 
}
bool isRepeat(int len, int op1,int op2,int opc)//判断重复      
{
	if(op1>=R||op2>=R)
		return false;
	if((add[op1][op2]==9)||(mul[op1][op2]==9))
		return true;
	if(opc==1)
	{
		switch (len)
		{
			//一个运算符
			case 3:
				if((add[op1][op2]==1)||(add[op1][op2]==4)||(add[op1][op2]==6))
					return true;
				else
				{
					add[op1][op2]+=1;
					add[op2][op1]+=1;
					return false;
				}
			//两个运算符
			case 5:
				if((add[op1][op2]==3)||(add[op1][op2]==4)||(add[op1][op2]==8))
					return true;
				else
				{
					add[op1][op2]+=3;
					add[op2][op1]+=3;
					return false;
				}
			//三个运算符
			case 7:
				if((add[op1][op2]==5)||(add[op1][op2]==6)||(add[op1][op2]==8))
					return true;
				else
				{
					add[op1][op2]+=5;
					add[op2][op1]+=5;
					return false;
				}
		}
	}
	if(opc==2)
	{
		switch (len)
		{
			//一个运算符
			case 3:
				if((mul[op1][op2]==1)||(mul[op1][op2]==4)||(mul[op1][op2]==6))
					return true;
				else
				{
					mul[op1][op2]+=1;
					mul[op2][op1]+=1;
					return false;
				}
			//两个运算符
			case 5:
				if((mul[op1][op2]==3)||(mul[op1][op2]==4)||(mul[op1][op2]==8))
					return true;
				else
				{
					mul[op1][op2]+=3;
					mul[op2][op1]+=3;
					return false;
				}
			//三个运算符
			case 7:
				if((mul[op1][op2]==5)||(mul[op1][op2]==6)||(mul[op1][op2]==8))
					return true;
				else
				{
					mul[op1][op2]+=5;
					mul[op2][op1]+=5;
					return false;
				}
		}
	}
}
bool calculate(deque<string>& cal3, stack<int>&cal4)//计算   
{
	int len= cal3.size();
    while(!cal3.empty())   
    {  
        string c =cal3.front();
        cal3.pop_front();  
          
        //如果是操作数，压入栈中  
        if(isNumber(c))   
        {  
            //减去'0'得出偏移值，即为真实数值（如果直接转换成int，结果不对，因为char 转换为int是其编码值，例如'1'的编码值为49  
            int op = atoi(c.c_str());      
            cal4.push(op);       
        }  
        else     //如果是操作符，从栈中弹出元素进行计算  
        {   
            int op1 = cal4.top();  
            cal4.pop();  
            int op2 = cal4.top();  
            cal4.pop();  
			switch(c[0])   
            {  
            case '+':
				if(isRepeat(len,op1,op2,1))
					return false;
                cal4.push(op2+op1);  
                break;  
            case '-': 
				if((op2-op1)<0)
					return false;
               cal4.push(op2-op1);  
                break;  
            case '*':
				if(isRepeat(len,op1,op2,2))
					return false;
                cal4.push(op2*op1);  
                break;  
            case '/': 
				if( op1==0 || op2%op1!=0 )
					return false;
               cal4.push(op2/op1);  //注意是op2(op)op1而不是op1(op)op2  
                break;  
            }  
        }
    }
	return true;
}
//获取执行文件路径
string GetProgramDir()  
{   
    char exeFullPath[MAX_PATH]; // Full path
    string strPath = "";
    GetModuleFileName(NULL,exeFullPath,MAX_PATH);
    strPath=(string)exeFullPath;    // Get full path of the file
    int pos = strPath.find_last_of('\\', strPath.length());
	strPath=strPath.substr(0, pos);
	int t=1,j=0;
	string s="";
	for(int i=0;i<strPath.length();i++){
		if(strPath[i]=='\\'){
			s+=strPath.substr(j,t);
			s+="\\";
			t=0;
			j=i+1;
		}
		t++;
	}
	s+=strPath.substr(j,t);
	strPath=s;
	strPath+="\\";
	strPath+="\\";
    return strPath;  // Return the directory without the file name
}
void initCmd(int argc,char *argv[],string &n,string &r,string &e,string &a)//初始化输入参数
{
		for(int i=1;i<argc;i++)
		{
			string s(argv[i]);
			if(s=="-n")
			{
				if(i+1<argc)
				{
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
					{
						n=str;
					}
					if(n=="")
					{
						cout<<"请输入-n的值！";
						return;
					}
				}
			}
			if(s=="-r")
			{
				if(i+1<argc)
				{
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
					{
						r=str;
					}
					if(r=="")
					{
						cout<<"请输入-r的值！";
						return;
					}
				}
			}
			if(s=="-e"){
				if(i+1<argc){
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
					{
						e=str;
					}
					if(e=="")
					{
						cout<<"请输入-e的值！";
						return;
					}
				}
			}
			if(s=="-a")
			{
				if(i+1<argc)
				{
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
					{
						a=str;
					}
					if(a=="")
					{
						cout<<"请输入-a的值！";
						return;
					}
				}
			}
		}
	}
void toQuestion(string n,string r)//随机生成题目
{
	if(n!="" && r!="")
	{
		/*DWORD start_time=GetTickCount();*/
		ofstream oufQuestion;
		ofstream oufAnswer;
		oufQuestion.open(programDir+"Exercises.txt");
		oufAnswer.open(programDir+"Answers.txt");
		N=atoi(n.c_str());
		R=atoi(r.c_str());
		string question[10000];//存放题目
		string answer[10000];//存放答案
		int Num[10000][4];//存放数字（随机生成）
		int operCharNumber[10000];//题目中包含运算符的数量（随机生成，最多为3，最少为1）
		char operate[10000][4];//运算符
		add = new int *[R];
		mul = new int *[R];
		for(int i=0;i<R;i++)//初始化判重数组
		{
			add[i]=new int[R];
			mul[i]=new int[R];
			memset(add[i], 0, sizeof(int)*R);
			memset(mul[i], 0, sizeof(int)*R);
		}
		srand((unsigned)time(NULL));
		for(int i=0;i<N;i++)
		{
			string operCharToString="";
			operCharNumber[i]=(rand()%3)+1;
			for(int j=0;j<operCharNumber[i];j++)
			{
				switch((rand()%4)+1)
				{
					case 1:operate[i][j]='+';break;
					case 2:operate[i][j]='-';break;
					case 3:operate[i][j]='*';break;
					case 4:operate[i][j]='/';break;
				}
				operCharToString+=operate[i][j];
			}
			for(int j=0;j<=operCharNumber[i];j++)
			{
				Num[i][j]=rand()%R;
			}
			question[i]="";
			deque<string> cal1;  //盛放中缀表达式  
			stack<string> cal2;  //盛放操作符  
			deque<string> cal3;    //盛放后缀表达式  
			stack<int>	cal4;  //计算后缀表达式的辅助容器
			if(operCharToString.length()>1)
				question[i]=addPra(operCharToString,Num[i],cal1);
			else
			{
				question[i]+=turnString(Num[i][0])+operate[i][0]+turnString(Num[i][0]);
				cal1.push_back(turnString(Num[i][0]));
				cal1.push_back(charToString(operate[i][0]));
				cal1.push_back(turnString(Num[i][0]));
			}
			 //从call中取出元素，分配元素到cal2和cal3中  
			allocate(cal1,cal2,cal3);   
			 //计算后缀表达式  
			if(!calculate(cal3,cal4))
			{
				question[i]="";
				i--;
				continue;
			}
			else
			{
				oufQuestion<<i+1<<'.'<<question[i]<<"="<<'\n';
				oufAnswer<<i+1<<'.'<<cal4.top()<<'\n';
			}
		}
		//DWORD end_time=GetTickCount();
		//cout<<"The run time is:"<<(end_time-start_time)<<"ms!"<<endl;//输出运行时间
		cout<<"题目生成完毕";
		oufQuestion.close();
		oufAnswer.close();
	}
}
int main(int argc,char *argv[])
{
	string cinStr[4];
	string n,r,e,a;
	initCmd(argc,argv,n,r,e,a);
	programDir=GetProgramDir();
	toQuestion(n,r);
	if(e!="" && a!="")//判定用户给定的文件
	{
		fstream openQuestion;
		openQuestion.open(programDir+e,ios::in);
		if(!openQuestion.good())
		{
			cout<<e+"文件打开失败";
			return 0;
		}
		fstream openAnswer;
		openAnswer.open(programDir+a,ios::in);
		if(!openAnswer.good())
		{
			cout<<a+"文件打开失败";
			return 0;
		}
		string *strQuestion = new string[10000]; // 开空间，注意 + 1
		string *strAnswer = new string[10000]; // 开空间，注意 + 1
		//处理
		int i=0;
		while(!openQuestion.eof())
		{
			char c[100];
			openQuestion.getline(c,100,'\n');
			strQuestion[i]=c;
			char c1[100];
			openAnswer.getline(c1,100,'\n');
			strAnswer[i]=c1;
			i++;
		}
		openQuestion.close();
		openAnswer.close();
		int correct[10000];
		int cor=0;
		int wrong[10000];
		int wro=0;
		for(int j=0;j<i;j++)
		{
			string question,answer;
			for(int k=0;k<strQuestion[j].length();k++)
			{
				if(strQuestion[j][k]=='.')
				{
					strQuestion[j]=strQuestion[j].substr(k+1);
					break;
				}
			}
			question=strQuestion[j];
			for(int k=0;k<strAnswer[j].length();k++)
			{
				if(strAnswer[j][k]=='.')
				{
					strAnswer[j]=strAnswer[j].substr(k+1);
					break;
				}
			}
			answer=strAnswer[j];
			deque<string> cal1;  //盛放中缀表达式  
			stack<string> cal2;  //盛放操作符  
			deque<string> cal3;    //盛放后缀表达式  
			stack<int>	cal4;  //计算后缀表达式的辅助容器
			string s="";
			bool b=false;
			if(question!="")
			{
				for(int k=0;k!=question.length()-1;++k)   
				{  
					//逐一加入每个字符，这里使用deque因为deque在两端删除添加的速度最快
					if(question[k]=='(')
					{
						cal1.push_back("(");
						continue;
					}
					if(isNotNum(question[k]))
					{
						if(s!="")
							cal1.push_back(s);
						string str=charToString(question[k]);
						cal1.push_back(str);
						s="";
						continue;
					}
					s+=question[k];
				}  
				if(question[question.length()-2]!=')')
					cal1.push_back(s);
				//从call中取出元素，分配元素到cal2和cal3中 
				allocate(cal1,cal2,cal3);
				//计算后缀表达式  
				calculate(cal3,cal4);
				if(cal4.top()==atoi(answer.c_str()))
				{
					correct[cor]=j+1;
					cor++;
				}
				else{
					wrong[wro]=j+1;
					wro++;
				}
			}
		}
		ofstream grade;
		grade.open(programDir+"Grade.txt");
		grade<<"Correct:"<<cor<<"(";
		for(int j=0;j<cor;j++)
		{
			grade<<correct[j];
			if(j!=cor-1)
				grade<<",";
		}
		grade<<")"<<'\n';
		grade<<"Wrong:"<<wro<<"(";
		for(int j=0;j<wro;j++)
		{
			grade<<wrong[j];
			if(j!=wro-1)
				grade<<",";
		}
		grade<<")"<<'\n';
		grade.close();
	}
	return 0;

}