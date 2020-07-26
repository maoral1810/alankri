#ifndef __SORTS_H__
#define __SORTS_H__

#include "vector.h" /* Vector Api */

/*
    BubbleSort - bubble each element to his place in vector.
    repeatedly swapping the adjacent elements if they are in wrong order.

    intput:
        vector- pointer to vector
    
    output:
       sorted vector from low to high

    stability: stable
    time complexsity: O(n^2)
    space complexsity : O(1)
        
    error:
        return NULL on failure     
*/
ADTErr BubbleSort(Vector *_vector);
/*
    ShakeSort 
    like bubble in two directions
    
    intput:
        vector- pointer to vector
    
    output:
        sorted vector from low to high

    stability: stable
    time complexsity: O(n^2)
    space complexsity : O(1)
        
    error:
        return NULL on failure     
*/
ADTErr ShakeSort(Vector *_vector);
/*
    QuickSort
    Divide and Conquer algorithm. 
    picks an element as pivot and partitions the given array around the picked pivot. 
   
    intput:
        vector- pointer to vector
    
    output:
        sorted vector from low to high

    stability: not stable
    time complexsity: O(log(n))
    space complexsity : O(1)
        
    error:
        return NULL on failure     
*/
ADTErr QuickSort(Vector *_vector);
/*
    InsertionSort
    Uses: Insertion sort is used when number of elements is small. 
    It can also be useful when input array is almost sorted, 
    only few elements are misplaced in complete big array.
    
    intput:
        vector- pointer to vector
        gup - jump elements compere 
    output:
        sorted vector from low to high

    stability: stable
    time complexsity: O(log(n))
    space complexsity : O(1)
        
    error:
        return NULL on failure     
*/
ADTErr InsertionSort(Vector *_vector, size_t _gup);
/*
    ShellSort
    The idea of shellSort is to allow exchange of far items. 
    In shellSort, we make the vector gup-sorted for a large value of gup. 
    We keep reducing the value of gup. 
    An vector is said to be gup-sorted if all sublists of every gup’th element is sorted.

    intput:
        vector- pointer to vector
    
    output:
        sorted vector from low to high

    stability: not stable
    time complexsity: O(log(n))
    space complexsity : O(1)
        
    error:
        return NULL on failure     
*/
ADTErr ShellSort(Vector *_vector);
/*
    SelectionSort
    sorts an array by repeatedly finding the minimum element 
    (considering ascending order) from unsorted part and putting it at the beginning. 
    The algorithm maintains two subarrays in a given array.

    1) The subarray which is already sorted.
    2) Remaining subarray which is unsorted.

    intput:
        vector- pointer to vector
    
    output:
        sorted vector from low to high

    stability: not stable
    time complexsity: O(n^2)
    space complexsity : O(1)
        
    error:
        return NULL on failure     
*/

ADTErr SelectionSort(Vector *_vector);
/*
    MargeSort
    Divide and Conquer algorithm. It divides input array in two halves, 
    calls itself for the two halves and then merges the two sorted halves. 
 
    intput:
        vector- pointer to vector
    
    output:
        sorted vector from low to high

    stability: stable
    time complexsity: O(n)
    space complexsity : O(n)
        
    error:
        return NULL on failure     
*/
ADTErr MargeSort(Vector *_vector);
/*
    CountingSort
    counting the number of objects having distinct key values (kind of hashing). 
    Then doing arithmetic to calculate the position of each object in the output sequence.

    intput:
        vector- pointer to vector
    
    output:
        sorted vector from low to high

    stability: stable
    time complexsity: O(n)
    space complexsity : O(n)
        
    error:
        return NULL on failure     
*/
ADTErr CountingSort(Vector *_vector, int _max, int _min);
ADTErr ItarativeQuickSort(Vector *_vector);
 
#endif  /* __SORTS_H__ */