#ifndef OPSYSTEM_UICOLLECTION_H
#define OPSYSTEM_UICOLLECTION_H

#include <iostream>
using namespace std;

class UiCollection{
public: //���캯���������ʼ������
    UiCollection()= default;

public: //����Ϊ���нӿ�

    //����ָ���
    static void printLine(){
        cout<<"---------------------"<<endl;
    }


    //������ͣ
    static void pause(){
        int temp;
        printLine();
        cout << "��������ָ��ز˵���" ;
        cin >> temp;
    }


    static void pauseAndClear(){
        pause();
        clear();
    }


    //���ѡ���б��������û������ָ�����Ƿ�ָ����ָ��0���˳���
    static int choices(const string& title, int numOfChoices, string choiceMenu[], bool isMainMenu = false){
        int cmdInput;
        do{
            //���������ѡָ���б�
            printChoice(title, numOfChoices, choiceMenu, isMainMenu);
            //�����û������ָ�Ĭ��ָ��0Ϊ�˳������˵�
            cin >> cmdInput;
            //��������ָ����ָ��У�����ֱ�ӷ��ظ�ָ��
            for(int cmd = 0; cmd <= numOfChoices; cmd++){
                if(cmd == cmdInput) {
                    return cmd;
                }
            } //end for

            //δ�ҵ���ָ���Ҫ����������
            clear();
            printLine();
            cout << "�Ƿ�ָ�" << endl <<"���������룡" << endl;
            printLine();
        }while(cmdInput);
        return 0;
    } //end define


    //����������ͨ������100��������
    static void clear(){
        for(int count = 0; count < 100; count++){
            cout << endl;
        }
    }


private: //����˽�й���ģ��
    //���ѡ��ָ����Ϣ
    static void printChoice(const string& title, int numOfChoices, string choiceInfo[], bool isMainMenu = false){
        if(title != "false")cout << title << endl;
        printLine();
        for(int index = 0; index < numOfChoices; index++){
            cout<<index+1<<"��";
            cout<<choiceInfo[index]<<endl;
        }
        if(!isMainMenu){
            cout << "0��������һ���˵�" << endl;
        }else{
            //��Ϊ���˵���ָ��0ӦΪ�˳�ϵͳ
            cout << "0���˳�ϵͳ" << endl;
        }
        printLine();
        cout << "������ָ�" << endl;
    }
};

#endif //OPSYSTEM_UICOLLECTION_H