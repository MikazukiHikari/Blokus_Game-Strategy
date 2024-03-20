#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc,const char *argv[]){ //argv[1]"Red"or"Blue,argv[2]Blokus Board Status,argv[3]Left Pattern,argv[4]Step Log
char  LeftPattern[21];
char color;
char ncolor;
//argv[1]="Red";//測試用 
if(strcmp(argv[1],"Red")==0){//判斷我方的block為'R'或'B' 
	color='R';
	ncolor='B';
}else{
    color='B';
	ncolor='R';	
}
 /*argv[2]="BlokusBoard.txt";
 argv[3]="LeftPattern_Red.txt";//測試用*/
int i;//以下八個為for迴圈專用函數 
int j;
int k;
int t;
int m;
int n;
int xx;
int yy;
int cross=1;//第一二步使用定式專用的變數 
int c;int d;int e;int f;// c=colormemoryrow[x];d=colormemorycol[x];e=ncolormemoryrow[x];f=ncolormemorycol[x];
int x=0;
int y=0;
int z=0;
int bestput;//紀錄最好的放置方式 
int bestrow;//紀錄最好的放置y座標 
int bestcol;//紀錄最好的放置x座標 
int tp=0;//紀錄目前最高分
int colorp=0;//紀錄我方可放格子數 
int ncp;
int cp;
int ncolorp=0;//紀錄敵方可放格子數 
int cc;//算分用 
int cn;//算分用
int cnn;//算分用
int cb;//算分用
int cs;//算分用
int cd;//算分用
int csb;//算分用
int cssb;//算分用
int csg;//算分用
int csc;//算分用
int ce;//算分用
int cj;//算分用
int colormemoryrow[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//紀錄雙方可放置的區域座標最多紀錄45個 
int colormemorycol[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int ncolormemoryrow[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int ncolormemorycol[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char blokusboard[14][14];//取得原來的blokusboard 
char newblokusboard[14][14];//輸出用的blokusboard 

char* readFile(char *filename){//讀檔用 
	FILE *fp;
    char temp[1000];
    char *return_string = "";
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Can't open file\n");
}
char *temp3 = "";
    while(fgets(temp, 1000, fp)!=NULL)
    {
        return_string = malloc((strlen(temp)+strlen(return_string)+1)*sizeof(char));
        strcpy(return_string,temp3);
        temp3 = malloc((strlen(temp)+strlen(temp3)+1)*sizeof(char));
        strcat(return_string,temp);
        strcpy(temp3,return_string);
    }
    fclose(fp);
    return return_string;
}
void writeFile(char *filename, char *content){//寫檔用(w)
    FILE *fpr;
    fpr = fopen(filename,"w");
    fprintf(fpr,content);
    fclose(fpr);

}
void writeFilea(char *filename, char *content){ //寫檔用(a)
    FILE *fpr;
    fpr = fopen(filename,"a");
    fprintf(fpr,content);
    fclose(fpr);
}
char *status =readFile(argv[2]);//status接收BlokusBoard.txt 
for(i=0;i<=13;i++){
	for(j=0;j<=13;j++){
	blokusboard[i][j]=*(status+28*i+2*j);//轉換為二維矩陣的blokusboard 
}
}
char *left=readFile(argv[3]);//left接收LeftPattern.txt 
int length=strlen(left);//判斷長度 
for(i=20;i>=0;i--){
LeftPattern[i]=*(left+length-2-2*(20-i));//轉換並放入LeftPattern[] 
}


char BlokusBoard[16][16];//將14*14blokusboard轉換成四周有牆的16*16BlokusBoard 
for(m=0;m<=15;m++){
	for(n=0;n<=15;n++){
		if(m==0||n==0){
			BlokusBoard[m][n]='W';
		}else if(m==15||n==15){
			BlokusBoard[m][n]='W';
		}else{
			BlokusBoard[m][n]=blokusboard[m-1][n-1];
		}
	}
}


void put(int n,int a,int b){//將所有放置方法編號排序(共313種,附判斷是否能放置的function) 
	int r=0;
	int c=0;
	switch(n){
case 1:
	if(LeftPattern[0]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]!=color&&BlokusBoard[a][b+1]!=color&&BlokusBoard[a-1][b]!=color
	&&BlokusBoard[a+1][b]!=color){
	BlokusBoard[a][b]=color;}
break;
case 2:
	if(LeftPattern[1]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a][b-1]!=color&&BlokusBoard[a][b+2]!=color
	&&BlokusBoard[a-1][b]!=color&&BlokusBoard[a+1][b]!=color&&BlokusBoard[a-1][b+1]!=color&&BlokusBoard[a+1][b+1]!=color){
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a][b]=color;}
break;
case 3:
	if(LeftPattern[1]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a-1][b-1]!=color&&BlokusBoard[a][b-2]!=color
	&&BlokusBoard[a-1][b]!=color&&BlokusBoard[a+1][b]!=color&&BlokusBoard[a][b+1]!=color&&BlokusBoard[a+1][b-1]!=color){
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a][b]=color;}
break;
case 4:
	if(LeftPattern[1]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a-1][b]!=color&&BlokusBoard[a+2][b]!=color
	&&BlokusBoard[a+1][b-1]!=color&&BlokusBoard[a+1][b+1]!=color&&BlokusBoard[a][b+1]!=color&&BlokusBoard[a][b-1]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+1][b]=color;}
break;
case 5:
	if(LeftPattern[1]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-2][b]!=color&&BlokusBoard[a+1][b]!=color
	&&BlokusBoard[a-1][b-1]!=color&&BlokusBoard[a-1][b+1]!=color&&BlokusBoard[a][b+1]!=color&&BlokusBoard[a][b-1]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 6:
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a+1][b+1]=='N'&&BlokusBoard[a-1][b]!=color&&BlokusBoard[a+1][b]!=color
	&&BlokusBoard[a-1][b+1]!=color&&BlokusBoard[a+2][b+1]!=color&&BlokusBoard[a][b+2]!=color&&BlokusBoard[a][b-1]!=color&&BlokusBoard[a+1][b+2]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a+1][b+1]=color;}
break;
case 7:
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a-1][b-1]!=color&&BlokusBoard[a+1][b-1]!=color
	&&BlokusBoard[a-1][b]!=color&&BlokusBoard[a+2][b]!=color&&BlokusBoard[a][b+1]!=color&&BlokusBoard[a][b-2]!=color&&BlokusBoard[a+1][b+1]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a+1][b]=color;}
break;
case 8:
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b-1]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-2][b-1]!=color&&BlokusBoard[a][b-1]!=color
	&&BlokusBoard[a-2][b]!=color&&BlokusBoard[a+1][b]!=color&&BlokusBoard[a-1][b+1]!=color&&BlokusBoard[a-1][b-2]!=color&&BlokusBoard[a][b+1]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b-1]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 9:
 r=1;
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+1][b-1]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+1][b-1]=color;
	BlokusBoard[a+1][b]=color;}
break;
case 10:
 c=1;
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a-1][b+1]=='N'&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a-1][b+1]=color;}
break;
case 11:
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 12:
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a+1][b]=color;}
break;
case 13:
	c=-1;
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a+1][b-1]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a+1][b-1]=color;}
break;
case 14:
	r=-1;
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b+1]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b+1]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 15:
	r=1;
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+1][b+1]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+1][b+1]=color;
	BlokusBoard[a+1][b]=color;}
break;
case 16:
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 17:
	c=-1;
	if(LeftPattern[2]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a-1][b-1]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a-1][b-1]=color;}
break;
case 18:
	c=1;
	if(LeftPattern[3]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a][b+2]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a][b+2]=color;}
break;
case 19:
	c=-1;
	if(LeftPattern[3]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a][b-2]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a][b-2]=color;}
break;
case 20:
	r=1;
	if(LeftPattern[3]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a+2][b]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a+2][b]=color;}
break;
case 21:
	r=-1;
	if(LeftPattern[3]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-2][b]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b]=color;
	BlokusBoard[a-2][b]=color;}
break;
case 22:
	if(LeftPattern[4]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a+1][b+1]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a+1][b+1]=color;}
break;
case 23:
	c=-1;
	if(LeftPattern[4]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a+1][b-1]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a+1][b-1]=color;
	BlokusBoard[a+1][b]=color;}
break;
case 24:
	r=-1;
	if(LeftPattern[4]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b+1]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b+1]=color;
	BlokusBoard[a-1][b]=color;
	BlokusBoard[a][b+1]=color;}
break;
case 25:
	r=-1;c=-1;
	if(LeftPattern[4]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a-1][b-1]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a-1][b-1]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 26:
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a][b+2]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a][b+2]=color;}
break;
case 27:
	c=-2;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a+1][b-2]=='N'&&BlokusBoard[a][b-2]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a+1][b-2]=color;
	BlokusBoard[a][b-2]=color;}
