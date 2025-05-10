int simple_test(void) {
    int result = -1;

    int *var1 = (int)malloc(sizeof(int));

    if (var1 == NULL)
        goto error;

    int *var2 = (int)malloc(sizeof(int));
    if (var2 == NULL)
        goto free_var1;

    int *var3 = (int)malloc(sizeof(int));
    if (var3 == NULL)
        goto free_var2;
    //
    // code here
    //
    free(var3);
free_var2:
    free(var2);
free_var1:
    free(var1);
error:
    return (result);
}
