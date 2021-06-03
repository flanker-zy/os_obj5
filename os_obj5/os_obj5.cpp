#include"os_obj5.h"

//文件输入
void in(int* a, int work_num)
{
	const char* filename = "test.txt";
	ifstream ism;
	ism.open(filename);
	if (!ism.is_open())
	{
		cout << "hhhhhhhhh" << endl;
	}
	for (int i = 0; i < work_num; i++)
	{
		ism >> a[i];
	}
}

//初始化链表队列
void ini(LinkQueue* L,int* a)
{
	L->front = L->rear = new Lnode[sizeof(Lnode)];
	L->front->next = NULL;
	Lnode* s;
	int i = 0;
	while (i < 3)	//首先向链表队列中初始化三个作业
	{
		s = new Lnode[sizeof(Lnode)];
		s->num = a[i];
		s->next = NULL;
		L->rear->next = s;
		L->rear = s;
		i++;
	}
}

//先进先出
void FIFO(int* a, LinkQueue* L,float work_num)
{
	Lnode* s;
	Lnode* r;
	float result = 0;	//缺页率
	float hit_num = 0;	//命中次数
	int i = 3;
	int flag = 0;	//判断是否命中的标识符
	while (i < work_num)
	{
		s = L->front;	//将头节点给s
		while (s->next != NULL)
		{
			if (s->next->num == a[i])	//是否命中
			{
				break;
			}
			s = s->next;
		}
		if (s->next != NULL)	//若命中
		{
			hit_num++;
			i++;
			flag = 1;
		}
		else {		//未命中，更新队列信息，直接将第一个节点抛弃，将新节点加到队列尾部。
			r = new Lnode[sizeof(Lnode)];
			r->next = NULL;
			r->num = a[i];
			L->rear->next = r;
			L->rear = r;
			L->front = L->front->next;
			i++;
			flag = 0;
		}
		s = L->front;
		while (s->next != NULL)	//输出过程
		{
			if (flag == 1)
			{
				cout << "命中";
				break;
			}
			else {
				cout << s->next->num << "\t";
				s = s->next;
			}
			
		}
		cout << endl;
		
	}
	result = (work_num - hit_num) / work_num;	//输出结果
	cout << "命中次数为:" << hit_num << endl;
	cout << "缺页率为：" << result << endl;

}

//最佳选项
void OPI(int* a, LinkQueue* L, float work_num)
{
	Lnode* s;
	Lnode* q;
	float result = 0;
	int count = 0;
	float hit_num = 0;
	int i = 3;
	int flag = 0;
	while (i < work_num)
	{
		s = L->front;
		count++;
		while (s->next != NULL)	//是否命中
		{
			if (s->next->num == a[i])
			{
				break;
			}
			s = s->next;
		}
		if (s->next != NULL)	//若命中
		{
			hit_num++;
			i++;
			flag = 1;
		}
		else {		//未命中
			q = L->front;
			while (q->next != NULL)	//遍历整条队列
			{
				int current = i + 1;	//从下一个开始判断
				while (a[current] != q->next->num)	//看需要多少步才能再次使用到该作业
				{
					q->next->step += 1;
					current++;
					if (current >= work_num)	//太大就退出
					{
						break;
					}
				}
				q = q->next;
			}
			q = L->front;
			//寻找最大的步数的作业用来替换
			Lnode* z = q->next;
			Lnode* x = q->next->next;
			Lnode* c = q->next->next->next;
			Lnode* max = z;
			if (max->step < x->step)
			{
				max = x;
			}
		    if (max->step < c->step)
			{
				max = c;
			}
			max->num = a[i];
			i++;
			flag = 0;
		}
		s = L->front;
		while (s->next != NULL)		//输出结果信息
		{
			if (flag == 1)
			{
				cout << "命中";
				break;
			}
			else {
				cout << s->next->num << "\t";
				s = s->next;
			}
			s->step = 0;

		}
		cout << endl;
	}
	result = (work_num - hit_num) / work_num;
	cout << "命中次数为:" << hit_num << endl;
	cout << "缺页率为：" << result << endl;
}

//最近最不常使用
void LRU(int* a, LinkQueue* L, float work_num)
{
	Lnode* s;
	Lnode* q;
	float result = 0;
	int count = 0;
	float hit_num = 0;
	int i = 3;
	int flag = 0;
	while (i < work_num)
	{
		s = L->front;
		count++;
		while (s->next != NULL)
		{
			if (s->next->num == a[i])
			{
				break;
			}
			s = s->next;
		}
		if (s->next != NULL)
		{
			hit_num++;
			i++;
			flag = 1;
		}
		else {
			q = L->front;
			while (q->next != NULL)
			{
				int current = i - 1;
				while (a[current] != q->next->num)
				{
					q->next->step += 1;
					current--;
					if (current == 0)
					{
						break;
					}
				}
				q = q->next;
			}
			q = L->front;
			Lnode* z = q->next;
			Lnode* x = q->next->next;
			Lnode* c = q->next->next->next;
			Lnode* max = z;
			if (max->step < x->step)
			{
				max = x;
			}
			if (max->step < c->step)
			{
				max = c;
			}
			max->num = a[i];
			i++;
			flag = 0;
		}
		s = L->front;
		while (s->next != NULL)
		{
			if (flag == 1)
			{
				cout << "命中";
				break;
			}
			else {
				cout << s->next->num << "\t";
				s = s->next;
			}
			s->step = 0;

		}
		cout << endl;
	}
	cout << endl;
	result = (work_num - hit_num) / work_num;
	cout << "命中次数为:" << hit_num << endl;
	cout << "缺页率为：" << result << endl;
}

int main()
{
	int a[MAXSIZE];
	float work_num = 20;
	LinkQueue L ;
	in(a, work_num);
	cout << "作业数量为：" << work_num << endl;
	for (int i = 0; i < work_num; i++)
	{
		cout << a[i] << " ";
	}
	ini(&L, a);
	int b = 0;
	while (1)
	{
		cout << endl;
		cout << "pls input a number to select a function" << endl;
		cout << "1.FIFO" << endl;
		cout << "2.OPI" << endl;
		cout << "3.LRU" << endl;
		cout << "4.quit" << endl;

		cin >> b;
		if (b == 1)
		{
			cout << "--------FIFO--------" << endl;
			FIFO(a, &L, work_num);
		}
		else if (b == 2)
		{
			cout << "--------OPI--------" << endl;
			OPI(a, &L, work_num);
		}
		else if (b == 3)
		{
			cout << "--------LRU--------" << endl;
			LRU(a, &L, work_num);
		}
		else if (b == 4)
		{
			break;
		}
		else
		{
			cout << "pls intput a ture number" << endl;
		}
	}
	return 0;
}