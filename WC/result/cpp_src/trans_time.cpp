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
	string alg;
	vector<string> v;
	float CC_1[5000], CC_2[5000], A_1[2500], A_2[2500], M_1[400000], M_2[400000], CC_WF_1[5000], CC_WF_2[5000], CC_FW_1[5000],CC_FW_2[5000], A_WF_1[2500], A_WF_2[2500], A_FW_1[2500], A_FW_2[2500];
	float temp;
	//float CCWT_1[18100], CCWT_2[18100], AWT_1[18100], AWT_2[18100], MWT[18100];
	int CC_count1 = 0, CC_count2 = 0, A_count1 = 0, A_count2 = 0, M_count1 = 0, M_count2 = 0;
	ifstream inf1, inf2;
	ofstream outf1, outf2, outf3, outf4, outf5;
	cout << "Enter the MAC layer algorithm:(LCP, WGCL, AW-WGCL)" << endl;
	cin >> alg;
/*	
//===================================  計算CC Trans_time ===============================//
	inf1.open("beforeWGCL_WCCC_5G.txt");
	inf2.open("afterWGCL_FMCC_5G.txt");
	
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			CC_1[CC_count1] = stof(v[1]);
			CC_count1++;
		}	
		s.clear();
		v.clear();
	}
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			CC_2[CC_count2] = stof(v[1]);
			CC_count2++;
		}	
		s.clear();
		v.clear();
	}
	
	cout << "CC_count1 = " << CC_count1 <<endl;
	cout << "CC_count2 = " << CC_count2 <<endl;
	
	inf1.close();
	inf2.close();
	
	outf1.open("output/CC_trans_time.txt");
	
	for(int i = 0; i < CC_count2; i++)
	{
		temp = CC_2[i] - CC_1[i];
		outf1 << fixed<<setprecision(9) << temp << endl;
	}
	outf1.close();
	*/
//===================================  計算CC WC->FM E2E latency ===============================//	
	CC_count1 = 0, CC_count2 = 0;
	inf1.open("/home/lukelin/Desktop/result/before_WCCC_5G.txt");
	inf2.open("/home/lukelin/Desktop/result/after_WCCC_5G.txt");
	
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			CC_WF_1[CC_count1] = stof(v[1]);
			CC_count1++;
		}	
		s.clear();
		v.clear();
	}
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			CC_WF_2[CC_count2] = stof(v[1]);
			CC_count2++;
		}	
		s.clear();
		v.clear();
	}
	
	inf1.close();
	inf2.close();
	
	if (alg == "AW-WGCL")
	{
		outf1.open("/home/lukelin/Desktop/result/output/AW-WGCL_CC_WC->FM.txt");
	}
	else if (alg == "WGCL")
	{
		outf1.open("/home/lukelin/Desktop/result/output/WGCL_CC_WC->FM.txt");
	}
	else if (alg == "LCP")
	{
		outf1.open("/home/lukelin/Desktop/result/output/LCP_CC_WC->FM.txt");
	}
	
	for(int i = 0; i < CC_count1; i++)
	{
		temp = CC_WF_2[i] - CC_WF_1[i];
		outf1 << fixed<<setprecision(9) << temp << endl;
	}
	outf1.close();
//===================================  計算CC FM->WC E2E latency ===============================//		
	CC_count1 = 0, CC_count2 = 0;
	inf1.open("/home/lukelin/Desktop/result/before_FMCC_5G.txt");
	inf2.open("/home/lukelin/Desktop/result/after_FMCC_5G.txt");
	
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			CC_FW_1[CC_count1] = stof(v[1]);
			CC_count1++;
		}	
		s.clear();
		v.clear();
	}
	CC_FW_1[CC_count1] = 0;
	CC_count1++;
	
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			CC_FW_2[CC_count2] = stof(v[1]);
			CC_count2++;
		}	
		s.clear();
		v.clear();
	}
	CC_FW_2[CC_count2] = 0;
	CC_count2++;
	
	inf1.close();
	inf2.close();
	
	if (alg == "AW-WGCL")
	{
		outf1.open("/home/lukelin/Desktop/result/output/AW-WGCL_CC_FM->WC.txt");
	}
	else if (alg == "WGCL")
	{
		outf1.open("/home/lukelin/Desktop/result/output/WGCL_CC_FM->WC.txt");
	}
	else if (alg == "LCP")
	{
		outf1.open("/home/lukelin/Desktop/result/output/LCP_CC_FM->WC.txt");
	}
	
	for(int i = 0; i < CC_count1; i++)
	{
		temp = CC_FW_2[i] - CC_FW_1[i];
		outf1 << fixed<<setprecision(9) << temp << endl;
	}
	outf1.close();
