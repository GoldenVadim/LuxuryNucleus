namespace Providers
{
    namespace Graphics
    {
        struct GPU_provider_info
        {
            const char *const name;
            bool *const inited;
            void (*const write_func)(const char &);
            void (*const init_func)();
        };
    }
}