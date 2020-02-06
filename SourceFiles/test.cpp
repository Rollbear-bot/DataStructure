#if 1

#include "../HeaderFiles/TestSystem.h"
#include "../HeaderFiles/Others/HashTable.h"
#include "../HeaderFiles/Others/FromTextbook/Graphmtx.h"
#include "../HeaderFiles/Others/Sort.h"
#include "../HeaderFiles/Others/Heap.h"
#include "../HeaderFiles/Exp8/BinTreeByLink.h"

int main(){
    try {
        //测试区
        const string generalizeTable = "A(B(D,E(G,)),C(,F))";
        BinTreeByLink<char> bt(generalizeTable, '#');

        //交互式建立
        //BinTreeByLink<char> bt;

        //bt.removeByIndex(2);
        cout << bt.height() << endl;
        List<char> resultA, resultB;


        BinTreeByLink<char> bt3("#", '#');
        bt3 = bt;


        resultB = bt3.layerTraversalWithoutRecursion();
        resultB.printList(); //赋值重载不正常

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