/*	
//===================================  計算A Trans_time ===============================//		

	inf1.open("beforeWGCL_WCA_5G.txt");
	inf2.open("afterWGCL_FMA_5G.txt");
	
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			A_1[A_count1] = stof(v[1]);
			A_count1++;
		}	
		s.clear();
		v.clear();
	}
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			A_2[A_count2] = stof(v[1]);
			A_count2++;
		}	
		s.clear();
		v.clear();
	}
	
	cout << "A_count1 = " << A_count1 <<endl;
	cout << "A_count2 = " << A_count2 <<endl;
	
	inf1.close();
	inf2.close();
	
	outf1.open("output/A_trans_time.txt");
	
	for(int i = 0; i < A_count2; i++)
	{
		temp = A_2[i] - A_1[i];
		outf2 << fixed<<setprecision(9) << temp << endl;
	}
	outf2.close();*/
//===================================  計算A WC->FM E2E latency ===============================//	
	A_count1 = 0, A_count2 = 0;
	inf1.open("/home/lukelin/Desktop/result/before_WCA_5G.txt");
	inf2.open("/home/lukelin/Desktop/result/after_WCA_5G.txt");
	
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			A_WF_1[A_count1] = stof(v[1]);
			A_count1++;
		}	
		s.clear();
		v.clear();
	}
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			A_WF_2[A_count2] = stof(v[1]);
			A_count2++;
		}	
		s.clear();
		v.clear();
	}
	
	inf1.close();
	inf2.close();
	
	if (alg == "AW-WGCL")
	{
		outf1.open("/home/lukelin/Desktop/result/output/AW-WGCL_A_WC->FM.txt");
	}
	else if (alg == "WGCL")
	{
		outf1.open("/home/lukelin/Desktop/result/output/WGCL_A_WC->FM.txt");
	}
	else if (alg == "LCP")
	{
		outf1.open("/home/lukelin/Desktop/result/output/LCP_A_WC->FM.txt");
	}
	
	for(int i = 0; i < A_count1; i++)
	{
		temp = A_WF_2[i] - A_WF_1[i];
		outf1 << fixed<<setprecision(9) << temp << endl;
	}
	outf1.close();
//===================================  計算A FM->WC E2E latency ===============================//	
	A_count1 = 0, A_count2 = 0;
	inf1.open("/home/lukelin/Desktop/result/before_FMA_5G.txt");
	inf2.open("/home/lukelin/Desktop/result/after_FMA_5G.txt");
	
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			A_FW_1[A_count1] = stof(v[1]);
			A_count1++;
		}	
		s.clear();
		v.clear();
	}
	A_FW_1[A_count1] = 0;
	A_count1++;
	
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opcua")
		{
			A_FW_2[A_count2] = stof(v[1]);
			A_count2++;
		}	
		s.clear();
		v.clear();
	}
	A_FW_2[A_count2] = 0;
	A_count2++;
	
	inf1.close();
	inf2.close();
	
	if (alg == "AW-WGCL")
	{
		outf1.open("/home/lukelin/Desktop/result/output/AW-WGCL_A_FM->WC.txt");
	}
	else if (alg == "WGCL")
	{
		outf1.open("/home/lukelin/Desktop/result/output/WGCL_A_FM->WC.txt");
	}
	else if (alg == "LCP")
	{
		outf1.open("/home/lukelin/Desktop/result/output/LCP_A_FM->WC.txt");
	}
	
	
	for(int i = 0; i < A_count1; i++)
	{
		temp = A_FW_2[i] - A_FW_1[i];
		outf1 << fixed<<setprecision(9) << temp << endl;
	}
	outf1.close();