break;
case 28:
	r=-1;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b+1]=='N'&&BlokusBoard[a-1][b+2]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b+1]=color;
	BlokusBoard[a-1][b+2]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 29:
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a+2][b]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a+2][b]=color;}
break;
case 30:
	c=-1;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a+1][b-1]=='N'&&BlokusBoard[a+2][b-1]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a+1][b-1]=color;
	BlokusBoard[a+2][b-1]=color;}
break;
case 31:
	r=-2;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-2][b]=='N'&&BlokusBoard[a-2][b+1]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-2][b+1]=color;
	BlokusBoard[a-2][b]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 32:
	c=2;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a+1][b+2]=='N'&&BlokusBoard[a][b+2]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a+1][b+2]=color;
	BlokusBoard[a][b+2]=color;}
break;
case 33:
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a][b-2]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a][b-2]=color;}
break;
case 34:
	r=-1;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b-1]=='N'&&BlokusBoard[a-1][b-2]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b-1]=color;
	BlokusBoard[a-1][b-2]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 35:
	c=1;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a+1][b+1]=='N'&&BlokusBoard[a+2][b+1]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a+1][b+1]=color;
	BlokusBoard[a+2][b+1]=color;}
break;
case 36:
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a+2][b]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a+2][b]=color;}
break;
case 37:
	r=-2;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-2][b]=='N'&&BlokusBoard[a-2][b-1]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-2][b-1]=color;
	BlokusBoard[a-2][b]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 38:
	r=1;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a+1][b-1]=='N'&&BlokusBoard[a+1][b-2]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a+1][b-1]=color;
	BlokusBoard[a+1][b-2]=color;}
break;
case 39:
	c=2;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a][b+2]=='N'&&BlokusBoard[a-1][b+2]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a][b+2]=color;
	BlokusBoard[a-1][b+2]=color;}
break;
case 40:
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a][b-2]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a][b-2]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 41:
	r=2;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a+2][b]=='N'&&BlokusBoard[a+2][b-1]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a+2][b]=color;
	BlokusBoard[a+2][b-1]=color;}
break;
case 42:
	c=1;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a-1][b+1]=='N'&&BlokusBoard[a-2][b+1]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a-1][b+1]=color;
	BlokusBoard[a-2][b+1]=color;}
break;
case 43:
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-2][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b]=color;
	BlokusBoard[a-2][b]=color;
	BlokusBoard[a][b-1]=color;}
break;
case 44:
	r=1;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a+1][b+1]=='N'&&BlokusBoard[a+1][b+2]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a+1][b+1]=color;
	BlokusBoard[a+1][b+2]=color;}
break;
case 45:
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a][b+2]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a][b+2]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 46:
	c=-2;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a][b-2]=='N'&&BlokusBoard[a-1][b-2]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a][b-2]=color;
	BlokusBoard[a-1][b-2]=color;}
break;
case 47:
	r=2;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a+2][b]=='N'&&BlokusBoard[a+2][b+1]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a+2][b]=color;
	BlokusBoard[a+2][b+1]=color;}
break;
case 48:
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-2][b]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a-1][b]=color;
	BlokusBoard[a-2][b]=color;}
break;
case 49:
	c=-1;
	if(LeftPattern[5]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b-1]=='N'&&BlokusBoard[a-2][b-1]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b-1]=color;
	BlokusBoard[a-2][b-1]=color;
	BlokusBoard[a][b-1]=color;}
break;
case 50:
	c=1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a+1][b+1]=='N'&&BlokusBoard[a][b+2]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a+1][b+1]=color;
	BlokusBoard[a][b+2]=color;}
break;
case 51:
	c=-1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a+1][b-1]=='N'&&BlokusBoard[a][b-2]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a+1][b-1]=color;
	BlokusBoard[a][b-2]=color;}
break;
case 52:
	r=-1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b-1]=='N'&&BlokusBoard[a-1][b+1]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b-1]=color;
	BlokusBoard[a-1][b+1]=color;
	BlokusBoard[a-1][b]=color;}
break;
case 53:
	r=1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a+2][b]=='N'&&BlokusBoard[a+1][b+1]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a+2][b]=color;
	BlokusBoard[a+1][b+1]=color;}
break;
case 54:
	c=-1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b-1]=='N'&&BlokusBoard[a+1][b-1]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b-1]=color;
	BlokusBoard[a+1][b-1]=color;
	BlokusBoard[a][b-1]=color;}
break;
case 55:
	r=-1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b+1]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-2][b]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b+1]=color;
	BlokusBoard[a-1][b]=color;
	BlokusBoard[a-2][b]=color;}
break;
case 56:
	r=1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a+2][b]=='N'&&BlokusBoard[a+1][b-1]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a+2][b]=color;
	BlokusBoard[a+1][b-1]=color;}
break;
case 57:
	c=1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a-1][b+1]=='N'&&BlokusBoard[a+1][b+1]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a-1][b+1]=color;
	BlokusBoard[a+1][b+1]=color;}
break;
case 58:
	r=-1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a-1][b]=='N'&&BlokusBoard[a-2][b]=='N'&&BlokusBoard[a-1][b-1]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a-1][b]=color;
	BlokusBoard[a-2][b]=color;
	BlokusBoard[a-1][b-1]=color;}
break;
case 59:
	r=1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+1][b]=='N'&&BlokusBoard[a+1][b+1]=='N'&&BlokusBoard[a+1][b-1]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+1][b]=color;
	BlokusBoard[a+1][b+1]=color;
	BlokusBoard[a+1][b-1]=color;}
break;
case 60:
	c=1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b+1]=='N'&&BlokusBoard[a][b+2]=='N'&&BlokusBoard[a-1][b+1]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b+1]=color;
	BlokusBoard[a][b+2]=color;
	BlokusBoard[a-1][b+1]=color;}
break;
case 61:
	c=-1;
	if(LeftPattern[6]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a][b-1]=='N'&&BlokusBoard[a][b-2]=='N'&&BlokusBoard[a-1][b-1]=='N'&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a][b-1]=color;
	BlokusBoard[a][b-2]=color;
	BlokusBoard[a-1][b-1]=color;}
break;
case 62:
c=1;	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;	
case 63:
	if(LeftPattern[7]=='1'&&BlokusBoard[a][b]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a][b]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 64:
