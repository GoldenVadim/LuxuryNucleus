namespace Miscellaneous
{
    namespace Str_Int
    {
        extern unsigned long long __sizeof(const char *const &);
        extern const char* to_string(int, const char &base, char additional_offset);
        extern int bcd_to_bin(int bcd);
        extern bool __equal(const char *const &, const char *const &, const unsigned long long &);

        template<typename unit>
        bool same(const unit *const &first, const unit *const &second, const unsigned long long &size)
        {
            return __equal(first, second, size * sizeof(unit));
        }

        template<typename unit>
        unsigned long long length_of(const unit *const &string)
        {
            return __sizeof(string) / sizeof(unit);
        }
    }
}