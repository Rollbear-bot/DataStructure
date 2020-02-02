#if 1

#include "../HeaderFiles/TestSystem.h"
#include "../HeaderFiles/Others/HashTable.h"
#include "../HeaderFiles/Exp11/FromTextbook/Graphmtx.h"
#include "../HeaderFiles/Others/Sort.h"
#include "../HeaderFiles/Others/Heap.h"
#include "../HeaderFiles/Exp8/BinTreeByLink.h"

int main(){
    try {
        //测试区
        //string generalizeTable = "A(B(D,E(G,)),C(,F))";
        //BinTreeByLink<char> bt = BinTreeByLink<char>(generalizeTable, '#');

        //交互式建立
        BinTreeByLink<char> bt;

        List<char> result;
        result = bt.preOrderTraversal();
        result.printList();

        return 0;
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