r=-1;	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;	
case 65:
c=-1;r=-1;	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 66:
c=-1;	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;	
case 67:	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;	
case 68:
r=-1;	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 69:
c=1;r=-1;	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;	
case 70:
r=1;	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 71:	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 72:	
c=-1;
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 73:
c=-1;r=-1;	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 74:	
r=1;
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 75:	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 76:	
c=1;
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 77:
r=-1;c=1;	
if(LeftPattern[7]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 78:	
c=1;	
if(LeftPattern[8]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a-1+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;}
break;
case 79:	
c=-2;
if(LeftPattern[8]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a-1+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;}
break;
case 80:	
r=1;
if(LeftPattern[8]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color
	&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 81:	
r=-2;
if(LeftPattern[8]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color
	&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 82:
c=1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 83:
c=-1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 84:
r=-1;c=1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 85:	
r=-1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 86:
c=-1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 87:
c=1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 88:
r=-1;c=-1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 89:
r=-1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 90:	
r=1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 91:
r=-1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 92:	
c=-1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 93:
c=-1;r=-1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 94:	
r=-1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 95:	
r=1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 96:
c=-1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 97:
c=-1;r=1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 98:
r=1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 99:
r=-1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 100:	
c=1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 101:
c=1;r=-1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 102:
r=-1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 103:
r=1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 104:
c=1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 105:
r=1;c=1;	
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 106:
	c=1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 107:
	c=-1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 108:
	r=1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 109:
	r=1;c=-1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 110:
	c=-1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 111:
	c=1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 112:
	r=1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 113:
	r=1;c=1;
if(LeftPattern[9]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 114:
	r=-1;c=1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 115:
	c=1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 116:
	c=-1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 117:
	c=-1;r=-1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 118:
	r=1;c=-1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 119:
	r=1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 120:
	r=-1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 121:
	r=-1;c=-1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 122:
	r=1;c=1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 123:
	r=1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 124:
	r=-1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 125:
	r=-1;c=1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 126:
	c=1;r=1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 127:
	c=1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 128:
	c=-1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 129:
	c=-1;r=1;
if(LeftPattern[10]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 130:
	c=1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 131:
	c=-1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 132:
	r=-1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 133:
	r=-2;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 134:
	r=1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 135:
	r=-1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 136:
	c=-1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 137:
	c=-2;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 138:
	r=1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 139:
	r=-1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 140:
	c=1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 141:
	c=2;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color
	&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 142:
	c=1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 143:
	c=-1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 144:
	r=1;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 145:
	r=2;
if(LeftPattern[11]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 146:
	c=-2;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 147:
	c=-1;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 148:
	r=-1;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 149:
	r=-2;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 150:
	c=2;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 151:
	c=1;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 152:
	r=-1;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 153:
	r=-2;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 154:
	c=-2;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 155:
	c=-1;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 156:
	r=1;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 157:
	r=2;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 158:
	c=2;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 159:
	c=1;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 160:
	r=1;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 161:
	r=2;
if(LeftPattern[12]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;}
break;
case 162:
	r=1;c=1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 163:
	r=1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 164:
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 165:
	c=-1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 166:
	c=-1;r=-1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 167:
	r=1;c=-1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 168:
	r=1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 169:
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 170:
	c=1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 171:
	c=1;r=-1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 172:
	c=-1;r=1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 173:
	c=-1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 174:
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 175:
	r=-1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 176:
	r=-1;c=1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 177:
	r=1;c=1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 178:
	c=1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 179:
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 180:
	r=-1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 181:
	c=-1;r=-1;
if(LeftPattern[13]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 182:
	r=1;c=1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 183:
	c=1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 184:
	c=-1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 185:
	r=-1;c=-1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 186:
	r=1;c=-1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 187:
	c=-1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 188:
	c=1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 189:
	c=1;r=-1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 190:
	r=1;c=-1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 191:
	r=1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 192:
	r=-1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 193:
	r=-1;c=1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 194:
	r=1;c=1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 195:
	r=1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 196:
	r=-1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 197:
	r=-1;c=-1;
if(LeftPattern[14]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 198:
	r=-1;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+r][b+3+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+3+c]!=color&&BlokusBoard[a+r][b+4+c]!=color
	&&BlokusBoard[a+1+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+r][b+3+c]=color;}
break;
case 199:
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+r][b+3+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+3+c]!=color&&BlokusBoard[a+r][b+4+c]!=color
	&&BlokusBoard[a+1+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+r][b+3+c]=color;}
break;
case 200:
	c=-3;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+r][b+3+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+3+c]!=color&&BlokusBoard[a+r][b+4+c]!=color
	&&BlokusBoard[a+1+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+r][b+3+c]=color;}
break;
case 201:
	c=-1;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+3+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+3+r][b+1+c]!=color&&BlokusBoard[a+4+r][b+c]!=color&&BlokusBoard[a+3+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+3+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 202:
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+3+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+3+r][b+1+c]!=color&&BlokusBoard[a+4+r][b+c]!=color&&BlokusBoard[a+3+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+3+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 203:
	r=-3;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+3+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+3+r][b+1+c]!=color&&BlokusBoard[a+4+r][b+c]!=color&&BlokusBoard[a+3+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+3+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 204:
	r=-1;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+r][b-3+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-3+c]!=color&&BlokusBoard[a+r][b-4+c]!=color
	&&BlokusBoard[a+1+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+r][b-3+c]=color;}
	break;
case 205:
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+r][b-3+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-3+c]!=color&&BlokusBoard[a+r][b-4+c]!=color
	&&BlokusBoard[a+1+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+r][b-3+c]=color;}
break;
case 206:
	c=3;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+r][b-3+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-3+c]!=color&&BlokusBoard[a+r][b-4+c]!=color
	&&BlokusBoard[a+1+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+r][b-3+c]=color;}
	break;
	case 207:
		c=1;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+3+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+3+r][b-1+c]!=color&&BlokusBoard[a+4+r][b+c]!=color&&BlokusBoard[a+3+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+3+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 208:
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+3+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+3+r][b-1+c]!=color&&BlokusBoard[a+4+r][b+c]!=color&&BlokusBoard[a+3+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+3+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 209:
	r=-3;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+3+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+3+r][b-1+c]!=color&&BlokusBoard[a+4+r][b+c]!=color&&BlokusBoard[a+3+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+3+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 210:
	r=1;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+r][b-3+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-3+c]!=color&&BlokusBoard[a+r][b-4+c]!=color
	&&BlokusBoard[a-1+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+r][b-3+c]=color;}
	break;
case 211:
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+r][b-3+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-3+c]!=color&&BlokusBoard[a+r][b-4+c]!=color
	&&BlokusBoard[a-1+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+r][b-3+c]=color;}
	break;
	case 212:
		c=3;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+r][b-3+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-3+c]!=color&&BlokusBoard[a+r][b-4+c]!=color
	&&BlokusBoard[a-1+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+r][b-3+c]=color;}
	break;
	case 213:
		c=1;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a-3+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-3+r][b-1+c]!=color&&BlokusBoard[a-4+r][b+c]!=color&&BlokusBoard[a-3+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a-3+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 214:
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a-3+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-3+r][b-1+c]!=color&&BlokusBoard[a-4+r][b+c]!=color&&BlokusBoard[a-3+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a-3+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 215:
	r=3;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a-3+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-3+r][b-1+c]!=color&&BlokusBoard[a-4+r][b+c]!=color&&BlokusBoard[a-3+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a-3+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 216:
	r=1;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+r][b+3+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+3+c]!=color&&BlokusBoard[a+r][b+4+c]!=color
	&&BlokusBoard[a-1+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+r][b+3+c]=color;}
	break;
case 217:
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+r][b+3+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+3+c]!=color&&BlokusBoard[a+r][b+4+c]!=color
	&&BlokusBoard[a-1+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+r][b+3+c]=color;}
	break;
case 218:
	c=-3;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'&&BlokusBoard[a+r][b+3+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+3+c]!=color&&BlokusBoard[a+r][b+4+c]!=color
	&&BlokusBoard[a-1+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;
	BlokusBoard[a+r][b+3+c]=color;}
	break;
	case 219:
		c=-1;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a-3+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-3+r][b+1+c]!=color&&BlokusBoard[a-4+r][b+c]!=color&&BlokusBoard[a-3+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a-3+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 220:
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a-3+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-3+r][b+1+c]!=color&&BlokusBoard[a-4+r][b+c]!=color&&BlokusBoard[a-3+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a-3+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 221:
	r=3;
if(LeftPattern[17]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a-3+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-3+r][b+1+c]!=color&&BlokusBoard[a-4+r][b+c]!=color&&BlokusBoard[a-3+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a-3+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 222:
	c=-1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-2+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-3+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-2+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 223:
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-2+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-3+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-2+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 224:
	r=1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-2+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-3+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-2+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 225:
	r=1;c=2;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-2+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-3+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-2+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 226:
	r=1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+2+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+3+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+2+r][b+1+c]=color;}
break;
case 227:
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+2+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+3+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+2+r][b+1+c]=color;}
break;
case 228:
	c=-1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+2+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+3+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+2+r][b+1+c]=color;}
break;
case 229:
	c=-1;r=-2;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+2+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+3+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+2+r][b+1+c]=color;}
break;
case 230:
	c=1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+2+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+3+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-2+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 231:
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+2+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+3+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+2+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 232:
	r=1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+2+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+3+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+2+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 233:
	r=1;c=-2;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+2+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+3+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+2+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 234:
	r=1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a+2+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+3+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a+2+r][b-1+c]=color;}
break;
case 235:
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a+2+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+3+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a+2+r][b-1+c]=color;}
break;
case 236:
	c=1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a+2+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+3+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a+2+r][b-1+c]=color;}
break;
case 237:
	c=1;r=-2;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a+2+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+3+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a+2+r][b-1+c]=color;}
break;
case 238:
	c=-1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-2+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-3+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-2+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 239:
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-2+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-3+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-2+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 240:
	r=-1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-2+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-3+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-2+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 241:
	r=-1;c=2;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b-2+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-3+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;
	BlokusBoard[a+1+r][b-2+c]=color;
	BlokusBoard[a+r][b+1+c]=color;}
break;
case 242:
	r=-1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a-2+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-3+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a-2+r][b+1+c]=color;}
break;
case 243:
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a-2+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-3+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a-2+r][b+1+c]=color;}
break;
case 244:
	c=-1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a-2+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-3+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a-2+r][b+1+c]=color;}
break;
case 245:
	c=-1;r=2;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'&&BlokusBoard[a-2+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-3+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;
	BlokusBoard[a-2+r][b+1+c]=color;}
break;
case 246:
	c=1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+2+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+3+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+2+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 247:
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+2+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+3+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+2+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 248:
	r=-1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+2+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+3+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+2+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 249:
	r=-1;c=-2;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+2+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+3+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+2+c]=color;
	BlokusBoard[a+r][b-1+c]=color;}
break;
case 250:
	r=-1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a-2+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-3+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a-2+r][b-1+c]=color;}
break;
case 251:
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a-2+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-3+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a-2+r][b-1+c]=color;}
break;
case 252:
	c=1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a-2+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-3+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a-2+r][b-1+c]=color;}
break;
case 253:
	r=2;c=1;
if(LeftPattern[18]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'&&BlokusBoard[a-2+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-3+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;
	BlokusBoard[a-2+r][b-1+c]=color;}
break;
case 254:
	c=1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;}
break;
case 255:
	r=-1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;}
