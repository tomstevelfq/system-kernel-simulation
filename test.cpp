#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
#define N 100001
//算法类型（0:FCFS 1:RR），RR算法类型（0:时间片固定 1:可变）,进程数，时间片
int k, k_RR, n, q;

int now = 0; //当前时间
struct process
{
    int id; //编号
    int pos; //排序后的位置
    int arrive; //到达时间
    int work; //区间时间
    int begin; //开始时间
    int end; //完成时间
    int turnaround; //周转时间
    int wait; //等待时间
    bool in; //是否进入过就绪队列
    bool finish; //是否完成
    int rest; //剩余区间时间
    int block_p; //最近一次被阻塞的时间点
    int block_t; //阻塞时间长度
} proc[N];
queue <process> ready; //就绪队列
queue <process> block; //阻塞队列（RR）
queue <process> block_new; //(临时)新阻塞队列,用于阻塞队列的更新（RR）

bool cmp_FCFS(process a, process b)
{
    if (a.arrive != b.arrive)
        return a.arrive < b.arrive;
    else
        return a.id < b.id;
}

bool cmp_id(process a, process b)
{
    return a.id < b.id;
}

void init()
{
    cout << "请输入算法类型（0:FCFS 1:RR）：";
    cin >> k;
    cout << "请输入进程个数：";
    cin >> n;
    if (k == 1)
    {
        cout << "请输入时间片大小：";
        cin >> q;
        cout << "请输入RR算法类型（0:时间片固定 1:时间片可变）:";
        cin >> k_RR;
    }
    cout << "请按进程到达先后输入进程信息（1~n）：到达时间 区间时间" <<
        endl; //要求按到达先后顺序输入，以便于到达时间相同时判断先后
    for (int i = 1; i <= n; i++)
    {
        cout << "进程" << i << ":";
        cin >> proc[i].arrive >> proc[i].work;
        //信息初始化
        proc[i].id = i;
        proc[i].in = 0;
        proc[i].begin = -1; //表示还没开始
        proc[i].finish = 0;
        proc[i].block_t = 0;
        proc[i].rest = proc[i].work;
    }
    sort(proc, proc + n + 1, cmp_FCFS);
    for (int i = 1; i <= n; i++)
    {
        proc[i].pos = i;
    }
}

void block_check() //查看阻塞队列中是否有进程被唤醒
{
    while (!block.empty()) //遍历旧阻塞队列一次
    {
        process t2 = block.front();
        block.pop();
        if (t2.block_p != now) //如果不是刚被阻塞，则有唤醒的可能
        {
            if (rand() % 2) //设定阻塞进程有1/2的概率被唤醒
            {
                t2.block_t += (now - t2.block_p); //更新阻塞时长
                cout << "在时刻" << now << "，进程" << t2.id << "被唤醒" << endl;
                ready.push(t2);
            }
            else //仍被阻塞，入新阻塞队列
            {
                block_new.push(t2);
            }
        }
        else //刚被阻塞，入新阻塞队列
        {
            block_new.push(t2);
        }
    }
    block = block_new; //阻塞队列更新
    while (!block_new.empty()) //清空临时的阻塞队列
    {
        block_new.pop();
    }
}

