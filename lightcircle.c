
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

#define RIGHT_MOVE 1
#define LEFT_MOVE 3
#define UP_MOVE 2
#define DOWN_MOVE 4

int asiato[21][61];//移動履歴
int i,j;//ループ制御
int x,y;    //player制御　位置
int houkou; //　　　　　　 方向
int ex2,ey2,ex1,ey1;    //enemy制御 位置
int ehoukou2,ehoukou1;  //          方向
int movecount;//移動回数
char gamemode;//難易度
int HIGHSCORE=0;//HIGHSCORE初期値設定
int score;//点数
int speed;//移動速度

void gotoXY(int x,int y);//位置移動
void setColor(int color);//色変更
void asiato_0(void);//移動履歴初期化
void TITLE_BORD(void);//タイトル
void GAME_BORD(void);//プレイ画面
void SUB_BORD(void);//ゲーム情報表示
void ENEMY1(void);//敵移動・表示
void ENEMY2(void);//
void PLAYER_MOVE(void);//Player移動・表示
int Xlimit(int xl);     //移動範囲上限指定
int Ylimit(int yl);     //
int ehoukoulimit(int a);  //
void GAME_SCORE(void);//点数計算


int main(void)
{
    srand((int)time(NULL));
    char end;
    

    do{
        TITLE_BORD();//タイトル画面表示
        asiato_0();//配列初期化
        x=40;       //初期位置指定
        y=10;       //
        ex2=60;     //
        ey2=20;     //
        ex1=0;      //
        ey1=0;      //
        movecount=1;//スコア計算用カウント
        speed=100;  //初期速度設定
        ehoukou2=LEFT_MOVE; //初期方向設定
        ehoukou1=RIGHT_MOVE;//
        houkou=RIGHT_MOVE;  //

        GAME_BORD();//ゲームボード表示
        while(GetAsyncKeyState(VK_ESCAPE)==0){  //Esc入力まで続行
            
            ENEMY1();//enemy1配置・移動

            if(gamemode=='3'){//HARDMODEならenemy2配置・移動
                ENEMY2();
            }
            movecount++;//カウント更新
            PLAYER_MOVE();//Player配置・移動
            if(asiato[y][x]==3){//負け判定・死亡位置に印
                gotoXY(x,y);
                setColor(0xdf);
                printf("X");
                break;//ゲーム終了しスコア画面へ
            }
            SUB_BORD();//ゲーム情報表示
            Sleep(speed);
            if(gamemode!='1'&&movecount%20==0&&speed>=50)speed=speed-5;//gamemodeがEASYの時以外20回事にスピードアップ
        }
        setColor(0x7c);
        gotoXY(63,19);
        printf("end? y/n:>");//終了判定
	    fflush(stdin);
        end = getchar();
        fflush(stdin);
        }while(end!='y');//endにｙが入力されるまで繰り返し
    return 0;
}


void GAME_SCORE(void){
    int count=0;
    for(i=0;i<61;i++){
        for(j=0;j<21;j++){
            if(asiato[j][i]==1)count++;//playerが通ったマスの数カウント
        }
    }
    score=count*gamemode/10;//点数計算
    if(gamemode=='3'){  //難易度ごとに加点
        score=score*3;
    }
    if(gamemode=='2'){
        score=score*2; 
    }
    if(score>HIGHSCORE)HIGHSCORE=score;//最高得点を超えたらHIGHTSCORE更新
    return;
}

void SUB_BORD(void){    //ゲーム中情報表示
    setColor(0x70);
    gotoXY(62,3);
    printf("ライトサークルゲーム");
    gotoXY(63,5);
    printf("GAMEMODE:");
    switch(gamemode){
        case '1':
            printf("EASY");
            break;
        case '2':
            printf("NORMAL");
            break;
        case '3':
            printf("HARD");
            break;
    }
    GAME_SCORE();
    gotoXY(63,7);
    printf("HIGHSCORE:%d",HIGHSCORE);
    gotoXY(63,9);
    
    printf("SCORE:%d",score);
    gotoXY(63,11);
    printf("SPEED:%3d",speed);
    

    

}

void PLAYER_MOVE(void){
    gotoXY(x,y);    //初期位置又は前回移動位置にマーカー表示
    setColor(0x9f); //
    printf("@");    //
    if(GetAsyncKeyState(VK_RIGHT)!=0&&houkou!=LEFT_MOVE)houkou=RIGHT_MOVE;  //上下左右入力で移動方向指定
    if(GetAsyncKeyState(VK_LEFT)!=0&&houkou!=RIGHT_MOVE)houkou=LEFT_MOVE;   //
    if(GetAsyncKeyState(VK_UP)!=0&&houkou!=DOWN_MOVE)houkou=UP_MOVE;        //
    if(GetAsyncKeyState(VK_DOWN)!=0&&houkou!=UP_MOVE)houkou=DOWN_MOVE;      //
    if(houkou==RIGHT_MOVE)x++;  //移動方向に位置移動
    if(houkou==LEFT_MOVE)x--;   //
    if(houkou==UP_MOVE)y--;     //
    if(houkou==DOWN_MOVE)y++;   //
    x=Xlimit(x);//XY上限判定・移動
    y=Ylimit(y);//
    if(asiato[y][x]!=0){//すでに誰か通っていたらasiatoに３
        asiato[y][x]=3;   
    }else{
        asiato[y][x]=1;//誰も通っていなければasiatoに１
    }
    return;
}

