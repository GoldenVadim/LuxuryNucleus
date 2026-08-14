namespace Memory
{
    extern void* __malloc(const unsigned long long &);
    extern void __copy(char *const &, const char *const &, const unsigned long long &);

    template<typename unit>
    unit* allocate(const unsigned long long &size)
    {
        return static_cast<unit*>(__malloc(size * sizeof(unit)));
    }

    template<typename unit>
    void copy_to(unit *const &destination, const unit *const &source, const unsigned long long &size)
    {
        return __copy(destination, source, size * sizeof(unit));
    }

    template<typename unit>
    void fill_at(unit *const &destination, const unit &with, const unsigned long long &size)
    {
        for (unsigned long long _ = 0; _ != size; ++_)
            destination[_] = with;
    }

    template<typename unit>
    void clean(unit *const &buffer, const unsigned long long &size)
    {
        return fill_at<unit>(buffer, 0, size * sizeof(unit));
    }

    template<typename unit>
    void remove(unit *&buffer, const unsigned long long &size)
    {
        clean<unit>(buffer,size);
        clean<unsigned long long>(const_cast<unsigned long long*>(&size), sizeof(unsigned long long));
    }
}