void FCFS_And_RR()
{
    srand((unsigned int)(time(0))); //随机数生成种子随系统时间变化
    int left = n; //剩余的未完成进程数
    int once_max; //一个进程最大连续运行时间
    int once; //记录一个进程一次的运行时间
    while (left > 0) //有进程没有完成
    {
        int min_arrive = 0x3f3f3f; //未到达进程的最小到达时间（可能有多个进程）
        int in_flag = 0; //当前时间是否有进程入就绪队列
        for (int i = 1; i <= n; i++)
        {
            if (!proc[i].in && proc[i].arrive < min_arrive)
            {
                min_arrive = proc[i].arrive;
                in_flag = 1;
            }
        }
        if (min_arrive >= now && in_flag)
        {
            //若当前时间小于剩余未完成进程（存在时in_flag=1）的最小到达时间，则输出以下信息并更新值
            if (min_arrive > now)
                cout << "在时间" << now << "-" << min_arrive << "内,没有进程在运行" << endl;
            now = min_arrive;
            for (int i = 1; i <= n; i++)
            {
                if (proc[i].arrive == min_arrive)
                {
                    proc[i].in = 1;
                    ready.push(proc[i]);
                }
            }
        }
        if (!ready.empty())
        {
            process t = ready.front(); //取出就绪队列队首
            ready.pop();
            if (t.begin == -1) //如果是第一次出就绪队列
            {
                t.begin = now; //开始时间=当前时间
            }
            if (k == 0) //FCFS
            {
                once_max = t.rest; //一个进程单次最大运行时间为剩余区间时间（即不发生阻塞的情况）
            }
            else //RR
            {
                once_max = min(q, t.rest);
                //一个进程单次最大运行时间为时间片长度和剩余区间时间的相比较的最小值
            }
            once = 0;
            while (once < once_max) //一个进程运行中
            {
                now++; //当前时间加1
                once++; //单次进程运行时间加1
                t.rest--; //剩余时间减1
                for (int i = 1; i <= n; i++) //遍历所有进程
                {
                    if (!proc[i].in && proc[i].arrive == now) //若有进程还没有进入过就绪队列，且当前到达
                    {
                        proc[i].in = 1; //更改标记
                        ready.push(proc[i]); //进入就绪队列
                    }
                }
                block_check(); //查看阻塞队列中是否有进程被唤醒
                if (rand() % 10 == 0 && t.rest != 0) //设定当前进程单位时间有1/10的概率发生阻塞
                {
                    t.block_p = now; //更新最近一次被阻塞的时间点
                    block.push(t); //阻塞，入阻塞队列队尾
                    break;
                }
            }
            if (t.rest > 0) //剩余时间大于0
            {
                cout << "在时间" << now - once << "-" << now << "内,进程" << t.id << "在运行";
                if (t.block_p == now) //说明阻塞
                {
                    cout << ",后阻塞";
                }
                else //没阻塞则入就绪队列
                {
                    ready.push(t);
                }
                cout << endl;
            }
            else //剩余时间等于0，表示运行完成
            {
                cout << "在时间" << now - once << "-" << now << "内,进程" << t.id << "在运行。该进程完成。" << endl;
                t.end = now; //完成时间=当前时间
                t.finish = 1; //更新标记：已完成
                t.turnaround = t.end - t.arrive; //周转时间=完成时间-到达时间
                t.wait = t.turnaround - t.work - t.block_t; //等待时间=周转时间-区间时间-阻塞时间
                proc[t.pos] = t; //更新（已完成的）进程信息
                left--; //剩余进程数减1
                if (k == 1 && k_RR == 1) //时间片可变的RR算法
                {
                    q = ((double)n / left) * q;
                }
            }
        }
        else //可能当就绪队列为空时，也有进程在阻塞队列
        {
            int in_block = 0; //停留在阻塞队列的时间
            while (1)
            {
                block_check();//查看阻塞队列中是否有进程被唤醒
                if (left == block.size() && left > 0) //如果未完成的进程都在阻塞队列里
                {
                    in_block++; //更新停留在阻塞队列的时间，继续进行循环
                    now++;
                }
                else
                {
                    break; //否则只进行一次遍历，因为还有其他没有在阻塞队列的进程
                }
            }
            if (in_block > 0) //只剩阻塞队列中的进程，且没运行，输出信息
            {
                cout << "在时间" << now - in_block << "-" << now << "内,没有进程在运行" << endl;
            }
        }
    }
}

//输出结果
void display()
{
    sort(proc, proc + n + 1, cmp_id);
    cout << "所有进程已完成，结果如下：" << endl;
    cout << setw(8) << "进程编号" << setw(10) << "到达时间" << setw(10) << "区间时间" << setw(10) << "开始时间" << setw(
        10) << "完成时间" << setw(10) << "周转时间" << setw(10) << "等待时间" << setw(10) << "阻塞时间";
    cout << endl;
    int sum_work = 0, sum_turnaround = 0, sum_wait = 0, sum_block = 0;
    //总区间（服务）时间，总周转时间，总等待时间，平均阻塞时间
    for (int i = 1; i <= n; i++)
    {
        sum_work += proc[i].work;
        sum_turnaround += proc[i].turnaround;
        sum_block += proc[i].block_t;
        sum_wait += proc[i].wait;
        cout << left << setw(10) << proc[i].id << setw(10) << proc[i].arrive << setw(10) << proc[i].work << setw(10) << proc[i].begin << setw(10) << proc[i].end << setw(10) << proc[i].turnaround << setw(10) << proc[i].wait << setw(10) << proc[i].block_t << endl;
    }
    cout << "平均周转时间：" << (double)sum_turnaround / n << endl;
    cout << "平均带权周转时间：" << (double)sum_turnaround / sum_work / n << endl;
    cout << "平均等待时间：" << (double)sum_wait / n << endl;
    cout << "平均阻塞时间：" << (double)sum_block / n << endl;
    return;
}

int main()
{
    init();
    FCFS_And_RR();
    display();
    return 0;
}