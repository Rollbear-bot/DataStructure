//
// Created by 13592 on 2019/11/11.
// ʵ���ģ�����ʽ����

#ifndef DATASTRUCTURE_MENU4_H
#define DATASTRUCTURE_MENU4_H

#include "PolyByList.h"
#include "PolyByArr.h"
#include "PolyByLinearTable.h"

class Menu4{
public:
    Menu4(){}

public:
    //������Բ˵�
    static void menu(){
        string menuChoice[] = {"����ʽ������ʵ��", "����ʽ������ʵ��", "����ʽ��ѭ���ʵ��"};
        do{
            cmd = UiCollection::choices("����ʽ���Բ˵�", 3, menuChoice, false);
            switch(cmd){
                case 1:
                    polyMenu<PolyByList<int>>();
                    break;

                case 2:
                    polyMenu<PolyByArr<int>>();
                    break;

                case 3:
                    polyMenu<PolyByLinearTable<int>>();
                    break;

                default:
                    break;
            }
        }while (cmd);
    }


protected:
    //����ʽ�����˵�������ģ��ʵ�֣������������������ʵ�ֵĶ���ʽ
    template <class T>
    static void polyMenu(){
        int hig = 0, value = 0, index = 0, preCmd = 0;
        //�����˵�ǰ��Ӧ���ȶԶ���ʽ��ʼ��
        cout << "��������ʽ" << endl << "��������ߴ���Ĵ�����";
        cin >> hig;
        //����TΪ����ʵ�ֻ�������ʵ��
        T pl(hig);
        for(int ind = hig; ind >= 0; ind--){
            cout << "������" << ind << "�����ϵ����";
            cin >> value;
            pl.alter(ind, value);
        }
        string menuChoices[] = {"�޸�ĳ���ϵ��", "�������ʽ", "����ʽ����"};
        //���������˵�
        do{
            preCmd = UiCollection::choices("false", 3, menuChoices, false);
            switch(preCmd){
                case 1:
                    cout << "������Ҫ�޸ĵ���Ĵ�����";
                    cin >> index;
                    cout << "�������޸ĺ��ϵ��ֵ��";
                    cin >> value;
                    UiCollection::printLine();
                    try{
                        pl.alter(index, value);
                        cout << "�޸ĳɹ���" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    UiCollection::printLine();
                    try {
                        pl.printPoly();
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    try {
                        calculate<T>(pl);
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    break;

                default:
                    break;
            }
        }while(preCmd);
    }

    //����ʽ����˵�
    template <class T>
    static void calculate(T thisPoly){
        int index, value = 0, hig = 0;
        //�����ڶ�������ʽ
        cout << "�����ڶ�������ʽ" << endl << "��������ߴ���Ĵ�����";
        cin >> hig;
        T another(hig);
        for(int ind = hig; ind >= 0; ind--){
            cout << "������" << ind << "�����ϵ����";
            cin >> value;
            another.alter(ind, value);
        }
        int preCmd;
        T sln(1);
        string menuChoices[] = {"�ӷ�����", "��������"};
        do{
            preCmd = UiCollection::choices("����ʽ����˵�", 2, menuChoices, false);
            switch(preCmd){
                case 1:
                    sln = thisPoly + another;
                    UiCollection::printLine();
                    cout << "������Ϊ��" << endl;
                    sln.printPoly();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                /*���������������
                case 2:
                    sln = thisPoly - another;
                    UiCollection::printLine();
                    cout << "������Ϊ��" << endl;
                    sln.printPoly();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;
                    */

                default:
                    break;
            }
        }while (preCmd);
    }

    static int cmd;
};

//��̬��Ա�ĳ�ʼ��
int Menu4::cmd = 0;

#endif //DATASTRUCTURE_MENU4_H
