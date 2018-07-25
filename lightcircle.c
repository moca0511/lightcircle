
//C������K�P�@�ŏI�ۑ�@���C�g�T�[�N���Q�[��
//R18E1002�@R1A�@�����~��
//�Q�O�P�W�E�O�V�E�Q�S

#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

#define RIGHT_MOVE 1
#define LEFT_MOVE 3
#define UP_MOVE 2
#define DOWN_MOVE 4

int asiato[21][61];//�ړ�����
int i,j;//���[�v����
int x,y;    //player����@�ʒu
int houkou; //�@�@�@�@�@�@ ����
int ex2,ey2,ex1,ey1;    //enemy���� �ʒu
int ehoukou2,ehoukou1;  //          ����
int movecount;//�ړ���
char gamemode;//��Փx
int HIGHSCORE=0;//HIGHSCORE�����l�ݒ�
int score;//�_��
int speed;//�ړ����x

void gotoXY(int x,int y);//�ʒu�ړ�
void setColor(int color);//�F�ύX
void asiato_0(void);//�ړ�����������
void TITLE_BORD(void);//�^�C�g��
void GAME_BORD(void);//�v���C���
void SUB_BORD(void);//�Q�[�����\��
void ENEMY1(void);//�G�ړ��E�\��
void ENEMY2(void);//
void PLAYER_MOVE(void);//Player�ړ��E�\��
int Xlimit(int xl);     //�ړ��͈͏���w��
int Ylimit(int yl);     //
int ehoukoulimit(int a);  //
void GAME_SCORE(void);//�_���v�Z


int main(void)
{
    srand((int)time(NULL));
    char end;
    

    do{
        TITLE_BORD();//�^�C�g����ʕ\��
        asiato_0();//�z�񏉊���
        x=40;       //�����ʒu�w��
        y=10;       //
        ex2=60;     //
        ey2=20;     //
        ex1=0;      //
        ey1=0;      //
        movecount=1;//�X�R�A�v�Z�p�J�E���g
        speed=100;  //�������x�ݒ�
        ehoukou2=LEFT_MOVE; //���������ݒ�
        ehoukou1=RIGHT_MOVE;//
        houkou=RIGHT_MOVE;  //

        GAME_BORD();//�Q�[���{�[�h�\��
        while(GetAsyncKeyState(VK_ESCAPE)==0){  //Esc���͂܂ő��s
            
            ENEMY1();//enemy1�z�u�E�ړ�

            if(gamemode=='3'){//HARDMODE�Ȃ�enemy2�z�u�E�ړ�
                ENEMY2();
            }
            movecount++;//�J�E���g�X�V
            PLAYER_MOVE();//Player�z�u�E�ړ�
            if(asiato[y][x]==3){//��������E���S�ʒu�Ɉ�
                gotoXY(x,y);
                setColor(0xdf);
                printf("X");
                break;//�Q�[���I�����X�R�A��ʂ�
            }
            SUB_BORD();//�Q�[�����\��
            Sleep(speed);
            if(gamemode!='1'&&movecount%20==0&&speed>=50)speed=speed-5;//gamemode��EASY�̎��ȊO20�񎖂ɃX�s�[�h�A�b�v
        }
        setColor(0x7c);
        gotoXY(63,19);
        printf("end? y/n:>");//�I������
	    fflush(stdin);
        end = getchar();
        fflush(stdin);
        }while(end!='y');//end�ɂ������͂����܂ŌJ��Ԃ�
    return 0;
}


void GAME_SCORE(void){
    int count=0;
    for(i=0;i<61;i++){
        for(j=0;j<21;j++){
            if(asiato[j][i]==1)count++;//player���ʂ����}�X�̐��J�E���g
        }
    }
    score=count*gamemode/10;//�_���v�Z
    if(gamemode=='3'){  //��Փx���Ƃɉ��_
        score=score*3;
    }
    if(gamemode=='2'){
        score=score*2; 
    }
    if(score>HIGHSCORE)HIGHSCORE=score;//�ō����_�𒴂�����HIGHTSCORE�X�V
    return;
}

