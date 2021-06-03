#include"os_obj5.h"

//�ļ�����
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

//��ʼ���������
void ini(LinkQueue* L,int* a)
{
	L->front = L->rear = new Lnode[sizeof(Lnode)];
	L->front->next = NULL;
	Lnode* s;
	int i = 0;
	while (i < 3)	//��������������г�ʼ��������ҵ
	{
		s = new Lnode[sizeof(Lnode)];
		s->num = a[i];
		s->next = NULL;
		L->rear->next = s;
		L->rear = s;
		i++;
	}
}

//�Ƚ��ȳ�
void FIFO(int* a, LinkQueue* L,float work_num)
{
	Lnode* s;
	Lnode* r;
	float result = 0;	//ȱҳ��
	float hit_num = 0;	//���д���
	int i = 3;
	int flag = 0;	//�ж��Ƿ����еı�ʶ��
	while (i < work_num)
	{
		s = L->front;	//��ͷ�ڵ��s
		while (s->next != NULL)
		{
			if (s->next->num == a[i])	//�Ƿ�����
			{
				break;
			}
			s = s->next;
		}
		if (s->next != NULL)	//������
		{
			hit_num++;
			i++;
			flag = 1;
		}
		else {		//δ���У����¶�����Ϣ��ֱ�ӽ���һ���ڵ����������½ڵ�ӵ�����β����
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
		while (s->next != NULL)	//�������
		{
			if (flag == 1)
			{
				cout << "����";
				break;
			}
			else {
				cout << s->next->num << "\t";
				s = s->next;
			}
			
		}
		cout << endl;
		
	}
	result = (work_num - hit_num) / work_num;	//������
	cout << "���д���Ϊ:" << hit_num << endl;
	cout << "ȱҳ��Ϊ��" << result << endl;

}

//���ѡ��
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
		while (s->next != NULL)	//�Ƿ�����
		{
			if (s->next->num == a[i])
			{
				break;
			}
			s = s->next;
		}
		if (s->next != NULL)	//������
		{
			hit_num++;
			i++;
			flag = 1;
		}
		else {		//δ����
			q = L->front;
			while (q->next != NULL)	//������������
			{
				int current = i + 1;	//����һ����ʼ�ж�
				while (a[current] != q->next->num)	//����Ҫ���ٲ������ٴ�ʹ�õ�����ҵ
				{
					q->next->step += 1;
					current++;
					if (current >= work_num)	//̫����˳�
					{
						break;
					}
				}
				q = q->next;
			}
			q = L->front;
			//Ѱ�����Ĳ�������ҵ�����滻
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
		while (s->next != NULL)		//��������Ϣ
		{
			if (flag == 1)
			{
				cout << "����";
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
	cout << "���д���Ϊ:" << hit_num << endl;
	cout << "ȱҳ��Ϊ��" << result << endl;
}

//������ʹ��
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
				cout << "����";
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
	cout << "���д���Ϊ:" << hit_num << endl;
	cout << "ȱҳ��Ϊ��" << result << endl;
}

int main()
{
	int a[MAXSIZE];
	float work_num = 20;
	LinkQueue L ;
	in(a, work_num);
	cout << "��ҵ����Ϊ��" << work_num << endl;
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