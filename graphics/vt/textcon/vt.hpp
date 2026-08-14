namespace Graphics
{
    namespace VT
    {
        extern void (*move_cursor)(const unsigned short &X, const unsigned short &Y);
        extern void (*put_entry)(const char &, const unsigned short &X, const unsigned short &Y);
        extern char (*get_entry)(const unsigned short &X, const unsigned short &Y);
        extern const unsigned short *width, *height;
        extern bool text_mode, native_text;
    }
}