void SUB_BORD(void){    //�Q�[�������\��
    setColor(0x70);
    gotoXY(62,3);
    printf("���C�g�T�[�N���Q�[��");
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
    gotoXY(x,y);    //�����ʒu���͑O��ړ��ʒu�Ƀ}�[�J�[�\��
    setColor(0x9f); //
    printf("@");    //
    if(GetAsyncKeyState(VK_RIGHT)!=0&&houkou!=LEFT_MOVE)houkou=RIGHT_MOVE;  //�㉺���E���͂ňړ������w��
    if(GetAsyncKeyState(VK_LEFT)!=0&&houkou!=RIGHT_MOVE)houkou=LEFT_MOVE;   //
    if(GetAsyncKeyState(VK_UP)!=0&&houkou!=DOWN_MOVE)houkou=UP_MOVE;        //
    if(GetAsyncKeyState(VK_DOWN)!=0&&houkou!=UP_MOVE)houkou=DOWN_MOVE;      //
    if(houkou==RIGHT_MOVE)x++;  //�ړ������Ɉʒu�ړ�
    if(houkou==LEFT_MOVE)x--;   //
    if(houkou==UP_MOVE)y--;     //
    if(houkou==DOWN_MOVE)y++;   //
    x=Xlimit(x);//XY�������E�ړ�
    y=Ylimit(y);//
    if(asiato[y][x]!=0){//���łɒN���ʂ��Ă�����asiato�ɂR
        asiato[y][x]=3;   
    }else{
        asiato[y][x]=1;//�N���ʂ��Ă��Ȃ����asiato�ɂP
    }
    return;
}

void TITLE_BORD(void){  //�^�C�g����ʁE�Q�[�����[�h����

    gotoXY(0,0);                    //�{�[�h�w�i�\��
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
    printf("���C�g�T�[�N���Q�[��\n\n");
    
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
    printf("PLAYER MOVE:��������");

    do{     //�Q�[�����[�h�I�����[�v
    setColor(0x2f);
    gotoXY(12,12);
    printf("GAMEMODE  1:EASY 2:NOMAL 3:HARD >:"); 
        gotoXY(46,12);
        scanf("%c",&gamemode);
        if(gamemode>'3'||gamemode<'1'){ //gamemode���̓G���[����
            gotoXY(21,14);
            setColor(0x2c);
            printf("gamemode error!");
            fflush(stdin);
            for(i=46;i<61;i++){ //���͓��e��w�i�ŏ㏑������
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


void GAME_BORD(void){   //play���
    setColor(0x22);
    gotoXY(0,0);
    for(j=0;j<21;j++){
        for(i=0;i<61;i++){
            printf("+");
        }
        printf("\n");
    }
}

void ENEMY1(void){  //enemy1�ړ��E�\��
    int eran1;
    gotoXY(ex1,ey1);//�����ʒu���͑O��ʒu�Ɉړ��A�}�[�J�[�\��
    setColor(0xc0); //
    printf("*");    //
    if(movecount%5==0){//5��ړ����邲�Ƃɕ����]��
        eran1=rand()%3;
        switch(eran1){
            case 0:
                ehoukou1++;//����
                break;
            case 1:
                ehoukou1--;//�E��
                break;
            case 3: //���̂܂�
                break;
        }
    }
    ehoukou1=ehoukoulimit(ehoukou1);//ehoukou���P�`�S�ɂȂ�悤�ɐ���

    if(ehoukou1==RIGHT_MOVE)ex1++;  //�ʒu�ύX
    if(ehoukou1==LEFT_MOVE)ex1--;   //
    if(ehoukou1==UP_MOVE)ey1--;     //
    if(ehoukou1==DOWN_MOVE)ey1++;   //
    
    ex1=Xlimit(ex1);//�ʒu����
    ey1=Ylimit(ey1);//
    if(asiato[ey1][ex1]!=1){    //�_���v�Z�łP���J�E���g���邽�߁A�㏑�����Ȃ��悤��
        asiato[ey1][ex1]=2;     //�ړ��ꏊ�ɂQ����
    }
    return;
}

void ENEMY2(void){  //enemy2�ړ��E�\��
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


void asiato_0(void){    //�ړ��������Z�b�g
    for(j=0;j<21;j++){
        for(i=0;i<61;i++){
            asiato[j][i]=0;
        }
    }
    return;
}

int Xlimit(int xl){ //X������
    if(xl>60)xl=0;
    if(xl<0)xl=60;

    return xl;
}
int Ylimit(int yl){ //Y������
    if(yl<0)yl=20;
    if(yl>20)yl=0;
    return yl;
}

int ehoukoulimit(int a){    //��������
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