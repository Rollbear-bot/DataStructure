#if 1

#include "../HeaderFiles/TestSystem.h"
#include "../HeaderFiles/Others/HashTable.h"
#include "../HeaderFiles/Others/FromTextbook/Graphmtx.h"
#include "../HeaderFiles/Others/Sort.h"
#include "../HeaderFiles/Others/Heap.h"
#include "../HeaderFiles/Exp8/BinTreeByLink.h"

int main(){
    try {
        //������
        const string generalizeTable = "A(B(D,E(G,)),C(,F))";
        BinTreeByLink<char> bt(generalizeTable, '#');

        //����ʽ����
        //BinTreeByLink<char> bt;

        //bt.removeByIndex(2);
        cout << bt.height() << endl;
        List<char> resultA, resultB;


        BinTreeByLink<char> bt3("#", '#');
        bt3 = bt;


        resultB = bt3.layerTraversalWithoutRecursion();
        resultB.printList(); //��ֵ���ز�����

        return 0;
    }
    catch (Ex ex){
        ex.printInfo();
    }
    catch (NoFound nf){
        nf.print();
    }
    catch (IndexOutException of){
        of.print();
    }
    catch(OverFlowException ofe){
        ofe.print();
    }
    catch (NullPointer np){
        np.print();
    }
    return 0;
}

#endif