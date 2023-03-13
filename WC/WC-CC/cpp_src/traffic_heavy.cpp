#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include <typeinfo>

using namespace std;

double Mtime[900] = {0.0};
double exetime2_1[10000] = {0.0};
double exetime3_2[10000] = {0.0};
int temp = 1;
double temp_time;

string input;


void SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);           // 回傳顯示字串"c"的索引值
    pos1 = 0;
    while(string::npos != pos2)  // 當讀入的字串中有包含字串"c"的索引值,則執行下列迴圈
     {
        v.push_back(s.substr(pos1, pos2-pos1));  // 將讀入的字串從[0]到"c"的索引值,引入vector中
         
        pos1 = pos2 + c.size();  // pos1設為讀入v的字串後的索引值
        pos2 = s.find(c, pos1);  // 接著搜尋下一個包含字串"c"的索引值
    }
    if(pos1 != s.length())   // 當完整讀完的字串後的索引值!=輸入字串長度
        v.push_back(s.substr(pos1));   // 則將剩下的輸入字串接在vector後面
}

int main ()
{
	string s;
	vector<string> v;
	int payload;
	int couter_1 = 0, couter_2 = 0, couter_3 = 0, couter_4 = 0, couter_5 = 0;
	int max = 900;
	int mcount = 0;
	int stage1 = 0, stage2 = 0, stage3 = 0, stage4 = 0, stage5 = 0;
	
	again:printf("Type the traffic scenario (demo or thesis):");
	
	cin >> input;
	
	if(input == "demo")
	{
		stage1 = 59;
		stage2 = 1;
		stage3 = 59;
		stage4 = 1;
		stage5 = 59;
	}
	else if(input == "thesis")
	{
		stage1 = 9;
		stage2 = 23;
		stage3 = 36;
		stage4 = 49;
		stage5 = 62;
	}
	else
	{
		printf("Wrong scenario you type, try again.\n");
		goto again;
	}
	
	srand(time(NULL));
	
	ifstream inf;
	inf.open("wcmpacket.txt");
	ofstream outf;
	outf.open("wcmpacket_demo.txt");
	// 將trace file中的封包紀錄檔做流量改變
	while(getline(inf, s)) 
	{
		couter_1 = 0;
		couter_2 = 0;
		couter_3 = 0;
		couter_4 = 0;
		couter_5 = 0;
		
		SplitString(s, v, " ");  
		
		if(v[1]=="192.168.0.102" && v.size()==5)			
		{
			if(150<temp && temp<196)
			{
				while(couter_1 < stage1)
				{		
					outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<' '<<endl;
					couter_1++;
				}
			}
			else if(300<temp && temp<346)
			{
				while(couter_2 < stage2)
				{		
					outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<' '<<endl;
					couter_2++;
				}
			}
			else if(450<temp && temp<496)
			{
				while(couter_3 < stage3)
				{
					outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<' '<<endl;
					couter_3++;
				}
			}
			else if(600<temp && temp<646)
			{
				while(couter_4 < stage4)
				{
					outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<' '<<endl;
					couter_4++;
				}
			}
			else if(750<temp && temp<796)
			{
				while(couter_5 < stage5)
				{
					outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<' '<<endl;
					couter_5++;
				}
			}
			else
			{
				outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<' '<<endl;
			}
		}	
		else if(v[1]=="192.168.0.102" && v.size()==6)			
		{	
			if(150<temp && temp<196)
			{
				while(couter_1 < stage1)
				{		
					outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
					couter_1++;
				}
			}
			else if(300<temp && temp<346)
			{
				while(couter_2 < stage2)
				{		
					outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
					couter_2++;
				}
			}
			else if(450<temp && temp<496)
			{
				while(couter_3 < stage3)
				{
					outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
					couter_3++;
				}
			}
			else if(600<temp && temp<646)
			{
				while(couter_4 < stage4)
				{
					outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
					couter_4++;
				}
			}
			else if(750<temp && temp<796)
			{
				while(couter_5 < stage5)
				{
					outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
					couter_5++;
				}
			}	
			else
			{			
				outf<<v[0]<<' '<<v[1]<<' '<<v[2]<<' '<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;		
			}
			
			temp++;
		}
		
		s.clear();
		v.clear();
	}
	inf.close();
	outf.close();
	// 將執行延遲的紀錄檔做修正
	inf.open("../recording/ts_2-1_Mpub.txt");
	outf.open("../recording/ts_2-1_Mpub_demo.txt");
	
	while(getline(inf, s)) 
	{	
		temp_time = stod(s);
		Mtime[mcount] =temp_time; 
		mcount++;	
	}
	
	for(int i = 0; i < 150; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}	
	
	for(int i = 150; i < 195; i++)
	{
		int j = 0;
		
		while(j < stage1)
			{
				int x = rand() % (max+1);
				outf<<fixed<<setprecision(9)<<Mtime[x]<<endl;
				j++;
			}
	}	
	
	for(int i = 195; i < 300; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}
	
	for(int i = 300; i < 345; i++)
	{
		int j = 0;
		while(j < stage2)
			{
				int x = rand() % (max+1);
				outf<<fixed<<setprecision(9)<<Mtime[x]<<endl;
				j++;
			}	
	}
	
	for(int i = 345; i < 450; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}
	
	for(int i = 450; i < 495; i++)
	{
		int j = 0;
		while(j < stage3)
			{
				int x = rand() % (max+1);
				outf<<fixed<<setprecision(9)<<Mtime[x]<<endl;
				j++;
			}	
	}
	for(int i = 495; i < 600; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}
	
	for(int i = 600; i < 645; i++)
	{
		int j = 0;
		while(j < stage4)
			{
				int x = rand() % (max+1);
				outf<<fixed<<setprecision(9)<<Mtime[x]<<endl;
				j++;
			}	
	}
	for(int i = 645; i < 750; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}
	
	for(int i = 750; i < 795; i++)
	{
		int j = 0;
		while(j < stage5)
			{
				int x = rand() % (max+1);
				outf<<fixed<<setprecision(9)<<Mtime[x]<<endl;
				j++;
			}	
	}
	for(int i = 795; i < 900; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}
	
	
	inf.close();
	outf.close();
	
	mcount = 0;
	
	inf.open("../recording/ts_3-2_Mpub.txt");
	outf.open("../recording/ts_3-2_Mpub_demo.txt");
	
	while(getline(inf, s)) 
	{	
		temp_time = stod(s);
		Mtime[mcount] =temp_time; 
		mcount++;	
	}
	
	for(int i = 0; i < 150; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}	
	
	for(int i = 150; i < 195; i++)
	{
		int j = 0;
		
		while(j < stage1)
			{
				int x = rand() % (max+1);
				outf<<fixed<<setprecision(9)<<Mtime[x]<<endl;
				j++;
			}
	}	
	
	for(int i = 195; i < 300; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}
	
	for(int i = 300; i < 345; i++)
	{
		int j = 0;
		while(j < stage2)
			{
				int x = rand() % (max+1);
				outf<<fixed<<setprecision(9)<<Mtime[x]<<endl;
				j++;
			}	
	}
	
	for(int i = 345; i < 450; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}
	
	for(int i = 450; i < 495; i++)
	{
		int j = 0;
		while(j < stage3)
			{
				int x = rand() % (max+1);
				outf<<fixed<<setprecision(9)<<Mtime[x]<<endl;
				j++;
			}	
	}
	for(int i = 495; i < 600; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}
	
	for(int i = 600; i < 645; i++)
	{
		int j = 0;
		while(j < stage4)
			{
				int x = rand() % (max+1);
				outf<<fixed<<setprecision(9)<<Mtime[x]<<endl;
				j++;
			}	
	}
	for(int i = 645; i < 750; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}
	
	for(int i = 750; i < 795; i++)
	{
		int j = 0;
		while(j < stage5)
			{
				int x = rand() % (max+1);
				outf<<fixed<<setprecision(9)<<Mtime[x]<<endl;
				j++;
			}	
	}
	for(int i = 795; i < 900; i++)
	{
		outf<<fixed<<setprecision(9)<<Mtime[i]<<endl;
	}
	
	
	inf.close();
	outf.close();
	
	mcount = 0;
	
	inf.open("../recording/ts_2-1_Mpub_demo.txt");
	while(getline(inf, s)) 
	{	
		temp_time = stod(s);
		exetime2_1[mcount] =temp_time; 
		mcount++;	
	}
	inf.close();
	
	mcount = 0;
	
	inf.open("../recording/ts_3-2_Mpub_demo.txt");
	while(getline(inf, s)) 
	{	
		temp_time = stod(s);
		exetime3_2[mcount] =temp_time; 
		mcount++;	
	}
	inf.close();
	
	outf.open("../recording/WCM_exe.txt");
	//cout << mcount <<endl;
	
	int i = 0;
	while(i < mcount)
	{
		outf<<fixed<<setprecision(9)<<exetime2_1[i]+exetime3_2[i]<<endl;
		i++;
	}
	outf.close();
	
	return 0;
}
