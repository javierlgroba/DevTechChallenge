#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

int orderArray(int* unorderedArray, size_t arraySize);

void printArray(const int* arrayToPrint, const size_t arraySize)
{
  if(arrayToPrint==NULL || arraySize<1)
  {
    printf("Imposible to print an empty array\n");
    return;
  }
  printf("array[%lu]:  [", arraySize);
  for(size_t i = 0; i<arraySize-1; ++i)
  {
    printf("%d, ", arrayToPrint[i]);
  }
    printf("%d", arrayToPrint[arraySize-1]);
    printf("]\n");
}

bool checkIsOrdered(int* zeros, int* ones, int* twos, int* searchArray, size_t arraySize)
{
  if(searchArray==NULL || arraySize<=1)
  {
    //if the array is empty or only 1 number, it is already ordered
    return true;
  }
  //The array should start at 0, if there is any
  int currentValue = 0;
  bool isOrdered = true;
  //Count each number repetitions and check if it is ordered.
  for (size_t i = 0; i < arraySize; i++) {
    if(currentValue>searchArray[i])
    {
      isOrdered = false;
    }
    else if (currentValue<searchArray[i])
    {
      currentValue = searchArray[i];
    }
    switch (searchArray[i]) {
      case 0:
        ++(*zeros);
      break;
      case 1:
        ++(*ones);
      break;
      case 2:
        ++(*twos);
      break;
    }
  }
  return isOrdered;
}

void testArray(int* unorderedArray, size_t arraySize)
{
  //retrieve the number of 0s, 1s and 2s in the array
  //and print it
  int zeros = 0, ones = 0, twos = 0;
  checkIsOrdered(&zeros, &ones, &twos, unorderedArray, arraySize);
  printArray(unorderedArray, arraySize);
  //order the array
  if(orderArray(unorderedArray, arraySize)!=0)
  {
      printf("Error ordering array\n");
      return;
  }
  //If everything went well check that the array is ordered and that the number
  //of 0s, 1s and 2s is the same.
  int orderedZeros = 0, orderedOnes = 0, orderedTwos = 0;
  assert(checkIsOrdered(&orderedZeros, &orderedOnes, &orderedTwos, unorderedArray, arraySize));
  assert(zeros==orderedZeros);
  assert(ones==orderedOnes);
  assert(twos==orderedTwos);
  printArray(unorderedArray, arraySize);
}

size_t createUnorderedRandomArray(int** pointerToNewArray, size_t arraySize)
{
  //size
  if(arraySize==0)
    arraySize = rand() % 255;
  int* localpointerToNewArray = (int *) realloc(*pointerToNewArray, sizeof(int)*arraySize);

  //populate random array
  for(int i = 0; i<arraySize; ++i)
  {
    if(rand()>(0.999 * RAND_MAX))
      localpointerToNewArray[i] = rand();
    else
      localpointerToNewArray[i] = rand() % 3;
  }

  //return array and array size
  *pointerToNewArray = localpointerToNewArray;
  return arraySize;
}

int main() {
  //Array in the example
  int example[30] = {2, 2, 1, 0, 1, 0, 1, 1, 0, 2, 2, 1, 1, 1, 2, 0, 0, 1, 1, 0, 1, 0, 1, 2, 0, 0, 0, 1, 1, 2};
  size_t arraySize = sizeof(example)/sizeof(int);
  testArray(example, arraySize);

  //wrong one sized array
  int* wrongArray;
  wrongArray = (int [1]){3};
  testArray(wrongArray, 1);

  wrongArray = (int [1]){-1};
  testArray(wrongArray, 1);

  //empty array
  int* emptyArray;
  testArray(emptyArray, 0);

  //initialize the random seed
  srand((unsigned int)time(NULL));

  //array of one element
  int* testingArray = NULL;
  for(int  i = 0; i<10; ++i)
  {
    testArray(testingArray, createUnorderedRandomArray(&testingArray, 1));
  }

  //array of 2 elements
  for(int  i = 0; i<100; ++i)
  {
    testArray(testingArray, createUnorderedRandomArray(&testingArray, 2));
  }

  //array of 3 elements
  for(int  i = 0; i<100; ++i)
  {
    testArray(testingArray, createUnorderedRandomArray(&testingArray, 3));
  }

  //random arrays
  for(int i = 0; i<255; ++i)
  {
      testArray(testingArray, createUnorderedRandomArray(&testingArray, 0));
  }

  free(testingArray);

  return 0;
}
