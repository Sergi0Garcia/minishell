

#include "../../include/minishell.h"


/* Function that will insert element at the end of stack */
void ft_unshift(t_sb *stack, t_si info)
{
    t_st *new;

    new = (t_st *)malloc(sizeof(t_st));
    if (new == NULL)
        ft_error("Error \n");
    new->i = info;
    if (stack->tail == NULL)
    {
        new->next = NULL;
        new->prev = NULL;
        stack->tail = new;
        stack->head = new;
    }
    else
    {
        new->next = NULL;
        new->prev = stack->tail;
        stack->tail->next = new;
        stack->tail = new;
    }
    stack->size++;
    return;
}

/* Add a new node at the top into existing double link list */
void ft_push(t_sb *stack, t_si info)
{
    t_st *new;

    new = (t_st *)malloc(sizeof(t_st));
    if (new == NULL)
        ft_error("Error \n");
    new->i = info;
    new->next = stack->head;
    new->prev = NULL;
    if (stack->tail == NULL)
    {
        stack->tail = new;
        stack->head = new;
    }
    else
    {
        stack->head->prev = new;
        stack->head = new;
    }
    stack->size++;
    return;
}

/* pop top element of a stack into doubly linked list */
t_si ft_pop(t_sb *stack)
{
    t_si info;
    t_st *tmp;

    if (stack->head == NULL)
        ft_error("Error \n");
    info = stack->head->i;
    tmp = stack->head;
    if (stack->head->next == NULL)
    {
        stack->head = NULL;
        stack->tail = NULL;
    }
    else
    {
        stack->head = stack->head->next;
        stack->head->prev = NULL;
    }
    if (stack->head != NULL)
        stack->head->prev = NULL;
    stack->size--;
    free(tmp);
    return (info);
}

/* shift removes the last item into the stack  */
t_si ft_shift(t_sb *stack)
{
    t_si si;
    t_st *tmp;

    if (stack->tail == NULL)
        ft_error("Error \n");
    si = stack->tail->i;
    tmp = stack->tail;
    if (stack->tail->prev != NULL)
        stack->tail = stack->tail->prev;
    if (stack->tail == NULL)
        stack->head = NULL;
    else if (stack->tail->next != NULL)
        stack->tail->next = NULL;
    stack->size--;
    if (stack->size == 1)
        stack->head = stack->tail;
    if (stack->size == 0)
    {
        stack->head = NULL;
        stack->tail = NULL;
    }
    free(tmp);
    return (si);
}
