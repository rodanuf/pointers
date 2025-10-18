template <typename T>
struct control_block
{
    int strongrf_count;
    int weakrf_count;

    explicit control_block();
    ~control_block() = default;

    void add_strongrf();
    void add_weakrf();
    void subtract_strongrf();
    void subtract_weakrf();
}