void TITLE_BORD(void){  //タイトル画面・ゲームモード処理

    gotoXY(0,0);                    //ボード背景表示
    for(j=0;j<21;j++){              //
        setColor(0x22);             //
        for(i=0;i<83;i++){          //
            if(i>60){               //
                setColor(0x77);     //
                if(i==61){          //
                    setColor(0xff); //
                }                   //
            }                       //
            printf("+");            //
        }                           //
        printf("\n");               //
    }                               //
    for(j=0;j<22;j++){              //
        setColor(0xff);             //
        gotoXY(83,j);               //
        printf("+");                //
    }                               //
    for(i=0;i<=83;i++){             //
        setColor(0xff);             //
        gotoXY(i,21);               //
        printf("+");                //
    }                               //

    setColor(0x2f);
    gotoXY(18,7);
    printf("ライトサークルゲーム\n\n");
    
    setColor(0x70);
    gotoXY(63,7);
    printf("HIGHSCORE:%d",HIGHSCORE);
    gotoXY(63,14);
    printf("PLAYER:");
    setColor(0x9f);
    printf("@");
    gotoXY(63,15);
    setColor(0x70);
    printf("ENEMY:");
    setColor(0xc0);
    printf("*");
    setColor(0x70);
    printf(",");
    setColor(0xe0);
    printf("*");
    gotoXY(63,17);
    setColor(0x70);
    printf("PLAYER MOVE:↑↓←→");

    do{     //ゲームモード選択ループ
    setColor(0x2f);
    gotoXY(12,12);
    printf("GAMEMODE  1:EASY 2:NOMAL 3:HARD >:"); 
        gotoXY(46,12);
        scanf("%c",&gamemode);
        if(gamemode>'3'||gamemode<'1'){ //gamemode入力エラー判定
            gotoXY(21,14);
            setColor(0x2c);
            printf("gamemode error!");
            fflush(stdin);
            for(i=46;i<61;i++){ //入力内容を背景で上書き消去
                gotoXY(i,12);
                setColor(0x22);
                printf("+");
            }
        }
    }while(gamemode>'3'||gamemode<'1');
    
    fflush(stdin);
    gotoXY(18,16);
    printf("Press Enter to start!");
    getchar();
    fflush(stdin);
    return;
}


void GAME_BORD(void){   //play画面
    setColor(0x22);
    gotoXY(0,0);
    for(j=0;j<21;j++){
        for(i=0;i<61;i++){
            printf("+");
        }
        printf("\n");
    }
}

void ENEMY1(void){  //enemy1移動・表示
    int eran1;
    gotoXY(ex1,ey1);//初期位置又は前回位置に移動、マーカー表示
    setColor(0xc0); //
    printf("*");    //
    if(movecount%5==0){//5回移動するごとに方向転換
        eran1=rand()%3;
        switch(eran1){
            case 0:
                ehoukou1++;//左折
                break;
            case 1:
                ehoukou1--;//右折
                break;
            case 3: //そのまま
                break;
        }
    }
    ehoukou1=ehoukoulimit(ehoukou1);//ehoukouが１～４になるように制限

    if(ehoukou1==RIGHT_MOVE)ex1++;  //位置変更
    if(ehoukou1==LEFT_MOVE)ex1--;   //
    if(ehoukou1==UP_MOVE)ey1--;     //
    if(ehoukou1==DOWN_MOVE)ey1++;   //
    
    ex1=Xlimit(ex1);//位置制限
    ey1=Ylimit(ey1);//
    if(asiato[ey1][ex1]!=1){    //点数計算で１をカウントするため、上書きしないように
        asiato[ey1][ex1]=2;     //移動場所に２を代入
    }
    return;
}

void ENEMY2(void){  //enemy2移動・表示
    int eran2;
    gotoXY(ex2,ey2);
    setColor(0xe0);
    printf("*");
    if(movecount%5==0){
        eran2=rand()%3;
        switch(eran2){
            case 0:
                ehoukou2++;
                break;
            case 1:
                ehoukou2--;
                break;
            case 3:
                break;
        }
    }
    ehoukou2=ehoukoulimit(ehoukou2);

    if(ehoukou2==RIGHT_MOVE)ex2++;
    if(ehoukou2==LEFT_MOVE)ex2--;
    if(ehoukou2==UP_MOVE)ey2--;
    if(ehoukou2==DOWN_MOVE)ey2++;
    

    ex2=Xlimit(ex2);
    ey2=Ylimit(ey2);
    if(asiato[ey2][ex2]!=1){
        asiato[ey2][ex2]=2;
    }
    return;
}


void asiato_0(void){    //移動履歴リセット
    for(j=0;j<21;j++){
        for(i=0;i<61;i++){
            asiato[j][i]=0;
        }
    }
    return;
}

int Xlimit(int xl){ //X軸制限
    if(xl>60)xl=0;
    if(xl<0)xl=60;

    return xl;
}
int Ylimit(int yl){ //Y軸制限
    if(yl<0)yl=20;
    if(yl>20)yl=0;
    return yl;
}

int ehoukoulimit(int a){    //方向制限
    if(a>4)a=1;
    if(a<1)a=4;
    return a;
}

void gotoXY(int x,int y){
    COORD pos;
    pos.X= x;
    pos.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    return;
}

void setColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    return;
}
