struct control_block
{
    long strongrf_count;
    long weakrf_count;

    control_block() : strongrf_count(0), weakrf_count(0) {};
    control_block(long strong, long weak) : strongrf_count(strong), weakrf_count(weak) {};
    ~control_block() = default;
};