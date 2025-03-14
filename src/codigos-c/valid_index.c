static inline int
valid_index(Py_ssize_t i, Py_ssize_t limit)
{
    /* The cast to size_t lets us use just a single comparison
       to check whether i is in the range: 0 <= i < limit.

       See:  Section 14.2 "Bounds Checking" in the Agner Fog
       optimization manual found at:
       https://www.agner.org/optimize/optimizing_cpp.pdf
    */
    return (size_t) i < (size_t) limit;
}
