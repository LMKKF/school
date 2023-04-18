//�ൺũҵ��ѧУ԰����ϵͳ
//����Դ����
//2021/10/6
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Infinity 65535	//��ʾ�����
#define MaxNumber 23	//�����ڽӾ���
#define vertex 15	//�������
typedef struct side//�ߵ�Ȩֵ
{
    int wet;//Ȩֵ
}side,wetmatrix[MaxNumber][MaxNumber];//�ߵ��ڽӾ�������
typedef struct vetinf//������Ϣ
{
    int number;//������
    char name[64];//��������
    char intro[256];//�������
}vetinf;
typedef struct mapstr//ͼ�ṹ��Ϣ
{
    vetinf vets[MaxNumber];//��������
    wetmatrix mat;//�ڽӾ���
    int vetnum,sidenum;
}mapstr;
//ȫ�ֱ���
mapstr campus;//ͼ�ṹ������ѧУУ԰��
int d[30];
int visited[50];
int shortest[MaxNumber][MaxNumber];//����ȫ�ֱ����洢��С·��
int pathh[MaxNumber][MaxNumber];//����洢·��
//1.ͼ�ĳ�ʼ��
mapstr initmap()
{
    mapstr m;//����ͼm
    int i=0,j=0;
    m.vetnum=15;//���嶥�����
    m.sidenum=23;//����ߵ�����
    for (i=1;i<=vertex;i++)//�������ö�����Ϣ
        m.vets[i].number=i;
    //���붥����Ϣ
    strcpy(m.vets[1].name,"ݸ������");strcpy(m.vets[1].intro,"�������ţ�ѧ��ס�޳���");
    strcpy(m.vets[2].name,"��һ����");strcpy(m.vets[2].intro,"Ϊѧ���ṩ�Ͳͳ���");
    strcpy(m.vets[3].name,"��һ·");strcpy(m.vets[3].intro,"���ӱ��������ţ������ٲ����򳡺�����");
    strcpy(m.vets[4].name,"������");strcpy(m.vets[4].intro,"ѧУ�ٰ������ĳ���");
    strcpy(m.vets[5].name,"�ٲ�����");strcpy(m.vets[5].intro,"�廷������");
    strcpy(m.vets[6].name,"ݸܰ����");strcpy(m.vets[6].intro,"Ů��ס�޳���");
    strcpy(m.vets[7].name,"�������ò���");strcpy(m.vets[7].intro,"�������ź�ݸܰ�������Ͳͳ���");
    strcpy(m.vets[8].name,"������");strcpy(m.vets[8].intro,"������������͵�ѧУ��һ�������ľ�ɫ");
    strcpy(m.vets[9].name,"������ǰ��");strcpy(m.vets[9].intro,"ѧУ�ĺ�����ɫ����");
    strcpy(m.vets[10].name,"�������");strcpy(m.vets[10].intro,"λ��ѧУ�����ˣ�Ϊѧ��������");
    strcpy(m.vets[11].name,"��̬�������̼����з�����");strcpy(m.vets[11].intro,"������ѧУ�ĿƼ�¥,��ѧ¥");
    strcpy(m.vets[12].name,"�칫¥ͼ�������¥");strcpy(m.vets[12].intro,"������ѧУ�İ칫¥,ͼ���,����¥");
    strcpy(m.vets[13].name,"��ѧ¥");strcpy(m.vets[13].intro,"ѧ��ѧϰ�ĳ���");
    strcpy(m.vets[14].name,"����¥,�ľ�¥");strcpy(m.vets[14].intro,"������ѧУ�Ĺ���¥,�ľ�¥");
    strcpy(m.vets[15].name,"�³��㳡");strcpy(m.vets[15].intro,"���ſڣ��ٰ���ֻ�ĵط�");
    for (i=1;i<=vertex;i++)
        for (j=1;j<=vertex;j++)
            m.mat[i][j].wet=Infinity;//��ʼ��ͼ���ڽӾ���
    m.mat[1][2].wet=10;m.mat[2][3].wet=40;m.mat[3][4].wet=20;m.mat[3][8].wet=40;m.mat[3][11].wet=40;
    m.mat[4][5].wet=20;m.mat[4][8].wet=20;m.mat[5][6].wet=30;m.mat[5][8].wet=30;m.mat[6][7].wet=10;
    m.mat[6][9].wet=70;m.mat[7][9].wet=60;m.mat[7][10].wet=40;m.mat[8][9].wet=10;m.mat[9][10].wet=30;
    m.mat[9][13].wet=15;m.mat[9][14].wet=30;m.mat[10][14].wet=10;m.mat[11][12].wet=50;m.mat[11][15].wet=70;
    m.mat[12][13].wet=5;m.mat[12][15].wet=10;m.mat[13][14].wet=40;
    for(i=1;i<=vertex;i++)//�����Ȩͼ�ǶԳƾ���,������һ�븳ֵ
        for(j=1;j<=vertex;j++)
            m.mat[j][i].wet=m.mat[i][j].wet;
    return m;
}
//2.��ѯ������ͼ�е����
int locatevet(mapstr m,int v)
{
    int i;
    for(i=0;i<=m.vetnum;i++)
        if(v==m.vets[i].number) return i;//�ҵ����ض���i
    return -1;//δ�ҵ�
}
//3.��ѯ�������l,n��ĳ��Ȳ�����10�������·��
void path(mapstr m,int l,int n,int k)
{
    int s,t=k+1;int length=0;//t���ڴ洢·������һ�����Ӧ��d[]����Ԫ�ص��±�
    if(d[k]==n&&k<8)//��d[k]���յ��Ҿ������<8���������·��
    {
        for(s=0;s<k;s++)
        {
            length=length+m.mat[d[s]][d[s+1]].wet;
        }
        if(length<200)//��ӡ·��С��200����������·��
        {
            for(s=0;s<k;s++)//�����·����s=0ʱΪ���m
            {
                printf("%d%s--->",d[s],m.vets[d[s]].name);
            }
            printf("%d%s  ",d[s],m.vets[d[s]].name);//������һ������
            printf("��·�߳�Ϊ%d��\n\n",length);
        }
    }
    else
    {
        s=1;
        while(s<=m.vetnum)//�ӵ�m�����㣬�������ж����Ƿ���·��
        {
            if((m.mat[d[k]][s].wet<Infinity)&&(visited[s]==0))//�����б���δ������
            {
                visited[s]=1;
                d[k+1]=s;//�洢������
                path(m,l,n,t);
                visited[s]=0;//���ҵ���·���ϵĶ���ķ��ʱ�־��������Ϊ������̽���µ�·��
            }
            s++;//������һ����s��ʼ�Ƿ��е��յ��·����
        }
    }
}
//4.��ѯ�����������·��
int allpath(mapstr m)
{
    int k,i,j,l,n;
    printf("\n\n����������Ҫ��ѯ����������ı�ţ�\n\n");
    scanf("%d%d",&i,&j);printf("\n\n");
    l=locatevet(m,i);//locatevet ȷ���ö����Ƿ���ڡ������ڣ����ظö����š�
    n=locatevet(m,j);
    d[0]=l;//·�����l(��ĸ).(d[]����Ϊȫ�ֱ���)
    for(k=0;k<vertex;k++)
        visited[k]=0;
    visited[l]=1;
    path(m,l,n,0);
    return 1;
}
//5.�Ͻ�˹�����㷨��Դ���·��
void shortestpath(mapstr m)
{
    int v0,v,w,k=1,min,t,p;
    int final[MaxNumber];//final[w]=1��ʾ�Ѿ���ö���V0��Vw�ĵ����·��
    int Pathside[MaxNumber];//���ڴ洢���·���±������
    int ShortPathwet[MaxNumber];//���ڴ洢���������·����Ȩֵ��
    printf("\n��������ʼ����ı�ţ�");
    scanf("%d",&v0);
    printf("\n\n");
    while(v0<0||v0>vertex)//�ж��Ƿ�������ȷ
    {
        printf("\n������ľ����Ų�����\n");
        printf("���������룺");
        scanf("%d",&v0);
    }
    for(v=1;v<=m.vetnum;v++)//�����ʼ��
    {
        final[v]=0;//ȫ�������ʼ��Ϊδ�ҵ�·��
        ShortPathwet[v]=m.mat[v0][v].wet;//����v0�����ߵ�·������Ȩֵ
        Pathside[v]=0;//��ʼ��·������Ϊ0
    }
    ShortPathwet[v0]=0;
    final[v0]=1;
    //Dijkstr�㷨����
    for(v=1;v<=m.vetnum;v++)
    {
        min=Infinity;
        for(w=1;w<=m.vetnum;w++)//�ҳ��뵱ǰָ�򶥵�����ĵ�
        {
            if(!final[w]&&ShortPathwet[w]<min)//δ�������Ҵ��ڱ�
            {
                k=w;
                min=ShortPathwet[w];
            }
        }
        final[k]=1;//���ҵ����뵱ǰ�����������1
        //����
        for(w=1;w<=m.vetnum;w++)
        {
            if(!final[w]&&(min+m.mat[k][w].wet<ShortPathwet[w]))
            {
                ShortPathwet[w]=min+m.mat[k][w].wet;//�޸ĵ�ǰ����·������
                Pathside[w]=k;//���ǰ�����
            }
        }
    }
    printf("��ӡP����:");	 //��ӡp����
    for(t=1;t<=m.vetnum;t++)
    {
        printf("%d ",Pathside[t]);
    }
    printf("\n\n");
    printf("��ӡS����:");	 //��ӡs����
    for(t=1;t<=m.vetnum;t++)
    {
        printf("%d ",ShortPathwet[t]);
    }
    printf("\n\n");
    //��ӡ���·��
    for(t=1;t<=m.vetnum;t++)
    {
        p=t;
        if(t!=v0)
        {
            printf("%d%s",t,m.vets[t].name);
            for(w=1;w<=m.vetnum;w++)
            {
                if(Pathside[p]!=0)
                {
                    printf("<--%d%s",Pathside[p],m.vets[p].name);
                    p=Pathside[p];
                }
            }
            printf("<--%d%s",v0,m.vets[v0].name);
            printf("\n��·�߳�Ϊ%d��\n\n",ShortPathwet[t]);
        }
    }
}
//6.��ҳ
void menu()
{	printf(" ����������������������������������������������������������������������������������������������������������������\n");
    printf(" �� �q �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �r   ��\n");
    printf(" �� ����        �� ӭ ʹ �� У ԰ �� �� ϵ ͳ          ����  ��\n");
    printf(" �� �t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T �s   ��\n");
    printf(" ��                       ��ӭ����                         ��\n");
    printf(" ��                      ��ݸ��ѧԺ                       ��\n");
    printf(" ��                      �� �� ѡ ��                       ��\n");
    printf(" ��  *************************************************** ��\n");
    printf(" ��  *  1.��ҳ                **   2.�鿴����·��      *     ��\n");
    printf(" ��  *************************************************** ��\n");
    printf(" ��  *  3.��ѯ��������·��  **   4.��ѯ���������·��*        ��\n");
    printf(" ��  *************************************************** ��\n");
    printf(" ��  *  5.ѧУ�������        **   6.ѧУ��ͼ          * ��\n");
    printf(" ��  *************************************************** ��\n");
    printf(" ��  *  7.����ͼ��Ϣ          **   0.�˳�              * ��\n");
    printf(" ��  *************************************************** ��\n");
    printf(" ����������������������������������������������������������������������������������������������������������������\n");
}
//�������޸�ͼ�������Ϣ��
//7.���¹���ͼ
int creatmap(mapstr *m)
{
    int i,j,l,n,v0,v1,distance;
    printf("������ͼ�Ķ������ͱ���:\n");
    scanf("%d %d",&m->vetnum,&m->sidenum);
    printf("�����붥����Ϣ: \n");
    for(i=0;i<=m->vetnum;i++)//����������Ӧ�ľ�����Ϣ
    {
        printf("�����뾰����:");
        scanf("%d",&m->vets[i].number);
        printf("�����뾰������:");
        scanf("%s",&m->vets[i].name);
        scanf("�����뾰����:");
        scanf("%s",&m->vets[i].intro);
    }
    for(i=0;i<=m->vetnum;i++)//Ȩֵ��ʼ��Ϊ����
        for(j=0;j<=m->vetnum;j++)
            m->mat[i][j].wet=Infinity;
    printf("������ͼ�и�����ߵ���Ϣ \n");
    for(i=1;i<=m->sidenum;i++)
    {
        printf("\n�������%d���ߵ���㣬�յ㣬����Ϊ��",i);
        scanf("%d %d %d",&v0,&v1,&distance);
        l=locatevet(campus,v0);
        n=locatevet(campus,v1);
        if(l>0&&n>0)
        {
            m->mat[l][n].wet=distance;
            m->mat[n][l].wet=m->mat[l][n].wet;
        }
    }
    return 1;
}
//8.����ͼ������Ϣ
int newmap(mapstr *m)
{
    int changenum,i,l,n,t,distance,v0,v1;
    printf("\n������������Ҫ�޸ĵľ���ĸ�����\n");//�޸Ķ����Ӧ�ľ���
    scanf("%d",&changenum);
    while(changenum<0||changenum>vertex)
    {
        printf("\n���������������������");
        scanf("%d",&changenum);
    }
    for(i=0;i<changenum;i++)
    {
        printf("\n�����뾰���ţ�");
        scanf("&d",&l);
        t=locatevet(campus,l);
        printf("\n�������޸ĺ󾰵�����ƣ�");
        scanf("%s",&m->vets[t].name);
        printf("\n�������޸ĺ󾰵�ļ��:");
        scanf("%s",&m->vets[t].intro);
    }
    printf("\n������������Ҫ�޸ĵıߵĸ���");
    scanf("%d",&changenum);
    while(changenum<0||changenum>vertex);
    {
        printf("\n���������������������");
        scanf("%d",&changenum);
    }
    if(changenum!=0)
        printf("\n������������±ߵ���Ϣ��\n");
    for(i=1;i<=changenum;i++)
    {
        printf("\n�޸ĵĵ�%d���ߵ���� �յ� ����Ϊ:",i);
        scanf("%d %d %d",&v0,&v1,&distance);
        l=locatevet(campus,v0);
        n=locatevet(campus,v1);
        if(l>=0&&n>=0)
        {
            m->mat[l][n].wet=distance;
            m->mat[n][l].wet=m->mat[l][n].wet;
        }
    }
    return 1;
}
//9.����һ����
int incside(mapstr *m)
{
    int l,n,distance;
    printf("\n������ߵ������յ��ţ�Ȩֵ:");
    scanf("%d%d%d",&l,&n,&distance);
    while(l<0||l>m->vetnum||n<0||n>m->vetnum)
    {
        printf("�����������������");
        scanf("%d %d",&l,&n);
    }
    if(locatevet(campus,l)<0)
    {
        printf("�˽ڵ�%d��ɾ��",l);
        return 1;
    }
    if(locatevet(campus,n)<0)
    {
        printf("�˽ڵ�%d�ѱ�ɾ��",n);
        return 1;
    }
    m->mat[l][n].wet=distance;
    m->mat[n][l].wet=m->mat[l][n].wet;
    m->sidenum ++;
    return 1;
}
//10.����һ�����
int incvet(mapstr *m)
{
    int i;
    m->vetnum++;//��������һ
    printf("��������Ҫ���ӽ�����Ϣ��");
    printf("\n���:");
    scanf("%d",&m->vets[m->vetnum].number);
    printf("����:");
    scanf("%s",&m->vets[m->vetnum].name);
    printf("���:");
    scanf("%s",&m->vets[m->vetnum].intro);
    for(i=1;i<=m->vetnum;i++)
    {
        m->mat[m->vetnum][i].wet=Infinity;
        m->mat[i][m->vetnum].wet=Infinity;
    }
    return 1;
}
//11.ɾ��һ�����
int delvet(mapstr *m)
{
    int i=0,j,l,v;
    if(m->vetnum<=0)
    {
        printf("ͼ�����޶���");
        return 1;
    }
    printf("\n������������Ҫɾ���ľ����ţ�");
    scanf("%d",&v);
    while(v<0||v>m->vetnum)
    {
        printf("\n�����������������:");
        scanf("%d",&v);
    }
    l=locatevet(campus,v);
    if(l<0)
    {
        printf("����%d��ɾ��\n",v);
        return 1;
    }
    for(i=l;i<=m->vetnum-1;i++)
        for(j=1;j<=m->vetnum;j++)//����ά�����еĵ�m+1��������ǰ�ƶ�һ�У�ɾ����m�У�
            m->mat[i][j]=m->mat[i+1][j];
    for(i=l;i<=m->vetnum-1;i++)
        for(j=1;j<=m->vetnum;j++)//����ά�����еĵ�m+1��������ǰ�ƶ�һ�У�ɾ����m�У�
            m->mat[j][i]=m->mat[j][i+1];
    m->vets[v].number=-1;//��ʾ�˵���ɾ�������ڴ�ӡҲ������ʾ�õ�
    m->vetnum--;//�������-1
    return 1;
}
//12.ɾ��һ����
int delside(mapstr *m)
{
    int l,n,v0,v1;
    if(m->vetnum<=0)
    {
        printf("ͼ��û�б��ˣ��޷�ɾ��");
        return 1;
    }
    printf("\n������������Ҫɾ���ıߵ������յ��ţ�");
    scanf("%d %d",&v0,&v1);
    l=locatevet(campus,v0);
    if(m<0)
    {
        printf("��%d������ɾ��",v0);
        return 1;
    }
    n=locatevet(campus,v1);
    if(n<0)
    {
        printf("��%d������ɾ��",v1);
        return 1;
    }
    m->mat[l][n].wet=Infinity;//��ɾ���ıߵ�Ȩֵ��Ϊ����
    m->mat[n][l].wet=Infinity;
    m->sidenum--;//ͼ�ı�����һ
    return 1;
}
//13.���ͼ���ڽӾ����ֵ
void printmapstr(mapstr m)
{
    int i,j,k=0;
    for(i=1;i<=vertex;i++)
    {
        if(m.vets[i].number!=-1)
            printf("%6d",i);
    }
    printf("\n");
    for(i=1;i<=m.vetnum;i++)
    {
        for(j=1;j<=m.vetnum;j++)
        {
            if(m.mat[i][j].wet==Infinity)
                printf(" **** ");
            else
                printf("%6d",m.mat[i][j].wet);
            k++;
            if(k%m.vetnum==0)
                printf("\n");
        }
    }
}
//14.ͼ�Ĳ���������
int changemap(mapstr *m)
{
    int choice;
    printf("(1)���½�ͼ     (2)ɾ�����  (3)ɾ����\n");
    printf("(4)���ӽ��     (5)���ӱ�    (6)������Ϣ\n");
    printf("(7)����ڽӾ��� (8)������ҳ		\n");
    do
    {
        printf("���������ѡ��");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:creatmap(m);break;
            case 2:delvet(m);break;
            case 3:delside(m);break;
            case 4:incvet(m);break;
            case 5:incside(m);break;
            case 6:newmap(m);break;
            case 7:printmapstr(campus);break;
            case 8:system("cls");menu();return 1;
            default:printf("δ�ҵ��ù��ܣ���������Чѡ�\n");break;
        }
    }while(choice);
}
//15.�û���¼
int userlog()
{
    int i;
    int a[6]={1,2,3,4,5,6},b[6];
    printf("\n��������λ����(�ÿո����)��\n");
    for(i=0;i<6;i++)
        scanf("%d",&b[i]);
    for(i=0;i<6;i++)
    {
        if(a[i]!=b[i])
        {
            printf("��������Զ�������ҳ��\n");
            menu();
            return 0;
        }
    }
    printf("������ȷ����½�ɹ���\n\n");
    changemap(&campus);
}
//16.���������㷨
void floyd(mapstr m)
{
    int i,j,k;
    for(i=1;i<=vertex;i++)//��ͼ���ڽӾ���ֵ�� shortest��ά���飬������pathhȫ����ʼ��Ϊ-1
    {
        for(j=1;j<=vertex;j++)
        {
            shortest[i][j]=m.mat[i][j].wet;
            pathh[i][j]=j;
        }
    }
    int ii,jj,k1=0;
    for(ii=1;ii<=vertex;ii++)
        printf("%6d",ii);//���ű��1��11
    printf("\n");
    for(ii=1;ii<=vertex;ii++)
    {
        printf("%d",ii);
        for(jj=1;jj<=vertex;jj++)
        {
            printf("%6d",pathh[ii][jj]);
            k1++;
            if(k1%vertex==0)
                printf("\n");
        }
    }
    printf("\n\n\n");
    for(k=1;k<=vertex;k++)//���Ĳ������������kΪ�м������еĶ���ԣ�i,j�����м����޸�
    {	for(i=1;i<=vertex;i++)
        {	for(j=1;j<=vertex;j++)
            {
                if(shortest[i][j]>shortest[i][k]+shortest[k][j])
                {	shortest[i][j]=shortest[i][k]+shortest[k][j];
                    pathh[i][j]=pathh[i][k];//��¼һ�����ߵ�· //P�����������ǰ������
                }
            }
        }
    }
}
//17.�������
void printarray()
{
    int i,j,k=0;
    for(i=1;i<=vertex;i++)
        printf("%6d",i);//���ű��0-11
    printf("\n");
    for(i=0;i<=vertex;i++)
    {
        printf("%d",i);//���ű��0-11
        for(j=1;j<=vertex;j++)
        {
            printf("%6d",pathh[i][j]);
            k++;
            if(k%vertex==0)
                printf("\n");
        }
    }
    printf("\n\n\n");
}
//18.������·��
void display(mapstr m,int i,int j)
{
    int a,b;
    a=i,b=j;
    printf("��Ҫ��ѯ������������·����\n\n");
    printf("%d%s",a,m.vets[a].name);
    while(pathh[i][j]!=b)
    {
        printf("-->%d%s",pathh[i][j],m.vets[pathh[i][j]].name);
        i=pathh[i][j];
    }
    printf("-->%d%s\n\n",b,m.vets[b].name);
    printf("%s-->%s�����·���ǣ�%d��\n\n",m.vets[a].name,m.vets[b].name,shortest[a][b]);
}
//19�����������루16-19��
int shortdistance(mapstr m)
{
    int i,j;
    printf("������Ҫ��ѯ��������������ֱ��(�ÿո����)\n");
    scanf("%d %d",&i,&j);
    if(i<0||i>vertex||j<0||j>vertex)
    {
        printf("������Ϣ����\n\n");
        printf("������Ҫ��ѯ��������������ֱ��(�ÿո����)\n");
        scanf("%d %d",&i,&j);
    }
    else
    {
        floyd(m);
        printarray();
        display(m,i,j);
    }
    return 1;
}
//20��ʾ���о�����Ϣ
void compusinfor(mapstr m)
{
    int i;
    printf(" \n\n���     ��������                        ���\n");
    printf("*************************************************************************\n");
    for(i=1;i<=vertex;i++)
    {
        if(m.vets[i].number!=-1)
            printf("%-10d%-25s%-70s\n",m.vets[i].number,m.vets[i].name,m.vets[i].intro);
    }
    printf("*************************************************************************\n");
}
//21��ݸ��ѧԺ��ͼ
void schoolmap()
{
    printf(" ---------------------------------��ݸ��ѧԺ��ͼ----------------------------------------\n");
    printf("`````````````````````           ����             `````````````````````````````````````````\n");
    printf("````````````````````````````````````````````ݸ��``````````````````````````````````````````\n");
    printf("```````````````````````````````````````````````````````````````�³��㳡`````````````ݸܰ``````````\n");
    printf("````````````````````````````````````````````````````````````````````````````  �ڶ�����``````````\n");
    printf("`````���������```````````````````````````````````````````````````````````````````````````````\n");
    printf("``````````````````````������````` ����```````````````````````````````````````````````````````````````\n");
    printf("``````````````````````````````````````````````````````````````````�ٲ�����``````````\n");
    printf("````````````````````````````````````````````````````````````````````````````````````\n");
    printf("``````````````````````````````````````````````````````````````````````````````````````````\n");
    printf("``````````````````````````````````````````````````````````````````````````````````````````\n");
    printf("```````       `````````````````````````````````�����ú�`````````````````````````````\n");
    printf("         ```````````````````````````````````````````````````````````````````````````\n");
    printf("```````````````````````````````````````````````````````````````````````````����¥````````\n");
    printf("``````````````�Ƽ�¥``````````````````````````````````````````````````````````````````````\n");
    printf("``````````````��Ϣ¥```````````����¥`````�칫¥````��ѧ¥`````````````````�ľ�¥```````\n");
    printf("``````````````��ѧ¥``````````````````````ͼ���``````````````````````````````````````````\n");
    printf("``````````````````````````````````````````````````````````````````````````````````````````\n");
    printf("````````````````````````````````````````````````````````````````````````````````````\n");
    printf("\n\n");
    printf("\n 																		��<---|--->��     \n");
}
//22�û�����
void mainwork()
{
    menu();
    int choice;
    campus=initmap();
    do
    {
        printf("���������ѡ��");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:system("cls");menu();break;
            case 2:system("cls");shortestpath(campus);break;
            case 3:system("cls");shortdistance(campus);break;
            case 4:system("cls");allpath(campus);break;
            case 5:system("cls");compusinfor(campus);break;
            case 6:system("cls");schoolmap();break;
            case 7:system("cls");userlog();break;
            case 0:system("cls");printf("ллʹ��\n");break;
            default:printf("δ�ҵ��ù��ܣ���������Чѡ�\n");break;
        }
    }while(choice);
}
int main()
{
    mainwork();
    return 0;
}
