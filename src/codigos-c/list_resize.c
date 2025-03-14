static int
list_resize(PyListObject *self, Py_ssize_t newsize)
{
    size_t new_allocated, target_bytes;
    Py_ssize_t allocated = self->allocated;

    /* Bypass realloc() when a previous overallocation is large enough
       to accommodate the newsize.  If the newsize falls lower than half
       the allocated size, then proceed with the realloc() to shrink the list.
    */
    if (allocated >= newsize && newsize >= (allocated >> 1)) {
        assert(self->ob_item != NULL || newsize == 0);
        Py_SET_SIZE(self, newsize);
        return 0;
    }

    /* This over-allocates proportional to the list size, making room
     * for additional growth.  The over-allocation is mild, but is
     * enough to give linear-time amortized behavior over a long
     * sequence of appends() in the presence of a poorly-performing
     * system realloc().
     * Add padding to make the allocated size multiple of 4.
     * The growth pattern is:  0, 4, 8, 16, 24, 32, 40, 52, 64, 76, ...
     * Note: new_allocated won't overflow because the largest possible value
     *       is PY_SSIZE_T_MAX * (9 / 8) + 6 which always fits in a size_t.
     */
    new_allocated = ((size_t)newsize + (newsize >> 3) + 6) & ~(size_t)3;
    /* Do not overallocate if the new size is closer to overallocated size
     * than to the old size.
     */
    if (newsize - Py_SIZE(self) > (Py_ssize_t)(new_allocated - newsize))
        new_allocated = ((size_t)newsize + 3) & ~(size_t)3;

    if (newsize == 0)
        new_allocated = 0;

    ensure_shared_on_resize(self);

#ifdef Py_GIL_DISABLED
    _PyListArray *array = list_allocate_array(new_allocated);
    if (array == NULL) {
        PyErr_NoMemory();
        return -1;
    }
    PyObject **old_items = self->ob_item;
    if (self->ob_item) {
        if (new_allocated < (size_t)allocated) {
            target_bytes = new_allocated * sizeof(PyObject*);
        }
        else {
            target_bytes = allocated * sizeof(PyObject*);
        }
        memcpy(array->ob_item, self->ob_item, target_bytes);
    }
    if (new_allocated > (size_t)allocated) {
        memset(array->ob_item + allocated, 0, sizeof(PyObject *) * (new_allocated - allocated));
    }
     _Py_atomic_store_ptr_release(&self->ob_item, &array->ob_item);
    self->allocated = new_allocated;
    Py_SET_SIZE(self, newsize);
    if (old_items != NULL) {
        free_list_items(old_items, _PyObject_GC_IS_SHARED(self));
    }
#else
    PyObject **items;
    if (new_allocated <= (size_t)PY_SSIZE_T_MAX / sizeof(PyObject *)) {
        target_bytes = new_allocated * sizeof(PyObject *);
        items = (PyObject **)PyMem_Realloc(self->ob_item, target_bytes);
    }
    else {
        // integer overflow
        items = NULL;
    }
    if (items == NULL) {
        PyErr_NoMemory();
        return -1;
    }
    self->ob_item = items;
    Py_SET_SIZE(self, newsize);
    self->allocated = new_allocated;
#endif
    return 0;
}