break;
case 256:
	c=-2;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;}
break;
case 257:
	c=1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;}
break;
case 258:
	r=1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;}
break;
case 259:
	c=-2;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;}
break;
case 260:
	c=-1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;}
break;
case 261:
	r=1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;}
break;
case 262:
	c=2;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;}
break;
case 263:
	c=-1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;}
break;
case 264:
	r=-1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;}
break;
case 265:
	c=2;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b-2+c]=color;}
break;
case 266:
	r=1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 267:
	c=-1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 268:
	r=-2;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 269:
	r=1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 270:
	c=1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 271:
	r=-2;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color
	&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+c]=color;}
break;
case 272:
	r=-1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 273:
	c=1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 274:
	r=2;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color
	&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 275:
	r=-1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 276:
	c=-1;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 277:
	r=2;
if(LeftPattern[19]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color
	&&BlokusBoard[a-3+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+c]=color;}
break;
case 278:
	c=2;
if(LeftPattern[20]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;}
break;
case 279:
	c=-2;
if(LeftPattern[20]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+r][b-2+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+r][b+2+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-3+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+3+c]!=color
	&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+r][b-2+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+r][b+2+c]=color;}
break;
case 280:
	r=2;
if(LeftPattern[20]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 281:
	r=-2;
if(LeftPattern[20]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a-2+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+2+r][b+c]=='N'
	&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+3+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-3+r][b+c]!=color
	&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a-2+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+2+r][b+c]=color;}
break;
case 282:
	r=1; c=1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 283:
  c=1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 284:
 c=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 285:
	r=-1; 
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 286:
	r=1; c=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 287:
	c=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 288:
	 c=1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 289:
	r=-1; 
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-1+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+2+r][b+c]!=color
	&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 290:
	r=1; c=1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 291:
	r=1; 
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 292:
	 c=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 293:
	r=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a-1+r][b-1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a-1+r][b-1+c]=color;}
break;
case 294:
	r=-1; c=1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 295:
	r=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 296:
 c=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 297:
	r=1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+r][b-1+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
	break;
case 298:
	r=1; c=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 299:
	r=1; 
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 300:
	 c=1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 301:
	r=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a-1+r][b+1+c]=='N'
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-2+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a-1+r][b+1+c]=color;}
break;
case 302:
	r=-1; c=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 303:
	r=-1; 
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 304:
	c=1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 305:
	r=1; 
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a+1+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+2+r][b+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+r][b+1+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color
	&&BlokusBoard[a-2+r][b+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a+1+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 306:
 c=1; r=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 307:
 c=1; 
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 308:
 c=-1; 
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 309:
  r=1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b-1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a+1+r][b-2+c]!=color&&BlokusBoard[a+2+r][b-1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b-1+c]=color;}
break;
case 310:
 c=-1; r=-1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 311:
 c=-1; 
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 312:
 c=1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
case 313:
  r=1;
if(LeftPattern[15]=='1'&&BlokusBoard[a+r][b+c]=='N'&&BlokusBoard[a-1+r][b+c]=='N'&&BlokusBoard[a+r][b-1+c]=='N'&&BlokusBoard[a+r][b+1+c]=='N'&&BlokusBoard[a+1+r][b+1+c]=='N'
	&&BlokusBoard[a+1+r][b+c]!=color&&BlokusBoard[a+1+r][b-1+c]!=color&&BlokusBoard[a+r][b-2+c]!=color&&BlokusBoard[a-1+r][b-1+c]!=color&&BlokusBoard[a-2+r][b+c]!=color
	&&BlokusBoard[a-1+r][b+1+c]!=color&&BlokusBoard[a+r][b+2+c]!=color&&BlokusBoard[a+1+r][b+2+c]!=color&&BlokusBoard[a+2+r][b+1+c]!=color){
	BlokusBoard[a+r][b+c]=color;
	BlokusBoard[a-1+r][b+c]=color;
	BlokusBoard[a+r][b-1+c]=color;
	BlokusBoard[a+r][b+1+c]=color;
	BlokusBoard[a+1+r][b+1+c]=color;}
