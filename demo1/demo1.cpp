/*
 *  author:iris
 *  date:2019/02/20
 *  desc:猜费氏数列小游戏
 */



#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string usr_name;
	int usr_guess;	// 用户猜的数字
	int ask_all = 0; //已回答总次数
	int ask_right = 0; //用户答对次数
	int ask_wrong = 0; //用户答错次数
	int try_wrong = 0; //用户连续答题次数
	double usr_score = 0.0; //用户分数
	char usr_try = 'Y'; //用户想继续
	bool usr_again = true; //用户可继续
	bool usr_status = true; //用户游戏状态

	//游戏参数
	const int max_repeat = 3; //最多重复答题次数
	const int max_wrong = 5; //设置最多答错次数
	const int max_ask = 11; //设置最多总答题数
	int elem; //预备要猜的值
	int step = 0; //游戏步数
	bool ask_status = true; //游戏可继续

	//游戏值	
	const int seq_size = 10; //定义组内存储题的个数
	vector<int> pell_seq(seq_size, 0);//声明组

	pell_seq[0] = 1;
	pell_seq[1] = 2;
	cout << pell_seq[0] << ',' << pell_seq[1] << ',';
	for(int i=2; i<seq_size; ++i)
	{
		pell_seq[i] = pell_seq[i-2] + 2*pell_seq[i-1];
		cout << pell_seq[i] << ','; //打印出数列，测试用，可注释掉
	}
	cout << endl;

	cout << "游戏开始..." << endl;
	//游戏主体
	while (ask_status)
	{
		if (ask_all > max_ask)
		{
			cout << "答题次数已达上限,";
			ask_status = false;
			continue;
		}
		if (step > seq_size)
		{
			cout << "恭喜您走到最后，是个高玩,";
			ask_status = false;
                        continue;
		}
		// 展示前两个参数
		cout << "********************************\n";
		cout << step  << ':' << pell_seq[step] << '\n';
		cout << step+1 << ':' << pell_seq[step+1] << '\n';
		elem = pell_seq[step+2];
		// 用户输入
		cout << "下一个数字为：";
		//cout << ask_all << "下一个数字为：";
		int wrong_time = 0;
		while(usr_status == true)
		{
			cin >> usr_guess;
			if (cin.fail())
			{
				//cout<<"cin.fail()="<<cin.fail()<<endl;
				if (wrong_time < 1)
				{
					cout << "输入错误，请重新输入数字：" ;
				}
				else
				{
					cout << "不要开玩笑了，请输入数字吧：" ;
				}
				cin.clear();//输入错误，failbit为1，将failbit重置为0
				cin.ignore(); //取走输入流中的上一个字符
				wrong_time += 1;
				continue;
			}
			else
			{
				//cout << "cin.fail()=" << cin.fail() << endl;
				break;
			}
		}

		ask_all += 1;
		// 判断值
		if (usr_guess == elem)
		{
			usr_again = true;
			ask_right += 1;
		}
		else
		{
			usr_again = false;
			ask_wrong += 1;
		}
		// 用户答错
		if (usr_again == false)
		{
			//判断游戏是否可继续
			if (ask_wrong > max_wrong)
			{
				cout << "回答错误数已达上限,";
				ask_status = false;
				continue;
			}
			cout << "答错了，还想要再尝试一次吗?（Y/N）：";
			try_wrong = 0;
		}
		// 用户输入参数错误
		while (usr_again == false)
		{
			cin >> usr_try;		
			if (usr_try == 'N' || usr_try == 'n')
			{
				usr_status = false;
				ask_status = false;
				cout << "好的，即将退出游戏。" << endl;
				break;
			}
			else if (usr_try == 'Y' || usr_try == 'y')
			{
				usr_status = true;
				ask_status = true;
				//cout << usr_guess << "\t" << usr_again << '\n';
				cout << "坚持才是胜利。" << endl;
				break;
			}
			else
			{
				cout << "输入错误，只能选择Y/N或者y/n：";
			}
		}
		// 用户猜错了，但选择继续
		while ((usr_status == true && usr_again != true))
		{
			if (try_wrong >= max_repeat)
			{
				cout << "\n您已连续答错" << try_wrong << "次，";
				cout << "超过"<< max_repeat << "次\n";
				ask_status = false;
				break;
			}
			cout << "请输入准确答案：";
			//cout << ask_all << "请输入准确答案：";
			cin >> usr_guess;
			if (usr_guess == elem)
			{
				if (try_wrong == 0)
				{
					ask_wrong -= 1;
					ask_right += 1;
					ask_all += 1;
					cout << "恭喜，你答对了，再加一分" << endl;
					usr_again = true;
					break;
				}
				else if (try_wrong == 1)
				{
					//ask_wrong -= 1;
					ask_all += 1;
                                        cout << "你总算对了，本次回答不加分" << endl;
					try_wrong = 0;
					usr_again = true;
                                        break;
				}
				else
				{
					cout << "终于答对了，你的错题数已经有"
					     << ask_wrong << "个了， 超过" 
					     << max_wrong << "个就结束游戏了哟" << endl;
					ask_all += 1;
					try_wrong = 0;
					usr_again = true;
					break;
				}
			
			}
			else
			{
				try_wrong += 1;
				ask_wrong += 1;
				ask_all += 1;
				cout << "本轮答错，请再重新来吧\n";
			}
		}
		if (ask_status == false)
			break;

		step++;

	}
	usr_score = (float(ask_right) / ask_all) * 100;
	cout << "游戏结束" << endl;
	cout << "恭喜你，你总共回答了" 
	     << ask_all << "个问题\n其中答对了"
	     << ask_right << "个问题， 分数为："
	     << usr_score << "分。\n";
	return 0;

}
