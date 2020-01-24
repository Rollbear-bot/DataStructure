#if 1

#include "../HeaderFiles/TestSystem.h"
#include "../HeaderFiles/Exp10/FormTextBook/BST.h"
#include "../HeaderFiles/Others/HashTable.h"
#include "../HeaderFiles/Exp11/FromTextbook/Graphmtx.h"
#include "../HeaderFiles/Others/Sort.h"
#include "../HeaderFiles/Others/Heap.h"

int main(){
    try {
        //²âÊÔÇø
        int arr[] = {4, 2, 6, 1, 9};
        Heap<int> hp(arr, 5);
        hp.printLayerOrder();

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