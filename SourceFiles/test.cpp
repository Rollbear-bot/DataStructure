#if 0

#include "../HeaderFiles/TestSystem.h"
#include "../HeaderFiles/Exp10/FormTextBook/BST.h"
#include "../HeaderFiles/Others/HashTable.h"
#include "../HeaderFiles/Exp11/FromTextbook/Graphmtx.h"
#include "../HeaderFiles/Others/Sort.h"

int main(){
    try {
        //²âÊÔÇø
        int arr[] = {1, 2, 3, 5, 4};
        LinearTable<int> lt(5, 5, arr);
        Sort<int>::quickSort(lt);
        lt.printTable();

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