namespace Providers
{
    namespace Graphics
    {
        struct Display
        {
            const char *const name;
            const unsigned short width, height, update_freq;
            const bool type_colour, builtin;
        };

        struct Framebuffer
        {
            const char *const name;
            const bool type_text, type_colour;
            const unsigned short max_width, max_height;
            bool *const inited;

            void (*const &cursor_set_func)(const unsigned short &X, const unsigned short &Y);
            void (*const &write_func)(const char &, const unsigned short &X, const unsigned short &Y);
            char (*const &get_func)(const unsigned short &X, const unsigned short &Y);
        };

        struct GPU
        {
            const char *const name;
            const bool sw_accel;
            bool *const inited;

            const Display **const &displays;
            unsigned displays_len;
            unsigned primary_display;

            const Framebuffer *const *const &fbs;
            unsigned fbs_len;

            void (*const &init_func)();
        };
    }
}