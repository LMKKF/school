//青岛农业大学校园管理系统
//完整源代码
//2021/10/6
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Infinity 65535	//表示无穷大
#define MaxNumber 23	//用于邻接矩阵
#define vertex 15	//顶点个数
typedef struct side//边的权值
{
    int wet;//权值
}side,wetmatrix[MaxNumber][MaxNumber];//边的邻接矩阵类型
typedef struct vetinf//顶点信息
{
    int number;//顶点编号
    char name[64];//顶点名称
    char intro[256];//顶点介绍
}vetinf;
typedef struct mapstr//图结构信息
{
    vetinf vets[MaxNumber];//顶点数组
    wetmatrix mat;//邻接矩阵
    int vetnum,sidenum;
}mapstr;
//全局变量
mapstr campus;//图结构变量（学校校园）
int d[30];
int visited[50];
int shortest[MaxNumber][MaxNumber];//定义全局变量存储最小路径
int pathh[MaxNumber][MaxNumber];//定义存储路径
//1.图的初始化
mapstr initmap()
{
    mapstr m;//构件图m
    int i=0,j=0;
    m.vetnum=15;//定义顶点个数
    m.sidenum=23;//定义边的条数
    for (i=1;i<=vertex;i++)//依次设置顶点信息
        m.vets[i].number=i;
    //输入顶点信息
    strcpy(m.vets[1].name,"莞逸社区");strcpy(m.vets[1].intro,"靠近北门，学生住宿场所");
    strcpy(m.vets[2].name,"第一饭堂");strcpy(m.vets[2].intro,"为学生提供就餐场所");
    strcpy(m.vets[3].name,"西一路");strcpy(m.vets[3].intro,"连接北门与南门，经过假草足球场和篮球场");
    strcpy(m.vets[4].name,"体育馆");strcpy(m.vets[4].intro,"学校举办文体活动的场所");
    strcpy(m.vets[5].name,"假草足球场");strcpy(m.vets[5].intro,"五环体育场");
    strcpy(m.vets[6].name,"莞馨宿舍");strcpy(m.vets[6].intro,"女生住宿场所");
    strcpy(m.vets[7].name,"第三饭堂餐厅");strcpy(m.vets[7].intro,"靠近东门和莞馨社区，就餐场所");
    strcpy(m.vets[8].name,"松仔岭");strcpy(m.vets[8].intro,"在这里可以欣赏到学校的一处优美的景色");
    strcpy(m.vets[9].name,"大礼堂前湖");strcpy(m.vets[9].intro,"学校的湖，景色优美");
    strcpy(m.vets[10].name,"真草足球场");strcpy(m.vets[10].intro,"位于学校最西端，为学生踢球场所");
    strcpy(m.vets[11].name,"生态环境工程技术研发中心");strcpy(m.vets[11].intro,"这里有学校的科技楼,化学楼");
    strcpy(m.vets[12].name,"办公楼图书馆生物楼");strcpy(m.vets[12].intro,"这里有学校的办公楼,图书馆,生物楼");
    strcpy(m.vets[13].name,"教学楼");strcpy(m.vets[13].intro,"学生学习的场所");
    strcpy(m.vets[14].name,"工程楼,文经楼");strcpy(m.vets[14].intro,"这里有学校的工程楼,文经楼");
    strcpy(m.vets[15].name,"下沉广场");strcpy(m.vets[15].intro,"大超门口，举办各种活动的地方");
    for (i=1;i<=vertex;i++)
        for (j=1;j<=vertex;j++)
            m.mat[i][j].wet=Infinity;//初始化图的邻接矩阵
    m.mat[1][2].wet=10;m.mat[2][3].wet=40;m.mat[3][4].wet=20;m.mat[3][8].wet=40;m.mat[3][11].wet=40;
    m.mat[4][5].wet=20;m.mat[4][8].wet=20;m.mat[5][6].wet=30;m.mat[5][8].wet=30;m.mat[6][7].wet=10;
    m.mat[6][9].wet=70;m.mat[7][9].wet=60;m.mat[7][10].wet=40;m.mat[8][9].wet=10;m.mat[9][10].wet=30;
    m.mat[9][13].wet=15;m.mat[9][14].wet=30;m.mat[10][14].wet=10;m.mat[11][12].wet=50;m.mat[11][15].wet=70;
    m.mat[12][13].wet=5;m.mat[12][15].wet=10;m.mat[13][14].wet=40;
    for(i=1;i<=vertex;i++)//无向带权图是对称矩阵,给其另一半赋值
        for(j=1;j<=vertex;j++)
            m.mat[j][i].wet=m.mat[i][j].wet;
    return m;
}
//2.查询景点在图中的序号
int locatevet(mapstr m,int v)
{
    int i;
    for(i=0;i<=m.vetnum;i++)
        if(v==m.vets[i].number) return i;//找到返回顶点i
    return -1;//未找到
}
//3.查询输入序号l,n间的长度不超过10个景点的路径
void path(mapstr m,int l,int n,int k)
{
    int s,t=k+1;int length=0;//t用于存储路径上下一顶点对应的d[]数组元素的下标
    if(d[k]==n&&k<8)//若d[k]是终点且景点个数<8，则输出该路径
    {
        for(s=0;s<k;s++)
        {
            length=length+m.mat[d[s]][d[s+1]].wet;
        }
        if(length<200)//打印路径小于200（定长）的路径
        {
            for(s=0;s<k;s++)//输出该路径，s=0时为起点m
            {
                printf("%d%s--->",d[s],m.vets[d[s]].name);
            }
            printf("%d%s  ",d[s],m.vets[d[s]].name);//输出最后一个顶点
            printf("总路线长为%d米\n\n",length);
        }
    }
    else
    {
        s=1;
        while(s<=m.vetnum)//从第m个顶点，访问所有顶点是否有路径
        {
            if((m.mat[d[k]][s].wet<Infinity)&&(visited[s]==0))//顶点有边且未被访问
            {
                visited[s]=1;
                d[k+1]=s;//存储顶点编号
                path(m,l,n,t);
                visited[s]=0;//将找到的路径上的顶点的访问标志重新设置为，便于探究新的路径
            }
            s++;//试验下一顶点s开始是否有到终点的路径；
        }
    }
}
//4.查询两景点的所有路径
int allpath(mapstr m)
{
    int k,i,j,l,n;
    printf("\n\n请输入您想要查询的两个景点的编号：\n\n");
    scanf("%d%d",&i,&j);printf("\n\n");
    l=locatevet(m,i);//locatevet 确定该顶点是否存在。若存在，返回该顶点编号。
    n=locatevet(m,j);
    d[0]=l;//路径起点l(字母).(d[]数组为全局变量)
    for(k=0;k<vertex;k++)
        visited[k]=0;
    visited[l]=1;
    path(m,l,n,0);
    return 1;
}
//5.迪杰斯特拉算法求单源最短路径
void shortestpath(mapstr m)
{
    int v0,v,w,k=1,min,t,p;
    int final[MaxNumber];//final[w]=1表示已经求得顶点V0到Vw的的最短路径
    int Pathside[MaxNumber];//用于存储最短路径下标的数组
    int ShortPathwet[MaxNumber];//用于存储到各点最短路径的权值和
    printf("\n请输入起始景点的编号：");
    scanf("%d",&v0);
    printf("\n\n");
    while(v0<0||v0>vertex)//判断是否输入正确
    {
        printf("\n您输入的景点编号不存在\n");
        printf("请重新输入：");
        scanf("%d",&v0);
    }
    for(v=1;v<=m.vetnum;v++)//数组初始化
    {
        final[v]=0;//全部顶点初始化为未找到路径
        ShortPathwet[v]=m.mat[v0][v].wet;//将与v0有连线的路径加上权值
        Pathside[v]=0;//初始化路径数组为0
    }
    ShortPathwet[v0]=0;
    final[v0]=1;
    //Dijkstr算法主体
    for(v=1;v<=m.vetnum;v++)
    {
        min=Infinity;
        for(w=1;w<=m.vetnum;w++)//找出离当前指向顶点最近的点
        {
            if(!final[w]&&ShortPathwet[w]<min)//未被访问且存在边
            {
                k=w;
                min=ShortPathwet[w];
            }
        }
        final[k]=1;//将找到的离当前顶点最近的置1
        //修正
        for(w=1;w<=m.vetnum;w++)
        {
            if(!final[w]&&(min+m.mat[k][w].wet<ShortPathwet[w]))
            {
                ShortPathwet[w]=min+m.mat[k][w].wet;//修改当前最优路径长度
                Pathside[w]=k;//存放前驱结点
            }
        }
    }
    printf("打印P数组:");	 //打印p数组
    for(t=1;t<=m.vetnum;t++)
    {
        printf("%d ",Pathside[t]);
    }
    printf("\n\n");
    printf("打印S数组:");	 //打印s数组
    for(t=1;t<=m.vetnum;t++)
    {
        printf("%d ",ShortPathwet[t]);
    }
    printf("\n\n");
    //打印最短路径
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
            printf("\n总路线长为%d米\n\n",ShortPathwet[t]);
        }
    }
}
//6.主页
void menu()
{	printf(" ┌──────────────────────────────────────────────────────┐\n");
    printf(" │ ╭ ═══════════════════════════════════════════════ ╮   │\n");
    printf(" │ ││        欢 迎 使 用 校 园 导 游 系 统          ││  │\n");
    printf(" │ ╰ ═══════════════════════════════════════════════ ╯   │\n");
    printf(" │                       欢迎来到                         │\n");
    printf(" │                      东莞理工学院                       │\n");
    printf(" │                      菜 单 选 择                       │\n");
    printf(" │  *************************************************** │\n");
    printf(" │  *  1.主页                **   2.查看游览路线      *     │\n");
    printf(" │  *************************************************** │\n");
    printf(" │  *  3.查询景点间最短路径  **   4.查询景点间所有路径*        │\n");
    printf(" │  *************************************************** │\n");
    printf(" │  *  5.学校景点介绍        **   6.学校地图          * │\n");
    printf(" │  *************************************************** │\n");
    printf(" │  *  7.更改图信息          **   0.退出              * │\n");
    printf(" │  *************************************************** │\n");
    printf(" └──────────────────────────────────────────────────────┘\n");
}
//以下是修改图的相关信息。
//7.重新构造图
int creatmap(mapstr *m)
{
    int i,j,l,n,v0,v1,distance;
    printf("请输入图的顶点数和边数:\n");
    scanf("%d %d",&m->vetnum,&m->sidenum);
    printf("请输入顶点信息: \n");
    for(i=0;i<=m->vetnum;i++)//输入各顶点对应的景点信息
    {
        printf("请输入景点编号:");
        scanf("%d",&m->vets[i].number);
        printf("请输入景点名称:");
        scanf("%s",&m->vets[i].name);
        scanf("请输入景点简介:");
        scanf("%s",&m->vets[i].intro);
    }
    for(i=0;i<=m->vetnum;i++)//权值初始化为无穷
        for(j=0;j<=m->vetnum;j++)
            m->mat[i][j].wet=Infinity;
    printf("请输入图中各景点边的信息 \n");
    for(i=1;i<=m->sidenum;i++)
    {
        printf("\n请输入第%d条边的起点，终点，长度为：",i);
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
//8.更改图部分信息
int newmap(mapstr *m)
{
    int changenum,i,l,n,t,distance,v0,v1;
    printf("\n下面请输入你要修改的景点的个数：\n");//修改定点对应的景点
    scanf("%d",&changenum);
    while(changenum<0||changenum>vertex)
    {
        printf("\n你的输入有误，请重新输入");
        scanf("%d",&changenum);
    }
    for(i=0;i<changenum;i++)
    {
        printf("\n请输入景点编号：");
        scanf("&d",&l);
        t=locatevet(campus,l);
        printf("\n请输入修改后景点的名称：");
        scanf("%s",&m->vets[t].name);
        printf("\n请输入修改后景点的简介:");
        scanf("%s",&m->vets[t].intro);
    }
    printf("\n下面请输入你要修改的边的个数");
    scanf("%d",&changenum);
    while(changenum<0||changenum>vertex);
    {
        printf("\n你的输入有误，请重新输入");
        scanf("%d",&changenum);
    }
    if(changenum!=0)
        printf("\n下面请输入更新边的信息：\n");
    for(i=1;i<=changenum;i++)
    {
        printf("\n修改的第%d条边的起点 终点 长度为:",i);
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
//9.增加一条边
int incside(mapstr *m)
{
    int l,n,distance;
    printf("\n请输入边的起点和终点编号，权值:");
    scanf("%d%d%d",&l,&n,&distance);
    while(l<0||l>m->vetnum||n<0||n>m->vetnum)
    {
        printf("输入错误，请重新输入");
        scanf("%d %d",&l,&n);
    }
    if(locatevet(campus,l)<0)
    {
        printf("此节点%d已删除",l);
        return 1;
    }
    if(locatevet(campus,n)<0)
    {
        printf("此节点%d已被删除",n);
        return 1;
    }
    m->mat[l][n].wet=distance;
    m->mat[n][l].wet=m->mat[l][n].wet;
    m->sidenum ++;
    return 1;
}
//10.增加一个结点
int incvet(mapstr *m)
{
    int i;
    m->vetnum++;//顶点数加一
    printf("请输入您要增加结点的信息：");
    printf("\n编号:");
    scanf("%d",&m->vets[m->vetnum].number);
    printf("名称:");
    scanf("%s",&m->vets[m->vetnum].name);
    printf("简介:");
    scanf("%s",&m->vets[m->vetnum].intro);
    for(i=1;i<=m->vetnum;i++)
    {
        m->mat[m->vetnum][i].wet=Infinity;
        m->mat[i][m->vetnum].wet=Infinity;
    }
    return 1;
}
//11.删除一个结点
int delvet(mapstr *m)
{
    int i=0,j,l,v;
    if(m->vetnum<=0)
    {
        printf("图中已无顶点");
        return 1;
    }
    printf("\n下面请输入您要删除的景点编号：");
    scanf("%d",&v);
    while(v<0||v>m->vetnum)
    {
        printf("\n输入错误！请重新输入:");
        scanf("%d",&v);
    }
    l=locatevet(campus,v);
    if(l<0)
    {
        printf("顶点%d已删除\n",v);
        return 1;
    }
    for(i=l;i<=m->vetnum-1;i++)
        for(j=1;j<=m->vetnum;j++)//将二维数组中的第m+1行依次向前移动一行（删除第m行）
            m->mat[i][j]=m->mat[i+1][j];
    for(i=l;i<=m->vetnum-1;i++)
        for(j=1;j<=m->vetnum;j++)//将二维数组中的第m+1列依次向前移动一列（删除第m列）
            m->mat[j][i]=m->mat[j][i+1];
    m->vets[v].number=-1;//表示此点已删除，后期打印也不会显示该点
    m->vetnum--;//顶点个数-1
    return 1;
}
//12.删除一条边
int delside(mapstr *m)
{
    int l,n,v0,v1;
    if(m->vetnum<=0)
    {
        printf("图中没有边了，无法删除");
        return 1;
    }
    printf("\n下面请输入您要删除的边的起点和终点编号：");
    scanf("%d %d",&v0,&v1);
    l=locatevet(campus,v0);
    if(m<0)
    {
        printf("此%d顶点已删除",v0);
        return 1;
    }
    n=locatevet(campus,v1);
    if(n<0)
    {
        printf("此%d顶点已删除",v1);
        return 1;
    }
    m->mat[l][n].wet=Infinity;//将删掉的边的权值改为无穷
    m->mat[n][l].wet=Infinity;
    m->sidenum--;//图的边数减一
    return 1;
}
//13.输出图的邻接矩阵的值
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
//14.图的操作主函数
int changemap(mapstr *m)
{
    int choice;
    printf("(1)重新建图     (2)删除结点  (3)删除边\n");
    printf("(4)增加结点     (5)增加边    (6)更新信息\n");
    printf("(7)输出邻接矩阵 (8)返回主页		\n");
    do
    {
        printf("请输入你的选择：");
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
            default:printf("未找到该功能，请输入有效选项！\n");break;
        }
    }while(choice);
}
//15.用户登录
int userlog()
{
    int i;
    int a[6]={1,2,3,4,5,6},b[6];
    printf("\n请输入六位密码(用空格隔开)：\n");
    for(i=0;i<6;i++)
        scanf("%d",&b[i]);
    for(i=0;i<6;i++)
    {
        if(a[i]!=b[i])
        {
            printf("密码错误！自动返回主页面\n");
            menu();
            return 0;
        }
    }
    printf("密码正确，登陆成功！\n\n");
    changemap(&campus);
}
//16.弗洛伊德算法
void floyd(mapstr m)
{
    int i,j,k;
    for(i=1;i<=vertex;i++)//将图的邻接矩阵赋值给 shortest二维数组，将矩阵pathh全部初始化为-1
    {
        for(j=1;j<=vertex;j++)
        {
            shortest[i][j]=m.mat[i][j].wet;
            pathh[i][j]=j;
        }
    }
    int ii,jj,k1=0;
    for(ii=1;ii<=vertex;ii++)
        printf("%6d",ii);//横着标号1到11
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
    for(k=1;k<=vertex;k++)//核心操作，完成了以k为中间点对所有的顶点对（i,j）进行检测和修改
    {	for(i=1;i<=vertex;i++)
        {	for(j=1;j<=vertex;j++)
            {
                if(shortest[i][j]>shortest[i][k]+shortest[k][j])
                {	shortest[i][j]=shortest[i][k]+shortest[k][j];
                    pathh[i][j]=pathh[i][k];//记录一下所走的路 //P数组用来存放前驱顶点
                }
            }
        }
    }
}
//17.输出数组
void printarray()
{
    int i,j,k=0;
    for(i=1;i<=vertex;i++)
        printf("%6d",i);//横着标号0-11
    printf("\n");
    for(i=0;i<=vertex;i++)
    {
        printf("%d",i);//竖着标号0-11
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
//18.输出最短路径
void display(mapstr m,int i,int j)
{
    int a,b;
    a=i,b=j;
    printf("您要查询的两景点间最短路径：\n\n");
    printf("%d%s",a,m.vets[a].name);
    while(pathh[i][j]!=b)
    {
        printf("-->%d%s",pathh[i][j],m.vets[pathh[i][j]].name);
        i=pathh[i][j];
    }
    printf("-->%d%s\n\n",b,m.vets[b].name);
    printf("%s-->%s的最短路径是：%d米\n\n",m.vets[a].name,m.vets[b].name,shortest[a][b]);
}
//19任意两点间距离（16-19）
int shortdistance(mapstr m)
{
    int i,j;
    printf("请输入要查询的两个景点的数字编号(用空格隔开)\n");
    scanf("%d %d",&i,&j);
    if(i<0||i>vertex||j<0||j>vertex)
    {
        printf("输入信息有误！\n\n");
        printf("请输入要查询的两个景点的数字编号(用空格隔开)\n");
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
//20显示所有景点信息
void compusinfor(mapstr m)
{
    int i;
    printf(" \n\n编号     景点名称                        简介\n");
    printf("*************************************************************************\n");
    for(i=1;i<=vertex;i++)
    {
        if(m.vets[i].number!=-1)
            printf("%-10d%-25s%-70s\n",m.vets[i].number,m.vets[i].name,m.vets[i].intro);
    }
    printf("*************************************************************************\n");
}
//21东莞理工学院地图
void schoolmap()
{
    printf(" ---------------------------------东莞理工学院地图----------------------------------------\n");
    printf("`````````````````````           北门             `````````````````````````````````````````\n");
    printf("````````````````````````````````````````````莞逸``````````````````````````````````````````\n");
    printf("```````````````````````````````````````````````````````````````下沉广场`````````````莞馨``````````\n");
    printf("````````````````````````````````````````````````````````````````````````````  第二餐厅``````````\n");
    printf("`````真草体育场```````````````````````````````````````````````````````````````````````````````\n");
    printf("``````````````````````体育馆````` 篮球场```````````````````````````````````````````````````````````````\n");
    printf("``````````````````````````````````````````````````````````````````假草足球场``````````\n");
    printf("````````````````````````````````````````````````````````````````````````````````````\n");
    printf("``````````````````````````````````````````````````````````````````````````````````````````\n");
    printf("``````````````````````````````````````````````````````````````````````````````````````````\n");
    printf("```````       `````````````````````````````````大礼堂湖`````````````````````````````\n");
    printf("         ```````````````````````````````````````````````````````````````````````````\n");
    printf("```````````````````````````````````````````````````````````````````````````工程楼````````\n");
    printf("``````````````科技楼``````````````````````````````````````````````````````````````````````\n");
    printf("``````````````信息楼```````````生物楼`````办公楼````教学楼`````````````````文经楼```````\n");
    printf("``````````````化学楼``````````````````````图书馆``````````````````````````````````````````\n");
    printf("``````````````````````````````````````````````````````````````````````````````````````````\n");
    printf("````````````````````````````````````````````````````````````````````````````````````\n");
    printf("\n\n");
    printf("\n 																		西<---|--->东     \n");
}
//22用户界面
void mainwork()
{
    menu();
    int choice;
    campus=initmap();
    do
    {
        printf("请输入你的选择：");
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
            case 0:system("cls");printf("谢谢使用\n");break;
            default:printf("未找到该功能，请输入有效选项！\n");break;
        }
    }while(choice);
}
int main()
{
    mainwork();
    return 0;
}