break;
}
}

 int checkcp(void){//測試若下了這步後我方可放置的格子數量 
 	cp=0;
   for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i][j]=='N'&&BlokusBoard[i+1][j]!=color&&BlokusBoard[i-1][j]!=color&&BlokusBoard[i][j+1]!=color&&
	 BlokusBoard[i][j-1]!=color){
	 if(BlokusBoard[i-1][j-1]==color||BlokusBoard[i+1][j-1]==color||BlokusBoard[i-1][j+1]==color||BlokusBoard[i+1][j+1]==color){
	 	cp++;
	}	
	 }
}	
	}//check cp
	return cp;
 }
 int checkncp(){//測試若下了這步後我方蓋住對方可放置的格子數量
 	ncp=0;
 	for(y=0;y<ncolorp;y++){
   	 e=ncolormemoryrow[y];
   	 f=ncolormemorycol[y];
 	if(BlokusBoard[e][f]==color){
 		ncp++;
	 }
}
	 return ncp;
 }
 int nnext;
  int checknnext(){//測試若下了這步後
 	nnext=0;
 	 for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i][j]==color&&BlokusBoard[i][j-1]==color&&BlokusBoard[i][j+1]==color&&
	  BlokusBoard[i+1][j-1]=='N'&&BlokusBoard[i+1][j+1]=='N'&&BlokusBoard[i+1][j]==ncolor&&BlokusBoard[i+2][j]==ncolor){
  		nnext++;
	}
	if(BlokusBoard[i][j]==color&&BlokusBoard[i][j-1]==color&&BlokusBoard[i][j+1]==color&&
	  BlokusBoard[i-1][j-1]=='N'&&BlokusBoard[i-1][j+1]=='N'&&BlokusBoard[i-1][j]==ncolor&&BlokusBoard[i-2][j]==ncolor){
  		nnext++;
	}
	if(BlokusBoard[i][j]==color&&BlokusBoard[i-1][j]==color&&BlokusBoard[i+1][j]==color&&
	  BlokusBoard[i+1][j-1]=='N'&&BlokusBoard[i-1][j-1]=='N'&&BlokusBoard[i][j-1]==ncolor&&BlokusBoard[i][j-2]==ncolor){
  		nnext++;
	}
	if(BlokusBoard[i][j]==color&&BlokusBoard[i-1][j]==color&&BlokusBoard[i+1][j]==color&&
	  BlokusBoard[i+1][j+1]=='N'&&BlokusBoard[i-1][j+1]=='N'&&BlokusBoard[i][j+1]==ncolor&&BlokusBoard[i][j+2]==ncolor){
  		nnext++;
	}
	  }
	 }
	 return nnext;
 }
 int block;
 int ncolorcount;
 int ncount;
 int checkblock(void){//測試若下了這步後
 	block=0;
 	ncolorcount=0; ncount=0;
   for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i][j]=='N'&&BlokusBoard[i+1][j]==color&&BlokusBoard[i+2][j]==color&&BlokusBoard[i+3][j]==color&&BlokusBoard[i+4][j]=='W'){
  		for(xx=1;xx<=3;xx++){
  			for(yy=1;yy<=4;yy++){
  			if(BlokusBoard[i+xx][j-yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i+xx][j-yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=4&&BlokusBoard[i][j+1]!='W'){
		  	block++;
		  }ncolorcount=0; ncount=0;
		  	for(xx=1;xx<=3;xx++){
  			for(yy=1;yy<=4;yy++){
  			if(BlokusBoard[i+xx][j+yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i+xx][j+yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=4&&BlokusBoard[i][j-1]!='W'){
		  	block++;
		  }
	 }ncolorcount=0; ncount=0;
	 if(BlokusBoard[i][j]=='N'&&BlokusBoard[i-1][j]==color&&BlokusBoard[i-2][j]==color&&BlokusBoard[i-3][j]==color&&BlokusBoard[i-4][j]=='W'){
	 	for(xx=1;xx<=3;xx++){
  			for(yy=1;yy<=4;yy++){
  			if(BlokusBoard[i-xx][j-yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i-xx][j-yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=4&&BlokusBoard[i][j+1]!='W'){
		  	block++;
		  }ncolorcount=0; ncount=0;
		  	for(xx=1;xx<=3;xx++){
  			for(yy=1;yy<=4;yy++){
  			if(BlokusBoard[i-xx][j+yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i-xx][j+yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=4&&BlokusBoard[i][j-1]!='W'){
		  	block++;
		  }
	 }ncolorcount=0; ncount=0;
	 if(BlokusBoard[i][j]=='N'&&BlokusBoard[i][j+1]==color&&BlokusBoard[i][j+2]==color&&BlokusBoard[i][j+3]==color&&BlokusBoard[i][j+4]=='W'){
	 	for(xx=1;xx<=4;xx++){
  			for(yy=1;yy<=3;yy++){
  			if(BlokusBoard[i-xx][j+yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i-xx][j+yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=4&&BlokusBoard[i+1][j]!='W'){
		  	block++;
		  }ncolorcount=0; ncount=0;
		  	for(xx=1;xx<=4;xx++){
  			for(yy=1;yy<=3;yy++){
  			if(BlokusBoard[i+xx][j+yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i+xx][j+yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=4&&BlokusBoard[i-1][j]!='W'){
		  	block++;
		  }
	 }ncolorcount=0; ncount=0;
	 if(BlokusBoard[i][j]=='N'&&BlokusBoard[i][j-1]==color&&BlokusBoard[i][j-2]==color&&BlokusBoard[i][j-3]==color&&BlokusBoard[i][j-4]=='W'){
	 		for(xx=1;xx<=4;xx++){
  			for(yy=1;yy<=3;yy++){
  			if(BlokusBoard[i-xx][j-yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i-xx][j-yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=4&&BlokusBoard[i+1][j]!='W'){
		  	block++;
		  }ncolorcount=0; ncount=0;
		  	for(xx=1;xx<=4;xx++){
  			for(yy=1;yy<=3;yy++){
  			if(BlokusBoard[i+xx][j-yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i+xx][j-yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=4&&BlokusBoard[i-1][j]!='W'){
		  	block++;
		  }
	 }ncolorcount=0; ncount=0;
	 if(BlokusBoard[i][j]=='N'&&BlokusBoard[i+1][j]==color&&BlokusBoard[i+2][j]==color&&BlokusBoard[i+3][j]=='W'){
	 		for(xx=1;xx<=2;xx++){
  			for(yy=1;yy<=4;yy++){
  			if(BlokusBoard[i+xx][j-yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i+xx][j-yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=3&&BlokusBoard[i][j+1]!='W'){
		  	block++;
		  }ncolorcount=0; ncount=0;
		  	for(xx=1;xx<=2;xx++){
  			for(yy=1;yy<=4;yy++){
  			if(BlokusBoard[i+xx][j+yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i+xx][j+yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=3&&BlokusBoard[i][j-1]!='W'){
		  	block++;
		  }
	 }ncolorcount=0; ncount=0;
	 if(BlokusBoard[i][j]=='N'&&BlokusBoard[i-1][j]==color&&BlokusBoard[i-2][j]==color&&BlokusBoard[i-3][j]=='W'){
	 		for(xx=1;xx<=2;xx++){
  			for(yy=1;yy<=4;yy++){
  			if(BlokusBoard[i-xx][j-yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i-xx][j-yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=3&&BlokusBoard[i][j+1]!='W'){
		  	block++;
		  }ncolorcount=0; ncount=0;
		  	for(xx=1;xx<=2;xx++){
  			for(yy=1;yy<=4;yy++){
  			if(BlokusBoard[i-xx][j+yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i-xx][j+yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=3&&BlokusBoard[i][j-1]!='W'){
		  	block++;
		  }
	 }ncolorcount=0; ncount=0;
	 if(BlokusBoard[i][j]=='N'&&BlokusBoard[i][j+1]==color&&BlokusBoard[i][j+2]==color&&BlokusBoard[i][j+3]=='W'){
	    for(xx=1;xx<=4;xx++){
  			for(yy=1;yy<=2;yy++){
  			if(BlokusBoard[i-xx][j+yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i-xx][j+yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=3&&BlokusBoard[i+1][j]!='W'){
		  	block++;
		  }ncolorcount=0; ncount=0;
		  	for(xx=1;xx<=4;xx++){
  			for(yy=1;yy<=2;yy++){
  			if(BlokusBoard[i+xx][j+yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i+xx][j+yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=3&&BlokusBoard[i-1][j]!='W'){
		  	block++;
		  }
	 }ncolorcount=0; ncount=0;
	 if(BlokusBoard[i][j]=='N'&&BlokusBoard[i][j-1]==color&&BlokusBoard[i][j-2]==color&&BlokusBoard[i][j-3]=='W'){
	 		for(xx=1;xx<=4;xx++){
  			for(yy=1;yy<=2;yy++){
  			if(BlokusBoard[i-xx][j-yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i-xx][j-yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=3&&BlokusBoard[i+1][j]!='W'){
		  	block++;
		  }ncolorcount=0; ncount=0;
		  	for(xx=1;xx<=4;xx++){
  			for(yy=1;yy<=2;yy++){
  			if(BlokusBoard[i+xx][j-yy]==ncolor){
  				ncolorcount++;
			  }
			  if(BlokusBoard[i+xx][j-yy]=='N'){
  				ncount++;
			  }
  		}
		  }
		  if(ncolorcount>=1&&ncount>=3&&BlokusBoard[i-1][j]!='W'){
		  	block++;
		  }
	 }ncolorcount=0; ncount=0;
}	
	}//check block
	return block;
 }
 int pnext=0;
 for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i][j]==color){
	  if(BlokusBoard[i+1][j]==ncolor||BlokusBoard[i-1][j]==ncolor||BlokusBoard[i][j+1]==ncolor||BlokusBoard[i][j-1]==ncolor||
	  BlokusBoard[i+1][j+1]==ncolor||BlokusBoard[i-1][j+1]==ncolor||BlokusBoard[i+1][j-1]==ncolor||BlokusBoard[i-1][j-1]==ncolor){
	  	pnext++;
  	}
	  }
	 }
}
 int next;
 int error;
  int checkerror(){
 	next=0;
 	error=0;
 	 for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i][j]==color){
	  if(BlokusBoard[i+1][j]==ncolor||BlokusBoard[i-1][j]==ncolor||BlokusBoard[i][j+1]==ncolor||BlokusBoard[i][j-1]==ncolor||
	  BlokusBoard[i+1][j+1]==ncolor||BlokusBoard[i-1][j+1]==ncolor||BlokusBoard[i+1][j-1]==ncolor||BlokusBoard[i-1][j-1]==ncolor){
	  	next++;
  	}
	  }
	 }
}
error=next-pnext;
  if(error==0){
  	error=1;
  }else{
  	error=0;
  }
	 return error;
 }
 int jump;
  int checkjump(){//測試若下了這步後
 	jump=0;
 	for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i][j]==color&&BlokusBoard[i][j+1]==ncolor&&BlokusBoard[i+1][j+1]!=color&&BlokusBoard[i+1][j]==ncolor){
  		if(BlokusBoard[i-1][j+1]=='N'&&BlokusBoard[i-1][j]=='N'){
  				jump++;
				  }else if(BlokusBoard[i+1][j-1]=='N'&&BlokusBoard[i][j-1]=='N'){
  		jump++;}
	}
	if(BlokusBoard[i][j]==color&&BlokusBoard[i][j+1]==ncolor&&BlokusBoard[i-1][j+1]!=color&&BlokusBoard[i-1][j]==ncolor){
  		if(BlokusBoard[i-1][j-1]=='N'&&BlokusBoard[i][j-1]=='N'){
  				jump++;
				  }else if(BlokusBoard[i+1][j+1]=='N'&&BlokusBoard[i+1][j]=='N'){
  		jump++;}
	}
	if(BlokusBoard[i][j]==color&&BlokusBoard[i][j-1]==ncolor&&BlokusBoard[i+1][j-1]!=color&&BlokusBoard[i+1][j]==ncolor){
  		if(BlokusBoard[i-1][j-1]=='N'&&BlokusBoard[i-1][j]=='N'){
  				jump++;
				  }else if(BlokusBoard[i+1][j+1]=='N'&&BlokusBoard[i][j+1]=='N'){
  		jump++;}
	}
	if(BlokusBoard[i][j]==color&&BlokusBoard[i][j-1]==ncolor&&BlokusBoard[i-1][j-1]!=color&&BlokusBoard[i-1][j]==ncolor){
  		if(BlokusBoard[i-1][j+1]=='N'&&BlokusBoard[i][j+1]=='N'){
  				jump++;
				  }else if(BlokusBoard[i+1][j-1]=='N'&&BlokusBoard[i+1][j]=='N'){
  		jump++;}
	}
}	
	}//check jump
	 return jump;
 }
 int slash;
  int checkslash(){//測試若下了這步後
 	slash=0;
 	for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i-1][j-1]!=color&&
	  BlokusBoard[i][j]=='N'&&BlokusBoard[i][j+1]==ncolor&&BlokusBoard[i+1][j+1]==color&&BlokusBoard[i+1][j]==ncolor){
	  	if(BlokusBoard[i-1][j]=='N'||BlokusBoard[i][j-1]=='N'){
  		slash++;}
	}
	if(BlokusBoard[i+2][j+2]!=color&&
	BlokusBoard[i][j]==color&&BlokusBoard[i][j+1]==ncolor&&BlokusBoard[i+1][j+1]=='N'&&BlokusBoard[i+1][j]==ncolor){
		if(BlokusBoard[i+2][j+1]=='N'||BlokusBoard[i+1][j+2]=='N'){
  		slash++;}
	}
	if(BlokusBoard[i-1][j+2]!=color&&
	BlokusBoard[i][j]==ncolor&&BlokusBoard[i][j+1]=='N'&&BlokusBoard[i+1][j+1]==ncolor&&BlokusBoard[i+1][j]==color){
		if(BlokusBoard[i-1][j+1]=='N'||BlokusBoard[i][j+2]=='N'){
  		slash++;}
	}
	if(BlokusBoard[i+2][j-1]!=color&&
	BlokusBoard[i][j]==ncolor&&BlokusBoard[i][j+1]==color&&BlokusBoard[i+1][j+1]==ncolor&&BlokusBoard[i+1][j]=='N'){
		if(BlokusBoard[i+2][j]=='N'||BlokusBoard[i+1][j-1]=='N'){
  		slash++;}
	}
}	
	}//check slash
	 return slash;
 }
 int defend;
  int checkdefend(){//測試若下了這步後
 	defend=0;
 	for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i-1][j]==color&&BlokusBoard[i][j-1]==color&&
	  BlokusBoard[i][j]=='N'&&BlokusBoard[i][j+1]==color&&BlokusBoard[i+1][j+1]==ncolor&&BlokusBoard[i+1][j]==color){
  		defend++;
	}
	if(BlokusBoard[i+2][j+1]==color&&BlokusBoard[i+1][j+2]==color&&
	BlokusBoard[i][j]==ncolor&&BlokusBoard[i][j+1]==color&&BlokusBoard[i+1][j+1]=='N'&&BlokusBoard[i+1][j]==color){
  		defend++;
	}
	if(BlokusBoard[i-1][j+1]==color&&BlokusBoard[i][j+2]==color&&
	BlokusBoard[i][j]==color&&BlokusBoard[i][j+1]=='N'&&BlokusBoard[i+1][j+1]==color&&BlokusBoard[i+1][j]==ncolor){
  		defend++;
	}
	if(BlokusBoard[i+2][j]==color&&BlokusBoard[i+1][j-1]==color&&
	BlokusBoard[i][j]==color&&BlokusBoard[i][j+1]==ncolor&&BlokusBoard[i+1][j+1]==color&&BlokusBoard[i+1][j]=='N'){
  		defend++;
	}
}	
	}//check defend
    return defend;
 }
 
 int superguard;
  int checksuperguard(){//測試若下了這步後
 	superguard=0;
 	for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i][j]=='N'&&BlokusBoard[i][j+1]==color&&BlokusBoard[i+1][j]==color&&BlokusBoard[i-1][j]==color&&BlokusBoard[i][j-1]==ncolor
	  &&BlokusBoard[i][j+2]!=ncolor&&BlokusBoard[i+1][j+1]!=ncolor&&BlokusBoard[i+2][j]!=ncolor&&BlokusBoard[i-2][j]!=ncolor&&BlokusBoard[i-1][j+1]!=ncolor){
	  	if(BlokusBoard[i-1][j-1]!=ncolor||BlokusBoard[i+1][j-1]!=ncolor){
  		superguard++;}
	}
	if(BlokusBoard[i][j]=='N'&&BlokusBoard[i][j+1]==color&&BlokusBoard[i+1][j]==color&&BlokusBoard[i-1][j]==ncolor&&BlokusBoard[i][j-1]==color
	&&BlokusBoard[i][j+2]!=ncolor&&BlokusBoard[i+1][j+1]!=ncolor&&BlokusBoard[i+2][j]!=ncolor&&BlokusBoard[i][j-2]!=ncolor&&BlokusBoard[i+1][j-1]!=ncolor){
  		if(BlokusBoard[i-1][j+1]!=ncolor||BlokusBoard[i-1][j-1]!=ncolor){
  		superguard++;}
	}
	if(BlokusBoard[i][j]=='N'&&BlokusBoard[i][j+1]==color&&BlokusBoard[i+1][j]==ncolor&&BlokusBoard[i-1][j]==color&&BlokusBoard[i][j-1]==color
	&&BlokusBoard[i][j+2]!=ncolor&&BlokusBoard[i-1][j+1]!=ncolor&&BlokusBoard[i-2][j]!=ncolor&&BlokusBoard[i][j-2]!=ncolor&&BlokusBoard[i-1][j-1]!=ncolor){
  		if(BlokusBoard[i+1][j-1]!=ncolor||BlokusBoard[i+1][j+1]!=ncolor){
  		superguard++;}
	}
	if(BlokusBoard[i][j]=='N'&&BlokusBoard[i][j+1]==ncolor&&BlokusBoard[i+1][j]==color&&BlokusBoard[i-1][j]==color&&BlokusBoard[i][j-1]==color
	&&BlokusBoard[i][j-2]!=ncolor&&BlokusBoard[i+1][j-1]!=ncolor&&BlokusBoard[i+2][j]!=ncolor&&BlokusBoard[i-2][j]!=ncolor&&BlokusBoard[i-1][j-1]!=ncolor){
  		if(BlokusBoard[i-1][j+1]!=ncolor||BlokusBoard[i+1][j+1]!=ncolor){
  		superguard++;}
	}
}	
	}//check superguard
    return superguard;
 }
 int selfcorner;
  int checkselfcorner(){//測試若下了這步後
 	selfcorner=0;
  	if(BlokusBoard[1][1]==color&&BlokusBoard[1][2]==color&&BlokusBoard[2][2]==color&&BlokusBoard[2][1]==color){
  		selfcorner++;
	}
	if(BlokusBoard[1][14]==color&&BlokusBoard[1][13]==color&&BlokusBoard[2][14]==color&&BlokusBoard[2][13]==color){
  		selfcorner++;
	}
	if(BlokusBoard[14][1]==color&&BlokusBoard[14][2]==color&&BlokusBoard[13][2]==color&&BlokusBoard[13][1]==color){
  		selfcorner++;
	}
	if(BlokusBoard[14][14]==color&&BlokusBoard[14][13]==color&&BlokusBoard[13][14]==color&&BlokusBoard[13][13]==color){
  		selfcorner++;
	}//check selfcorner
    return selfcorner;
 }
 int superblock;
 int checksuperblock(void){//測試若下了這步後
 	superblock=0;
   for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	 if(BlokusBoard[i][j]==color&&BlokusBoard[i+1][j]==ncolor&&BlokusBoard[i+2][j]==ncolor&&BlokusBoard[i+3][j]==ncolor&&BlokusBoard[i+4][j]=='W'){
  	 	if(BlokusBoard[i][j-1]!=ncolor&&BlokusBoard[i][j+1]!=ncolor){
	 	superblock++;}
	 }
	 if(BlokusBoard[i][j]==color&&BlokusBoard[i-1][j]==ncolor&&BlokusBoard[i-2][j]==ncolor&&BlokusBoard[i-3][j]==ncolor&&BlokusBoard[i-4][j]=='W'){
	 	if(BlokusBoard[i][j-1]!=ncolor&&BlokusBoard[i][j+1]!=ncolor){
	 	superblock++;}
	 }
	 if(BlokusBoard[i][j]==color&&BlokusBoard[i][j+1]==ncolor&&BlokusBoard[i][j+2]==ncolor&&BlokusBoard[i][j+3]==ncolor&&BlokusBoard[i][j+4]=='W'){
	 	if(BlokusBoard[i-1][j]!=ncolor&&BlokusBoard[i+1][j]!=ncolor){
	 	superblock++;}
	 }
	 if(BlokusBoard[i][j]==color&&BlokusBoard[i][j-1]==ncolor&&BlokusBoard[i][j-2]==ncolor&&BlokusBoard[i][j-3]==ncolor&&BlokusBoard[i][j-4]=='W'){
	 	if(BlokusBoard[i-1][j]!=ncolor&&BlokusBoard[i+1][j]!=ncolor){
	 	superblock++;}
	 }
	 if(BlokusBoard[i][j]==color&&BlokusBoard[i+1][j]==ncolor&&BlokusBoard[i+2][j]==ncolor&&BlokusBoard[i+3][j]=='W'){
	 	if(BlokusBoard[i][j-1]!=ncolor&&BlokusBoard[i][j+1]!=ncolor){
	 	superblock++;}
	 }
	 if(BlokusBoard[i][j]==color&&BlokusBoard[i-1][j]==ncolor&&BlokusBoard[i-2][j]==ncolor&&BlokusBoard[i-3][j]=='W'){
	 	if(BlokusBoard[i][j-1]!=ncolor&&BlokusBoard[i][j+1]!=ncolor){
	 	superblock++;}
	 }
	 if(BlokusBoard[i][j]==color&&BlokusBoard[i][j+1]==ncolor&&BlokusBoard[i][j+2]==ncolor&&BlokusBoard[i][j+3]=='W'){
	 	if(BlokusBoard[i-1][j]!=ncolor&&BlokusBoard[i+1][j]!=ncolor){
	 	superblock++;}
	 }
	 if(BlokusBoard[i][j]==color&&BlokusBoard[i][j-1]==ncolor&&BlokusBoard[i][j-2]==ncolor&&BlokusBoard[i][j-3]=='W'){
	 	if(BlokusBoard[i-1][j]!=ncolor&&BlokusBoard[i+1][j]!=ncolor){
	 	superblock++;}
	 }
}	
	}//check superblock
	return superblock;
 }
 int selfblock;
 int checkselfblock(void){//測試若下了這步後
 	selfblock=0;
   for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i+1][j]==color&&BlokusBoard[i+2][j]==color&&BlokusBoard[i+3][j]==color&&BlokusBoard[i+4][j]==color&&BlokusBoard[i+5][j]==color&&BlokusBoard[i+6][j]=='W'){
  	 	if(BlokusBoard[i+1][j-1]!=color&&BlokusBoard[i+2][j-1]!=color&&BlokusBoard[i+3][j-1]!=color&&BlokusBoard[i+4][j-1]!=color&&BlokusBoard[i+5][j-1]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i+1][j+1]!=color&&BlokusBoard[i+2][j+1]!=color&&BlokusBoard[i+3][j+1]!=color&&BlokusBoard[i+4][j+1]!=color&&BlokusBoard[i+5][j+1]!=color){
	 	selfblock++;}
	 }
    if(BlokusBoard[i-1][j]==color&&BlokusBoard[i-2][j]==color&&BlokusBoard[i-3][j]==color&&BlokusBoard[i-4][j]==color&&BlokusBoard[i-5][j]==color&&BlokusBoard[i-6][j]=='W'){
	 	if(BlokusBoard[i-1][j-1]!=color&&BlokusBoard[i-2][j-1]!=color&&BlokusBoard[i-3][j-1]!=color&&BlokusBoard[i-4][j-1]!=color&&BlokusBoard[i-5][j-1]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j+1]!=color&&BlokusBoard[i-2][j+1]!=color&&BlokusBoard[i-3][j+1]!=color&&BlokusBoard[i-4][j+1]!=color&&BlokusBoard[i-5][j+1]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i][j+1]==color&&BlokusBoard[i][j+2]==color&&BlokusBoard[i][j+3]==color&&BlokusBoard[i][j+4]==color&&BlokusBoard[i][j+5]==color&&BlokusBoard[i][j+6]=='W'){
	 	if(BlokusBoard[i+1][j+1]!=color&&BlokusBoard[i+1][j+2]!=color&&BlokusBoard[i+1][j+3]!=color&&BlokusBoard[i+1][j+4]!=color&&BlokusBoard[i+1][j+5]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j+1]!=color&&BlokusBoard[i-1][j+2]!=color&&BlokusBoard[i-1][j+3]!=color&&BlokusBoard[i-1][j+4]!=color&&BlokusBoard[i-1][j+5]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i][j-1]==color&&BlokusBoard[i][j-2]==color&&BlokusBoard[i][j-3]==color&&BlokusBoard[i][j-4]==color&&BlokusBoard[i][j-5]==color&&BlokusBoard[i][j-6]=='W'){
	 	if(BlokusBoard[i+1][j-1]!=color&&BlokusBoard[i+1][j-2]!=color&&BlokusBoard[i+1][j-3]!=color&&BlokusBoard[i+1][j-4]!=color&&BlokusBoard[i+1][j-5]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j-1]!=color&&BlokusBoard[i-1][j-2]!=color&&BlokusBoard[i-1][j-3]!=color&&BlokusBoard[i-1][j-4]!=color&&BlokusBoard[i-1][j-5]!=color){
	 	selfblock++;}
	 }
  	 if(BlokusBoard[i+1][j]==color&&BlokusBoard[i+2][j]==color&&BlokusBoard[i+3][j]==color&&BlokusBoard[i+4][j]==color&&BlokusBoard[i+5][j]=='W'){
  	 	if(BlokusBoard[i+1][j-1]!=color&&BlokusBoard[i+2][j-1]!=color&&BlokusBoard[i+3][j-1]!=color&&BlokusBoard[i+4][j-1]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i+1][j+1]!=color&&BlokusBoard[i+2][j+1]!=color&&BlokusBoard[i+3][j+1]!=color&&BlokusBoard[i+4][j+1]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i-1][j]==color&&BlokusBoard[i-2][j]==color&&BlokusBoard[i-3][j]==color&&BlokusBoard[i-4][j]==color&&BlokusBoard[i-5][j]=='W'){
	 	if(BlokusBoard[i-1][j-1]!=color&&BlokusBoard[i-2][j-1]!=color&&BlokusBoard[i-3][j-1]!=color&&BlokusBoard[i-4][j-1]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j+1]!=color&&BlokusBoard[i-2][j+1]!=color&&BlokusBoard[i-3][j+1]!=color&&BlokusBoard[i-4][j+1]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i][j+1]==color&&BlokusBoard[i][j+2]==color&&BlokusBoard[i][j+3]==color&&BlokusBoard[i][j+4]==color&&BlokusBoard[i][j+5]=='W'){
	 	if(BlokusBoard[i+1][j+1]!=color&&BlokusBoard[i+1][j+2]!=color&&BlokusBoard[i+1][j+3]!=color&&BlokusBoard[i+1][j+4]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j+1]!=color&&BlokusBoard[i-1][j+2]!=color&&BlokusBoard[i-1][j+3]!=color&&BlokusBoard[i-1][j+4]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i][j-1]==color&&BlokusBoard[i][j-2]==color&&BlokusBoard[i][j-3]==color&&BlokusBoard[i][j-4]==color&&BlokusBoard[i][j-5]=='W'){
	 	if(BlokusBoard[i+1][j-1]!=color&&BlokusBoard[i+1][j-2]!=color&&BlokusBoard[i+1][j-3]!=color&&BlokusBoard[i+1][j-4]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j-1]!=color&&BlokusBoard[i-1][j-2]!=color&&BlokusBoard[i-1][j-3]!=color&&BlokusBoard[i-1][j-4]!=color){
	 	selfblock++;}
	 }
  	 if(BlokusBoard[i+1][j]==color&&BlokusBoard[i+2][j]==color&&BlokusBoard[i+3][j]==color&&BlokusBoard[i+4][j]=='W'){
  	 	if(BlokusBoard[i+1][j-1]!=color&&BlokusBoard[i+2][j-1]!=color&&BlokusBoard[i+3][j-1]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i+1][j+1]!=color&&BlokusBoard[i+2][j+1]!=color&&BlokusBoard[i+3][j+1]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i-1][j]==color&&BlokusBoard[i-2][j]==color&&BlokusBoard[i-3][j]==color&&BlokusBoard[i-4][j]=='W'){
	 	if(BlokusBoard[i-1][j-1]!=color&&BlokusBoard[i-2][j-1]!=color&&BlokusBoard[i-3][j-1]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j+1]!=color&&BlokusBoard[i-2][j+1]!=color&&BlokusBoard[i-3][j+1]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i][j+1]==color&&BlokusBoard[i][j+2]==color&&BlokusBoard[i][j+3]==color&&BlokusBoard[i][j+4]=='W'){
	 	if(BlokusBoard[i+1][j+1]!=color&&BlokusBoard[i+1][j+2]!=color&&BlokusBoard[i+1][j+3]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j+1]!=color&&BlokusBoard[i-1][j+2]!=color&&BlokusBoard[i-1][j+3]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i][j-1]==color&&BlokusBoard[i][j-2]==color&&BlokusBoard[i][j-3]==color&&BlokusBoard[i][j-4]=='W'){
	 	if(BlokusBoard[i+1][j-1]!=color&&BlokusBoard[i+1][j-2]!=color&&BlokusBoard[i+1][j-3]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j-1]!=color&&BlokusBoard[i-1][j-2]!=color&&BlokusBoard[i-1][j-3]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i+1][j]==color&&BlokusBoard[i+2][j]==color&&BlokusBoard[i+3][j]=='W'){
	 	if(BlokusBoard[i+1][j-1]!=color&&BlokusBoard[i+2][j-1]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i+1][j+1]!=color&&BlokusBoard[i+2][j+1]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i-1][j]==color&&BlokusBoard[i-2][j]==color&&BlokusBoard[i-3][j]=='W'){
	 	if(BlokusBoard[i-1][j-1]!=color&&BlokusBoard[i-2][j-1]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j+1]!=color&&BlokusBoard[i-2][j+1]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i][j+1]==color&&BlokusBoard[i][j+2]==color&&BlokusBoard[i][j+3]=='W'){
	 	if(BlokusBoard[i+1][j+1]!=color&&BlokusBoard[i+1][j+2]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j+1]!=color&&BlokusBoard[i-1][j+2]!=color){
	 	selfblock++;}
	 }
	 if(BlokusBoard[i][j-1]==color&&BlokusBoard[i][j-2]==color&&BlokusBoard[i][j-3]=='W'){
	 	if(BlokusBoard[i+1][j-1]!=color&&BlokusBoard[i+1][j-2]!=color){
	 	selfblock++;}
	 	 else if(BlokusBoard[i-1][j-1]!=color&&BlokusBoard[i-1][j-2]!=color){
	 	selfblock++;}
	 }
}	
	}//check selfblock
	return selfblock;
 }
 for(i=0;i<=44;i++){//重置雙方可放置的區域座標(不一定需要) 
colormemoryrow[i]=0;
colormemorycol[i]=0;
ncolormemoryrow[i]=0;
ncolormemorycol[i]=0;}
   if(LeftPattern[16]!='0'){//第一步定式 
   	if(color=='R'){
   BlokusBoard[5][5]=color;
   BlokusBoard[6][5]=color;
   BlokusBoard[7][5]=color;
   BlokusBoard[6][4]=color;
   BlokusBoard[6][6]=color;
     LeftPattern[16]='0';
     cross=0;
	 }else if(BlokusBoard[5][5]=='N'){
    BlokusBoard[5][5]=color;
   BlokusBoard[6][5]=color;
   BlokusBoard[7][5]=color;
   BlokusBoard[6][4]=color;
   BlokusBoard[6][6]=color;
     LeftPattern[16]='0';
     cross=0;
	 }else{
   BlokusBoard[10][10]=color;
   BlokusBoard[9][10]=color;
   BlokusBoard[8][10]=color;
   BlokusBoard[9][9]=color;
   BlokusBoard[9][11]=color;
   LeftPattern[16]='0';
     cross=0;
	 }
}

