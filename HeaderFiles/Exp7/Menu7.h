//
// Created by 13592 on 2019/11/11.
// ��������

#ifndef DATASTRUCTURE_MENU7_H
#define DATASTRUCTURE_MENU7_H

#include "String.h"
#include "..//UiCollection.h"

class Menu7{
public:
    Menu7(){}

public:
    static void menu(){
        int index, value, len, index2, matchIndex;
        String<char> temp;
        char c;
        string menuChoice[] = {"�½���", "�鿴�����ѱ���Ĵ�", "���Ӵ�", "�޸Ĵ�", "ɾ����", "��������ƥ��"};
        do{
            cmd = UiCollection::choices("�����Բ˵�", 6, menuChoice,  false);
            switch (cmd){
                case 1:
                    cout << "�������½����ĳ��ȣ�";
                    cin >> len;
                    UiCollection::printLine();
                    temp = String<char>(len);
                    temp.rewrite(len);
                    lt.append(temp);
                    cout << "�´�����ӣ�" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    UiCollection::printLine();
                    cout << "�ѱ���Ĵ���" << endl;
                    try {
                        for(int index = 0; index < lt.length(); index++){
                            cout << index << ":";
                            lt.find(index)->data.printString();
                        }
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    cout << "��ѡ���һ����������һ���ѱ���Ĵ���������";
                    cin >> index;
                    cout << "�����븽�ӵ���һ��������Ĵ���������";
                    cin >> index2;
                    try {
                        //�����Ӳ������´���ӵ������ĩβ
                        temp = lt.find(index)->data.append(lt.find(index2)->data);
                        lt.append(temp);
                        cout << "�������´�����ӣ�" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    cout << "������Ҫ�޸ĵĴ���������";
                    cin >> index;
                    cout << "�������´��ĳ��ȣ�";
                    cin >> len;
                    UiCollection::printLine();
                    try {
                        lt.find(index)->data.rewrite(len);
                        cout << "�޸���ɣ�" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    cout << "������Ҫɾ���Ĵ���������";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        lt.removeByIndex(index);
                        cout << "ɾ���ɹ���" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    cout << "����Ŀ�괮��������";
                    cin >> index;
                    cout << "����ģʽ����������";
                    cin >> index2;
                    try {
                        matchIndex = lt.find(index)->data.match(lt.find(index2)->data);
                        if(matchIndex==-1)cout << "ƥ��ʧ�ܣ�" << endl;
                        else cout << "ƥ��ɹ���ƥ��λ��Ϊ��" << matchIndex << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                default:
                    break;
            }
        }while (cmd);
    }

protected:
    static int cmd;
    static List<String<char>> lt; //����ѱ���Ĵ�������
};

//��̬��Ա�ĳ�ʼ��
int Menu7::cmd = 1;
List<String<char>> Menu7::lt(0);

#endif //DATASTRUCTURE_MENU7_H
