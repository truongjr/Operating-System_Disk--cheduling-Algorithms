#include <winbgim.h> 
#include <bits/stdc++.h>
using namespace std;
vector<int> block;
int numberBlock, startHead;
map<int, int> query;
unordered_map <int, int> posBlock;
#define M_PI 3.14159265358979323846
void DrawTriangle(int x1, int y1, int x2, int y2, int color) {
	setcolor(color);
	float s60 = sin(30 * M_PI / 180);
	float c60 = cos(30 * M_PI / 180);
	x1 = 2 * x1 - x2;
	y1 = 2 * y1 - y2;
	float x3 = c60 * (x1 - x2) - s60 * (y1 - y2) + x2; 
  	float y3 = s60 * (x1 - x2) + c60 * (y1 - y2) + y2;
  	float x4 = c60 * (x1 - x2) + s60 * (y1 - y2) + x2;
  	float y4 = -s60 * (x1 - x2) + c60 * (y1 - y2) + y2;
  	int polypoints[] = {x2, y2, int(round(x3)), int(round(y3)), int(round(x4)), int(round(y4)), x2, y2};
  	setfillstyle(1, color);
  	fillpoly(4, polypoints);
}
void CreateLine(int x1, int y1, int x2, int y2, int color) {
	// tim diem dau tien
	float xx2 = 0, yy2 = 0, xx1 = x1, yy1 = y1;
	xx1 -= x2, yy1 -= y2;
	float a = yy2 - yy1;
	float b = xx1 - xx2;
	float c = a * xx1 + b * yy1; 
	float x0 = -a * c * 1.0 / (a * a + b * b), y0 = -b * c / (a * a + b * b);
	float d = c * c * 1.0 / (a * a + b * b);
	float mult = sqrt(d / (a * a + b * b));
	float ax, ay;
	ax = x0 + b * mult;
	ay = y0 - a * mult;
	ax += x2, ay += y2; // diem cuoi de ve mui ten
	// tim diem thu 2
	float midx = (x1 + x2) / 2;
	float midy = (y1 + y2) / 2;
	float bx = 2 * midx - ax;
	float by = 2 * midy - ay;
	// tim diem de ve mui ten
	float vectorx = x1 - x2, vectory = y1 - y2;
	float factor = 7 / sqrt(pow(vectorx, 2) + pow(vectory, 2));
	vectorx *= factor;
	vectory *= factor;
	float x3 = ax + vectorx, y3 = ay + vectory;
	// ve duong thang
	line(x1, y1, x2, y2);	
	DrawTriangle(x3, y3, ax, ay, color);
}
void FCFS(){
    setcolor(0);
    int count = 210;
    string ans = "FCFS Thu tu doc la: " + to_string(block[1]) + " ";
    outtextxy(0, 650, (char*)ans.c_str());
    delay(1000);
    for(int i = 1; i < numberBlock; i++){
        ans += to_string(block[i+1]) + " ";
        outtextxy(0, 650, (char*)ans.c_str());
        CreateLine(posBlock[block[i]], count, posBlock[block[i+1]], count + 30, 0);
        count += 30;
        delay(1000);
    }
}
void SSTF(int start){
    setcolor(0);
    map <int, bool> C;
    for(auto it:block){
        C[it] = true;
    }
    vector<int> res;
    res.push_back(start);
    C[start] = false;
    int a = start, ans = start, c = 200;
    while(res.size() < numberBlock){
        for(int i = 1; i <= numberBlock; i++){
            if(block[i] != a && C[block[i]] == true){
                if(abs(a - block[i]) < c){
                    c = abs(a - block[i]);
                    ans = block[i];
                }
            }
        }
        res.push_back(ans);
        C[ans] = false;
        a = ans;
        c = 200;
    }
    int count = 210;
    string da = "SSTF Thu tu doc: " + to_string(res[0]) + " ";
    outtextxy(0, 650, (char*)da.c_str());
    delay(1000);
    for(int i = 0; i < numberBlock - 1; i++){
        da += to_string(res[i+1]) + " ";
        outtextxy(0, 650, (char*)da.c_str());
        CreateLine(posBlock[res[i]], count, posBlock[res[i+1]], count + 30, 0);
        count += 30;
        delay(1000);
    }
}
void SCAN(int start){
    setcolor(0);
    int idx = -1;
    vector<int> res = block;
    sort(res.begin(), res.end());
    for(int i = 0; i < numberBlock; i++){
        if(res[i] == start){
            idx = i;
            break;
        }
    }
    string da = "SCAN Thu tu doc: ";
    int count = 210;
    for(int i = idx; i > 0; i--){
        da += to_string(res[i]) + " ";
        outtextxy(0, 650, (char*)da.c_str());
        CreateLine(posBlock[res[i]], count, posBlock[res[i-1]], count + 30, 0);
        count += 30;
        delay(1000);
    }
    da += to_string(res[idx+1]) + " ";
    outtextxy(0, 650, (char*)da.c_str());
    CreateLine(posBlock[res[0]], count, posBlock[res[idx+1]], count + 30, 0);
    count += 30;
    delay(1000);
    for(int i = idx + 1; i < numberBlock; i++){
        da += to_string(res[i+1]) + " ";
        outtextxy(0, 650, (char*)da.c_str());
        CreateLine(posBlock[res[i]], count, posBlock[res[i+1]], count + 30, 0);
        count += 30;
        delay(1000);
    }
}
void C_SCAN(int start){
    setcolor(0);
    int idx = -1;
    vector<int> res = block;
    sort(res.begin(), res.end());
    for(int i = 0; i < numberBlock; i++){
        if(res[i] == start){
            idx = i;
            break;
        }
    }
    int count = 210;    
    string da = "C_SCAN Thu tu doc: ";
    da += to_string(res[idx]) + " ";
    outtextxy(0, 650, (char*)da.c_str());
    delay(1000);
    for(int i = idx; i <= numberBlock; i++){
        if(res[i+1] != 200)
        da += to_string(res[i+1]) + " ";
        outtextxy(0, 650, (char*)da.c_str());
        CreateLine(posBlock[res[i]], count, posBlock[res[i+1]], count + 30, 0);
        count += 30;
        delay(1000);
    }
    CreateLine(posBlock[res[numberBlock + 1]], count, posBlock[res[0]], count + 30, 0);
    count += 30;
    delay(1000);
    for(int i = 0; i < idx - 1; i++){
        da += to_string(res[i + 1]) + " ";
        outtextxy(0, 650, (char*)da.c_str());
        CreateLine(posBlock[res[i]], count, posBlock[res[i+1]], count + 30, 0);
        count += 30;
        delay(1000);
    }
}
void InputData(){
    initwindow(1200, 700);
    setbkcolor(15);						
   	cleardevice();
	setcolor(0);
    settextstyle(3, HORIZ_DIR, 3);
    string s = "Nhap vao so luong khoi can doc (< 20): ";						
	outtextxy(0, 0, (char*)s.c_str());
    string tmp = "";
    while(1){
        if(kbhit()){
            char key = getch();
            if(key >= 48 && key <= 57 && tmp.size() < 2){
                tmp += (char)key;
                outtextxy(0, 0, (char*)(s+tmp).c_str());
            }
            else if(key == 13){
                numberBlock = atoi((char*)tmp.c_str());
                break;
            }
        }
    }

    s = "Thu tu cac khoi can doc: ";
    int y = textheight("c");
    outtextxy(0, y, (char*)s.c_str());
    block.push_back(0);
    for(int i = 1; i <= numberBlock; i++){
        tmp = "";
        while(1){
            if(kbhit()){
                char key = getch();
                if(key >= 48 && key <= 57 && tmp.size() < 3){
                    tmp += (char)key;
                    s.erase(s.end() - tmp.size() + 1, s.end());
                    s += tmp;
                    outtextxy(0, y, (char*)s.c_str());
                }
                else if(key == 13 || key == 32){
                    if(s[s.size() - 1] != ' '){
                        block.push_back(atoi((char*)tmp.c_str()));
                        s += ", ";
                        outtextxy(0, y, (char*)s.c_str());
                        break;
                    } 
                }
            }
        }
    }
    block.push_back(200);
    s = "Vi tri dau doc ban dau: ";						
	outtextxy(0, y*2, (char*)s.c_str());
    tmp = "";
    while(1){
        if(kbhit()){
            char key = getch();
            if(key >= 48 && key <= 57 && tmp.size() < 3){
                tmp += (char)key;
                outtextxy(0, y*2, (char*)(s+tmp).c_str());
            }
            else if(key == 13){
                startHead = atoi((char*)tmp.c_str());
                break;
            }
        }
    }
    int tpos = 1180 / (numberBlock + 1);
    vector<int> ex = block;
    sort(ex.begin(), ex.end());
    for(int i = 0; i <= numberBlock + 1; i++){
        query[block[i]] = i;
        if(i != 0) posBlock[ex[i]] =  tpos*i - textwidth("000") + 10;
        else posBlock[ex[i]] =  10;
    }
    setcolor(0);
    setlinestyle(0, 0, 3);
    line(0, 200, 1200, 200);
    for(auto it:posBlock){
        if(it.first == 200) outtextxy(it.second - 10, 170, "...");
        else outtextxy(it.second - 10, 170, (char*)to_string(it.first).c_str());
    }
    FCFS();
    delay(2000);
    setfillstyle(1, 15);
    bar(0, 205, 1200, 700);
    SSTF(startHead);
    delay(2000);
    setfillstyle(1, 15);
    bar(0, 205, 1200, 700);
    SCAN(startHead);
    delay(2000);
    setfillstyle(1, 15);
    bar(0, 205, 1200, 700);
    C_SCAN(startHead);
    while(1){
        if(kbhit()){
            char key = getch();
            if(key == 27){
                return;
            }
        }
    }
}

int main(){
	InputData();   
    return 0;
}
