#include <stdio.h>
#include <stdlib.h>

typedef struct array
{
    double * data;
    size_t size;
    size_t alloc;
}t_array;

t_array * new_array ( size_t capacity )
{
    t_array * array = (t_array*) malloc( sizeof(t_array) );

    array->size=0;
    array->alloc=capacity;
    array->data=(double*) malloc( sizeof(double) * array->alloc );

    return array;
}

t_array * resize_array ( t_array * array, size_t capacity )
{
    double *tmp =(double*)realloc(array->data,capacity * sizeof(double));
    if ( tmp != NULL )
    {
        array->data=tmp;  
        array->alloc=capacity;
        array->size=( array->size > capacity ) ? capacity : array->size;
    }
    return array;
}

t_array * push_back_array ( double item,t_array * array )
{
    if ( array->size == array->alloc )
    {
        array = resize_array(array, array->alloc * 2);
    }
    array->data[array->size++]=item;
    return array;
}

t_array * pop_back_array ( t_array * array )
{
    if (array->size == 0)
    {
        return array;
    }
    array->size--;
    if (array->size <= array->alloc / 4)
    {
        array = resize_array(array,array->alloc/2);
    }
    return array;
}

t_array * sort_array ( t_array * array )
{
    return array;
}

t_array * delete_array ( t_array * array )
{
    free(array->data);
    free(array);
    return NULL;
}

void print_array ( t_array * array )
{
    for (size_t i = 0; i < array->size; ++i)
    {
        printf("%f ", array->data[i]);
    }
    printf("\n");
}

//void print_reverse ( t_array * array )
//{
//    
//}

int main ( void )
{
    t_array * array = new_array(1);
    print_array( push_back_array(9.4,push_back_array(3.2,push_back_array(6.0,array))));
    free(array);
    return 0;
}