#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include <typeinfo>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

using namespace std;

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
	string s, input;
	vector<string> v;
	int PCP5 = 0, PCP4 = 0, PCP0 = 0;
	double exlatency, e2elatency;
	double LR5 = 0.015*3.0/13.0, LR2 = 0.0225*3.0/5.0, LR1 = 0.225;
	
	int stage1 = 0, stage2 = 0, stage3 = 0, stage4 = 0, stage5 = 0;
	
	again: printf("Type the traffic scenario (demo or thesis):");
	
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
	
	ifstream inf1;
	inf1.open("../recording/WCCC_exe.txt");
	ifstream inf2;
	inf2.open("../recording/WCA_exe.txt");
	ifstream inf3;
	//inf3.open("wcmpacket_demo.txt");
	inf3.open("../recording/WCM_exe.txt");
	ofstream outf1;
	outf1.open("WC_CC_priority.txt");
	ofstream outf2;
	outf2.open("WC_A_priority.txt");
	ofstream outf3;
	outf3.open("WC_M_priority.txt");
	ofstream outf4;
	outf4.open("WC_CC_PBR.txt");
	ofstream outf5;
	outf5.open("WC_A_PBR.txt");
	ofstream outf6;
	outf6.open("WC_M_PBR.txt");
	
	cout << "Logical Channel Config. for 5QI86 (Control Command)" << endl;
	usleep(3000000);
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{		
		PCP5 ++;
		cout << "[" << PCP5 << "] Priority = ";
		exlatency = atof(s.c_str()); // 數字字串轉成 double
		e2elatency = LR5 - exlatency; 
		if(e2elatency<=0.002)
		{
			outf1<<"priority = 1"<<endl;
			cout << "1";
		}
		else if(e2elatency>0.002 && e2elatency<=0.004)
		{
			outf1<<"priority = 2"<<endl;
			cout << "2";
		}
		else if(e2elatency>0.004 && e2elatency<=0.008)
		{
			outf1<<"priority = 3"<<endl;
			cout << "3";
		}
		else if(e2elatency>0.008 && e2elatency<=0.016)
		{
			outf1<<"priority = 4"<<endl;
			cout << "4";
		}	
		else if(e2elatency>0.016 && e2elatency<=0.032)
		{
			outf1<<"priority = 5"<<endl;
			cout << "5";
		}
		else if(e2elatency>0.032 && e2elatency<=0.064)
		{
			outf1<<"priority = 6"<<endl;
			cout << "6";
		}
		else if(e2elatency>0.064 && e2elatency<=0.128)
		{
			outf1<<"priority = 7"<<endl;
			cout << "7";
		}
		else if(e2elatency>0.128 && e2elatency<=0.256)
		{
			outf1<<"priority = 8"<<endl;
			cout << "8";
		}
		else if(e2elatency>0.256 && e2elatency<=0.512)
		{
			outf1<<"priority = 9"<<endl;
			cout << "9";
		}
		else if(e2elatency>0.512 && e2elatency<=1.024)
		{
			outf1<<"priority = 10"<<endl;
			cout << "10";
		}
		else if(e2elatency>1.024 && e2elatency<=2.048)
		{
			outf1<<"priority = 11"<<endl;
			cout << "11";
		}
		else if(e2elatency>2.048&& e2elatency<=4.096)
		{
			outf1<<"priority = 12"<<endl;
			cout << "12";
		}
		else if(e2elatency>4.096 && e2elatency<=8.192)
		{
			outf1<<"priority = 13"<<endl;
			cout << "13";
		}
		else if(e2elatency>8.192 && e2elatency<=16.384)
		{
			outf1<<"priority = 14"<<endl;
			cout << "14";
		}
		else if(e2elatency>16.384 && e2elatency<=32.768)
		{
			outf1<<"priority = 15"<<endl;
			cout << "15";
		}
		else if(e2elatency>32.768)
		{
			outf1<<"priority = 16"<<endl;
			cout << "16";
		}
		else
		{
			outf1<<"Error"<<endl;
		}
		
		outf4<<"kBps8192"<<endl;
		cout << " PBR = "<< "kBps8192" << " BSD = ms5" << endl;
		usleep(1000);
		
		
		s.clear();
	}
	
	cout << "Logical Channel Config. for 5QI82 (Warning)" << endl;
	usleep(3000000);
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{		
		PCP4 ++;
		cout << "[" << PCP4 << "] Priority = ";
		
		exlatency = atof(s.c_str()); // 數字字串轉成 double
		e2elatency = LR2 - exlatency; 
		if(e2elatency<=0.002)
		{
			outf2<<"priority = 1"<<endl;
			cout << "1";
		}
		else if(e2elatency>0.002 && e2elatency<=0.004)
		{
			outf2<<"priority = 2"<<endl;
			cout << "2";		
		}
		else if(e2elatency>0.004 && e2elatency<=0.008)
		{
			outf2<<"priority = 3"<<endl;
			cout << "3";
		}
		else if(e2elatency>0.008 && e2elatency<=0.016)
		{
			outf2<<"priority = 4"<<endl;
			cout << "4";
		}	
		else if(e2elatency>0.016 && e2elatency<=0.032)
		{
			outf2<<"priority = 5"<<endl;
			cout << "5";
		}
		else if(e2elatency>0.032 && e2elatency<=0.064)
		{
			outf2<<"priority = 6"<<endl;
			cout << "6";
		}
		else if(e2elatency>0.064 && e2elatency<=0.128)
		{
			outf2<<"priority = 7"<<endl;
			cout << "7";
		}
		else if(e2elatency>0.128 && e2elatency<=0.256)
		{
			outf2<<"priority = 8"<<endl;
			cout << "8";
		}
		else if(e2elatency>0.256 && e2elatency<=0.512)
		{
			outf2<<"priority = 9"<<endl;
			cout << "9";
		}
		else if(e2elatency>0.512 && e2elatency<=1.024)
		{
			outf2<<"priority = 10"<<endl;
			cout << "10";
		}
		else if(e2elatency>1.024 && e2elatency<=2.048)
		{
			outf2<<"priority = 11"<<endl;
			cout << "11";
		}
		else if(e2elatency>2.048&& e2elatency<=4.096)
		{
			outf2<<"priority = 12"<<endl;
			cout << "12";
		}
		else if(e2elatency>4.096 && e2elatency<=8.192)
		{
			outf2<<"priority = 13"<<endl;
			cout << "13";
		}
		else if(e2elatency>8.192 && e2elatency<=16.384)
		{
			outf2<<"priority = 14"<<endl;
			cout << "14";
		}
		else if(e2elatency>16.384 && e2elatency<=32.768)
		{
			outf2<<"priority = 15"<<endl;
			cout << "15";
		}
		else if(e2elatency>32.768)
		{
			outf2<<"priority = 16"<<endl;
			cout << "16";
		}
		else
		{
			outf2<<"Error"<<endl;
		}
		
		outf5<<"kBps2048"<<endl;
		
		cout << " PBR = "<< "kBps2048" << " BSD = ms5" << endl;
		usleep(1000);
		
		s.clear();
	}
	
	cout << "Logical Channel Config. for 5QI71 (S.D Uploading)" << endl;
	usleep(3000000);
	while(getline(inf3, s))  //  將文檔一行一行讀入字串s
	{		
		exlatency = atof(s.c_str()); // 數字字串轉成 double
		e2elatency = LR1 - exlatency; 
		if(e2elatency<=0.002)
		{
			outf3<<"priority = 1"<<endl;
		}
		else if(e2elatency>0.002 && e2elatency<=0.004)
		{
			outf3<<"priority = 2"<<endl;
		}
		else if(e2elatency>0.004 && e2elatency<=0.008)
		{
			outf3<<"priority = 3"<<endl;
		}
		else if(e2elatency>0.008 && e2elatency<=0.016)
		{
			outf3<<"priority = 4"<<endl;
		}	
		else if(e2elatency>0.016 && e2elatency<=0.032)
		{
			outf3<<"priority = 5"<<endl;
		}
		else if(e2elatency>0.032 && e2elatency<=0.064)
		{
			outf3<<"priority = 6"<<endl;
		}
		else if(e2elatency>0.064 && e2elatency<=0.128)
		{
			outf3<<"priority = 7"<<endl;
		}
		else if(e2elatency>0.128 && e2elatency<=0.256)
		{
			outf3<<"priority = 8"<<endl;
		}
		else if(e2elatency>0.256 && e2elatency<=0.512)
		{
			outf3<<"priority = 9"<<endl;
		}
		else if(e2elatency>0.512 && e2elatency<=1.024)
		{
			outf3<<"priority = 10"<<endl;
		}
		else if(e2elatency>1.024 && e2elatency<=2.048)
		{
			outf3<<"priority = 11"<<endl;
		}
		else if(e2elatency>2.048&& e2elatency<=4.096)
		{
			outf3<<"priority = 12"<<endl;
		}
		else if(e2elatency>4.096 && e2elatency<=8.192)
		{
			outf3<<"priority = 13"<<endl;
		}
		else if(e2elatency>8.192 && e2elatency<=16.384)
		{
			outf3<<"priority = 14"<<endl;
		}
		else if(e2elatency>16.384 && e2elatency<=32.768)
		{
			outf3<<"priority = 15"<<endl;
		}
		else if(e2elatency>32.768)
		{
			outf3<<"priority = 16"<<endl;
		}
		else
		{
			outf3<<"Error"<<endl;
		}
		s.clear();
	}
	
	for(int i = 0; i < 150; i++)
	{
		outf6<<"kBps4096"<<endl;
		PCP0 ++;
		cout << "[" << PCP0 << "] Priority = 8 PBR = kBps4096 BSD = ms5"<< endl;
		usleep(1000);
	}	
	
	for(int i = 150; i < 195; i++)
	{
		int j = 0;
		
		while(j < stage1)
			{	
				if(input == "demo")
				{
					outf6<<"kBps32768"<<endl;
					j++;
					PCP0 ++;
					cout << "[" << PCP0 << "] Priority = 8 PBR = kBps16384 BSD = ms5"<< endl;
					usleep(1000);
				}
				else if(input == "thesis")
				{
					outf6<<"kBps16384"<<endl;
					j++;
					PCP0 ++;
					cout << "[" << PCP0 << "] Priority = 8 PBR = kBps16384 BSD = ms5"<< endl;
					usleep(1000);
				}
			}
	}
	
	for(int i = 195; i < 300; i++)
	{
		outf6<<"kBps4096"<<endl;
		PCP0 ++;
		cout << "[" << PCP0 << "] Priority = 8 PBR = kBps4096 BSD = ms5"<< endl;
		usleep(1000);
	}	
	
	for(int i = 300; i < 345; i++)
	{
		int j = 0;
		
		while(j < stage2)
			{	
				if(input == "demo")
				{
					outf6<<"kBps4096"<<endl;
					j++;
					PCP0 ++;
					cout << "[" << PCP0 << "] Priority = 8 PBR = kBps16384 BSD = ms5"<< endl;
					usleep(1000);
				}
				else if(input == "thesis")
				{
					outf6<<"kBps16384"<<endl;
					j++;
					PCP0 ++;
					cout << "[" << PCP0 << "] Priority = 8 PBR = kBps16384 BSD = ms5"<< endl;
					usleep(1000);
				}
			}
	}	
	
	for(int i = 345; i < 450; i++)
	{
		outf6<<"kBps4096"<<endl;
		PCP0 ++;
		cout << "[" << PCP0 << "] Priority = 8 PBR = kBps4096 BSD = ms5"<< endl;
		usleep(1000);
	}
	
	for(int i = 450; i < 495; i++)
	{
		int j = 0;
		while(j < stage3)
			{	
				if(input == "demo")
				{
					outf6<<"kBps32768"<<endl;
					j++;
					PCP0 ++;
					cout << "[" << PCP0 << "] Priority = 8 PBR = kBps16384 BSD = ms5"<< endl;
					usleep(1000);
				}
				else if(input == "thesis")
				{
					outf6<<"kBps32768"<<endl;
					j++;
					PCP0 ++;
					cout << "[" << PCP0 << "] Priority = 8 PBR = kBps32768 BSD = ms5"<< endl;
					usleep(1000);
				}	
			}	
	}
	
	for(int i = 495; i < 600; i++)
	{
		outf6<<"kBps4096"<<endl;
		PCP0 ++;
		cout << "[" << PCP0 << "] Priority = 8 PBR = kBps4096 BSD = ms5"<< endl;
		usleep(1000);
	}
	
	for(int i = 600; i < 645; i++)
	{
		int j = 0;
		while(j < stage4)
			{
				if(input == "demo")
				{
					outf6<<"kBps4096"<<endl;
					j++;
					PCP0 ++;
					cout << "[" << PCP0 << "] Priority = 8 PBR = kBps16384 BSD = ms5"<< endl;
					usleep(1000);
				}
				else if(input == "thesis")
				{
					outf6<<"kBps32768"<<endl;
					j++;
					PCP0 ++;
					cout << "[" << PCP0 << "] Priority = 8 PBR = kBps32768 BSD = ms5"<< endl;
					usleep(1000);
				}	
			}	
	}
	
	for(int i = 645; i < 750; i++)
	{
		outf6<<"kBps4096"<<endl;
		PCP0 ++;
		cout << "[" << PCP0 << "] Priority = 8 PBR = kBps4096 BSD = ms5"<< endl;
		usleep(1000);
	}
	
	for(int i = 750; i < 795; i++)
	{
		int j = 0;
		while(j < stage5)
			{
				if(input == "demo")
				{
					outf6<<"kBps32768"<<endl;
					j++;
					PCP0 ++;
					cout << "[" << PCP0 << "] Priority = 8 PBR = kBps16384 BSD = ms5"<< endl;
					usleep(1000);
				}
				else if(input == "thesis")
				{
					outf6<<"kBps32768"<<endl;
					j++;
					PCP0 ++;
					cout << "[" << PCP0 << "] Priority = 8 PBR = kBps32768 BSD = ms5"<< endl;
					usleep(1000);
				}	
			}	
	}
	
	for(int i = 795; i < 900; i++)
	{
		outf6<<"kBps4096"<<endl;
		PCP0 ++;
		cout << "[" << PCP0 << "] Priority = 8 PBR = kBps4096 BSD = ms5" << endl;
		usleep(1000);
	}
	
	inf1.close();
	inf2.close();
	inf3.close();
	outf1.close();
	outf2.close();
	outf3.close();
	outf4.close();
	outf5.close();
	outf6.close();
	
	return 0;
}
