//
// Created by 13592 on 2019/11/11.
// ʵ���壺ջ����ջ

#ifndef DATASTRUCTURE_MENU5_H
#define DATASTRUCTURE_MENU5_H

#include "../UiCollection.h"
#include "LinkedStack.h"
#include "Stack.h"

//ʵ���壺ջ����ջ
class Menu5{
public:
    Menu5(){}

public:
    static void menu(){
        string menuChoices[] = {"ջ����", "��ջ����"};
        do{
            cmd = UiCollection::choices("ʵ���壺ջ����ջ", 2, menuChoices, false);
            switch (cmd){
                case 1:
                    stackMenu<Stack<int>>();
                    break;

                case 2:
                    stackMenu<LinkedStack<int>>();
                    break;

                default:
                    break;
            }
        }while (cmd);
    }

private:
    //ջ���Բ˵���ʹ�ú���ģ��ʵ��
    template <class Type>
    static void stackMenu(){
        int preCmd, len, index, value;
        string menuChoices[] = {"��ջ", "��ջ", "���ջ", "ջ�ÿ�", "���ջ��Ԫ�ظ���", "���ջ��", "�п�", "����"};
        cout << "����ջ" << endl << "������ջ�";
        cin >> len;
        Type st(len);
        do{
            preCmd = UiCollection::choices("false", 8, menuChoices, false);
            switch(preCmd){
                case 1:
                    cout << "��������ջ��Ԫ�ص�ֵ��";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        st.push(value);
                        cout << "��ջ�ɹ���" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    UiCollection::printLine();
                    try {
                        cout << "��ջ��Ԫ���ǣ�" << st.pop() << endl;
                        cout << "��ջ�ɹ���" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    cout << "ջ�е�Ԫ��Ϊ��" << endl;
                    try {
                        st.printStack();
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    UiCollection::printLine();
                    st.clear();
                    cout << "�ÿ���ɣ�" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    UiCollection::printLine();
                    cout << "ջ�е�Ԫ�ظ���Ϊ��" << st.getEleNum() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    UiCollection::printLine();
                    cout << "ջ��Ϊ��" << st.getMaxLen() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 7:
                    UiCollection::printLine();
                    if(st.isEmpty()) cout << "ջ�գ���" << endl;
                    else cout << "ջ�գ���" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 8:
                    UiCollection::printLine();
                    if(st.isFull()) cout << "ջ������" << endl;
                    else cout << "ջ������" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                default:
                    break;

            } //end switch
        }while (preCmd);
    }

    static int cmd;
};

//��̬��Ա��ʼ��
int Menu5::cmd = 0;

#endif //DATASTRUCTURE_MENU5_H
