/*
 *  author:iris
 * date:2019/02/25
 * desc:计算数值小游戏
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

int add(int x, int y)
{
	int result = x + y;
	return result;
}

int sub(int x, int y)
{
	int result = x - y;
	return result;
}

int multiply(int x, int y)
{
        int result = x * y;
        return result;
}

int modulu(int x, int y)
{
        int result = x % y;
        return result;
}

int random(int a, int b)
{
	int result = ((double)rand()/RAND_MAX)*(b-a)+a;
	return result;
}

void interface(int step, int time_s, int time_us, int left_value, string way, int right_value)
{
	while(true)
	{
   	//system("clear");
   	cout << "步数：" << step << " \t";
        if (time_s > 0)
        {
     		cout << "用时：" << time_s
     			<< "." << time_us << "秒" << endl;
     	}
        else
        {
       		cout << "用时：" << time_us << "秒" << endl;
      	}
        cout << "**************************************" << endl;
	cout << left_value << way << right_value << endl; 
	cout << "答案为：";
	
	usleep(1000);//sleep0.1秒
	}
}


int main()
{
	string usr_name;
	int usr_guess;	// 用户猜的数字
	int ask_all = 0; //已回答总次数
	double usr_score = 0.0; //用户分数
	bool usr_status = false; //用户游戏状态

	//游戏参数
	const int max_time = 60; //设置游戏时间
        const int max_ask = 60; //最多答题数
        int left_value, right_value; //设置随机计算值
	//设置难度
	int smart_value=1, max_value=38;//设置最大最小随机计算值
	int method = 2, mskip = 5;//一开始设置为加减，答对第五道开启乘法取余
	int increase = 10, skip = 4; //每答对5道，最大随机值增加10
	int max_wait = 5; //设置等待最长秒数
        bool ask_status = true; //游戏可继续
	int score = 0; //游戏奖励分

        struct timeval start, newt, finish;//计时
        string way; //方法
        int time_s = 0, time_us, time_once, time_os; //时间差
        int elem; //预备要猜的值
        int step = 0; //游戏步数

	srand(time(NULL));
	
	system("clear");
	cout << "用户名：";
	cin >> usr_name;
	cout << "\t\t\t\t\t|你好，" << usr_name << "，游戏开始..." << endl;
	sleep(1);
	//游戏主体
	gettimeofday(&start, NULL);
	while (ask_status == true)
	{
		//游戏值
		left_value = random(smart_value, max_value);
                right_value = random(smart_value, max_value);
		usr_status = false;
		if (time_s > max_time)
		{
			cout << time_s << "s，";
			ask_status = false;
                        continue;
		}
                if (ask_all > max_ask)
                {
                        cout << "\t\t\t\t\t|恭喜您走到最后，是个高玩,";
                        ask_status = false;
                        continue;
                }
		
		if (step == mskip)
			method += 2;
		if (step % skip == 0 && step != 0)
			max_value += increase;
			if (skip > increase)
				skip += 1;
			else
				skip += 2;

                switch(rand() % method)
                {
                        case 0:
                                elem = add(left_value, right_value);
				way = '+';
                                break;
                        case 1:
                                elem = sub(left_value, right_value);
				way = '-';
                                break;
                        case 2:
                                elem = multiply(left_value, right_value);
				way = '*';
                                break;
                        case 3:
                                elem = modulu(left_value, right_value);
				way = '%';
                                break;
			//default:
		}
		//gettimeofday(&newt, NULL);
		
		// 等待玩家答题
		while(true)
                {
                        gettimeofday(&finish, NULL);
                        //time_all = (finish.tv_sec - start.tv_sec) * 100000
                        //         + (finish.tv_usec - start.tv_usec);
                        time_s = finish.tv_sec - start.tv_sec;
                        time_us = finish.tv_usec - start.tv_usec;

			if (time_us < 0)
			{
				time_s -= 1;
				time_us = time_us + 1000000;
			}
			time_os = time_s - time_once;
			if (time_os < 2)
			{
				score += 4;
			}

			system("clear");
			cout << "\n\n\n\n\n";
		        cout << "\t\t\t\t\t 步数：" << step << " \t";
			//cout << "上一步用时：" << time_s << "-" <<time_once << "\t";
			cout << "上一步用时：" << time_os << "\t";
		        if (time_s > 0)
	        	{
		               	cout << "总用时：" << time_s
                		        	<< "." << time_us << "秒" << endl;
		        }
		        else
        		{
        		        cout << "总用时：" << "0." << time_us << "秒" << endl;
        		}
		        cout << "\t\t\t\t\t******************************************************" << endl;
		        cout << "\t\t\t\t\t|" << left_value << way << right_value << endl;
		        cout << "\t\t\t\t\t|答案为：";

		        while(true)
		        {
				cin >> usr_guess;
				if (cin.fail())
				{
					cout << "\t\t\t\t\t|输入错误，请重新输入数字：" ;
					cin.clear();//输入错误，需重置failbit
					cin.ignore(); //取走输入流中的上一个字符
					continue;
	
				}
				else
				{
					usr_status = true;
					break;
				}
			}

			//time_once = (finish.tv_sec - newt.tv_sec) * 100000
			//         + (finish.tv_usec - newt.tv_usec);

			//time_os = time_once / 100000;
			if (time_s > max_time)
			{
				cout << "\t\t\t\t\t|游戏时间结束，您共花费" << time_os << "秒";
                                ask_status = false;
                                break;
			}

			if (time_os > max_wait)
			{
				//cout << "\t\t\t\t\t|上一道共花费" << time_s << "-"
				//	<< time_once << "=" << time_os << "秒，已超时，";
				cout << "\t\t\t\t\t|上一道共花费" << time_os << "秒，已超时，";
				ask_status = false;
				break;
			}
			if (usr_status == true)
			{
				break;
			}
			//usleep(1000);//sleep0.1秒

           	}
		time_once = time_s;
		ask_all += 1;
		// 判断值
		if (usr_guess != elem && ask_status != false)
		{
			cout << "\t\t\t\t\t|输入错误";
			ask_status = false;
		}

		if (ask_status == false)
			break;

		if (usr_guess == elem && method > 2)
		{
			score += 1;
		}

		step++;

	}
	usr_score = ask_all *100 - (time_s - ask_all) * 10 + score;
	cout << "游戏结束" << endl;
	cout << "\t\t\t\t\t|恭喜你，你总共回答了" 
	     << ask_all << "个问题\n\t\t\t\t\t|分数："
	     << usr_score << "。\n";
	return 0;

}


