#include <stdbool.h>
#include <stdlib.h>

size_t findNext0sPosition(size_t current0sPosition, const size_t lastPosible0sPosition, const int* searchArray)
{
  //If there is already a 0, move to the next position
  //If current0sPosition and lastPosible0sPosition are the same the array is already ordered
  while ((searchArray[current0sPosition] == 0) && (++current0sPosition<lastPosible0sPosition)) {
  }
  return current0sPosition;
}

size_t findNext2sPosition(size_t current2sPosition, const size_t lastPosible2sPosition, const int* searchArray)
{
  //If there is already a 2, move to the previous positions
  //If current2sPosition and lastPosible2sPosition are the same the array is already ordered
  while ((searchArray[current2sPosition] == 2) && (--current2sPosition>lastPosible2sPosition)) {
  }
  return current2sPosition;
}

bool isArrayOrdered(const size_t next0sPosition, const size_t next2sPosition)
{
  //If both indexes are at the same position the array is ordered
  return (next0sPosition>=next2sPosition);
}

void swap(int* affectedArray, size_t fromPosition, size_t toPosition)
{
  //swap two values in the array. TODO: This can be modified since we know
  //what value are we swaping when we call the function
  int aux = affectedArray[fromPosition];
  affectedArray[fromPosition] = affectedArray[toPosition];
  affectedArray[toPosition] = aux;
}

int orderArray(int* unorderedArray, size_t arraySize)
{
  //Do not order an empty array
  if(unorderedArray==NULL)
    return 1;

  //An array of size 1 or less is already ordered
  if(arraySize<=1)
  {
    //Cannot order an array with numbers greater than 2
    if(arraySize==1)
      return (unorderedArray[0]>2);

    return 0;
  }

  //0s at the starting, 1s, and 2s at the end
  //Find the tempting positions for 0s and 2s at the start and the end
  size_t next0sPosition = 0;
  size_t next2sPosition = arraySize-1;
  //starting with the 0s first tempting position
  next0sPosition = findNext0sPosition(next0sPosition, next2sPosition, unorderedArray);
  //search for the first 2s tempting position
  next2sPosition = findNext2sPosition(next2sPosition, next0sPosition, unorderedArray);

  //After this search we may conclude that the array is already ordered
  if(isArrayOrdered(next0sPosition, next2sPosition))
    return 0;

  //The array is not ordered, iterate through the remaining positions to order the array
  size_t currentPosition = next0sPosition;
  while(currentPosition<=next2sPosition)
  {
    switch (unorderedArray[currentPosition]) {
      case 0:
        //move the 0 to its position (next0sPosition) if it is not already there
        if(next0sPosition!=currentPosition)
          swap(unorderedArray, next0sPosition, currentPosition);
        //go to the next available 0s position. It is the next one because it was already checked
        //or it is going to be checked
        ++next0sPosition;
        //after moving a 0, there is a 1 in the current position. Between next0sPosition and currentPosition there are only 1s
      case 1:
        //When it is a 1, the current pointer is able to move to the next position
        ++currentPosition;
      break;
      case 2:
        //move the 2 to its position (next2sPosition) if it is not already there
        if(next2sPosition!=currentPosition)
          swap(unorderedArray, next2sPosition, currentPosition);
        //go to the next available 2s position
        next2sPosition = findNext2sPosition(--next2sPosition, currentPosition, unorderedArray);
      break;
      default:
        //The value is neither a 0, 1 or 2. something is wrong
        //worst case scenario we already went through O(n) to discover it.
        return 1;
    }
  }

  //At this point the array is ordered
  return 0;
}