if(cross==1){//非定式(以後)下法 
	
   for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i][j]=='N'&&BlokusBoard[i+1][j]!=ncolor&&BlokusBoard[i-1][j]!=ncolor&&BlokusBoard[i][j+1]!=ncolor&&BlokusBoard[i][j-1]!=ncolor){
	 if(BlokusBoard[i-1][j-1]==ncolor||BlokusBoard[i+1][j-1]==ncolor||BlokusBoard[i-1][j+1]==ncolor||BlokusBoard[i+1][j+1]==ncolor){
	 	ncolormemoryrow[ncolorp]=i;
	 	ncolormemorycol[ncolorp]=j;
	 	ncolorp++;//紀錄敵方可放格子數
	}	
	 }
}	
	}//check ncolorp
//printf("%d,\n",ncolorp);
 for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(BlokusBoard[i][j]=='N'&&BlokusBoard[i+1][j]!=color&&BlokusBoard[i-1][j]!=color&&BlokusBoard[i][j+1]!=color&&BlokusBoard[i][j-1]!=color){
	 if(BlokusBoard[i-1][j-1]==color||BlokusBoard[i+1][j-1]==color||BlokusBoard[i-1][j+1]==color||BlokusBoard[i+1][j+1]==color){
	 	colormemoryrow[colorp]=i;
	 	colormemorycol[colorp]=j;
	 	colorp++;//紀錄我方可放格子數
	}	
	 }
}	
	}//check colorp
