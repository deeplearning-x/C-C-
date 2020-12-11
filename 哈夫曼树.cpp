#include"iostream"
#include"cstdlib"
#include"cctype"
#include"cstring"


using namespace std;

class Tree {

public:
	double a;
	char name;
	Tree* R;
	Tree* L;
public:
	Tree(char n, double c) :R(NULL), L(NULL)
	{
		a = c;
		name = n;
	}
};

int* tongji(char *C)
{
	int *num = new int[95]{ 0 };
	char* t = C;
	while (*t != '\0')
	{
		if (*t>='a'&&*t<='z')
			num[(int)(*t - 61)]++;
		else if (isupper(*t))
			num[(int)(*t - 55)]++;
		else if (isdigit(*t))
			num[(int)(*t - 48)]++;
		else if (*t>=' '&&*t<='/')
		    num[(int)(*t + 30)]++;
		else if (*t>=':'&&*t<=64)
		    num[(int)(*t + 20)]++;
		else if (*t>='['&&*t<=96)
		    num[(int)(*t - 6 )]++;
		else if (*t>='{'&&*t<='~')
		    num[(int)(*t - 32)]++;
		t++;
	}
	return num;
}

double* quan(char* C)
{
	int* N = tongji(C);
	double* Q = new double[95];
	for (int i = 0; i<95; i++)
	{
		Q[i] = N[i] / (double)strlen(C);
	}
	delete[]N;
	return Q;
}

int p;

Tree** saomiao(char* C)
{
	int n = 0, b[95] = { 0 }, j = 0;
	double* Q = quan(C);
	for (int i = 0; i<95; i++)
	{
		if (!(Q[i] - 1e-6<0) && (Q[i] + 1e-6>0))
		{
			b[j++] = i;
			n++;
		}
	}
	p = n;
	Tree** T = new Tree*[n];
	for (int i = 0; i<n; i++)
	{
		if (b[i]>=36&&b[i]<=61)
			T[i] = new Tree(b[i] + 61, Q[b[i]]);
		else if (b[i]>=10&&b[i]<=35)
			T[i] = new Tree(b[i] + 55, Q[b[i]]);
		else if (b[i]>=0&&b[i]<=9)
			T[i] = new Tree(b[i] + 48, Q[b[i]]);
		else if (b[i]>=62&&b[i]<=77)
			T[i] = new Tree(b[i] - 30, Q[b[i]]);
		else if (b[i]>=78&&b[i]<=84)
			T[i] = new Tree(b[i] - 20, Q[b[i]]);
		else if (b[i]>=85&&b[i]<=90)
			T[i] = new Tree(b[i] + 6, Q[b[i]]);
		else if (b[i]>=91&&b[i]<=94)
			T[i] = new Tree(b[i] + 32, Q[b[i]]);
	}
	return T;
}


Tree** paixu1(char *C)
{
	Tree** T = saomiao(C), *K = NULL;
	int flag = 0;
	for (int i = 0; i<p; i++)
	{
		for (int j = 0; j<p - 1; j++)
		{
			if (T[j]->a<T[j + 1]->a)
			{
				K = T[j];
				T[j] = T[j + 1];
				T[j + 1] = K;
				flag = 1;
			}
		}
		if (flag == 0)break;
	}
	return T;
}

Tree** paixu2(Tree** T, int n)
{
	Tree* K = NULL;
	int flag = 0;
	for (int i = 0; i<n - 1; i++)
	{
		if (T[n - 1 - i]->a>T[n - 2 - i]->a)
		{
			K = T[n - 1 - i];
			T[n - 1 - i] = T[n - 2 - i];
			T[n - 2 - i] = K;
			flag = 1;
		}
		if (!flag)break;
		else flag = 0;
	}
	return T;
}

Tree** caozuo(char *C)
{
	Tree** T = paixu1(C);
	Tree* K = NULL;
	int h = p;
	for (int i = 0; i<p - 1; i++)
	{
		K = T[p - 2 - i];
		T[p - 2 - i] = new Tree('#', (T[p - 1 - i]->a + K->a));
		T[p - 2 - i]->L = T[p - 1 - i];
		T[p - 2 - i]->R = K;
		h--;
		T = paixu2(T, h);
	}
	return T;
}

char* input()
{
	cout << "请输入英文句子：" << endl;
	char *a = new char[1000];
	gets(a);
	return a;
}

void Dfirstroot(Tree *T,Tree* bT)//递归先根遍历 (修改版) 
{
	if (bT != NULL)if (T != bT->L&&bT->name == '#')
		cout << ',';
	cout << T->name;
	if (T->name == '#')
		cout << '(';
	
	{
		
		
		if (bT != NULL)if (T == bT->R&&bT->name == '#'&&T->name!='#')
			cout << ')';
	}
	if (T->L != NULL)
		Dfirstroot(T->L, T);
	if (T->R != NULL)
		Dfirstroot(T->R, T);
	if (bT!= NULL)if (T->name == '#'&&bT->R == T)
		cout << ')';
}

void guangyibiao(Tree *T, Tree* bT)
{
	Dfirstroot(T, bT);
}



int main()
{
	char* C = input();
	Tree** T = caozuo(C);
	cout << "广义表:"; 
	guangyibiao(*T,NULL);
	system("pause");
}