//===================================  計算M WC->FM E2E latency ===============================//
	inf1.open("/home/lukelin/Desktop/result/before_WCM_5G.txt");
	inf2.open("/home/lukelin/Desktop/result/after_WCM_5G.txt");
	
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[8] == "opcua")
		{
			M_1[M_count1] = stof(v[1]);
			M_count1++;
		}	
		s.clear();
		v.clear();
	}
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[8] == "opcua")
		{
			M_2[M_count2] = stof(v[1]);
			M_count2++;
		}	
		s.clear();
		v.clear();
	}
	
	//cout << "M_count1 = " << M_count1 <<endl;
	//cout << "M_count2 = " << M_count2 <<endl;
	
	inf1.close();
	inf2.close();

	if (alg == "AW-WGCL")
	{
		outf1.open("/home/lukelin/Desktop/result/output/AW-WGCL_M_WC->FM.txt");
	}
	else if (alg == "WGCL")
	{
		outf1.open("/home/lukelin/Desktop/result/output/WGCL_M_WC->FM.txt");
	}
	else if (alg == "LCP")
	{
		outf1.open("/home/lukelin/Desktop/result/output/LCP_M_WC->FM.txt");
	}
	
	for(int i = 0; i < M_count2; i++)
	{
		temp = M_2[i] - M_1[i];
		outf1 << fixed<<setprecision(9) << temp << endl;
	}
	outf1.close();
	
	if (alg == "AW-WGCL")
	{
		//cout << "Algorithm is AW-WGCL" << endl;
		inf1.open("/home/lukelin/Desktop/result/WTrecord.txt");
		outf1.open("/home/lukelin/Desktop/result/output/AW-WGCL_CCWT_1.txt");
		outf2.open("/home/lukelin/Desktop/result/output/AW-WGCL_AWT_1.txt");
		outf3.open("/home/lukelin/Desktop/result/output/AW-WGCL_MWT.txt");
		outf4.open("/home/lukelin/Desktop/result/output/AW-WGCL_CCWT_2.txt");
		outf5.open("/home/lukelin/Desktop/result/output/AW-WGCL_AWT_2.txt");
		
		while(getline(inf1, s))  //  將文檔一行一行讀入字串s
		{	
			SplitString(s, v, " "); 
			
			outf1 << v[2] << endl;
			outf2 << v[4] << endl;
			outf3 << v[6] << endl;
			outf4 << v[9] << endl;
			outf5 << v[11] << endl;
			
			s.clear();
			v.clear();
		}
		
	}
	else if (alg == "WGCL")
	{
		//cout << "Algorithm is AW-WGCL" << endl;
		inf1.open("/home/lukelin/Desktop/result/WTrecord.txt");
		outf1.open("/home/lukelin/Desktop/result/output/WGCL_CCWT_1.txt");
		outf2.open("/home/lukelin/Desktop/result/output/WGCL_AWT_1.txt");
		outf3.open("/home/lukelin/Desktop/result/output/WGCL_MWT.txt");
		outf4.open("/home/lukelin/Desktop/result/output/WGCL_CCWT_2.txt");
		outf5.open("/home/lukelin/Desktop/result/output/WGCL_AWT_2.txt");
		
		while(getline(inf1, s))  //  將文檔一行一行讀入字串s
		{	
			SplitString(s, v, " "); 
			
			outf1 << v[2] << endl;
			outf2 << v[4] << endl;
			outf3 << v[6] << endl;
			outf4 << v[9] << endl;
			outf5 << v[11] << endl;
			
			s.clear();
			v.clear();
		}
		
	}
	else if (alg == "LCP")
	{
		//cout << "Algorithm is AW-WGCL" << endl;
		inf1.open("/home/lukelin/Desktop/result/WTrecord.txt");
		outf1.open("/home/lukelin/Desktop/result/output/LCP_CCWT_1.txt");
		outf2.open("/home/lukelin/Desktop/result/output/LCP_AWT_1.txt");
		outf3.open("/home/lukelin/Desktop/result/output/LCP_MWT.txt");
		outf4.open("/home/lukelin/Desktop/result/output/LCP_CCWT_2.txt");
		outf5.open("/home/lukelin/Desktop/result/output/LCP_AWT_2.txt");
		
		while(getline(inf1, s))  //  將文檔一行一行讀入字串s
		{	
			SplitString(s, v, " "); 
			
			outf1 << v[2] << endl;
			outf2 << v[4] << endl;
			outf3 << v[6] << endl;
			outf4 << v[9] << endl;
			outf5 << v[11] << endl;
			
			s.clear();
			v.clear();
		}
		
	}
	else
	{
		cout << "There is no algorithm you insert!" << endl;
	}
	
	outf1.close();
	outf2.close();
	outf3.close();
	outf4.close();
	outf5.close();
	
	return 0;
}