//printf("%d,\n",colorp);
   for(x=0;x<colorp;x++){
   	 c=colormemoryrow[x];
   	 d=colormemorycol[x];
   	for(k=1;k<=313;k++){//將每一個能放的步法模擬並評分,得出最高分的步法 
   		put(k,c,d);
   		if(BlokusBoard[c][d]!='N'){
   			cc=checkcp();
   			cn=checkncp();
   			cb=checkblock();
   			cs=checkslash();
   			cd=checkdefend();
   			csb=checksuperblock();
   			cssb=checkselfblock();
   			csg=checksuperguard();
   			csc=checkselfcorner();
   			cnn=checknnext();
   			ce=checkerror();
   			cj=checkjump();
   			t=1*(cc)+3*(cn)+6*(cb)+5*(cs)+8*(cd)+10*(csb)+3*(csg)+2*(cnn)+4*(cj)-4*(cssb)-3*(csc)-10*(ce);
   			if(k>=2&&k<=5){
   				t=t+5;
			   }
			   if(k>=6&&k<=21){
   				t=t+10;
			   }
			   if(k>=22&&k<=81){
   				t=t+12;
			   }
			   if(k>=82&&k<=313){
   				t=t+15;
			   }
   			//printf("%d,%d,%d,%d,%d,%d\n",k,c,d,cc,cn,t);
   		if(t>=tp){
   			tp=t;
bestput=k;
bestrow=c;
bestcol=d;}
//printf("%d,%d,%d,%d\n",bestput,bestrow,bestcol,tp);
}
for(m=0;m<=15;m++){//重置盤面 
	for(n=0;n<=15;n++){
		if(m==0||n==0){
			BlokusBoard[m][n]='W';
		}else if(m==15||n==15){
			BlokusBoard[m][n]='W';
		}else{
			BlokusBoard[m][n]=blokusboard[m-1][n-1];
		}
	}
}

 		
}

}//check 
for(m=0;m<=15;m++){//重置盤面
	for(n=0;n<=15;n++){
		if(m==0||n==0){
			BlokusBoard[m][n]='W';
		}else if(m==15||n==15){
			BlokusBoard[m][n]='W';
		}else{
			BlokusBoard[m][n]=blokusboard[m-1][n-1];
		}
	}
}
//printf("%d,%d,%d\n",bestput,bestrow,bestcol);
put(bestput,bestrow,bestcol);//放置最好的放法 
if(bestput==1){//將這回合使用的pattern由1->0 
	LeftPattern[0]='0';
}
if(bestput>=2&&bestput<=5){
	LeftPattern[1]='0';
}
if(bestput>=6&&bestput<=17){
	LeftPattern[2]='0';
}
if(bestput>=18&&bestput<=21){
	LeftPattern[3]='0';
}
if(bestput>=22&&bestput<=25){
	LeftPattern[4]='0';
}
if(bestput>=26&&bestput<=49){
	LeftPattern[5]='0';
}
if(bestput>=50&&bestput<=61){
	LeftPattern[6]='0';
}
if(bestput>=62&&bestput<=77){
	LeftPattern[7]='0';
}
if(bestput>=78&&bestput<=81){
	LeftPattern[8]='0';
}
if(bestput>=82&&bestput<=113){
	LeftPattern[9]='0';
}
if(bestput>=114&&bestput<=129){
	LeftPattern[10]='0';
}
if(bestput>=130&&bestput<=145){
	LeftPattern[11]='0';
}
if(bestput>=146&&bestput<=161){
	LeftPattern[12]='0';
}
if(bestput>=162&&bestput<=181){
	LeftPattern[13]='0';
}
if(bestput>=182&&bestput<=197){
	LeftPattern[14]='0';
}
if(bestput>=198&&bestput<=221){
	LeftPattern[17]='0';
}
if(bestput>=222&&bestput<=253){
	LeftPattern[18]='0';
}
if(bestput>=254&&bestput<=277){
	LeftPattern[19]='0';
}
if(bestput>=278&&bestput<=281){
	LeftPattern[20]='0';
}
if(bestput>=282&&bestput<=313){
	LeftPattern[15]='0';
}
}
for(i=0;i<=13;i++){
	for(j=0;j<=13;j++){
	newblokusboard[i][j]=BlokusBoard[i+1][j+1];	
	}
}
int difference=0;
for(i=0;i<=13;i++){
	for(j=0;j<=13;j++){
	if(newblokusboard[i][j]!=blokusboard[i][j]){
		difference++;
	}	
	}
}
//printf("%d\n",difference);
if(difference!=0){//若沒有可放置的步法則不輸出txt 
char output[500];
for(i=0;i<=499;i++){
	output[i]='\0';
}
for(i=0;i<=13;i++){//輸出BlokusBoard.txt 
	for(j=0;j<=13;j++){
		char trans[2]={newblokusboard[i][j],'\0'};
	strcat(output,trans);
	if(j==13){
		strcat(output,"\n");
	}else{
		strcat(output,",");
	}
}
}
char output1[100];
for(i=0;i<=99;i++){//輸出LeftPattern.txt
	output1[i]='\0';
}
strcat(output1,"\n");
strcat(output1,"[");
for(i=0;i<=20;i++){
		char trans[2]={LeftPattern[i],'\0'};
	strcat(output1,trans);
	if(i!=20){
	strcat(output1,",");
}else{
	strcat(output1,"]");
}
}

//printf("%s\n",output);
//printf("%s\n",output1);
writeFile(argv[2],output); 
writeFilea(argv[3],output1); 

}
 /*for(i=0;i<=15;i++){
  for(j=0;j<=15;j++){
  	if(j!=15){
	printf("%c",BlokusBoard[i][j]);	
}else{
	printf("%c\n",BlokusBoard[i][j]);
}
}	
	}//輸出blokusboard */

return 0;
}


