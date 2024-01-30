#ifndef LOCAL_DARRAY_H_INCLUDE_GUARD
#define LOCAL_DARRAY_H_INCLUDE_GUARD
#define define_list(type) \
typedef struct list_ ## type{ type *data; size_t size; size_t capacity; } list_ ## type;\
void list_## type ## _init(list_ ## type *instance);\
void list_ ## type ## _add(list_ ## type *instance, type element); \
void list_ ## type ## _remove(list_ ## type *instance, size_t index);\
void list_ ## type ## _free(list_ ## type *instance);\
void list_## type ## _init(list_ ## type *instance) {\
    instance->data = NULL;\
    instance->capacity = 1;\
    instance->size = 0;\
    instance->data = (type*)malloc(sizeof(type));\
    if(instance->data == NULL) { perror("Error, list memory allocation failed\n"); }\
    else { printf("memory allocation successed\n"); }\
}; \
void list_ ## type ## _add(list_ ## type  *instance, type element){\
    if(instance->size == instance->capacity)\
    {\
        instance->capacity *= 2;\
        instance->data = (int*)realloc(instance->data, sizeof(type) * instance->capacity);\
        printf("New capacity: %d\n", instance->capacity);\
        if(instance->data == NULL)\
        {\
            perror("Error, memory reallocation failed\n");\
            return;\
        }\
    }\
    instance->data[instance->size] = element;\
    instance->size++;\
};\
void list_ ## type ## _remove(list_ ## type *instance, size_t index)\
{\
    if(index > instance->size)\
    {\
        perror("Error, atempt to remove elements outside the bound\n");\
        return;\
    }\
    for(size_t temp = index; temp < instance->size - 1; temp++)\
    {\
        instance->data[temp] = instance->data[temp + 1];\
    }\
    instance->size--;\
};\
void list_ ## type ## _free(list_ ## type *instance){\
    if(instance->data == NULL)\
    {\
        perror("Error, atempt to free an empty list\n");\
        return;\
    }\
    free(instance->data);\
    instance->capacity = 0;\
    instance->size = 0;\
};
#endif